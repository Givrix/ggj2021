#ifndef GAME_HUB_H
#define GAME_HUB_H

#include <gf/GameManager.h>

#include "StartScene.h"

namespace xy {

  struct GameHub : gf::GameManager {
    GameHub();

    StartScene start;

  };

}


#endif // GAME_HUB_H
