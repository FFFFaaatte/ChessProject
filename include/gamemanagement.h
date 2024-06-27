#ifndef GAMEMANAGEMENT_H
#define GAMEMANAGEMENT_H

#include <memory>

#include "chessboard.h"
#include "include/coordinate.h"


class GameManagement {
public:
    GameManagement();

    bool makeMove(const Coordinate &from, const Coordinate &to);
    bool getCurrentPlayer() const;
    bool isGameOver();
    void displayBoard() const;
    void announceWinner() const;

private:
    ChessBoard m_board;
    bool m_currentPlayer;

    bool isValidMove(const Coordinate &from, const Coordinate &to) const;
    bool isInCheck(bool color) const;
    bool isCheckmate(bool color);
    void switchPlayer();
    void promotePawn(const Coordinate& coordinate);
};

#endif // GAMEMANAGEMENT_H
