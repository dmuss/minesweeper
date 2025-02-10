#include "minefield.hpp"

#include <array>
#include <random>
#include <unordered_set>

// TODO: Is this sufficient for what we need here?
struct PointHasher {
  size_t operator()(const SDL_Point point) const {
    return std::hash<int>()(point.x) ^ std::hash<int>()(point.y);
  }
};

constexpr bool operator==(const SDL_Point& first, const SDL_Point& second) {
  return (first.x == second.x) && (first.y == second.y);
}

Cell& Minefield::getCellAt_(SDL_Point pos) {
  size_t i = static_cast<size_t>(gridSize_.x * pos.y + pos.x);
  return cells_.at(i);
}

bool Minefield::inBounds_(SDL_Point pos) {
  return (pos.x >= 0 && pos.x < gridSize_.x) &&
         (pos.y >= 0 && pos.y < gridSize_.y);
}

void Minefield::setMine_(Cell& cell) {
  cell.SetMine();

  constexpr std::array<SDL_Point, 8> dirs{
      SDL_Point{.x = -1, .y = 0}, SDL_Point{.x = -1, .y = -1},
      SDL_Point{.x = 0, .y = -1}, SDL_Point{.x = 1, .y = -1},
      SDL_Point{.x = 1, .y = 0},  SDL_Point{.x = 1, .y = 1},
      SDL_Point{.x = 0, .y = 1},  SDL_Point{.x = -1, .y = 1},
  };

  for (const auto& dir : dirs) {
    SDL_Point neighbour = {
        .x = cell.X() + dir.x,
        .y = cell.Y() + dir.y,
    };

    if (inBounds_(neighbour)) { getCellAt_(neighbour).AddAdjacentMine(); }
  }
}

Minefield::Minefield() {
  // Create grid.
  for (auto i = 0; i < gridSize_.x * gridSize_.y; ++i) {
    SDL_Point pos = {
        .x = i % gridSize_.x,
        .y = i / gridSize_.x,
    };
    cells_.push_back(Cell(pos));
  }

  // Set mines.
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<uint8_t> randX(
      0, static_cast<uint8_t>(gridSize_.x - 1));
  std::uniform_int_distribution<uint8_t> randY(
      0, static_cast<uint8_t>(gridSize_.y - 1));

  std::unordered_set<SDL_Point, PointHasher> mines{};
  while (mines.size() < 10) {  // TODO: Remove magic number.
    SDL_Point pos = {
        .x = randX(gen),
        .y = randY(gen),
    };

    auto [_, inserted] = mines.insert(pos);
    if (inserted) { setMine_(getCellAt_(pos)); }
  }

  // TODO: temporarily reveal all cells
  for (auto& cell : cells_) { cell.Reveal(); }
}

std::vector<Cell> Minefield::Cells() const { return cells_; }

CellState Minefield::RevealCell(SDL_Point pos) {
  auto& cell = getCellAt_(pos);
  cell.Reveal();
  return cell.State();
}

void Minefield::ChangeFlag(SDL_Point pos) { getCellAt_(pos).ChangeFlag(); }
