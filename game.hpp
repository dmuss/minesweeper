#ifndef GAME_HPP_
#define GAME_HPP_

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wold-style-cast"
#include <SDL3/SDL_init.h>
#pragma GCC diagnostic pop

#include "minefield.hpp"
#include "sdl_helpers.hpp"

class Game {
 private:
  static bool isInit_;

  static constexpr uint8_t TARGET_FPS_ = 30;
  static constexpr uint8_t TARGET_FRAME_TIME_MS_ = 1000 / TARGET_FPS_;

  // TODO: Grid dimensions should exist in Minefield. When minefield is to be
  // displayed, resize window based on the size of the minefield.
  static constexpr uint8_t CELL_GRID_WIDTH_ = 9;
  static constexpr uint8_t CELL_GRID_HEIGHT_ = 9;
  static constexpr uint8_t CELL_RENDER_SIZE_PX_ = 50;

  bool running_;
  uint64_t currFrameMS_;
  uint64_t lastFrameMS_;
  uint64_t deltaMS_;

  Minefield minefield_;

  SDL3::WindowUPtr window_;
  SDL3::RendererUPtr renderer_;
  SDL3::TextureUPtr spritesheet_;

 public:
  Game();

  SDL_AppResult Tick();

  void HandleMouseButtonEvent(SDL_Event* event);
};

#endif
