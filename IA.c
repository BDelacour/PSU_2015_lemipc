/*
** IA.c for C in /home/delaco_c/rendu/PSU_2015_lemipc
** 
** Made by Delacour Benjamin
** Login   <delaco_c@epitech.net>
** 
** Started on  Fri Mar 25 16:33:29 2016 Delacour Benjamin
** Last update Sun Mar 27 18:23:15 2016 Delacour Benjamin
*/

#include "lemipc.h"

int	IA_lowerMove(struct s_case *map, t_player *plr, int vec_x, int vec_y)
{
  if (ABS(vec_x) >= ABS(vec_y) &&
      plr->x + FNEG(vec_x) >= 0 && plr->x + FNEG(vec_x) < WIDTH &&
      map[plr->y * WIDTH + plr->x + FNEG(vec_x)].nteam == 0)
    {
      map[plr->y * WIDTH + plr->x].nteam = 0;
      map[plr->y * WIDTH + plr->x + FNEG(vec_x)].nteam = plr->team;
      plr->x += FNEG(vec_x);
    }
  else if (plr->y + FNEG(vec_y) >= 0 && plr->y + FNEG(vec_y) < HEIGHT &&
	   map[(plr->y + FNEG(vec_y)) * WIDTH + plr->x].nteam == 0)
    {
      map[plr->y * WIDTH + plr->x].nteam = 0;
      map[(plr->y + FNEG(vec_y)) * WIDTH + plr->x].nteam = plr->team;
      plr->y += FNEG(vec_y);
    }
  else
    return (0);
  return (1);
}

void	IA_otherMove(struct s_case *map, t_player *plr, int vec_x, int vec_y)
{
  if (ABS(vec_x) > ABS(vec_y) && plr->y - FNEG(vec_y) >= 0 &&
      plr->y - FNEG(vec_y) < HEIGHT &&
      map[(plr->y - FNEG(vec_y)) * WIDTH + plr->x].nteam == 0)
    {
      map[plr->y * WIDTH + plr->x].nteam = 0;
      map[(plr->y - FNEG(vec_y)) * WIDTH + plr->x].nteam = plr->team;
      plr->y -= FNEG(vec_y);
    }
  else if (plr->x - FNEG(vec_x) >= 0 && plr->x - FNEG(vec_x) < WIDTH &&
	   map[plr->y * WIDTH + plr->x - FNEG(vec_x)].nteam == 0)
    {
      map[plr->y * WIDTH + plr->x].nteam = 0;
      map[plr->y * WIDTH + plr->x - FNEG(vec_x)].nteam = plr->team;
      plr->x -= FNEG(vec_x);
    }
}

void	IA_move(struct s_case *map, t_player *plr, const t_player *enemy)
{
  int		vec_x;
  int		vec_y;

  vec_x = enemy->x - plr->x;
  if (vec_x == 0)
    {
      if (plr->x == 0 || map[plr->y * WIDTH + plr->x - 1].nteam != 0)
	vec_x = 1;
      else
	vec_x = -1;
    }
  vec_y = enemy->y - plr->y;
  if (vec_y == 0)
    {
      if (plr->y == 0 || map[(plr->y - 1) * WIDTH + plr->x].nteam != 0)
	vec_y = 1;
      else
	vec_y = -1;
    }
  if (!IA_lowerMove(map, plr, vec_x, vec_y))
    IA_otherMove(map, plr, vec_y, vec_y);
}
