#ifndef MINEFIELD_HPP_
#define MINEFIELD_HPP_

#include <vector>

#include "cell.hpp"

class Minefield {
 private:
  SDL_Point gridSize_ = {.x = 9, .y = 9};
  std::vector<Cell> cells_;

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
};

#endif
