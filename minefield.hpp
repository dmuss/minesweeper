#ifndef MINEFIELD_HPP_
#define MINEFIELD_HPP_

#include <array>
#include <unordered_set>
#include <vector>

#include "cell.hpp"

enum class MinefieldState : uint8_t { Playing, Won, Lost };

class Minefield {
 private:
  /// Array of directions to get neighbouring cells.
  static constexpr std::array<SDL_Point, 8> dirs_{
      SDL_Point{.x = -1, .y = 0}, SDL_Point{.x = -1, .y = -1},
      SDL_Point{.x = 0, .y = -1}, SDL_Point{.x = 1, .y = -1},
      SDL_Point{.x = 1, .y = 0},  SDL_Point{.x = 1, .y = 1},
      SDL_Point{.x = 0, .y = 1},  SDL_Point{.x = -1, .y = 1},
  };
  SDL_Point gridSize_ = {.x = 9, .y = 9};  // TODO: Configurable.
  MinefieldState state_ = MinefieldState::Playing;
  uint8_t numMines_ = 10;
  uint16_t numRevealedCells_ = 0;
  std::vector<Cell> cells_;

  /// Reveals the whole minefield.
  void reveal_();

  /// Returns a reference to the cell at the provided position.
  Cell& getCellAt_(SDL_Point pos);

  /// Reveals the provided cell and increments the number of revealed cells.
  void revealCell_(Cell& cell);

  /// Returns whether the given position is within the bounds of the minefield.
  bool inBounds_(SDL_Point pos);

  /// Sets the provided cell as a mine.
  void setMine_(Cell& cell);

  /// Reveals all empty cells and their neighbours.
  void floodReveal_(Cell& cell);

  /// Recursive flood reveal of all empty cells adjacent to `cell`.
  void recurseFlood_(Cell& cell, std::unordered_set<Cell, CellHash>& revealed);

  /// Reveal the all neighbouring cells to those contained in `revealed`.
  void revealNeighbours_(const std::unordered_set<Cell, CellHash>& revealed);

 public:
  Minefield();

  MinefieldState State() const;

  /// Returns all of the current cells in the minefield.
  std::vector<Cell> Cells() const;

  /// Reveals the cell at the provided position in the minefield.
  void RevealCell(SDL_Point pos);

  /// Change the flagged state of the cell at the provided position in the
  /// minefield.
  void ChangeFlag(SDL_Point pos);
};

#endif
