#include "include/chessDerivedPieces/knight.h"

#include <iostream>

#include "include/logic/coordinate.h"

Knight::Knight(Player color, Coordinate coordinate) : ChessPiece(color, coordinate) {}

std::string Knight::getPieceSymbol() const {
    return m_color == BLACK ? "♞" : "♘";
}

std::vector<Coordinate> Knight::availableMoves(const ChessBoard &board) const {
    std::vector<Coordinate> moves;

    int validMovements[8][2] = {{2, 1}, {2, -1}, {-2, 1}, {-2, -1},
                                {1, 2}, {1, -2}, {-1, 2}, {-1, -2}};

    for (auto &validMove : validMovements) {
        Coordinate move(m_coordinate.getX() + validMove[0], m_coordinate.getY() + validMove[1]);

        if (board.isInChessBoard(move) && (board.isEmpty(move)||board.isOpponentPiece(move, m_color)))
            moves.push_back(move);
    }
    return moves;
}
