#include "Plot.h"

#include "GameHub.h"

using namespace gf::literals;

namespace tlw {
  Plot::Plot(GameHub& game)
  : m_game(game)
  {
    loadChapter(m_game.state.chapter);
  }

  void Plot::onDialogEnd(gf::Id dialogId) {
    switch (dialogId) {
      case "Chap1Dread1"_id:
        m_game.state.characters[CharacterType::Dread].dialog = "Chap1Dread_NotFinished"_id;
        m_game.state.nextDialogSuccess = "Chap1Dread_Success"_id;
        m_game.state.nextDialogFailure = "Chap1Dread_Failure"_id;
        m_game.state.result = ChallengeResult::None;
        m_game.sliderChallenge.reset(SliderChallengeDifficulty::Easy);
        m_game.pushScene(m_game.sliderChallenge);
        break;

      case "Chap1SearchWoodHouse"_id:
        m_game.state.nextDialogSuccess = "Chap1SearchWoodHouse_Success"_id;
        m_game.state.nextDialogFailure = "Chap1SearchWoodHouse_Failure"_id;
        m_game.state.result = ChallengeResult::None;
        m_game.pushScene(m_game.streakChallenge);
        break;

      case "Chap1Dread_Success"_id:
      case "Chap1Dread_Failure"_id:
      case "Chap1SearchWoodHouse_Success"_id:
      case "Chap1SearchWoodHouse_Failure"_id:
        if (checkEndChapter()) {
          m_game.state.characters.at(CharacterType::Dread).dialog = "Chap1Dread_Finished"_id;
          m_game.state.currentDialog = "RaymondEndChapter"_id;
          m_game.pushScene(m_game.dialog);
        }
        break;

      case "Chap1Elders1"_id:
        m_game.state.characters[CharacterType::Elders].dialog = "Chap1Elders2"_id;
        break;

      case "Chap1Dread_Finished"_id:
        loadChapter(++m_game.state.chapter);
        m_game.replaceScene(m_game.introduction);
        break;

      // Chapter 2
      case "Chap2Elders"_id:
        m_game.state.characters[CharacterType::Elders].dialog = "Chap2Elders_Failure"_id;
        m_game.state.nextDialogSuccess = "Chap2Elders_Success"_id;
        m_game.state.nextDialogFailure = "Chap2Elders_Failure"_id;
        m_game.state.result = ChallengeResult::None;
        m_game.sliderChallenge.reset(SliderChallengeDifficulty::Medium);
        m_game.pushScene(m_game.sliderChallenge);

        // Add other dialogs for other NPC
        m_game.state.characters[CharacterType::Bouquet].dialog =  "Chap2BouquetInvestigation"_id;
        break;

      case "Chap2SearchGarbageCan"_id:
        m_game.state.nextDialogSuccess = "Chap2SearchGarbageCan_Success"_id;
        m_game.state.nextDialogFailure = "Chap2SearchGarbageCan_Failure"_id;
        m_game.state.result = ChallengeResult::None;
        m_game.pushScene(m_game.streakChallenge);
        break;

      case "Chap2BouquetInvestigation"_id:
        m_game.state.characters[CharacterType::Bouquet].dialog = "Chap2Bouquet"_id;
        m_game.state.nextDialogSuccess = "Chap2BouquetInvestigation_Success"_id;
        m_game.state.nextDialogFailure = "Chap2BouquetInvestigation_Failure"_id;
        m_game.state.result = ChallengeResult::None;
        m_game.sliderChallenge.reset(SliderChallengeDifficulty::Medium);
        m_game.pushScene(m_game.sliderChallenge);
        break;


      case "Chap2BouquetInvestigation_Success"_id:
      case "Chap2BouquetInvestigation_Failure"_id:
      case "Chap2SearchGarbageCan_Success"_id:
      case "Chap2SearchGarbageCan_Failure"_id:
        if (checkEndChapter()) {
          m_game.state.currentDialog = "RaymondEndChapter2"_id;
          m_game.pushScene(m_game.dialog);
        }
        break;

      case "Chap2Dread_Finished"_id:
        loadChapter(++m_game.state.chapter);
        m_game.replaceScene(m_game.introduction);
        break;

      //Chapter 3
      case "Chap3MafiaDogInvestigation"_id:
          m_game.state.characters[CharacterType::DogPack].dialog = "Chap3MafiaDog2"_id;
          m_game.state.nextDialogSuccess = "Chap3MafiaDogInvestigation_Success"_id;
          m_game.state.nextDialogFailure = "Chap3MafiaDogInvestigation_Failure"_id;
          m_game.state.result = ChallengeResult::None;
          m_game.sliderChallenge.reset(SliderChallengeDifficulty::Medium);
          m_game.pushScene(m_game.sliderChallenge);
          break;

      case "Chap3MafiaDogInvestigation_Success"_id:
      case "Chap3MafiaCatInvestigation_Success"_id:
      case "Chap3MafiaCatInvestigation_Failure"_id:
      case "Chap3MafiaDogInvestigation_Failure"_id:
          if (checkEndChapter()) {
              m_game.state.currentDialog = "RaymondEndChapter2"_id;
              m_game.pushScene(m_game.dialog);
          }
      default:
        break;
    }
  }

