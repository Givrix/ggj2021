#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <cstddef>
#include <map>

#include <gf/Id.h>
#include <gf/Vector.h>

namespace tlw {

  enum class CharacterType : int {
    BadCat,
  };

  struct Character {
    gf::Id dialog = gf::InvalidId;

    gf::Vector2i pos;
    bool visible = false;
  };

  struct Hero {
    gf::Vector2i pos = {0, 0};
  };

  enum class ChallengeResult {
    None,
    Success,
    Failure,
  };

  struct GameState {
    GameState();

    std::size_t chapter = 0;

    gf::Id currentDialog = gf::InvalidId;
    std::size_t currentLine = 0;
    gf::Id nextDialogSuccess = gf::InvalidId;
    gf::Id nextDialogFailure = gf::InvalidId;

    ChallengeResult result = ChallengeResult::None;

    Hero hero;
    std::map<CharacterType, Character> characters;
  };

}

#endif // GAME_STATE_H
