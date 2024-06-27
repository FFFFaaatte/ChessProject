#include "include/gamemanagement.h"

#include <iostream>
#include <algorithm>
#include <stdexcept>

#include "include/chesspiece.h"
#include "include/chessboard.h"
#include "include/chessDerivedPieces/pawn.h"
#include "include/chessDerivedPieces/queen.h"
#include "include/chessDerivedPieces/rook.h"
#include "include/chessDerivedPieces/bishop.h"
#include "include/chessDerivedPieces/knight.h"


GameManagement::GameManagement() : m_currentPlayer(0) {}

bool GameManagement::getCurrentPlayer() const {
           return m_currentPlayer;
}

bool GameManagement::isValidMove(const Coordinate &from, const Coordinate &to) const {
    auto piece = m_board.getPieces()[from.getX()][from.getY()];

    if (!piece || piece->getColor() != m_currentPlayer)
        return false;

    auto moves = piece->availableMoves(m_board);
    return std::find(moves.begin(), moves.end(), to) != moves.end();
}

bool GameManagement::isInCheck(bool color) const {
    Coordinate kingCoordinate(0,0);
    // find the king
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            auto piece = m_board.getPieces()[i][j];
            if (piece && piece->getColor() == color && (piece->getPieceSymbol() == "♔"
                                                        || piece->getPieceSymbol() == "♚")) {
                kingCoordinate = piece->getCoordinate();
                break;
            }
        }
    }

    // check if any opponent piece can capture the king
    for (int i= 0; i < 8; ++i) {
        for (int j= 0; j < 8; ++j) {
            auto piece = m_board.getPieces()[i][j];
            if (piece && piece->getColor() != color) {
                auto moves = piece->availableMoves(m_board);
                if (std::find(moves.begin(), moves.end(), kingCoordinate) != moves.end())
                    return true;
            }
        }
    }
    return false;
}

//bool GameManagement::isCheckmate(bool color) {
//    if (!isInCheck(color))
//        return false;
//    //fm debug!
////    ChessBoard boardCopy = m_board;
//    // check if there is any valid move that can prevent the check
//    for (int i= 0; i < 8; ++i) {
//        for (int j= 0; j < 8; ++j) {
//            auto piece = m_board.getPieces()[i][j];
//            if (piece && piece->getColor() == color) {
//                auto movements = piece->availableMoves(m_board);
//                for (auto &move : movements) {
//                    // move
//                    auto originalPiece = m_board.getPiece(move);
//                    m_board.movePiece(piece->getCoordinate(), move);
//                    bool stillInCheck = isInCheck(color);
//                    // undo
//                    m_board.movePiece(move, piece->getCoordinate());
//                    // fm?
////                    m_board.getPieces()[move.getX()][move.getY()] = originalPiece;
//                    m_board.setPiece(move, originalPiece);
////                    m_board = boardCopy;
//                    if (!stillInCheck)
//                        return false;
//                }
//            }
//        }
//    }
////    m_board= boardCopy;
//    return true;
//}

bool GameManagement::isCheckmate(bool color) {
    if (!isInCheck(color))
        return false;

    std::cout << "Checking for checkmate...\n";

    // check if there is any valid move that can prevent the check
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            auto piece = m_board.getPieces()[i][j];

            if (piece && piece->getColor() == color) {
                auto movements = piece->availableMoves(m_board);
                Coordinate initialCoordinate = piece->getCoordinate();
                for (auto &move : movements) {
                    // move
                    auto capturedPiece = m_board.getPiece(move);
//                    std::cout << "Moving piece from (" << piece->getCoordinate().getX() << ", " << piece->getCoordinate().getY()
//                              << ") to (" << move.getX() << ", " << move.getY() << ")\n";

                    m_board.movePiece(piece->getCoordinate(), move);
//                    std::cout << "Board after move:\n" << m_board.getString();

                    bool stillInCheck = isInCheck(color);
//                    std::cout << "Is still in check: " << stillInCheck << "\n";

                    // undo the move
//                    std::cout<< piece->getPieceSymbol() << piece->getCoordinate().getX() <<piece->getCoordinate().getY()<<std::endl;
                    m_board.movePiece(move, initialCoordinate);
                    piece->setCoordinate(initialCoordinate);
                    m_board.setPiece(move, capturedPiece);

//                    std::cout << "Board after undo:\n" << m_board.getString();

                    if (!stillInCheck) {
//                        std::cout << "Found a move that prevents checkmate.\n";
                        return false;
                    }
                }
            }
        }
    }

    std::cout << "Checkmate detected.\n";
    return true;
}

void GameManagement::switchPlayer() {
    m_currentPlayer = !m_currentPlayer;
}

void GameManagement::displayBoard() const {
    std::cout << m_board.getString();
}

void GameManagement::promotePawn(const Coordinate& coordinate) {
    char choice;
    std::cout << "Promote pawn to (Q/R/B/N): ";
    std::cin >> choice;

    std::shared_ptr<ChessPiece> newPiece;
    switch (choice) {
        case 'Q':
        case 'q':
            newPiece = std::make_shared<Queen>(m_currentPlayer, coordinate);
            break;
        case 'R':
        case 'r':
            newPiece = std::make_shared<Rook>(m_currentPlayer, coordinate);
            break;
        case 'B':
        case 'b':
            newPiece = std::make_shared<Bishop>(m_currentPlayer, coordinate);
            break;
        case 'N':
        case 'n':
            newPiece = std::make_shared<Knight>(m_currentPlayer, coordinate);
            break;
        default:
            std::cout << "Invalid choice. Promoting to Queen by default.\n";
            newPiece = std::make_shared<Queen>(m_currentPlayer, coordinate);
            break;
    }
    m_board.setPiece(coordinate, newPiece);
}


bool GameManagement::makeMove(const Coordinate &from, const Coordinate &to) {
    if (isValidMove(from, to)) {
        std::shared_ptr<ChessPiece> capturedPiece = m_board.movePiece(from, to);

        // check to promote pawn
        if ((m_currentPlayer == 0 && to.getX() == 0) || (m_currentPlayer == 1 && to.getX() == 7)) {
            if (std::dynamic_pointer_cast<Pawn>(m_board.getPiece(to)))
                // fm? when call this a bad output detects!
                promotePawn(to);
        }

        if (isInCheck(m_currentPlayer)) {
            m_board.movePiece(to, from);
            m_board.setPiece(to, capturedPiece);
            std::cout << "This move puts your king in check. Try again.\n";
            return false;
        }

        switchPlayer();

        if (isInCheck(m_currentPlayer))
            std::cout << "Check!\n";

        return true;
    }
//    std::cout << "Invalid move. Try again.\n";
    return false;
}


bool GameManagement::isGameOver() {
    return isCheckmate(m_currentPlayer);
}

void GameManagement::announceWinner() const {
    std::cout << (m_currentPlayer ? "Black" : "White") << " wins!\n";
}
