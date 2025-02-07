#ifndef GAME_HPP
#define GAME_HPP

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wold-style-cast"
#include <SDL3/SDL_init.h>
#pragma GCC diagnostic pop

#include "sdl_helpers.hpp"

class Game {
 public:
  Game();

  SDL_AppResult Tick();

  void HandleMouseButtonEvent(SDL_Event* event);

 private:
  static bool is_init_;

  bool running_;

  SDL3::WindowUPtr window_;
  SDL3::RendererUPtr renderer_;
  SDL3::TextureUPtr spritesheet_;
};

#endif
