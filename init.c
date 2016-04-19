/*
** init.c for C in /home/delaco_c/rendu/PSU_2015_lemipc
** 
** Made by Delacour Benjamin
** Login   <delaco_c@epitech.net>
** 
** Started on  Tue Mar 22 18:20:17 2016 Delacour Benjamin
** Last update Fri Mar 25 17:53:39 2016 Delacour Benjamin
*/

#include "lemipc.h"

static void	catch_sigint(int sign)
{
  if (sign == SIGINT)
    g_exit = 1;
}

static void	init_map(struct s_case *map)
{
  int		i;

  i = 0;
  while (i < WIDTH * HEIGHT)
    {
      map[i].x = i % WIDTH;
      map[i].y = i / WIDTH;
      map[i].nteam = 0;
      i++;
    }
}

static void	init_player(const key_t key, t_ipcs *ipcs, const int team)
{
  void		*addr;

  if ((addr = shmat(ipcs->shm_id, NULL, SHM_R | SHM_W)) == (void *)-1)
    return ;
  if ((ipcs->sem_id = semget(key, 1, SHM_R | SHM_W)) == -1)
    return ;
  if ((ipcs->msg_id = msgget(key, SHM_R | SHM_W)) == -1)
    return ;
  ipcs->sops.sem_num = 0;
  ipcs->sops.sem_op = -1;
  ipcs->sops.sem_flg = 0;
  play(addr, team, ipcs);
}

static void	*first_init(const key_t key, t_ipcs *ipcs)
{
  void		*addr;

  if (signal(SIGINT, catch_sigint) == SIG_ERR)
    return (NULL);
  if ((ipcs->shm_id = shmget(key, WIDTH * HEIGHT * sizeof(struct s_case),
			     IPC_CREAT | SHM_R | SHM_W)) == -1)
    return (NULL);
  if ((ipcs->sem_id = semget(key, 1, IPC_CREAT | SHM_R | SHM_W)) == -1 ||
      semctl(ipcs->sem_id, 0, SETVAL, 1) == -1)
    return (NULL);
  ipcs->sops.sem_num = 0;
  ipcs->sops.sem_op = -1;
  ipcs->sops.sem_flg = 0;
  if ((ipcs->msg_id = msgget(key, IPC_CREAT | SHM_R | SHM_W)) == -1)
    return (NULL);
  if ((addr = shmat(ipcs->shm_id, NULL, SHM_R | SHM_W)) == (void *)-1)
    return (NULL);
  init_map(addr);
  return (addr);
}

void		init_lemipc(const char *path, const int team)
{
  key_t		key;
  t_ipcs	ipcs;
  void		*addr;
  pid_t		pid;

  if ((key = ftok(path, 0)) == -1)
    return ;
  if ((ipcs.shm_id = shmget(key, WIDTH * HEIGHT * sizeof(struct s_case),
			    SHM_R | SHM_W)) == -1)
    {
      if ((addr = first_init(key, &ipcs)) == NULL ||
	  (pid = fork()) == -1)
	return ;
      if (pid == 0)
	play(addr, team, &ipcs);
      else
	screen(addr, &ipcs);
    }
  else
    init_player(key, &ipcs, team);
}
