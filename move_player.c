/*
** move_player.c for C in /home/delaco_c/rendu/PSU_2015_lemipc
** 
** Made by Delacour Benjamin
** Login   <delaco_c@epitech.net>
** 
** Started on  Tue Mar 22 12:50:16 2016 Delacour Benjamin
** Last update Fri Mar 25 18:45:40 2016 Delacour Benjamin
*/

#include "lemipc.h"

static t_player	closestEnemy(struct s_case *map, t_player *plr)
{
  int		i;
  t_player	res;
  double	dist;
  double	ret;

  i = 0;
  res.x = -1;
  res.y = -1;
  dist = -1;
  while (i < HEIGHT * WIDTH)
    {
      if (map[i].nteam > 0 && map[i].nteam != plr->team)
	{
	  ret = sqrt(pow(map[i].x - plr->x, 2) + pow(map[i].y - plr->y, 2));
	  if (dist == -1 || ret < dist)
	    {
	      res.x = map[i].x;
	      res.y = map[i].y;
	      res.team = map[i].nteam;
	      dist = ret;
	    }
	}
      i++;
    }
  return (res);
}

static void	random_move(struct s_case *map, t_player *plr)
{
  int		dep;
  int		choice;

  do
    {
      dep = (random() % 2 == 1) ? 1 : -1;
      choice = random() % 2;
    } while (plr->x + dep * (choice == 1) < 0 ||
	     plr->x + dep * (choice == 1) >= WIDTH ||
	     plr->y + dep * (choice == 0) < 0 ||
	     plr->y + dep * (choice == 0) >= HEIGHT ||
	     map[(plr->y + dep * (choice == 0)) * WIDTH
		 + plr->x + dep * (choice == 1)].nteam != 0);
  map[(plr->y + dep * (choice == 0)) * WIDTH
      + plr->x + dep * (choice == 1)].nteam = plr->team;
  map[plr->y * WIDTH + plr->x].nteam = 0;
  plr->y += dep * (choice == 0);
  plr->x += dep * (choice == 1);
}

static int	receiveMessage(t_player *plr, t_ipcs *ipcs, t_player *enemy)
{
  t_msg		player;

  if (msgrcv(ipcs->msg_id, &player, sizeof(t_msg),
	     plr->team, IPC_NOWAIT) == -1)
    return (0);
  *enemy = player.enemy;
  if (enemy->x == -1)
    return (0);
  return (1);
}

static void	sendMessage(t_player *plr, t_ipcs *ipcs, t_player *enemy)
{
  t_msg		player;

  player.mtype = plr->team;
  player.enemy = *enemy;
  msgsnd(ipcs->msg_id, &player, sizeof(t_msg), player.mtype);
}

void		movePlayer(struct s_case *map, t_player *plr, t_ipcs *ipcs)
{
  t_player	enemy;

  if ((plr->x - 1 >= 0 && map[plr->y * WIDTH + plr->x - 1].nteam == 0) ||
      (plr->x + 1 < WIDTH && map[plr->y * WIDTH + plr->x + 1].nteam == 0) ||
      (plr->y - 1 >= 0 && map[(plr->y - 1) * WIDTH + plr->x].nteam == 0) ||
      (plr->y + 1 < HEIGHT && map[(plr->y + 1) * WIDTH + plr->x].nteam == 0))
    {
      if (!receiveMessage(plr, ipcs, &enemy) ||
	  map[enemy.y * WIDTH + enemy.x].nteam == 0)
	enemy = closestEnemy(map, plr);
      sendMessage(plr, ipcs, &enemy);
      if (enemy.x != -1 && enemy.y != -1)
	IA_move(map, plr, &enemy);
      else
	random_move(map, plr);
    }
}
