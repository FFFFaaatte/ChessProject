#ifndef PAWN_H
#define PAWN_H

#include "include/logic/chesspiece.h"
#include "include/logic/player.h"

class Pawn : public ChessPiece {
public:
    Pawn(Player color, Coordinate coordinate);
    std::string getPieceSymbol() const override;
    std::vector<Coordinate> availableMoves(const ChessBoard &board) const override;
};

#endif // PAWN_H
