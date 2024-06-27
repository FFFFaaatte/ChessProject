#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <iostream>
#include <vector>

#include "include/chessboard.h"
#include "include/coordinate.h"

class ChessBoard;

class ChessPiece {
protected:
    bool m_color; // 0 : white & 1 : black
    Coordinate m_coordinate;

public:
    ChessPiece(bool color, Coordinate coordinate);
    virtual ~ChessPiece() = default;

    bool getColor() const;
    Coordinate getCoordinate() const;
    void setCoordinate(Coordinate coordinate);
    virtual std::string getPieceSymbol() const = 0;
    virtual std::vector<Coordinate> availableMoves(const ChessBoard &board) const = 0;
};

#endif // CHESSPIECE_H
