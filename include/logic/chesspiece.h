#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <iostream>
#include <vector>

#include "include/logic/chessboard.h"
#include "include/logic/coordinate.h"
#include "include/logic/player.h"

class ChessBoard;

class ChessPiece {
protected:
    Player m_color;
    Coordinate m_coordinate;

public:
    ChessPiece(Player color, Coordinate coordinate);
    virtual ~ChessPiece() = default;

    bool getColor() const;
    Coordinate getCoordinate() const;
    void setCoordinate(Coordinate coordinate);
    virtual std::string getPieceSymbol() const = 0;
    virtual std::vector<Coordinate> availableMoves(const ChessBoard &board) const = 0;
};

#endif // CHESSPIECE_H
