#ifndef SPRITES_HPP_
#define SPRITES_HPP_

#include <array>

#include <SDL3/SDL_rect.h>

/// Source rectangles for individual sprites on the spritesheet.
class Sprites {
 private:
  static constexpr SDL_Point BUTTON_SIZE_ = {.x = 182, .y = 25};
  static constexpr uint8_t CELL_SIZE_PX_ = 26;
  static constexpr uint8_t CELL_ROWS_ = 2;
  static constexpr uint8_t CELL_COLS_ = 7;
  static constexpr uint8_t NUM_CELLS_ = CELL_ROWS_ * CELL_COLS_;

 public:
  static constexpr SDL_FRect Title = {.x = 0, .y = 102, .w = 182, .h = 21};

  static constexpr SDL_FRect ButtonUp = {
      .x = 0, .y = 52, .w = BUTTON_SIZE_.x, .h = BUTTON_SIZE_.y};

  static constexpr SDL_FRect ButtonDown = {
      .x = 0, .y = 77, .w = BUTTON_SIZE_.x, .h = BUTTON_SIZE_.y};

  static constexpr std::array Cells{[]<auto... I>(std::index_sequence<I...>) {
    return std::array<SDL_FRect, NUM_CELLS_>{(SDL_FRect{
        .x = (I % CELL_COLS_) * CELL_SIZE_PX_,
        .y = (I / CELL_COLS_) * CELL_SIZE_PX_,  // Intentional integer division.
        .w = CELL_SIZE_PX_,
        .h = CELL_SIZE_PX_,
    })...};
  }(std::make_index_sequence<NUM_CELLS_>{})};
};

#endif
