#include "DialogEntity.h"

#include <cassert>

#include <gf/Coordinates.h>
#include <gf/RenderTarget.h>
#include <gf/Sprite.h>
#include <gf/Shapes.h>
#include <gf/Text.h>

#include "GameData.h"
#include "GameState.h"
#include "I18N.h"

namespace tlw {

  namespace {

    enum class DialogPart {
      Normal,
      Thoughts,
      Question,
    };

    DialogPart computeDialogPart(const Dialog& dialog, std::size_t line) {
      if (dialog.type == DialogType::Normal) {
        assert(line < dialog.lines.size());
        return DialogPart::Normal;
      }

      assert(dialog.type == DialogType::Investigation);

      if (line < dialog.lines.size()) {
        return DialogPart::Normal;
      }

      if (line == dialog.lines.size()) {
        return DialogPart::Thoughts;
      }

      assert(line == dialog.lines.size() + 1);
      return DialogPart::Question;
    }

  }

  DialogEntity::DialogEntity(gf::ResourceManager& resources, const GameData& data, GameState& state)
  : m_speakerFont(resources.getFont("Tippa.ttf"))
  , m_wordsFont(resources.getFont("Aquifer.otf"))
  , m_playerDialogTexture(resources.getTexture("images/raymond_dialog.png"))
  , m_data(data)
  , m_state(state)
  {
    m_playerDialogTexture.setSmooth(true);
  }

  void DialogEntity::update([[maybe_unused]] gf::Time time) {
  }

  void DialogEntity::render(gf::RenderTarget &target, const gf::RenderStates &states) {
    if (m_state.currentDialog == gf::InvalidId) {
      return;
    }

    gf::Coordinates coords(target);

    gf::Vector2f backgroundSize = coords.getRelativeSize({ 1.0f, 0.35f });

    gf::RectangleShape background(backgroundSize);
    background.setColor(gf::Color::Black * gf::Color::Opaque(0.7f));
    background.setPosition(coords.getRelativePoint({ 0.0, 0.65 }));
    background.setAnchor(gf::Anchor::TopLeft);
    target.draw(background, states);
    // TODO background

    auto it = m_data.dialogs.find(m_state.currentDialog);
    assert(it != m_data.dialogs.end());
    auto& [ currentId, currentDialog ] = *it;

    auto drawDialog = [&](const DialogLine& line, gf::Color4f color) {
      unsigned speakerCharacterSize = coords.getRelativeCharacterSize(0.05f);

      gf::Text speaker(line.speaker, m_speakerFont, speakerCharacterSize);
      speaker.setColor(color);
      speaker.setPosition(coords.getRelativePoint({ 0.2, 0.7 }));
      speaker.setAnchor(gf::Anchor::TopLeft);
      target.draw(speaker, states);

      float wordsWidth = coords.getRelativeSize({ 0.6f, 0.0f }).width;
      unsigned wordsCharacterSize = coords.getRelativeCharacterSize(0.04f);

      gf::Text words(line.words, m_wordsFont, wordsCharacterSize);
      words.setParagraphWidth(wordsWidth);
      words.setAlignment(gf::Alignment::Justify);
      words.setColor(color);
      words.setPosition(coords.getRelativePoint({ 0.2, 0.8 }));
      words.setAnchor(gf::Anchor::TopLeft);
      target.draw(words, states);

      if (line.speaker == "Raymond") {
        float spriteHeight = coords.getRelativeSize(gf::vec(0.0f, 0.70f)).height;
        float spriteScale = spriteHeight / m_playerDialogTexture.getSize().height;

        gf::Sprite sprite(m_playerDialogTexture, gf::RectF::fromPositionSize({ 0.0f, 0.0f }, { 1.0f, 0.6f }));
        sprite.setPosition(coords.getRelativePoint({ 0.95f, 0.65f }));
        sprite.setAnchor(gf::Anchor::BottomRight);
        sprite.setScale(spriteScale);
        target.draw(sprite, states);
      }
    };

    switch (computeDialogPart(currentDialog, m_state.currentLine)) {
      case DialogPart::Normal:
        drawDialog(currentDialog.lines[m_state.currentLine], gf::Color::White);
        break;

      case DialogPart::Thoughts:
        drawDialog(currentDialog.thoughts, gf::Color::Gray());
        break;

      case DialogPart::Question:
        drawDialog(currentDialog.question, gf::Color::Orange);
        break;
    }

  }

}
