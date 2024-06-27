#include "include/chessDerivedPieces/pawn.h"

#include <vector>
#include <iostream>

#include "include/coordinate.h"

Pawn::Pawn(bool color, Coordinate coordinate) : ChessPiece(color, coordinate) {}

std::string Pawn::getPieceSymbol() const {
    return m_color ? "♟" : "♙";
}

std::vector<Coordinate> Pawn::availableMoves(const ChessBoard &board) const {
    std::vector<Coordinate> moves;

    int direction = m_color ? 1 : -1; // white is 0 at the bottom
    int startRow = m_color ? 1 : 6;

    Coordinate oneSquareForward(m_coordinate.getX() + direction, m_coordinate.getY());
    Coordinate captureLeft(m_coordinate.getX() + direction, m_coordinate.getY() - 1);
    Coordinate captureRight(m_coordinate.getX() + direction, m_coordinate.getY() + 1);

    if (board.isEmpty(oneSquareForward)) {
        moves.push_back(oneSquareForward);

        if (m_coordinate.getX() == startRow) {
            Coordinate twoSquaresForward(m_coordinate.getX() +2* direction,
                                         m_coordinate.getY());

            if (board.isEmpty(twoSquaresForward))
                moves.push_back(twoSquaresForward);
        }
    }

    if (board.isOpponentPiece(captureLeft, m_color))
        moves.push_back(captureLeft);

    if (board.isOpponentPiece(captureRight, m_color))
        moves.push_back(captureRight);

    return moves;
}
