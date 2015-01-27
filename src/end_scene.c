#include "game.h"

static void	graphic(Layer *l, GContext *ctx)
{
  Game		*game = USER_PTR;
  char		disp[64];

  snprintf(disp, sizeof(disp), "%d points, not bad !", game->score);
  putstr(disp, 0, 0, ctx);
  putstr("Should I ?", 0, 12, ctx);
  putstr_font("Retry", FONT_KEY_GOTHIC_28, 50, 33, ctx);
  putstr_font("Quit", FONT_KEY_GOTHIC_28, 50, 63, ctx);
  draw_img_pos(game->img[0], 47, 110, ctx);
}

static void	choice()
{
  Game		*game = USER_PTR;

  window_stack_pop(true);
  if (!game->pos)
    game_scene();
}

static void	change_layer_pos()
{
  Game		*game = USER_PTR;

  if (!game->pos)
    invert_set_pos(game->layer, 48, 65);
  else
    invert_set_pos(game->layer, 48, 35);
  game->pos = !game->pos;
  refresh();
}

static void	click()
{
  window_single_click_subscribe(BUTTON_ID_UP, change_layer_pos);
  window_single_click_subscribe(BUTTON_ID_DOWN, change_layer_pos);
  window_single_click_subscribe(BUTTON_ID_SELECT, choice);
}

static void	load()
{
  Game		*game = USER_PTR;

  game->pos = false;
  game->layer = create_invert_layer(48, 35, 53, 30);
  if (persist_read_int(SCORE) < game->score)
    new_record_scene(game->score);
}

void		end_scene()
{
  create_basic_scene_fullscreen(graphic, load, NULL, click);
}
