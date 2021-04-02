#include <fstream>
#include "JanetAIModule.h"
#include "../Engine/CrossPlatform.h"
#include "../Engine/Options.h"

namespace OpenXcom
{
  JanetTable* JanetAIModule::janet_env = NULL;

  JanetAIModule::JanetAIModule(SavedBattleGame *save, BattleUnit *unit, Node *node) : AIModule(save, unit, node)
  {
    _targetFaction = FACTION_HOSTILE;
    if (unit->getFaction() != FACTION_PLAYER)
    {
      CrossPlatform::showError("WTF? Tried to attach a JanetAIModule to a " + unit->getType());
      exit(0);
    }

    if (Options::aiCode.size() > 0)
    {
      std::string code = slurpFile(Options::aiCode);
      CrossPlatform::showError(code);

      int result = janet_dostring(janet_env, code.c_str(), Options::aiCode.c_str(), &_aiFunc);
      if (result > 0)
      {
        CrossPlatform::showError("Couldn't load Janet code from " + Options::aiCode + "! Error code: " + std::to_string(result));
        exit(0);
      }
      if (!janet_checktype(_aiFunc, JANET_FUNCTION))
      {
        CrossPlatform::showError("Janet script at " + Options::aiCode + " returned " + std::to_string(janet_type(_aiFunc)) + ", not a function.");
        exit(0);
      }
    }
    else
    {
      CrossPlatform::showError("No aiCode parameter supplied. Falling back to built-in AIModule behaviour.");
      _aiFunc = janet_wrap_nil();
    }
  }

  std::string JanetAIModule::slurpFile(std::string &filename)
  {
    std::ifstream input(filename);
    std::string result;

    input.seekg(0, std::ios::end);
    result.reserve(input.tellg());
    input.seekg(0, std::ios::beg);

    result.assign((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());
    return result;
  }

  void JanetAIModule::SetUp() {
    janet_init();
    janet_env = janet_core_env(NULL);
  }

  void JanetAIModule::TearDown() {
    janet_deinit();
    janet_env = NULL;
  }

}
