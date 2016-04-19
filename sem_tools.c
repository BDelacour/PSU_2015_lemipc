/*
** sem_tools.c for C in /home/delaco_c/rendu/PSU_2015_lemipc
** 
** Made by Delacour Benjamin
** Login   <delaco_c@epitech.net>
** 
** Started on  Tue Mar 22 12:38:52 2016 Delacour Benjamin
** Last update Fri Mar 25 17:21:21 2016 Delacour Benjamin
*/

#include "lemipc.h"

int	sem_lock(t_ipcs *ipcs)
{
  ipcs->sops.sem_op = -1;
  return (semop(ipcs->sem_id, &ipcs->sops, 1));
}

int	sem_unlock(t_ipcs *ipcs)
{
  ipcs->sops.sem_op = 1;
  return (semop(ipcs->sem_id, &ipcs->sops, 1));
}
