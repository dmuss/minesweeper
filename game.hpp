#ifndef GAME_HPP
#define GAME_HPP

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wold-style-cast"
#include <SDL3/SDL_init.h>
#pragma GCC diagnostic pop

#include "sdl_helpers.hpp"

class Game {
 private:
  static bool isInit_;
  static constexpr uint8_t TARGET_FPS_ = 30;
  static constexpr uint8_t TARGET_FRAME_TIME_MS_ = 1000 / TARGET_FPS_;

  bool running_;
  uint64_t currFrameMS_;
  uint64_t lastFrameMS_;
  uint64_t deltaMS_;

  SDL3::WindowUPtr window_;
  SDL3::RendererUPtr renderer_;
  SDL3::TextureUPtr spritesheet_;

 public:
  Game();

  SDL_AppResult Tick();

  void HandleMouseButtonEvent(SDL_Event* event);
};

#endif
