#ifndef TITLE_ENTITY_H
#define TITLE_ENTITY_H

#include <gf/Entity.h>
#include <gf/Font.h>
#include <gf/ResourceManager.h>

namespace tlw {

  class TitleEntity : public gf::Entity {
  public:
    TitleEntity(gf::ResourceManager& resources);
    void update(gf::Time time) override;
    void render(gf::RenderTarget &target, const gf::RenderStates &states) override;

  private:
    gf::Font& m_font;
    gf::Texture& m_backgroundTexture;
  };


}


#endif // TITLE_ENTITY_H
