#include "StartScene.h"

#include <gf/Color.h>

#include "Constants.h"
#include "GameHub.h"

namespace tlw {

  StartScene::StartScene(GameHub& game)
  : gf::Scene(game.getRenderer().getSize())
  , m_game(game)
  , m_startAction("Start")
  , m_fullscreenAction("Fullscreen")
  , m_titleEntity(game.resources)
  {
    setClearColor(gf::Color::Black);

    m_startAction.addGamepadButtonControl(gf::AnyGamepad, gf::GamepadButton::A);
    m_startAction.addGamepadButtonControl(gf::AnyGamepad, gf::GamepadButton::B);
    m_startAction.addGamepadButtonControl(gf::AnyGamepad, gf::GamepadButton::X);
    m_startAction.addGamepadButtonControl(gf::AnyGamepad, gf::GamepadButton::Y);
    addAction(m_startAction);

    m_fullscreenAction.addGamepadButtonControl(gf::AnyGamepad, gf::GamepadButton::Guide);
    addAction(m_fullscreenAction);

    addHudEntity(m_titleEntity);
  }

  void StartScene::doHandleActions([[maybe_unused]] gf::Window& window) {
    if (!isActive()) {
      return;
    }

    if (m_fullscreenAction.isActive()) {
      window.toggleFullscreen();
    }

    if (m_startAction.isActive()) {
      m_game.replaceScene(m_game.introduction, m_game.blackout, gf::seconds(TransitionDelay));
    }
  }

}
