#ifndef BISHOP_H
#define BISHOP_H

#include "include/logic/chesspiece.h"
#include "include/logic/player.h"

class Bishop : public ChessPiece {
public:
    Bishop(Player color, Coordinate coordinate);
    std::string getPieceSymbol() const override;
    std::vector<Coordinate> availableMoves(const ChessBoard &board) const override;
};

#endif // BISHOP_H
