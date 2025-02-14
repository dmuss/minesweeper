#ifndef SCENES_GAME_SCENE_HPP_
#define SCENES_GAME_SCENE_HPP_

#include <cstdint>

#include "scene_interface.hpp"
#include "../minefield/minefield.hpp"

class GameScene final : public SceneInterface {
 private:
  static constexpr uint8_t CELL_RENDER_SIZE_PX_ = 50;

  MinefieldUPtr minefield_ = std::make_unique<Minefield>();

 public:
  void OnEnter(Game& game) override;
  void Update(Game& game, MouseState mouseState) override;
  void Draw(Game& game) override;
  void OnLeave(Game& game) override;
};

#endif
