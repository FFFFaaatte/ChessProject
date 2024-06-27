#include "include/chessDerivedPieces/king.h"

#include "include/chesspiece.h"
#include "include/coordinate.h"

King::King(bool color, Coordinate coordinate) : ChessPiece(color, coordinate) {}

std::string King::getPieceSymbol() const {
    return m_color ? "♚" : "♔";
}

std::vector<Coordinate> King::availableMoves(const ChessBoard &board) const {
    std::vector<Coordinate> moves;

    int validDirections[8][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1},
                                 {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

    for (auto &direction : validDirections) {
        Coordinate move(m_coordinate.getX()+direction[0], m_coordinate.getY()+direction[1]);

        if (board.isInChessBoard(move) && (board.isEmpty(move)||board.isOpponentPiece(move, m_color)))
            moves.push_back(move);
    }
    return moves;
}
