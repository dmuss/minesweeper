#ifndef MINEFIELD_HPP_
#define MINEFIELD_HPP_

#include <array>
#include <memory>
#include <unordered_set>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wold-style-cast"
#include <SDL3/SDL_rect.h>
#pragma GCC diagnostic pop

#include "cell.hpp"
#include "../game.hpp"

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
    bool isFirstClick_ = true;
    SDL_Point gridSize_;
    MinefieldState state_ = MinefieldState::Playing;
    uint8_t numMines_;
    uint16_t numRevealedCells_;
    std::vector<Cell> cells_;

    /// Resets the minefield based on the requested difficulty.
    ///
    /// \param difficulty The difficulty to reset the minefield to.
    void reset_(GameDifficulty difficulty);

    /// Reveals the whole minefield.
    void reveal_();

    /// Returns a reference to the cell at the provided position.
    Cell& getCellAt_(SDL_Point pos);

    /// Reveals the provided cell and increments the number of revealed cells.
    void revealCell_(Cell& cell);

    /// Returns whether the given position is within the bounds of the
    /// minefield.
    bool inBounds_(SDL_Point pos);

    /// Sets the provided cell as a mine.
    void setMine_(Cell& cell);

    /// Removes a mine at the provided cell.
    void removeMine_(Cell& cell);

    /// Reveals all empty cells and their neighbours.
    void floodReveal_(Cell& cell);

    /// Recursive flood reveal of all empty cells adjacent to `cell`.
    void recurseFlood_(Cell& cell, std::unordered_set<Cell>& revealed);

    /// Reveal the all neighbouring cells to those contained in `revealed`.
    void revealNeighbours_(const std::unordered_set<Cell>& revealed);

    /// Starting at the top and moving left-to-right across each row of the
    /// minefield, set the first non-mine cell to a mine.
    void setMineNextAvailablePos_();

  public:
    /// Resets the minefield to the provided difficulty.
    ///
    /// \param difficulty The difficulty to set the minefield up for.
    void Reset(GameDifficulty difficulty);

    /// Returns the current play state of the minefield.
    MinefieldState State() const;

    // Returns the minefield's width.
    int Width() const;

    // Returns the minefield's height.
    int Height() const;

    /// Returns all of the current cells in the minefield.
    std::vector<Cell> Cells() const;

    /// Reveals the cell at the provided position in the minefield.
    ///
    /// \ param pos The coordinate position of the cell to reveal.
    void RevealCell(SDL_Point pos);

    /// Change the flagged state of the cell at the provided position in the
    /// minefield.
    ///
    /// \ param pos The coordinate position of the cell to flag.
    void ChangeFlag(SDL_Point pos);
};

using MinefieldUPtr = std::unique_ptr<Minefield>;

#endif
