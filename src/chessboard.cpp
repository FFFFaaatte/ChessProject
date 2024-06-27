#include "include/chessboard.h"

#include <iostream>
#include <algorithm>

#include "include/coordinate.h"
#include "include/chessDerivedPieces/pawn.h"
#include "include/chessDerivedPieces/king.h"
#include "include/chessDerivedPieces/bishop.h"
#include "include/chessDerivedPieces/rook.h"
#include "include/chessDerivedPieces/knight.h"
#include "include/chessDerivedPieces/queen.h"

ChessBoard::ChessBoard() {
    for (int i = 0; i < 8; ++i)
        m_pieces.emplace_back(8, nullptr);

    for (int j = 0; j < 8; ++j) {
        m_pieces[1][j] = std::make_shared<Pawn>(1, Coordinate(1, j));
        m_pieces[6][j] = std::make_shared<Pawn>(0, Coordinate(6, j));
    }

    m_pieces[0][4] = std::make_shared<King>(1, Coordinate(0, 4));
    m_pieces[7][4] = std::make_shared<King>(0, Coordinate(7, 4));

    m_pieces[0][2] = std::make_shared<Bishop>(1, Coordinate(0, 2));
    m_pieces[0][5] = std::make_shared<Bishop>(1, Coordinate(0, 5));
    m_pieces[7][2] = std::make_shared<Bishop>(0, Coordinate(7, 2));
    m_pieces[7][5] = std::make_shared<Bishop>(0, Coordinate(7, 5));

    m_pieces[0][0] = std::make_shared<Rook>(1, Coordinate(0, 0));
    m_pieces[0][7] = std::make_shared<Rook>(1, Coordinate(0, 7));
    m_pieces[7][0] = std::make_shared<Rook>(0, Coordinate(7, 0));
    m_pieces[7][7] = std::make_shared<Rook>(0, Coordinate(7, 7));

    m_pieces[0][3] = std::make_shared<Queen>(1, Coordinate(0, 3));
    m_pieces[7][3] = std::make_shared<Queen>(0, Coordinate(7, 3));

    m_pieces[0][1] = std::make_shared<Knight>(1, Coordinate(0, 1));
    m_pieces[0][6] = std::make_shared<Knight>(1, Coordinate(0, 6));
    m_pieces[7][1] = std::make_shared<Knight>(0, Coordinate(7, 1));
    m_pieces[7][6] = std::make_shared<Knight>(0, Coordinate(7, 6));
}

//std::string ChessBoard::getString() const{
//    std::string result = "";
//    for (int i = 0; i < 8; ++i) {
//        for (int j = 0; j < 8; ++j) {
//            if (m_pieces[i][j] != nullptr)
//                result += m_pieces[i][j]->getPieceSymbol() + " ";
//            else
//                result += "▢ ";

//        }
//        result += "\n";
//    }
//    return result;
//}

std::string ChessBoard::getString() const {
    std::string result = "  a b c d e f g h\n";
    for (int i = 0; i < 8; ++i)
    {
        result += std::to_string(8 - i) + " ";
        for (int j = 0; j < 8; ++j)
        { if (m_pieces[i][j] != nullptr)
                result += m_pieces[i][j]->getPieceSymbol() + " ";
            else result += "▢ ";
        }
        result += std::to_string(8 - i) + "\n";
    } result += "  a b c d e f g h\n"; return result;
};
ChessBoard::BoardType ChessBoard::getPieces() const{
    return m_pieces;
}


bool ChessBoard::isInChessBoard(const Coordinate &coordinate) const {
    return coordinate.getX() >= 0 && coordinate.getX() < 8 && coordinate.getY() >= 0 && coordinate.getY() < 8;
}

std::shared_ptr<ChessPiece> ChessBoard::getPiece(const Coordinate &coordinate) const {
    if (isInChessBoard(coordinate))
        return m_pieces[coordinate.getX()][coordinate.getY()];
    return nullptr;
}

bool ChessBoard::isEmpty(const Coordinate &coordinate) const {
    return isInChessBoard(coordinate) && m_pieces[coordinate.getX()][coordinate.getY()] == nullptr;
}

bool ChessBoard::isOpponentPiece(const Coordinate &coordinate, bool color) const {
    return isInChessBoard(coordinate) && m_pieces[coordinate.getX()][coordinate.getY()] != nullptr
            && m_pieces[coordinate.getX()][coordinate.getY()]->getColor() != color;
}

void ChessBoard::setPiece (const Coordinate &coordinate, std::shared_ptr<ChessPiece> piece){
    m_pieces [coordinate.getX()][coordinate.getY()] = piece;
}

std::shared_ptr<ChessPiece> ChessBoard::movePiece(const Coordinate &from, const Coordinate &to) {
    if (isInChessBoard(from) && isInChessBoard(to)) {
        // fm
        std::shared_ptr<ChessPiece> capturedPiece =  m_pieces[to.getX()][to.getY()];
        m_pieces[to.getX()][to.getY()] = m_pieces[from.getX()][from.getY()];
        m_pieces[from.getX()][from.getY()] = nullptr;
        if (m_pieces[to.getX()][to.getY()])
            m_pieces[to.getX()][to.getY()]->setCoordinate(to);
        return capturedPiece;
    }
    return nullptr;
}
