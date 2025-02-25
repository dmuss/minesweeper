#include "minefield.hpp"

#include <random>

#include "../sdl_helpers.hpp"
#include "../hashers.hpp"

void Minefield::reset_(GameDifficulty difficulty) {
  numRevealedCells_ = 0;
  isFirstClick_     = true;
  state_            = MinefieldState::Playing;

  switch (difficulty) {
    case GameDifficulty::Easy: {
      gridSize_.x = 9;
      gridSize_.y = 9;

      numMines_ = 10;
      break;
    }
    case GameDifficulty::Medium: {
      gridSize_.x = 16;
      gridSize_.y = 16;

      numMines_ = 40;
      break;
    }
    case GameDifficulty::Hard: {
      gridSize_.x = 30;
      gridSize_.y = 16;

      numMines_ = 99;
      break;
    }
    default:
      break;
  }

  SDL_assert(gridSize_.x >= 0);
  SDL_assert(gridSize_.y >= 0);
  SDL_assert(numMines_ > 0);

  cells_.resize(static_cast<size_t>(gridSize_.x * gridSize_.y));

  // Re-init the cells with proper positions.
  for (size_t i = 0; i < cells_.size(); ++i) {
    const SDL_Point pos = {
        .x = static_cast<int>(i % static_cast<size_t>(gridSize_.x)),
        .y = static_cast<int>(i / static_cast<size_t>(gridSize_.x)),
    };
    cells_[i] = Cell(pos);
  }

  // Set mines.
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<uint8_t> randX(
      0, static_cast<uint8_t>(gridSize_.x - 1));
  std::uniform_int_distribution<uint8_t> randY(
      0, static_cast<uint8_t>(gridSize_.y - 1));

  std::unordered_set<SDL_Point> mines{};
  while (mines.size() < numMines_) {
    SDL_Point pos = {
        .x = randX(gen),
        .y = randY(gen),
    };

    auto [_, inserted] = mines.insert(pos);
    if (inserted) { setMine_(getCellAt_(pos)); }
  }
}

void Minefield::reveal_() {
  for (auto& cell : cells_) { cell.Reveal(); }
}

Cell& Minefield::getCellAt_(SDL_Point pos) {
  size_t i = static_cast<size_t>(gridSize_.x * pos.y + pos.x);
  return cells_.at(i);
}

void Minefield::revealCell_(Cell& cell) {
  if (!cell.IsRevealed()) {
    cell.Reveal();
    ++numRevealedCells_;
  }
}

bool Minefield::inBounds_(SDL_Point pos) {
  return (pos.x >= 0 && pos.x < gridSize_.x) &&
         (pos.y >= 0 && pos.y < gridSize_.y);
}

void Minefield::setMine_(Cell& cell) {
  cell.SetMine();

  for (const auto& dir : dirs_) {
    SDL_Point neighbour = {
        .x = cell.X() + dir.x,
        .y = cell.Y() + dir.y,
    };

    if (inBounds_(neighbour)) { getCellAt_(neighbour).AddAdjacentMine(); }
  }
}

void Minefield::removeMine_(Cell& cell) {
  cell.SetEmpty();

  for (const auto& dir : dirs_) {
    SDL_Point neighbourPos = {
        .x = cell.X() + dir.x,
        .y = cell.Y() + dir.y,
    };

    if (inBounds_(neighbourPos)) {
      auto& neighbourCell = getCellAt_(neighbourPos);
      if (neighbourCell.IsMine()) {
        cell.AddAdjacentMine();
      } else {
        neighbourCell.RemoveAdjacentMine();
      }
    }
  }
}

void Minefield::floodReveal_(Cell& cell) {
  std::unordered_set<Cell> revealed{};
  recurseFlood_(cell, revealed);
  revealNeighbours_(revealed);
}

void Minefield::recurseFlood_(Cell& cell, std::unordered_set<Cell>& revealed) {
  if (revealed.contains(cell) || !cell.IsEmpty()) { return; }

  revealCell_(cell);

  revealed.insert(cell);

  for (const auto& dir : dirs_) {
    SDL_Point neighbourPos{
        .x = cell.X() + dir.x,
        .y = cell.Y() + dir.y,
    };

    if (inBounds_(neighbourPos)) {
      recurseFlood_(getCellAt_(neighbourPos), revealed);
    }
  }
}

void Minefield::revealNeighbours_(const std::unordered_set<Cell>& revealed) {
  for (const auto& cell : revealed) {
    for (const auto& dir : dirs_) {
      SDL_Point neighbourPos{
          .x = cell.X() + dir.x,
          .y = cell.Y() + dir.y,
      };

      if (inBounds_(neighbourPos)) { revealCell_(getCellAt_(neighbourPos)); }
    }
  }
}

void Minefield::setMineNextAvailablePos_() {
  for (auto& cell : cells_) {
    if (!cell.IsMine()) {
      setMine_(cell);
      break;
    }
  }
}

void Minefield::Reset(GameDifficulty difficulty) { reset_(difficulty); }

MinefieldState Minefield::State() const { return state_; }

int Minefield::Width() const { return gridSize_.x; }

int Minefield::Height() const { return gridSize_.y; }

std::vector<Cell> Minefield::Cells() const { return cells_; }

void Minefield::RevealCell(SDL_Point pos) {
  auto& cell = getCellAt_(pos);

  if (isFirstClick_) {
    isFirstClick_ = false;

    if (cell.IsMine()) {
      setMineNextAvailablePos_();
      removeMine_(cell);
    }
  }

  revealCell_(cell);

  if (cell.IsMine()) {
    state_ = MinefieldState::Lost;
    cell.SetRevealedMine();
    reveal_();
  }

  if (cell.IsEmpty()) { floodReveal_(cell); }

  if (cells_.size() - numMines_ - numRevealedCells_ == 0) {
    state_ = MinefieldState::Won;
    reveal_();
  }
}

void Minefield::ChangeFlag(SDL_Point pos) { getCellAt_(pos).ChangeFlag(); }
