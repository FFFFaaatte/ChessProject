#ifndef BISHOP_H
#define BISHOP_H

#include <iostream>
#include "include/chesspiece.h"

class Bishop : public ChessPiece {
public:
    Bishop(bool color, Coordinate coordinate);
    std::string getPieceSymbol() const override;
    std::vector<Coordinate> availableMoves(const ChessBoard &board) const override;
};

#endif // BISHOP_H
