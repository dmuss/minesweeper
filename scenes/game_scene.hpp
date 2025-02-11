#ifndef SCENES_GAME_SCENE_HPP_
#define SCENES_GAME_SCENE_HPP_

#include "scene_interface.hpp"
#include "../minefield.hpp"

class GameScene : public SceneInterface {
 private:
  // TODO: Grid dimensions should exist in Minefield. When minefield is to be
  // displayed, resize window based on the size of the minefield.
  static constexpr uint8_t CELL_GRID_WIDTH_ = 9;
  static constexpr uint8_t CELL_GRID_HEIGHT_ = 9;
  static constexpr uint8_t CELL_RENDER_SIZE_PX_ = 50;

  bool playing_ = true;
  MinefieldUPtr minefield_ = std::make_unique<Minefield>();

 public:
  void OnEnter(Game& game) override;
  void Update(Game& game, SDL_Event* mouseEvent) override;
  void Draw(Game& game) override;
  void OnLeave(Game& game) override;
};

#endif
