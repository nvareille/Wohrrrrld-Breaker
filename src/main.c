#include "game.h"

static void	graphic(Layer *layer, GContext *ctx)
{
  Game		*game = USER_PTR;

  putstr_font("wohrrrrld", FONT_KEY_GOTHIC_28, 0, 0, ctx);
  putstr_font("breaker", FONT_KEY_GOTHIC_28, 50, 28, ctx);
  draw_img_pos(game->img[1], 40, 80, ctx);
}

static void	timer_callback(void *data, Timer *t)
{
  t->active = false;
  window_stack_pop(true);
  main_menu_scene();
}

static void	load()
{
  create_timer(3000, timer_callback, NULL);
}

static void	exec(void *data)
{
  Game		*game = data;

  srand(time(NULL));
  if (!persist_exists(LOGIN))
    {
      persist_write_string(LOGIN, "Nobody");
      persist_write_int(SCORE, 0);
    }
  game->img[0] = create_img_pos(RESOURCE_ID_DRAGON, 20, 80);
  game->img[1] = create_img_pos(RESOURCE_ID_DRAGON_LOVE, 60, 90);
  game->img[2] = create_img_pos(RESOURCE_ID_DRAGON_STRENGTH, 47, 70);
  game->arrow[0] = create_img(RESOURCE_ID_UP);
  game->arrow[1] = create_img(RESOURCE_ID_SELECT);
  game->arrow[2] = create_img(RESOURCE_ID_DOWN);
  create_basic_scene_fullscreen(graphic, load, NULL, NULL);
}

int		main()
{
  Game		game;

  app_init(&game, exec);
  return (0);
}
