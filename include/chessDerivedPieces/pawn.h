#ifndef PAWN_H
#define PAWN_H

#include <iostream>

#include "include/chesspiece.h"

class Pawn : public ChessPiece {
public:
    Pawn(bool color, Coordinate coordinate);
    std::string getPieceSymbol() const override;
    std::vector<Coordinate> availableMoves(const ChessBoard &board) const override;
};

#endif // PAWN_H
