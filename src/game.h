#ifndef GAME_H_
# define GAME_H_

# define LOGIN 0
# define SCORE 1

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
  Timer		*timer;
}		Game;

void		main_menu_scene();
void		hiscores_scene();
void		game_scene();
void		end_scene();
void		new_record_scene();

#endif
