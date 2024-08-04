#ifndef GAMEMANAGEMENT_H
#define GAMEMANAGEMENT_H

#include <memory>

#include "include/logic/chessboard.h"
#include "include/logic/coordinate.h"
#include "include/logic/player.h"
#include "include/logic/networkmanager.h"


class GameManagement {
public:
    GameManagement();

    void printWelcomeMessage () const;
    void displayBoard() const;
    bool getCurrentPlayer() const;
    bool makeMove(const Coordinate &from, const Coordinate &to);
    bool isGameOver();
    void announceWinner() const;

private:
    ChessBoard m_board;
    Player m_currentPlayer;

    bool isValidMove(const Coordinate &from, const Coordinate &to) const;
    void switchPlayer();
    void promotePawn(const Coordinate& coordinate);
    bool isInCheck(Player color) const;
    bool isCheckmate(Player color);
};

#endif // GAMEMANAGEMENT_H
