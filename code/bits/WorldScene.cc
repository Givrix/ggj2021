#include "WorldScene.h"

#include <gf/Log.h>

#include "GameHub.h"

namespace tlw {
  WorldScene::WorldScene(GameHub& game)
  : gf::Scene(game.getRenderer().getSize())
  , m_game(game)
  , m_moveXPosAction("MoveXPositive")
  , m_moveXNegAction("MoveXNegative")
  , m_moveYPosAction("MoveYPositive")
  , m_moveYNegAction("MoveYNegative")
  , m_playerEntity(game.state)
  {
    setClearColor(gf::Color::White);

    m_moveXPosAction.addGamepadAxisControl(gf::AnyGamepad, gf::GamepadAxis::LeftX, gf::GamepadAxisDirection::Positive);
    addAction(m_moveXPosAction);

    m_moveXNegAction.addGamepadAxisControl(gf::AnyGamepad, gf::GamepadAxis::LeftX, gf::GamepadAxisDirection::Negative);
    addAction(m_moveXNegAction);

    m_moveYPosAction.addGamepadAxisControl(gf::AnyGamepad, gf::GamepadAxis::LeftY, gf::GamepadAxisDirection::Positive);
    addAction(m_moveYPosAction);

    m_moveYNegAction.addGamepadAxisControl(gf::AnyGamepad, gf::GamepadAxis::LeftY, gf::GamepadAxisDirection::Negative);
    addAction(m_moveYNegAction);

    addWorldEntity(m_playerEntity);

    setWorldViewSize(game.getRenderer().getSize());
    setWorldViewCenter(game.getRenderer().getSize() / 2);
  }

  void WorldScene::doProcessEvent(gf::Event& event) {
    /*switch (event.type) {
      case gf::EventType::GamepadAxisMoved: {
        const gf::GamepadAxisEvent& gamepadEvent = event.gamepadAxis;
        std::string gamepadName = gf::Gamepad::getName(gamepadEvent.id);
        int32_t eventID = static_cast<int32_t>(gamepadEvent.id);
        std::string axisName = gf::Gamepad::getAxisName(gamepadEvent.axis);
        int16_t value = gamepadEvent.value;

        gf::Log::debug("gamepad: %s\n", gamepadName.c_str());
        gf::Log::debug("eventID: %d\n", eventID);
        gf::Log::debug("axisName: %s\n", axisName.c_str());
        gf::Log::debug("axisName: %d\n", value);
        break;
      }

      default:
        break;
    }*/
  }

  void WorldScene::doHandleActions([[maybe_unused]] gf::Window& window) {
    
    //Actions for moving player
    if (m_moveXPosAction.isActive()) {
      m_playerEntity.move(gf::Direction::Right);
    } else if (m_moveXNegAction.isActive()) {
      m_playerEntity.move(gf::Direction::Left);
    } else if (m_moveYPosAction.isActive()) {
      m_playerEntity.move(gf::Direction::Down);
    } else if (m_moveYNegAction.isActive()) {
      m_playerEntity.move(gf::Direction::Up);
    }
  }
}
