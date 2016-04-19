/*
** screen_map.c for  in /home/keewydandy/work/unix/PSU_2015_lemipc
**
** Made by Kevin Hillion
** Login   <keewydandy@epitech.net>
**
** Started on  Thu Mar 17 15:18:55 2016 Kevin Hillion
** Last update Fri Mar 25 17:23:01 2016 Delacour Benjamin
*/

#include "lemipc.h"

int		print_char(int i, int j, int k, struct s_case *map)
{
 static char	tab[] = "!\"#$%&'()*+,-./:;<=>?@\\[]^_`{|}~";

 if ((j == 0 || j == HEIGHT + 1) && (i == 0 || i == WIDTH + 1))
   printf("\033[36m%c\033[0m", '+');
 else if (j == 0 || j == HEIGHT + 1)
   printf("\033[34m%c\033[0m", '-');
 else if (i == 0 || i == WIDTH + 1)
   printf("\033[34m%c\033[0m", '|');
 else if (map[k].nteam != 0)
   {
     printf("\033[%dm%c\033[0m", (30 + map[k].nteam % 7),
	    tab[map[k].nteam % 32]);
     k += 1;
   }
 else
   {
     printf(" ");
     k += 1;
   }
 return (k);
}

void		print_map(struct s_case *map)
{
  int		i;
  int		j;
  int		k;

  j = 0;
  k = 0;
  system("clear");
  while (j != HEIGHT + 2)
    {
      i = 0;
      while (i != WIDTH + 2)
  	{
	  k = print_char(i, j, k, map);
	  i += 1;
  	}
      printf("%c", '\n');
      j += 1;
    }
}

void	getWinner(struct s_case *map)
{
  int	i;

  i = 0;
  while (i < WIDTH * HEIGHT)
    {
      if (map[i].nteam != 0)
	{
	  printf("Team %d Win!\n", map[i].nteam);
	  break ;
	}
      i++;
    }
}

int		checkTeamNumber(struct s_case *map, t_ipcs *ipcs)
{
  int		i;
  int		j;
  static int	flag = 0;
  int		n;

  i = -1;
  n = 0;
  sem_lock(ipcs);
  while (++i < HEIGHT * WIDTH)
    {
      j = i - 1;
      while (map[i].nteam != 0 && j >= 0)
	{
	  if (map[j].nteam == map[i].nteam)
	    break ;
	  j--;
	}
      if ((j < 0 && i > 0) || (i == 0 && map[i].nteam != 0))
	n++;
    }
  if (n > 1)
    flag = 1;
  if (flag == 1 && n <= 1)
    return (-1);
  return (0);
}

void	screen(struct s_case *map, t_ipcs *ipcs)
{
  while (checkTeamNumber(map, ipcs) == 0 && g_exit == 0)
    {
      print_map(map);
      usleep(REFRESH);
      sem_unlock(ipcs);
    }
  if (g_exit == 0)
    {
      print_map(map);
      getWinner(map);
      sem_unlock(ipcs);
    }
  shmctl(ipcs->shm_id, IPC_RMID, NULL);
  semctl(ipcs->sem_id, 1, IPC_RMID);
  msgctl(ipcs->msg_id, IPC_RMID, NULL);
}
