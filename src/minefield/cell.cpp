#include "cell.hpp"

#include <algorithm>

Cell::Cell(SDL_Point pos) : pos_(pos) {}

int Cell::X() const { return pos_.x; }

int Cell::Y() const { return pos_.y; }

SDL_Point Cell::Pos() const { return pos_; };

CellState Cell::State() const { return state_; }

bool Cell::IsEmpty() const {
  return value_ == static_cast<uint8_t>(CellState::Empty);
}

bool Cell::IsRevealed() const {
  return (state_ != CellState::Unrevealed) && (state_ != CellState::Flagged) &&
         (state_ != CellState::Question);
}

bool Cell::IsMine() const {
  return value_ == static_cast<uint8_t>(CellState::Mine);
}

void Cell::SetMine() { value_ = static_cast<uint8_t>(CellState::Mine); }

void Cell::SetEmpty() { value_ = static_cast<uint8_t>(CellState::Empty); }

void Cell::SetRevealedMine() {
  value_ = static_cast<uint8_t>(CellState::RevealedMine);
}

void Cell::AddAdjacentMine() {
  value_ = std::clamp(static_cast<uint8_t>(value_ + 1),
                      static_cast<uint8_t>(CellState::Empty),
                      static_cast<uint8_t>(CellState::Mine));
}

void Cell::RemoveAdjacentMine() {
  value_ = std::clamp(static_cast<uint8_t>(value_ - 1),
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
