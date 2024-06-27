#ifndef ROOK_H
#define ROOK_H

#include <iostream>

#include "include/chesspiece.h"

class Rook : public ChessPiece {
public:
    Rook(bool color, Coordinate coordinate);
    std::string getPieceSymbol() const override;
    std::vector<Coordinate> availableMoves(const ChessBoard &board) const override;
};

#endif // ROOK_H
