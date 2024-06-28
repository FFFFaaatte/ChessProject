#include "include/chessDerivedPieces/queen.h"


Queen::Queen(Player color, Coordinate coordinate) : ChessPiece(color, coordinate) {}

std::string Queen::getPieceSymbol() const {
    return m_color == BLACK ? "♛" : "♕";
}

std::vector<Coordinate> Queen::availableMoves(const ChessBoard &board) const {
    std::vector<Coordinate> moves;
    int validDirections[8][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1},
                                 {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

    for (auto &direction : validDirections) {
        for (int i= 1; i< 8; ++i) {
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
