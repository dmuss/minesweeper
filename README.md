# Minesweeper
A classic minesweeper game with three levels of difficulty built with SDL. Attempt to clear the minefield by revealing all non-mine cells.

Play it online [here](https://dmuss.github.io/minesweeper).

## How to Play
Reveal cells by clicking the left mouse button. When a cell is revealed, it will display a number representing how many neighbouring cells contain a mine.

Right-clicking a cell will cycle through several "flags", allowing you to mark cells as suspected mines.

The game is won when all cells not containing mines have been revealed.

When the game is over, click anywhere in the minefield to return to the difficulty selection screen.

## Difficulty

The game has three difficulty levels, which determine the size of the minefield and the number of mines placed.

| Difficulty | Minefield Dimensions (Width x Height) | Number of Mines |
|:----------:|:-------------------------------------:|:---------------:|
| Easy       | 9 x 9                                 | 10              |
| Medium     | 16 x 16                               | 40              |
| Hard       | 30 x 16                               | 99              |


## Building

Clone this repository and build with CMake. Dependency submodules should be downloaded automatically. 

```bash
$ git clone https://github.com/dmuss/minesweeper.git
$ cd minesweeper
$ mkdir build
$ cmake -B build -S .
$ cmake --build build
```

After building, run the executable in the `build/` folder.


