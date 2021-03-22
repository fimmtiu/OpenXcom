#pragma once

/* SURELY THIS WILL WORK */

#include "AIModule.h"
#include <janet/janet.h>

namespace OpenXcom
{
  class JanetAIModule : public AIModule
  {
  public:
    static JanetTable* janet_env;
    static void SetUp();
    static void TearDown();

    JanetAIModule(SavedBattleGame *save, BattleUnit *unit, Node *node);

  private:
    Janet _aiFunc;

    std::string slurpFile(std::string &filename);
  };
}
