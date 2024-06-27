#ifndef KING_H
#define KING_H
#include "include/chesspiece.h"

class King : public ChessPiece {
public:
    King(bool color, Coordinate coordinate);
    std::string getPieceSymbol() const override;
    std::vector<Coordinate> availableMoves(const ChessBoard &board) const override;
};

#endif // KING_H
