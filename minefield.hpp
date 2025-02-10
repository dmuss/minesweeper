#ifndef MINEFIELD_HPP_
#define MINEFIELD_HPP_

#include <array>
#include <unordered_set>
#include <vector>

#include "cell.hpp"

// TODO: Is this sufficient for what we need here?
struct Hasher {
  size_t operator()(const SDL_Point point) const {
    return std::hash<int>()(point.x) ^ std::hash<int>()(point.y);
  }
  size_t operator()(const Cell cell) const {
    return std::hash<int>()(cell.X()) ^ std::hash<int>()(cell.Y());
  }
};

constexpr bool operator==(const SDL_Point& first, const SDL_Point& second) {
  return (first.x == second.x) && (first.y == second.y);
}

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
  std::vector<Cell> cells_;

  /// Returns a reference to the cell at the provided position.
  Cell& getCellAt_(SDL_Point pos);

  /// Returns whether the given position is within the bounds of the minefield.
  bool inBounds_(SDL_Point pos);

  /// Sets the provided cell as a mine.
  void setMine_(Cell& cell);

  /// Reveals all empty cells and their neighbours.
  void floodReveal_(Cell& cell);

  /// Recursive flood reveal of all empty cells adjacent to `cell`.
  void recurseFlood_(Cell& cell, std::unordered_set<Cell, Hasher>& revealed);

  /// Reveal the all neighbouring cells to those contained in `revealed`.
  void revealNeighbours_(const std::unordered_set<Cell, Hasher>& revealed);

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
