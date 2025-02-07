#include "game.hpp"

#include <cmath>
#include <cstdlib>

bool Game::is_init_ = false;

Game::Game()
    : running_(true),
      window_(SDL3::CreateWindow("minesweeper", 400, 400, 0)),
      renderer_(SDL3::CreateRenderer(window_.get(), nullptr)),
      spritesheet_(
          SDL3::CreateTextureFromImage(renderer_.get(), "spritesheet.png")) {
  SDL_assert(SDL_WasInit(SDL_INIT_VIDEO));

  SDL_SetTextureScaleMode(spritesheet_.get(), SDL_SCALEMODE_NEAREST);
}

void Game::HandleMouseButtonEvent(SDL_Event* event) {
  SDL_Log("(%0.0f, %0.0f) || b: %d || down: %d || clicks: %d", event->button.x,
          event->button.y, event->button.button, event->button.down,
          event->button.clicks);
}

SDL_AppResult Game::Tick() {
  if (!running_) { return SDL_APP_SUCCESS; }

  auto time = static_cast<float>(SDL_GetTicks()) / 1000.0f;
  auto r = static_cast<uint8_t>((std::sin(time) + 1) / 2.0 * 255);
  auto g = static_cast<uint8_t>((std::sin(time / 2) + 1) / 2.0 * 255);
  auto b = static_cast<uint8_t>((std::sin(time * 2) + 1) / 2.0 * 255);

  SDL_SetRenderDrawColor(renderer_.get(), r, g, b, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(renderer_.get());
  SDL_RenderTexture(renderer_.get(), spritesheet_.get(), nullptr, nullptr);
  SDL_RenderPresent(renderer_.get());

  return SDL_APP_CONTINUE;
}
