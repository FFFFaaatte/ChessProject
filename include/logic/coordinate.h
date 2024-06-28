#ifndef COORDINATE_H
#define COORDINATE_H


class Coordinate
{
    int m_x;
    int m_y;
public:
    Coordinate(int x, int y);
    int getX() const;
    int getY() const;
    bool operator==(const Coordinate& other) const;
};

#endif // COORDINATE_H
