#include "game.hpp"

#include <cmath>
#include <cstdlib>

#include "sprites.hpp"

bool Game::isInit_ = false;

Game::Game()
    : running_(true),
      // Window size set in scene.
      window_(SDL3::CreateWindow("minesweeper", 0, 0, 0)),
      renderer_(SDL3::CreateRenderer(window_.get(), nullptr)),
      spritesheet_(
          SDL3::CreateTextureFromImage(renderer_.get(), "spritesheet.png")) {
  SDL_assert(SDL_WasInit(SDL_INIT_VIDEO));
  SDL_assert(!isInit_);
  isInit_ = true;

  SDL_SetTextureScaleMode(spritesheet_.get(), SDL_SCALEMODE_NEAREST);

  // TODO: TEMP
  gameScene_.OnEnter(*this);
}

void Game::HandleMouseButtonEvent(SDL_Event* mouseEvent) {
  SDL_assert(mouseEvent->type == SDL_EVENT_MOUSE_BUTTON_UP ||
             mouseEvent->type == SDL_EVENT_MOUSE_BUTTON_DOWN);

  gameScene_.Update(*this, mouseEvent);
}

SDL_AppResult Game::Tick() {
  if (!running_) { return SDL_APP_SUCCESS; }

  currFrameMS_ = SDL_GetTicks();
  deltaMS_ = currFrameMS_ - lastFrameMS_;
  lastFrameMS_ = currFrameMS_;

  SDL_RenderClear(renderer_.get());
  gameScene_.Draw(*this);
  SDL_RenderPresent(renderer_.get());

  if (deltaMS_ < TARGET_FRAME_TIME_MS_) {
    SDL_Delay(static_cast<uint32_t>(TARGET_FRAME_TIME_MS_ - deltaMS_));
  }

  return SDL_APP_CONTINUE;
}

void Game::SetWindowSize(SDL_Point requestedSize) {
  SDL_SetWindowSize(window_.get(), requestedSize.x, requestedSize.y);
}

void Game::RenderSprite(const SDL_FRect& srcRect, const SDL_FRect& destRect) {
  SDL_RenderTexture(renderer_.get(), spritesheet_.get(), &srcRect, &destRect);
}
