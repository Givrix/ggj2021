#ifndef STREAK_CHALLENGE_SCENE_H
#define STREAK_CHALLENGE_SCENE_H

#include <vector>
#include <iostream>
#include <gf/Scene.h>
#include <gf/Random.h>
#include <gf/Log.h>
#include <gf/Action.h>
#include <gf/Color.h>
#include <gf/Sprite.h>
#include <gf/Transformable.h>
#include <gf/Circ.h>
#include <gf/Drawable.h>
#include <gf/Shapes.h>

#include "StreakEntity.h"

namespace tlw {

  struct GameHub;

  class StreakChallengeScene : public gf::Scene {
  public:
      StreakChallengeScene(GameHub& game);
      std::vector<gf::GamepadButton> generateStreak();
      std::vector<gf::GamepadButton> m_streak;
      std::vector<gf::GamepadButton> m_streakPlayer;
      gf::Clock m_clock;
      gf::Time m_timer;
      gf::Action m_buttonA;
      gf::Action m_buttonB;
      gf::Action m_buttonX;
      gf::Action m_buttonY;

  private:
    GameHub& m_game;
    StreakEntity m_streakEntity;
    virtual void doProcessEvent(gf::Event& event) override;
    virtual void doHandleActions(gf::Window& window) override;

  };

}

#endif // STREAK_CHALLENGE_SCENE_H