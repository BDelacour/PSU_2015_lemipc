/*
** player.c for C in /home/delaco_c/rendu/PSU_2015_lemipc
** 
** Made by Delacour Benjamin
** Login   <delaco_c@epitech.net>
** 
** Started on  Mon Mar 21 12:17:09 2016 Delacour Benjamin
** Last update Fri Mar 25 17:45:37 2016 Delacour Benjamin
*/

#include "lemipc.h"

static int	checkTab(int teams[8], const t_player *player)
{
  int		i;
  int		j;

  i = 0;
  while (i < 8)
    {
      j = i - 1;
      while (j >= 0)
	{
	  if (teams[j] == teams[i] && teams[i] != 0 &&
	      teams[i] != player->team)
	    return (1);
	  j--;
	}
      i++;
    }
  return (0);
}

static int	checkLose(const struct s_case *map, const t_player *player,
			  t_ipcs *ipcs)
{
  int		teams[8];
  int		i;

  i = 0;
  while (i < 8)
    teams[i++] = 0;
  if (sem_lock(ipcs) == -1)
    return (-1);
  if (player->x - 1 >= 0 && player->y - 1 >= 0)
    teams[0] = map[(player->y - 1) * WIDTH + (player->x - 1)].nteam;
  if (player->y - 1 >= 0)
    teams[1] = map[(player->y - 1) * WIDTH + player->x].nteam;
  if (player->x + 1 < WIDTH && player->y - 1 > 0)
    teams[2] = map[(player->y - 1) * WIDTH + (player->x + 1)].nteam;
  if (player->x - 1 >= 0)
    teams[3] = map[player->y * WIDTH + (player->x - 1)].nteam;
  if (player->x + 1 < WIDTH)
    teams[4] = map[player->y * WIDTH + (player->x + 1)].nteam;
  if (player->x - 1 >= 0 && player->y + 1 < HEIGHT)
    teams[5] = map[(player->y + 1) * WIDTH + (player->x - 1)].nteam;
  if (player->y + 1 < HEIGHT)
    teams[6] = map[(player->y + 1) * WIDTH + player->x].nteam;
  if (player->x + 1 < WIDTH && player->y + 1 < HEIGHT)
    teams[7] = map[(player->y + 1) * WIDTH + (player->x + 1)].nteam;
  return (checkTab(teams, player));
}

static int	placeInMap(struct s_case *map)
{
  int		i;

  i = 0;
  while (i < WIDTH * HEIGHT)
    {
      if (map[i].nteam == 0)
	return (1);
      i++;
    }
  return (0);
}

static int	random_place(t_player *player, struct s_case *map,
			     t_ipcs *ipcs)
{
  sem_lock(ipcs);
  if (!placeInMap(map))
    {
      sem_unlock(ipcs);
      return (1);
    }
  do
    {
      player->x = random() % WIDTH;
      player->y = random() % HEIGHT;
    } while (map[player->y * WIDTH + player->x].nteam != 0);
  map[player->y * WIDTH + player->x].nteam = player->team;
  sem_unlock(ipcs);
  return (0);
}

void		play(struct s_case *map, const int team,
		     t_ipcs *ipcs)
{
  int		ret;
  t_player	player;

  player.team = team;
  if (random_place(&player, map, ipcs) != 0)
    return ;
  while (!(ret = checkLose(map, &player, ipcs)))
    {
      movePlayer(map, &player, ipcs);
      sem_unlock(ipcs);
      usleep(REFRESH);
    }
  if (ret == 1)
    {
      map[player.y * WIDTH + player.x].nteam = 0;
      sem_unlock(ipcs);
    }
}
