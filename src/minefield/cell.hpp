#ifndef CELL_HPP_
#define CELL_HPP_

#include <cstdint>
#include <functional>

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
    SDL_Point pos_;
    /// The underlying value of the cell, regardless of its state.
    ///
    /// This value will be in [0, 9], where zero through eight represents the
    /// number of mines adjacent to the cell and a value of nine that the cell
    /// is mined.
    uint8_t value_ = 0;
    /// The state of the current cell, used for determining which cell sprite to
    /// render.
    CellState state_ = CellState::Unrevealed;

  public:
    /// Create a cell at a given position.
    explicit Cell(SDL_Point pos = {.x = 0, .y = 0});

    inline bool operator==(const Cell& other) const {
      return (this->X() == other.X()) && (this->Y() == other.Y());
    }

    /// Returns the `x` coordinate of the cell.
    int X() const;
    /// Returns the `y` coordinate of the cell.
    int Y() const;
    /// Returns the position of the cell in the grid.
    SDL_Point Pos() const;
    /// Returns the cell's current render state.
    CellState State() const;
    /// Returns whether this cell is empty.
    bool IsEmpty() const;
    /// Returns whether this cell has been revealed or not.
    bool IsRevealed() const;
    /// Returns whether this cell contains a mine.
    bool IsMine() const;

    /// Sets the current cell to a mine.
    void SetMine();
    /// Sets the current cell to a empty.
    void SetEmpty();
    /// Sets the current cell to a revealed mine.
    void SetRevealedMine();
    /// Update the state of this cell reflecting the adddition of an adjacent
    /// mine.
    ///
    /// That is, adds one to the underlying value of the cell, clamping in
    /// [CellState::Empty, CellState::Mine].
    void AddAdjacentMine();
    /// Update the state of this cell reflecting the removal of an adjacent
    /// mine.
    ///
    /// That is, subtracts one from the underlying value of the cell, clamping
    /// in [CellState::Empty, CellState::Mine].
    void RemoveAdjacentMine();
    /// Reveals this current cell.
    void Reveal();
    /// Updates the flagged state of this cell.
    ///
    /// Cycles through unrevealed, flagged, and question mark render states.
    void ChangeFlag();
};

#endif
