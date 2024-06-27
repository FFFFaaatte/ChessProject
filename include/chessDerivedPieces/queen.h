#ifndef QUEEN_H
#define QUEEN_H

#include <iostream>

#include "include/chesspiece.h"


class Queen : public ChessPiece {
public:
    Queen(bool color, Coordinate coordinate);
    std::string getPieceSymbol() const override;
    std::vector<Coordinate> availableMoves(const ChessBoard &board) const override;
};

#endif // QUEEN_H
