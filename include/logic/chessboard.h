#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <iostream>
#include <vector>
#include <memory>

#include "include/logic/coordinate.h"
#include "include/logic/chesspiece.h"
#include "include/logic/player.h"


class ChessPiece;

class ChessBoard {
public:
    using BoardType = std::vector<std::vector<std::shared_ptr<ChessPiece>>>;

    ChessBoard();

    std::string getString() const;
    BoardType getPieces() const;
    std::shared_ptr<ChessPiece> getPiece(const Coordinate &coordinate) const;
    void setPiece (const Coordinate &coordinate, std::shared_ptr<ChessPiece> piece);
    std::shared_ptr<ChessPiece> movePiece(const Coordinate &from, const Coordinate &to);
    bool isInChessBoard(const Coordinate &coordinate) const; 
    bool isEmpty(const Coordinate &coordinate) const;
    bool isOpponentPiece(const Coordinate &coordinate, Player color) const;
    Coordinate findKing(const Player color) const;

private:
    BoardType m_pieces;
};

#endif // CHESSBOARD_H
