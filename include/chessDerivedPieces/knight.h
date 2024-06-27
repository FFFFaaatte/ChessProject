#ifndef KNIGHT_H
#define KNIGHT_H

#include<iostream>

#include "include/chesspiece.h"

class Knight : public ChessPiece {
public:
    Knight(bool color, Coordinate coordinate);
    std::string getPieceSymbol() const override;
    std::vector<Coordinate> availableMoves(const ChessBoard &board) const override;
};

#endif // KNIGHT_H
