#include "game_scene.hpp"

#include <cmath>

#include "../sprites.hpp"

void GameScene::OnEnter(Game& game) {
  minefield_->Reset(game.Difficulty());

  game.SetWindowSize({.x = minefield_->Width() * CELL_RENDER_SIZE_PX_,
                      .y = minefield_->Height() * CELL_RENDER_SIZE_PX_});
}

void GameScene::Update([[maybe_unused]] Game& game, MouseState mouseState) {
  if (minefield_->State() == MinefieldState::Playing) {
    SDL_Point gridPos = {
        .x = static_cast<int>(std::floor(mouseState.x / CELL_RENDER_SIZE_PX_)),
        .y = static_cast<int>(std::floor(mouseState.y / CELL_RENDER_SIZE_PX_)),
    };

    if (mouseState.leftClicked) { minefield_->RevealCell(gridPos); }

    if (mouseState.rightClicked) { minefield_->ChangeFlag(gridPos); }
  } else {
    if (mouseState.leftClicked || mouseState.rightClicked) { game.GoToMenu(); }
  }
}

void GameScene::Draw(Game& game) {
  for (const auto& cell : minefield_->Cells()) {
    const SDL_FRect destRect = {
        .x = static_cast<float>(cell.X() * CELL_RENDER_SIZE_PX_),
        .y = static_cast<float>(cell.Y() * CELL_RENDER_SIZE_PX_),
        .w = CELL_RENDER_SIZE_PX_,
        .h = CELL_RENDER_SIZE_PX_,
    };

    size_t cellSpriteIdx = static_cast<size_t>(cell.State());
    game.DrawSprite(Sprites::Cells.at(cellSpriteIdx), destRect);
  }
}

void GameScene::OnLeave([[maybe_unused]] Game& game) {}
