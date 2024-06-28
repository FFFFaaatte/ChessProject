#include "include/logic/chessboard.h"

#include <iostream>
#include <algorithm>

#include "include/logic/coordinate.h"
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
        m_pieces[1][j] = std::make_shared<Pawn>(BLACK, Coordinate(1, j));
        m_pieces[6][j] = std::make_shared<Pawn>(WHITE, Coordinate(6, j));
    }

    m_pieces[0][4] = std::make_shared<King>(BLACK, Coordinate(0, 4));
    m_pieces[7][4] = std::make_shared<King>(WHITE, Coordinate(7, 4));

    m_pieces[0][2] = std::make_shared<Bishop>(BLACK, Coordinate(0, 2));
    m_pieces[0][5] = std::make_shared<Bishop>(BLACK, Coordinate(0, 5));
    m_pieces[7][2] = std::make_shared<Bishop>(WHITE, Coordinate(7, 2));
    m_pieces[7][5] = std::make_shared<Bishop>(WHITE, Coordinate(7, 5));

    m_pieces[0][0] = std::make_shared<Rook>(BLACK, Coordinate(0, 0));
    m_pieces[0][7] = std::make_shared<Rook>(BLACK, Coordinate(0, 7));
    m_pieces[7][0] = std::make_shared<Rook>(WHITE, Coordinate(7, 0));
    m_pieces[7][7] = std::make_shared<Rook>(WHITE, Coordinate(7, 7));

    m_pieces[0][3] = std::make_shared<Queen>(BLACK, Coordinate(0, 3));
    m_pieces[7][3] = std::make_shared<Queen>(WHITE, Coordinate(7, 3));

    m_pieces[0][1] = std::make_shared<Knight>(BLACK, Coordinate(0, 1));
    m_pieces[0][6] = std::make_shared<Knight>(BLACK, Coordinate(0, 6));
    m_pieces[7][1] = std::make_shared<Knight>(WHITE, Coordinate(7, 1));
    m_pieces[7][6] = std::make_shared<Knight>(WHITE, Coordinate(7, 6));
}


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

std::shared_ptr<ChessPiece> ChessBoard::getPiece(const Coordinate &coordinate) const {
    if (isInChessBoard(coordinate))
        return m_pieces[coordinate.getX()][coordinate.getY()];
    return nullptr;
}


void ChessBoard::setPiece (const Coordinate &coordinate, std::shared_ptr<ChessPiece> piece){
    m_pieces [coordinate.getX()][coordinate.getY()] = piece;
}

std::shared_ptr<ChessPiece> ChessBoard::movePiece(const Coordinate &from, const Coordinate &to) {
    if (isInChessBoard(from) && isInChessBoard(to)) {
        // fm
        std::shared_ptr<ChessPiece> capturedPiece =  getPiece(to);
        m_pieces[to.getX()][to.getY()] = getPiece(from);
        m_pieces[from.getX()][from.getY()] = nullptr;
        if (m_pieces[to.getX()][to.getY()])
            getPiece(to)->setCoordinate(to);
        return capturedPiece;
    }
    return nullptr;
}

bool ChessBoard::isInChessBoard(const Coordinate &coordinate) const {
    return coordinate.getX() >= 0 && coordinate.getX() < 8 && coordinate.getY() >= 0 && coordinate.getY() < 8;
}

bool ChessBoard::isEmpty(const Coordinate &coordinate) const {
    return isInChessBoard(coordinate) && getPiece(coordinate)== nullptr;
}

bool ChessBoard::isOpponentPiece(const Coordinate &coordinate, Player color) const {
    return isInChessBoard(coordinate) && getPiece(coordinate) != nullptr
            && getPiece(coordinate)->getColor() != color;
}

Coordinate ChessBoard::findKing(const Player color) const {
    Coordinate kingCoordinate(0,0);
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            auto piece = m_pieces[i][j];
            if (piece && piece->getColor() == color && (piece->getPieceSymbol() == "♔"
                                                        || piece->getPieceSymbol() == "♚")) {
                kingCoordinate = piece->getCoordinate();
                break;
            }
        }
    }
    return kingCoordinate;
}
