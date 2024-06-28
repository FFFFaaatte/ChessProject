# Chess Game

Welcome to my Chess Game project! This command-line chess game is built in C++ using object-oriented programming principles, and Qt for development. It's designed to be extendable, so you can easily add new features or tweak existing ones.

![play-chess](https://github.com/FFFFaaatte/ChessProject/assets/98740260/3aa8f984-e53c-4f1b-aff9-fdf981795cd6)

## Features

- **Full Chess Rules:** Move pieces according to standard chess rules.
- **Special logic:** Includes pawn promotion.
- **Check and Checkmate Detection:** Alerts you when a player is in check or checkmate.
- **Command-Line Interface:** Play chess right in your terminal.

## How It Works

### Class Design

1. **ChessPiece:** 
   - Base class for all chess pieces.
   - Virtual method to get all possible moves for the piece.

2. **Derived Classes:** 
   - Specific classes for King, Queen, Rook, Bishop, Knight, and Pawn.

3. **ChessBoard:**
   - Manages the board and piece positions.
   - Handles move validation, piece placement, and game state checks.

4. **GameManagement:**
   - Manages the overall game flow.
   - Handles player moves and checks for check and checkmate.
### Main Gameplay

- **Initialize Board:** Sets up pieces in their starting positions.
- **Move Pieces:** Enter moves in standard chess notation (e.g., "e2 to e4").
- **Check Game State:** Automatically checks for check and checkmate after each move.

## Getting Started

### Prerequisites

- A C++ compiler that supports C++11 or later.

### Building the Game

1. Clone the repository.

2. Compile the code.

3. Run the game.

### Playing the Game

- **Input Moves:** Type moves in the format "e2 to e4".
- **Game Flow:** The game will handle move validation and check for special conditions like check and checkmate.
- **Promotions:** When a pawn reaches the opposite end, you'll be prompted to choose a piece for promotion.

## Example Moves

To test the game, you can try this sequence of moves that leads to checkmate:

1. `e2 to e4`
2. `e7 to e5`
3. `d1 to h5`
4. `b8 to c6`
5. `f1 to c4`
6. `g8 to f6`
7. `h5 to f7` (Checkmate)

## License

This project is licensed under the Apache License 2.0. See the [LICENSE](LICENSE) file for details.

