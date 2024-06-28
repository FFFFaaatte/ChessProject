#ifndef QUEEN_H
#define QUEEN_H

#include "include/logic/chesspiece.h"
#include "include/logic/player.h"

class Queen : public ChessPiece {
public:
    Queen(Player color, Coordinate coordinate);
    std::string getPieceSymbol() const override;
    std::vector<Coordinate> availableMoves(const ChessBoard &board) const override;
};

#endif // QUEEN_H
