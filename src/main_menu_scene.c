#include "game.h"

static SimpleMenuItem		items[] =
  {
    {"Play", NULL, NULL, game_scene},
    {"Hi-Scores", NULL, NULL, hiscores_scene}
  };

static SimpleMenuSection	sections[] =
  {
    {"Wohrrrrld Breaker", items, SIZE(items)}
  };

void				main_menu_scene()
{
  create_basic_menu_scene(sections, NULL, NULL, SIZE(sections));
}
