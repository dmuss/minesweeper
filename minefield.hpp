#ifndef MINEFIELD_HPP_
#define MINEFIELD_HPP_

#include <vector>

#include "cell.hpp"

class Minefield {
 private:
  SDL_Point gridSize_ = {.x = 9, .y = 9};
  std::vector<Cell> cells_;

  Cell& getCellAt_(SDL_Point pos) {
    size_t i = static_cast<size_t>(gridSize_.x * pos.y + pos.x);
    return cells_.at(i);
  }

 public:
  Minefield() {
    for (auto i = 0; i < gridSize_.x * gridSize_.y; ++i) {
      SDL_Point pos = {
          .x = i % gridSize_.x,
          .y = i / gridSize_.x,
      };
      cells_.push_back(Cell(pos));
    }
  }

  std::vector<Cell> Cells() const { return cells_; }

  CellState RevealCell(SDL_Point pos) {
    auto& cell = getCellAt_(pos);
    cell.Reveal();
    return cell.State();
  }

  void ChangeFlag(SDL_Point pos) { getCellAt_(pos).ChangeFlag(); }
};

#endif
