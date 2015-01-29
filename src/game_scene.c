#include "game.h"

static void	gen_arrow(Game *game)
{
  int		count = 0;

  if (game->score % 5 == 0)
    {
      if (game->complexity < 5)
	++game->complexity;
      if (game->score != 0)
	game->time += 5;
    }
      
  while (count < game->complexity)
    {
      game->input[count] = rand() % 3;
      ++count;
    }
}

static void	decal_arrow(Game *game)
{
  int		count = 0;

  while (count < game->complexity - 1)
    {
      game->input[count] = game->input[count + 1];
      ++count;
    }
  game->input[game->complexity - 1] = -1;
}

static void	wait_for_order(Game *game, GContext *ctx)
{
  int		size = 0;
  
  draw_img(game->img[0], ctx);
  while (size < 5)
    {
      draw_line(100 + size, 12, 100 + size, 170, ctx);
      ++size;
    }
}

static void	draw_wall(Game *game, GContext *ctx)
{
  int		size;

  size = 0;
  draw_img(game->img[2], ctx);
  while (size < 5)
    {
      draw_line(100 + size, 12, 100 + size, 170, ctx);
      ++size;
    }
}

static void	draw_wall_broken(Game *game, GContext *ctx)
{
  int		size;

  size = 0;
  draw_img(game->img[1], ctx);
  while (size < 5)
    {
      draw_line(100 + size, 12, 100 + size, 90, ctx);
      draw_line(100 + size, 150, 100 + size, 170, ctx);
      ++size;
    }
}

static void	(*anims[])(Game *, GContext *) =
{
  wait_for_order,
  draw_wall,
  draw_wall_broken
};

static void	graphic(Layer *l, GContext *ctx)
{
  Game		*game = USER_PTR;
  int		count = 0;

  while (count < game->complexity && game->input[count] >= 0)
    {
      if (!count)
	draw_img_effect_pos(game->arrow[game->input[0]], GCompOpAssignInverted, 115, 15, ctx);
      else
	draw_img_pos(game->arrow[game->input[count]], 115, 15 + count * 20, ctx);
      ++count;
    }
  putstr("Time:", 0, 0, ctx);
  putstr(game->time_left, 26, 0, ctx);
  putstr("Score:", 80, 0, ctx);
  putstr(game->score_disp, 116, 0, ctx);
  draw_line(0, 12, 144, 12, ctx);
  anims[game->animation](game, ctx);  
  if (game->combo)
    putstr_font("COMBO !", FONT_KEY_GOTHIC_28, 0, 20, ctx);
}

static void	timer_callback(void *data, Timer *t)
{
  Game		*game = data;

  if ((--game->time) == -1)
    {
      t->active = false;
      window_stack_pop(true);
      end_scene();
    }
  snprintf(game->time_left, sizeof(game->time_left), "%d", game->time == -1 ? 0 : game->time);
  refresh();
}

static void	reset_break(void *data, Timer *t)
{
  Game		*game = data;

  game->animation = 0;
  t->active = false;
}

static void	try_click(Game *game, int button)
{
  if (game->time > -1)
    {
      if (game->input[0] == button)
	{
	  decal_arrow(game);
	  if (game->input[0] < 0)
	    {
	      ++game->streak;
	      if (game->streak > 0 && game->streak % 3 == 0)
		++game->combo;
	      game->score += (game->combo + 1);
	      snprintf(game->score_disp, sizeof(game->score_disp), "%d", game->score);
	      game->animation = 2;
	      create_timer(200, reset_break, game);
	      vibes_short_pulse();
	      gen_arrow(game);
	    }
	}
      else
	{
	  game->combo = 0;
	  game->streak = 0;
	  game->animation = 1;
	  create_timer(200, reset_break, game);
	  vibes_short_pulse();
	}
    }
  refresh();
}

static void	load()
{
  Game		*game = USER_PTR;

  game->complexity = 0;
  game->animation = 0;
  game->time = 20;
  game->score = 0;
  game->combo = 0;
  game->streak = 0;
  gen_arrow(game);
  strcpy(game->time_left, "20");
  strcpy(game->score_disp, "0");
  game->timer = create_timer(1000, timer_callback, game);
}

static void	unload()
{
  Game		*game = USER_PTR;

  clean(game->timer);
}

static void	up()
{
  Game		*game = USER_PTR;

  try_click(game, 0);
}

static void	down()
{
  Game		*game = USER_PTR;

  try_click(game, 2);
}

static void	select()
{
  Game		*game = USER_PTR;

  try_click(game, 1);
}

static void	click()
{
  window_single_click_subscribe(BUTTON_ID_UP, up);
  window_single_click_subscribe(BUTTON_ID_DOWN, down);
  window_single_click_subscribe(BUTTON_ID_SELECT, select);
}

void		game_scene()
{
  create_basic_scene_fullscreen(graphic, load, unload, click);
}
