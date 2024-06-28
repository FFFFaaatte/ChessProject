#ifndef KING_H
#define KING_H

#include "include/logic/chesspiece.h"
#include "include/logic/player.h"

class King : public ChessPiece {
public:
    King(Player color, Coordinate coordinate);
    std::string getPieceSymbol() const override;
    std::vector<Coordinate> availableMoves(const ChessBoard &board) const override;
};

#endif // KING_H
