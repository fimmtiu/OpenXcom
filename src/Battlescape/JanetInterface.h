#pragma once

#include <janet/janet.h>
#include "BattlescapeGame.h"

namespace OpenXcom
{
  class JanetInterface
  {
  public:
    static void initJanetData(BattlescapeGame *game);
    static BattleAction think(BattleUnit* unit);

    static Janet battlescapeGame;
  private:
  };
}
