#include "include/chessDerivedPieces/king.h"

#include "include/logic/chesspiece.h"
#include "include/logic/coordinate.h"

King::King(Player color, Coordinate coordinate) : ChessPiece(color, coordinate) {}

std::string King::getPieceSymbol() const {
    return m_color == BLACK ? "♚" : "♔";
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
