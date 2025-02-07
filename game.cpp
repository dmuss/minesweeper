#include "game.hpp"

#include <cmath>
#include <cstdlib>

#include "sprites.hpp"

bool Game::isInit_ = false;

Game::Game()
    : running_(true),
      window_(SDL3::CreateWindow("minesweeper",
                                 CELL_GRID_WIDTH_ * CELL_RENDER_SIZE_PX_,
                                 CELL_GRID_HEIGHT_ * CELL_RENDER_SIZE_PX_, 0)),
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

  currFrameMS_ = SDL_GetTicks();
  deltaMS_ = currFrameMS_ - lastFrameMS_;
  lastFrameMS_ = currFrameMS_;

  SDL_RenderClear(renderer_.get());
  for (const auto& cell : minefield_.Cells()) {
    SDL_FRect destRect = {
        .x = static_cast<float>(cell.Pos().x * CELL_RENDER_SIZE_PX_),
        .y = static_cast<float>(cell.Pos().y * CELL_RENDER_SIZE_PX_),
        .w = CELL_RENDER_SIZE_PX_,
        .h = CELL_RENDER_SIZE_PX_,
    };
    SDL_RenderTexture(renderer_.get(), spritesheet_.get(),
                      &Sprites::Cells.at(static_cast<size_t>(cell.State())),
                      &destRect);
  }
  SDL_RenderPresent(renderer_.get());

  if (deltaMS_ < TARGET_FRAME_TIME_MS_) {
    SDL_Delay(static_cast<uint32_t>(TARGET_FRAME_TIME_MS_ - deltaMS_));
  }

  return SDL_APP_CONTINUE;
}
