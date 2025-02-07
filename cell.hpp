#ifndef CELL_HPP_
#define CELL_HPP_

#include <SDL3/SDL_rect.h>

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
  Cell(SDL_Point pos) : pos_(pos) {}

  SDL_Point Pos() const { return pos_; }
  CellState State() const { return state_; }

  void Reveal() { state_ = static_cast<CellState>(value_); }

  void ChangeFlag() {
    switch (state_) {
      case CellState::Unrevealed: {
        state_ = CellState::Flagged;
        break;
      }
      case CellState::Flagged: {
        state_ = CellState::Question;
        break;
      }
      case CellState::Question: {
        state_ = CellState::Unrevealed;
        break;
      }
      default:
        break;
    }
  }
};

#endif
