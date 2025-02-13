#include "game.hpp"

#include <cmath>
#include <cstdlib>
#include <ctime>

#include "scenes/scene_manager.hpp"

bool Game::isInit_ = false;

Game::Game()
    : window_(SDL3::CreateWindow("minesweeper", 0, 0, 0)),
      renderer_(SDL3::CreateRenderer(window_.get(), nullptr)),
      spritesheet_(
          SDL3::CreateTextureFromImage(renderer_.get(), "spritesheet.png")),
      font_(SDL3::CreateFont("SILKSCREENFONT.TTF", DEFAULT_FONT_PT_SIZE_)),
      running_(true),
      difficulty_(GameDifficulty::Easy),
      sceneManager_{*this, Scene::Menu} {
  SDL_assert(SDL_WasInit(SDL_INIT_VIDEO));
  SDL_assert(!isInit_);
  isInit_ = true;

  SDL_SetTextureScaleMode(spritesheet_.get(), SDL_SCALEMODE_NEAREST);
}

void Game::HandleMouseEvent() {
  mouse_.Update();
  sceneManager_.Update(mouse_.State());
}

SDL_AppResult Game::Tick() {
  if (!running_) { return SDL_APP_SUCCESS; }

  currFrameMS_ = SDL_GetTicks();
  deltaMS_ = currFrameMS_ - lastFrameMS_;
  lastFrameMS_ = currFrameMS_;

  SDL_RenderClear(renderer_.get());
  sceneManager_.Draw();
  SDL_RenderPresent(renderer_.get());

  if (deltaMS_ < TARGET_FRAME_TIME_MS_) {
    SDL_Delay(static_cast<uint32_t>(TARGET_FRAME_TIME_MS_ - deltaMS_));
  }

  return SDL_APP_CONTINUE;
}

GameDifficulty Game::Difficulty() const { return difficulty_; }

void Game::StartGame(GameDifficulty difficulty) {
  difficulty_ = difficulty;
  sceneManager_.SwitchScene(Scene::Game);
}

void Game::GoToMenu() { sceneManager_.SwitchScene(Scene::Menu); }

void Game::Quit() { running_ = false; }

void Game::SetWindowSize(SDL_Point requestedSize) {
  // TODO: SDL error checks through helper/macro.
  if (!SDL_SetWindowSize(window_.get(), requestedSize.x, requestedSize.y)) {
    SDL_Log("Failed to set window size: %s", SDL_GetError());
    running_ = false;
  };
}

void Game::RenderSprite(SDL_FRect srcRect, SDL_FRect destRect) {
  SDL_RenderTexture(renderer_.get(), spritesheet_.get(), &srcRect, &destRect);
}

void Game::RenderText(const std::string& str, SDL_FRect rect, SDL_Color color,
                      float ptSize) {
  if (textTextures_.find(str) == textTextures_.end()) {
    auto surface =
        SDL3::CreateBlendedTextSurface(font_.get(), str.c_str(), 0, color);

    textTextures_.insert(
        {str, SDL3::CreateTextureFromSurface(renderer_.get(), surface.get())});
  }

  TTF_SetFontSize(font_.get(), ptSize);

  int textWidth{0};
  int textHeight{0};
  TTF_GetStringSize(font_.get(), str.c_str(), 0, &textWidth, &textHeight);

  const SDL_FRect textRect = {
      .x = static_cast<float>(rect.x + (rect.w / 2.0) - (textWidth / 2.0)),
      .y = static_cast<float>(rect.y + (rect.h / 2.0) - (textHeight / 2.0)),
      .w = static_cast<float>(textWidth),
      .h = static_cast<float>(textHeight),
  };

  SDL_RenderTexture(renderer_.get(), textTextures_.at(str).get(), nullptr,
                    &textRect);
}

void Game::SetTextureColorMod(SDL_Color color) {
  SDL_SetTextureColorMod(spritesheet_.get(), color.r, color.g, color.b);
}
