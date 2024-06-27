#include "include/chesspiece.h"

#include <vector>
#include <iostream>

#include "include/chessboard.h"
#include "include/coordinate.h"


ChessPiece::ChessPiece(bool color, Coordinate coordinate)
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
