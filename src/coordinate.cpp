#include "include/coordinate.h"

Coordinate::Coordinate(int x, int y) : m_x(x), m_y(y)
{
}

int Coordinate::getX( )const{
    return m_x;
}

int Coordinate::getY() const{
    return m_y;
}

bool Coordinate::operator==(const Coordinate& otherCoordinate) const {
    return m_x == otherCoordinate.m_x && m_y == otherCoordinate.m_y;
}
