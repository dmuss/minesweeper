#ifndef POINT_HASHER_HPP_
#define POINT_HASHER_HPP_

#include <cstddef>
#include <functional>

#include <SDL3/SDL_rect.h>

#include "minefield/cell.hpp"

/// Hash function for two-dimensional points.
///
/// Uses the Cantor pairing function to produce an increasing integer value for
/// every coordinate pair.
template <> struct std::hash<SDL_Point> {
    std::size_t operator()(const SDL_Point& point) const {
      return static_cast<std::size_t>(
          (point.x + point.y + 1) * (point.x + point.y) * 0.5 + point.y);
    }
};

/// Hash function for Minefield cells.
///
/// Uses the Cantor pairing function on the cell's position.
template <> struct std::hash<Cell> {
    std::size_t operator()(const Cell& cell) const {
      return std::hash<SDL_Point>()(cell.Pos());
    }
};

#endif
