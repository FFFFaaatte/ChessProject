#include "include/logic/chesspiece.h"

#include <vector>
#include <iostream>

#include "include/logic/chessboard.h"
#include "include/logic/coordinate.h"


ChessPiece::ChessPiece(Player color, Coordinate coordinate)
    : m_color(color), m_coordinate(coordinate) {}

bool ChessPiece::getColor() const {
    return m_color;
}

Coordinate ChessPiece::getCoordinate() const {
    return m_coordinate;
}

void ChessPiece::setCoordinate(Coordinate coordinate) {
    m_coordinate = coordinate;
}
