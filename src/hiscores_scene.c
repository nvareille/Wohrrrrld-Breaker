#include "game.h"

static void	graphic(Layer *l, GContext *ctx)
{
  char		buf[10];
  char		disp[64];
  int		score;

  persist_read_string(LOGIN, buf, sizeof(buf));
  score = persist_read_int(SCORE);
  snprintf(disp, sizeof(disp), "%s:\n%d points", buf, score);
  putstr_font("Record", FONT_KEY_GOTHIC_28, 0, 0, ctx);
  putstr(disp, 0, 30, ctx);
}

void		hiscores_scene()
{
  create_basic_scene(graphic, NULL, NULL, NULL);
}
