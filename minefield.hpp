#ifndef MINEFIELD_HPP_
#define MINEFIELD_HPP_

#include <vector>

#include "cell.hpp"

class Minefield {
 private:
  SDL_Point gridSize_ = {.x = 9, .y = 9};  // TODO: Configurable.
  std::vector<Cell> cells_;

  /// Returns a reference to the cell at the provided position.
  Cell& getCellAt_(SDL_Point pos);

  /// Returns whether the given position is within the bounds of the minefield.
  bool inBounds_(SDL_Point pos);

  /// Sets the provided cell as a mine.
  void setMine_(Cell& cell);

 public:
  Minefield();

  /// Returns all of the current cells in the minefield.
  std::vector<Cell> Cells() const;

  /// Reveals the cell at the provided position in the minefield.
  CellState RevealCell(SDL_Point pos);

  /// Change the flagged state of the cell at the provided position in the
  /// minefield.
  void ChangeFlag(SDL_Point pos);
};

#endif
