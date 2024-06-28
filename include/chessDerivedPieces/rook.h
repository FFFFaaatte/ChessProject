#ifndef ROOK_H
#define ROOK_H

#include "include/logic/chesspiece.h"
#include "include/logic/player.h"

class Rook : public ChessPiece {
public:
    Rook(Player color, Coordinate coordinate);
    std::string getPieceSymbol() const override;
    std::vector<Coordinate> availableMoves(const ChessBoard &board) const override;
};

#endif // ROOK_H
