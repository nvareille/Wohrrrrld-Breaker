#ifndef GAME_H_
# define GAME_H_

# include "Khelljyr/Khelljyr.h"

typedef struct	s_Game
{
  Img		*img[3];
  Img		*arrow[3];
  int		time;
  char		time_left[3];
  char		score_disp[8];
  int		animation;
  int		score;
  short		input[5];
  short		complexity;
  short		streak;
  short		combo;
  InvertLayer	*layer;
  bool		pos;
}		Game;

void		game_scene();
void		end_scene();

#endif
