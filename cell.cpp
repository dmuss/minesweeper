#include "cell.hpp"

#include <algorithm>

Cell::Cell(SDL_Point pos) : pos_(pos) {}

int Cell::X() const { return pos_.x; }

int Cell::Y() const { return pos_.y; }

CellState Cell::State() const { return state_; }

bool Cell::Empty() const {
  return value_ == static_cast<uint8_t>(CellState::Empty);
}

void Cell::SetMine() { value_ = static_cast<uint8_t>(CellState::Mine); }

void Cell::AddAdjacentMine() {
  // TODO: Can we avoid these casts?
  value_ = std::clamp(static_cast<uint8_t>(value_ + 1),
                      static_cast<uint8_t>(CellState::Empty),
                      static_cast<uint8_t>(CellState::Mine));
}

void Cell::Reveal() { state_ = static_cast<CellState>(value_); }

void Cell::ChangeFlag() {
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
