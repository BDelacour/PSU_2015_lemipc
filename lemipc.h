/*
** lemipc.h for H in /home/delaco_c/rendu/PSU_2015_lemipc
**
** Made by Delacour Benjamin
** Login   <delaco_c@epitech.net>
**
** Started on  Sat Mar 19 15:11:10 2016 Delacour Benjamin
** Last update Sun Mar 27 18:24:56 2016 Delacour Benjamin
*/

#ifndef LEMIPC_H__
# define LEMIPC_H__
# define WIDTH 20
# define HEIGHT 20
# define REFRESH 100000
# define ABS(x) ((x < 0) ? -x : x)
# define FNEG(x) ((x < 0) ? (-1) : (1))
# include <sys/types.h>
# include <sys/ipc.h>
# include <sys/shm.h>
# include <sys/sem.h>
# include <sys/msg.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <signal.h>
# include <math.h>
# include <sys/time.h>

struct	s_case
{
  int	x;
  int	y;
  int	nteam;
};

typedef struct	s_ipcs
{
  int		sem_id;
  struct sembuf	sops;
  int		shm_id;
  int		msg_id;
}		t_ipcs;

int	g_exit;

typedef struct	s_player
{
  int		x;
  int		y;
  int		team;
}		t_player;

typedef struct	s_msg
{
  long		mtype;
  t_player	enemy;
}		t_msg;

typedef struct		s_msgqueue
{
  t_player		plr;
  struct s_msgqueue	*next;
}			t_msgqueue;

void	init_lemipc(const char *, const int);
int	sem_lock(t_ipcs *);
int	sem_unlock(t_ipcs *);
void	play(struct s_case *, const int, t_ipcs *);
void	movePlayer(struct s_case *, t_player *, t_ipcs *);
void	screen(struct s_case *, t_ipcs *);
void	IA_move(struct s_case *, t_player *, const t_player *);

#endif
