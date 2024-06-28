#include <iostream>
#include <regex>

#include "include/logic/gamemanagement.h"
#include "include/chessDerivedPieces/pawn.h"
#include "include/logic/coordinate.h"


int main() {
    GameManagement game;

    std::regex moveRegex("([a-h][1-8]) to ([a-h][1-8])");

    game.printWelcomeMessage();

    while (!game.isGameOver()) {
        game.displayBoard();
        std::string move;
        std::cout << (game.getCurrentPlayer() ? "Black" : "White") << "'s move: ";
        std::getline(std::cin, move);

        std::smatch match;
        if (!std::regex_match(move, match, moveRegex)) {
            std::cout << "Use this format for input: e.g. 'e2 to e4'.\n";
            continue;
        }
        Coordinate from(7 - (match[1].str()[1] - '1'), match[1].str()[0] - 'a');
        Coordinate to(7 - (match[2].str()[1] - '1'), match[2].str()[0] - 'a');

        if (!game.makeMove(from, to))
            std::cout << "Invalid move. Please try again.\n";
    }

    game.displayBoard();
    game.announceWinner();
    return 0;
}
