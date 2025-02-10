#ifndef CELL_HPP_
#define CELL_HPP_

// TODO: Move SDL headers into single header file to suppress old-style-cast
// warnings? Is there a way to ignore warnings for certain headers?
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wold-style-cast"
#include <SDL3/SDL_rect.h>
#pragma GCC diagnostic pop

/// Represents the current state of the cell as rendered in the minefield.
///
/// The underlying integral value of this enumeration is used to index into the
/// cell source rectangle array in the spritesheet.
enum class CellState : uint8_t {
  Empty,
  One,
  Two,
  Three,
  Four,
  Five,
  Six,
  Seven,
  Eight,
  Mine,
  RevealedMine,
  Unrevealed,
  Flagged,
  Question,
};

/// A cell in the minefield grid.
class Cell {
 private:
  /// This cell's coordinate position in the minefield.
  SDL_Point pos_ = {.x = 0, .y = 0};
  /// The underlying value of the cell, regardless of its state.
  ///
  /// This value will be in [0, 9], where zero through eight represents the
  /// number of mines adjacent to the cell and a value of nine that the cell is
  /// mined.
  uint8_t value_ = 0;
  /// The state of the current cell, used for determining which cell sprite to
  /// render.
  CellState state_ = CellState::Unrevealed;

 public:
  /// Create a cell at a given position.
  Cell(SDL_Point pos);

  /// Returns the `x` coordinate of the cell.
  int X() const;
  /// Returns the `y` coordinate of the cell.
  int Y() const;
  /// Returns the cell's current render state.
  CellState State() const;
  /// Sets the current cell as a mine.
  void SetMine();
  /// Adds an adjacent mine to this cell, updating its value.
  ///
  /// That is, adds one to the underlying value of the cell, clamping in [0, 9].
  void AddAdjacentMine();
  /// Reveals this current cell.
  void Reveal();
  /// Updates the flagged state of this cell.
  ///
  /// Cycles through unrevealed, flagged, and question mark render states.
  void ChangeFlag();
};

#endif
