#include "minefield.hpp"

#include <random>

#include "sdl_helpers.hpp"

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
    SDL_Point neighbour = {
        .x = cell.X() + dir.x,
        .y = cell.Y() + dir.y,
    };

    if (inBounds_(neighbour)) { getCellAt_(neighbour).RemoveAdjacentMine(); }
  }
}

void Minefield::floodReveal_(Cell& cell) {
  std::unordered_set<Cell, CellHash> revealed{};
  recurseFlood_(cell, revealed);
  revealNeighbours_(revealed);
}

void Minefield::recurseFlood_(Cell& cell,
                              std::unordered_set<Cell, CellHash>& revealed) {
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

void Minefield::revealNeighbours_(
    const std::unordered_set<Cell, CellHash>& revealed) {
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

void Minefield::moveMineToNextAvailablePos_() {
  for (auto& cell : cells_) {
    if (!cell.IsMine()) {
      setMine_(cell);
      break;
    }
  }
}

Minefield::Minefield() {
  // Create grid.
  for (auto i = 0; i < gridSize_.x * gridSize_.y; ++i) {
    SDL_Point pos = {
        .x = i % gridSize_.x,
        .y = i / gridSize_.x,
    };
    cells_.push_back(Cell(pos));
  }

  // Set mines.
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<uint8_t> randX(
      0, static_cast<uint8_t>(gridSize_.x - 1));
  std::uniform_int_distribution<uint8_t> randY(
      0, static_cast<uint8_t>(gridSize_.y - 1));

  std::unordered_set<SDL_Point, SDLPointHash> mines{};
  while (mines.size() < numMines_) {
    SDL_Point pos = {
        .x = randX(gen),
        .y = randY(gen),
    };

    auto [_, inserted] = mines.insert(pos);
    if (inserted) { setMine_(getCellAt_(pos)); }
  }
}

MinefieldState Minefield::State() const { return state_; }

std::vector<Cell> Minefield::Cells() const { return cells_; }

void Minefield::RevealCell(SDL_Point pos) {
  auto& cell = getCellAt_(pos);

  if (isFirstClick_) {
    isFirstClick_ = false;

    if (cell.IsMine()) {
      removeMine_(cell);
      moveMineToNextAvailablePos_();
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
