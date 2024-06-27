#include "include/chessDerivedPieces/rook.h"

#include "include/coordinate.h"

Rook::Rook(bool color, Coordinate coordinate) : ChessPiece(color, coordinate) {}

std::string Rook::getPieceSymbol() const {
     return m_color ? "♜" : "♖";
}

std::vector<Coordinate> Rook::availableMoves(const ChessBoard &board) const {
    std::vector<Coordinate> moves;

    int validDirections[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    for (auto &direction : validDirections) {
        for (int i = 1; i < 8; ++i) {
            Coordinate move(m_coordinate.getX() + i*direction[0], m_coordinate.getY()+i*direction[1]);
            if (!board.isInChessBoard(move)) break;
            if (board.isEmpty(move))
                moves.push_back(move);
            else {
                if (board.isOpponentPiece(move, m_color))
                    moves.push_back(move);
                break;
            }
        }
    }
    return moves;
}
