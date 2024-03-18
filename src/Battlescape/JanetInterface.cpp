#include "JanetInterface.h"
#include "BattlescapeGame.h"

extern "C" {

static Janet enemy_unit_p(int32_t argc, Janet *argv) {
  // FIXME
  return janet_wrap_nil();
}

static const JanetReg c_functions[] = {
  { "enemy-unit?", enemy_unit_p,
    "(xcom/enemy-unit? unit)\n\n"
    "Returns true if the argument is a unit belonging to the opposing faction and false otherwise."
  },
  {NULL, NULL, NULL}
};

JANET_MODULE_ENTRY(JanetTable *env) {
  janet_cfuns(env, "xcom", c_functions);
}

} /* extern "C" */

namespace OpenXcom
{
  void JanetInterface::initJanetData(BattlescapeGame *game)
  {
    JanetInterface::battlescapeGame = janet_wrap_abstract(game);
  }

  BattleAction JanetInterface::think(BattleUnit* unit)
  {
    BattleAction foo;
    return foo;
  }
}
