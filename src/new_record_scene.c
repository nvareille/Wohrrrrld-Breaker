#include "game.h"

static void	graphic(Layer *l, GContext *ctx)
{
  putstr_font("New Record !", FONT_KEY_GOTHIC_28, 0, 0, ctx);
  putstr("Please type your name press enter", 0, 30, ctx);
  putstr("Press back to continue", 0, 80, ctx);
}

static void	new_record(Keyboard *k)
{
  Game		*game = USER_PTR;

  persist_write_string(LOGIN, k->str);
  persist_write_int(SCORE, game->score);
}

void		new_record_scene()
{
  create_basic_keyboard_scene("name", 10, new_record);
  create_basic_scene_fullscreen(graphic, NULL, NULL, NULL);
}