  void Plot::onStreakChallengeEnd() {
    assert(m_game.state.result != ChallengeResult::None);

    if (m_game.state.result == ChallengeResult::Success) {
      m_game.state.currentDialog = m_game.state.nextDialogSuccess;
    } else {
      assert(m_game.state.result == ChallengeResult::Failure);
      m_game.state.currentDialog = m_game.state.nextDialogFailure;
    }

    ++m_game.state.finishedSearchs;

    m_game.pushScene(m_game.dialog);
  }

  void Plot::onSliderChallengeEnd() {
    assert(m_game.state.result != ChallengeResult::None);

    if (m_game.state.result == ChallengeResult::Success) {
      m_game.state.currentDialog = m_game.state.nextDialogSuccess;
    } else {
      assert(m_game.state.result == ChallengeResult::Failure);
      m_game.state.currentDialog = m_game.state.nextDialogFailure;
    }

    ++m_game.state.finishedInvestigations;

    m_game.pushScene(m_game.dialog);
  }

  bool Plot::checkEndChapter() {
    if ((m_game.state.finishedInvestigations + m_game.state.finishedSearchs) >= m_game.data.limitClues[m_game.state.chapter]) {
      if (m_game.state.chapter == 1){
        m_game.state.characters.at(CharacterType::Dread).dialog = "Chap1Dread_Finished"_id;
      }
      else if (m_game.state.chapter == 2) {
        m_game.state.characters.at(CharacterType::Dread).dialog = "Chap2Dread_Finished"_id;
      }  
      return true;
    }

    return false;
  }


    void Plot::loadChapter(int chapterNumber) {
      switch (chapterNumber) {
      case 0:
        // TODO: remove this
        // m_game.state.currentDialog = "Chap1Dread1"_id;

        m_game.state.characters[CharacterType::Holly].visibility = CharacterVisibility::Hidden;
        m_game.state.characters[CharacterType::Stock].visibility = CharacterVisibility::Hidden;

        m_game.state.characters[CharacterType::Bouquet].dialog = "Chap1Bouquet1"_id;
        m_game.state.characters[CharacterType::Elders].dialog = "Chap1Elders1"_id;
        m_game.state.characters[CharacterType::Dread].dialog = "Chap1Dread1"_id;
        m_game.state.characters[CharacterType::Gustavo].dialog = "Chap1Gustavo1"_id;
        break;

      case 1:
        m_game.state.characters[CharacterType::Bouquet].dialog = gf::InvalidId;
        m_game.state.characters[CharacterType::Elders].dialog = "Chap2Elders"_id;
        m_game.state.characters[CharacterType::Dread].dialog = gf::InvalidId;
        m_game.state.characters[CharacterType::Gustavo].dialog = gf::InvalidId;
        break;

      case 2:
        m_game.state.characters[CharacterType::Bouquet].dialog = gf::InvalidId;
        m_game.state.characters[CharacterType::Elders].dialog = "Chap3Elders"_id;
        m_game.state.characters[CharacterType::Dread].dialog = gf::InvalidId;
        m_game.state.characters[CharacterType::Gustavo].dialog = gf::InvalidId;
        m_game.state.characters[CharacterType::DogPack].dialog = "Chap3MafiaDogInvestigation"_id;
        m_game.state.characters[CharacterType::CatPack].dialog = "Chap3MafiaCatInvestigation"_id;
        break;

      default:
        break;
      }
    }

}
