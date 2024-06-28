#include "include/logic/gamemanagement.h"

#include <iostream>
#include <algorithm>
#include <stdexcept>

#include "include/logic/chesspiece.h"
#include "include/logic/chessboard.h"
#include "include/chessDerivedPieces/pawn.h"
#include "include/chessDerivedPieces/queen.h"
#include "include/chessDerivedPieces/rook.h"
#include "include/chessDerivedPieces/bishop.h"
#include "include/chessDerivedPieces/knight.h"


GameManagement::GameManagement() : m_currentPlayer() {}

void GameManagement::printWelcomeMessage() const {
    std::cout << "───── ⋆⋅☆⋅⋆ ───── ───── ⋆⋅☆⋅⋆ ───── ───── ⋆⋅☆⋅⋆ ─────" << std::endl;
    std::cout << "                   Welcome to Chess!                 " << std::endl;
    std::cout << "───── ⋆⋅☆⋅⋆ ───── ───── ⋆⋅☆⋅⋆ ───── ───── ⋆⋅☆⋅⋆ ─────"<< std::endl;
    std::cout << "                    Instructions                     " << std::endl;
    std::cout << "1. Moves should be entered in standard chess notation" << std::endl;
    std::cout << " (e.g., 'e2 to e4')." << std::endl;
    std::cout << "2. Press 'Enter' after each move." << std::endl;
    std::cout << "───── ───── ───── ───── ───── ───── ───── ───── ─────" << std::endl;
    std::cout << "               Let's start the game!                 " << std::endl;
    std::cout << "───── ───── ───── ───── ───── ───── ───── ───── ─────" << std::endl;
    std::cout << std::endl;
}

void GameManagement::displayBoard() const {
    std::cout << m_board.getString() << std::endl;
}

bool GameManagement::getCurrentPlayer() const {
           return m_currentPlayer;
}

bool GameManagement::makeMove(const Coordinate &from, const Coordinate &to) {
    if (isValidMove(from, to)) {
        std::shared_ptr<ChessPiece> capturedPiece = m_board.movePiece(from, to);

        // check to promote pawn
        if ((m_currentPlayer == WHITE && to.getX() == 0) || (m_currentPlayer == BLACK && to.getX() == 7)) {
            if (std::dynamic_pointer_cast<Pawn>(m_board.getPiece(to)))
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
    return false;
}

bool GameManagement::isGameOver() {
    return isCheckmate(m_currentPlayer);
}

void GameManagement::announceWinner() const {
    std::cout << (m_currentPlayer == WHITE ? "Black" : "White") << " wins!\n";
}

bool GameManagement::isValidMove(const Coordinate &from, const Coordinate &to) const {
    auto piece = m_board.getPiece(from);

    if (!piece || piece->getColor() != m_currentPlayer)
        return false;

    auto moves = piece->availableMoves(m_board);
    return std::find(moves.begin(), moves.end(), to) != moves.end();
}

void GameManagement::switchPlayer() {
    m_currentPlayer= (m_currentPlayer == WHITE) ? BLACK : WHITE;
}

void GameManagement::promotePawn(const Coordinate& coordinate) {
    char choice;
    std::cout << "Promote pawn to (Q(Queen)/R(Rook)/B(Bishop)/K(Knight)): ";
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
        case 'K':
        case 'k':
            newPiece = std::make_shared<Knight>(m_currentPlayer, coordinate);
            break;
        default:
            std::cout << "Invalid choice. Promoting to Queen by default.\n";
            newPiece = std::make_shared<Queen>(m_currentPlayer, coordinate);
            break;
    }

    m_board.setPiece(coordinate, newPiece);
}

bool GameManagement::isInCheck(Player color) const {
    Coordinate kingCoordinate = m_board.findKing(color);

    // check if any opponent piece can capture the king
    for (int i= 0; i < 8; ++i) {
        for (int j= 0; j < 8; ++j) {
            auto piece = m_board.getPiece(Coordinate(i,j));
            if (piece && piece->getColor() != color) {
                auto moves = piece->availableMoves(m_board);
                if (std::find(moves.begin(), moves.end(), kingCoordinate) != moves.end())
                    return true;
            }
        }
    }
    return false;
}

bool GameManagement::isCheckmate(Player color) {
    if (!isInCheck(color))
        return false;

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
                    m_board.movePiece(piece->getCoordinate(), move);
                    bool stillInCheck = isInCheck(color);

                    // undo the move
                    m_board.movePiece(move, initialCoordinate);
                    piece->setCoordinate(initialCoordinate);
                    m_board.setPiece(move, capturedPiece);


                    if (!stillInCheck)
                        return false;

                }
            }
        }
    }

    std::cout << "Checkmate detected.\n";
    return true;
}
// TODO: implement undo method
