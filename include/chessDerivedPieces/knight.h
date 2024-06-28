#ifndef KNIGHT_H
#define KNIGHT_H

#include "include/logic/chesspiece.h"
#include "include/logic/player.h"

class Knight : public ChessPiece {
public:
    Knight(Player color, Coordinate coordinate);
    std::string getPieceSymbol() const override;
    std::vector<Coordinate> availableMoves(const ChessBoard &board) const override;
};

#endif // KNIGHT_H
