# Tic-Tac-Toe in C++

A two-player Tic-Tac-Toe game for the console, written in C++17.
Players take turns placing `X` and `O` on a 3x3 board. The first player to get three in a row
(horizontally, vertically or diagonally) wins; if the board fills up with no winner, the match is a draw.

The project started as a plain C program (see [`c-version/`](c-version/)) and was then rewritten
in C++ using classes, pointers, references and the standard library.

## How to build and run

Requires a C++ compiler with C++11 support or later (tested with `g++ -std=c++17`).

```bash
g++ -std=c++17 -Wall -Wextra main.cpp -o tris
./tris
```

## How to play

1. Enter the names of the two players (`X` goes first).
2. On your turn, type the **row** and the **column** of the cell, from 1 to 3, separated by a space
   (for example `2 2` is the center).
3. After each match you are asked `Play again? (y/n)`. When you stop, a summary of all the matches is printed.

```
Name of player X: stefan
Name of player O: marco

   |   |
---|---|---
   |   |
---|---|---
   |   |

stefan (X), enter row and column (from 1 to 3): 2 2
```

## Features

- Two players with custom names
- Win and draw detection
- Input validation: out-of-range numbers, already occupied cells and non-numeric input are rejected
  without changing the turn; extra characters typed on the same line are ignored
- Multiple matches in a row
- Results of every match stored in memory and printed as a summary at the end

## Code structure

| Element | Role |
|---|---|
| `class Player` | Stores the name and the symbol (`X` or `O`) of a player |
| `class Board` | Holds the 3x3 grid and the move counter; places moves, checks for a winner or a full board, prints the grid |
| `class Game` | Runs one match: handles turns and returns the result |
| `struct MatchResult` | Result of one match: the two player names, the winner (or `"Draw"`) and the number of moves |
| `readMove()` | Reads row and column from the user and returns them by reference |

C++ concepts used:

- **Classes and encapsulation**: private data, public methods, constructors with initializer lists, `const` getters
- **Pointer**: `Player* current` always points to the player whose turn it is, and `switchTurn()` just moves the pointer
- **References**: `int&` parameters in `readMove()`, `const MatchResult&` in the summary loop
- **`std::vector<MatchResult>`** to store the matches, with `push_back` and a range-based `for` loop
- **`struct`** to group the data of a match

## Repository layout

```
.
├── main.cpp        # C++ version (main project)
├── c-version/
│   └── Main.C      # original C version, the starting point
└── README.md
```

## Possible improvements

- Statistics computed from the stored results (wins per player, draws, win rate) using `std::map`
- Leaderboard saved to a file and loaded at startup (file I/O with `ofstream` / `ifstream`)
