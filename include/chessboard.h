#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "include/coordinate.h"

#include <iostream>
#include <vector>
#include <memory>

#include "coordinate.h"
#include "chesspiece.h"


class ChessPiece;

class ChessBoard {
public:
    using BoardType = std::vector<std::vector<std::shared_ptr<ChessPiece>>>;

    ChessBoard();
    std::string getString() const;
    BoardType getPieces() const;
    // fm?
    void setPiece (const Coordinate &coordinate, std::shared_ptr<ChessPiece> piece);
    bool isInChessBoard(const Coordinate &coordinate) const;
    std::shared_ptr<ChessPiece> getPiece(const Coordinate &coordinate) const;
    bool isEmpty(const Coordinate &coordinate) const;
    bool isOpponentPiece(const Coordinate &coordinate, bool color) const;
    std::shared_ptr<ChessPiece> movePiece(const Coordinate &from, const Coordinate &to);

private:
    BoardType m_pieces;
};

#endif // CHESSBOARD_H
