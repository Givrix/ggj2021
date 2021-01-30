#ifndef PLAYER_ENTITY_H
#define PLAYER_ENTITY_H

#include <gf/Entity.h>
#include <gf/Direction.h>

namespace tlw {
  struct GameState;

  class PlayerEntity : public gf::Entity {
  public:
    PlayerEntity(GameState& state);
    void update(gf::Time time) override;
    void render(gf::RenderTarget &target, const gf::RenderStates &states) override;
    void move(gf::Direction dir);

  private:
    GameState& m_state;
  };

}


#endif // PLAYER_ENTITY_H