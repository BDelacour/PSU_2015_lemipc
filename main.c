/*
** main.c for C in /home/delaco_c/rendu/PSU_2015_lemipc
** 
** Made by Delacour Benjamin
** Login   <delaco_c@epitech.net>
** 
** Started on  Mon Mar 14 17:51:15 2016 Delacour Benjamin
** Last update Tue Mar 22 18:25:25 2016 Delacour Benjamin
*/

#include "lemipc.h"

int			main(int ac, char **av)
{
  struct timeval	tv;
  int			team;

  if (ac != 3)
    {
      fprintf(stderr, "Wrong parameters!\n");
      return (-1);
    }
  gettimeofday(&tv, NULL);
  srand(tv.tv_usec);
  g_exit = 0;
  if ((team = atoi(av[2])) <= 0)
    return (-1);
  init_lemipc(av[1], atoi(av[2]));
  return (0);
}
