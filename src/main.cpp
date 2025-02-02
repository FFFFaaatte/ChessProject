#include <iostream>
#include <regex>

#include "include/logic/gamemanagement.h"
#include "include/logic/networkmanager.h"

void initializeNetwork(std::shared_ptr<NetworkManager>& networkManager, std::string& username, bool& isServer);
void handlePlayerMove(GameManagement& game, std::shared_ptr<NetworkManager>& networkManager, const std::string& username, bool isServer);
void handleOpponentMove(GameManagement& game, std::shared_ptr<NetworkManager>& networkManager);

int main() {
    auto networkManager = std::make_shared<NetworkManager>();
    GameManagement game;

    std::string username;
    bool isServer;

    initializeNetwork(networkManager, username, isServer);
    networkManager->printConnectionInfo();
    game.printWelcomeMessage();

    while (!game.isGameOver()) {
        game.displayBoard();
        if ((isServer && game.getCurrentPlayer() == WHITE) || (!isServer && game.getCurrentPlayer() == BLACK)) {
            handlePlayerMove(game, networkManager, username, isServer);
        } else {
            handleOpponentMove(game, networkManager);
        }
    }

    game.displayBoard();
    game.announceWinner();
    networkManager->closeConnection();
    return 0;
}

void initializeNetwork(std::shared_ptr<NetworkManager>& networkManager, std::string& username, bool& isServer) {
    std::cout << "Enter your username: ";
    std::cin >> username;

    std::string mode;
    std::cout << "Choose mode (server/client): ";
    std::cin >> mode;

    isServer = (mode == "server");
    if (isServer) {
        int port;
        std::cout << "Enter port to listen on: ";
        std::cin >> port;
        if (!networkManager->setupServer(username, port)) {
            std::cout << "Failed to start server." << std::endl;
            exit(1);
        }
    } else {
        std::string ip;
        int port;
        std::cout << "Enter server IP address: ";
        std::cin >> ip;
        std::cout << "Enter server port: ";
        std::cin >> port;
        if (!networkManager->connectToServer(username, ip, port)) {
            std::cout << "Failed to connect to server." << std::endl;
            exit(1);
        }
    }
}

void handlePlayerMove(GameManagement& game, std::shared_ptr<NetworkManager>& networkManager, const std::string& username, bool isServer) {
    std::string move;
    bool validMove = false;

    while (!validMove) {
        std::cout << username << "'s move: ";
        std::getline(std::cin, move);

        std::regex moveRegex("([a-h][1-8]) to ([a-h][1-8])");
        std::smatch match;
        if (!std::regex_match(move, match, moveRegex)) {
            std::cout << "Use this format for input: e.g. 'e2 to e4'.\n";
            continue;
        }

        Coordinate from(7 - (match[1].str()[1] - '1'), match[1].str()[0] - 'a');
        Coordinate to(7 - (match[2].str()[1] - '1'), match[2].str()[0] - 'a');
        if (!game.makeMove(from, to)) {
            std::cout << "Invalid move. Please try again.\n";
        } else {
            validMove = true;
        }
    }

    if (!networkManager->sendMove(move)) {
        std::cout << "Failed to send move." << std::endl;
        exit(1);
    }
}

void handleOpponentMove(GameManagement& game, std::shared_ptr<NetworkManager>& networkManager) {
    std::string move;
    std::cout << "Waiting for opponent's move..." << std::endl;
    if (!networkManager->receiveMove(move)) {
        std::cout << "Failed to receive move." << std::endl;
        exit(1);
    }

    std::cout << "Opponent's move: " << move << std::endl;
    std::regex moveRegex("([a-h][1-8]) to ([a-h][1-8])");
    std::smatch match;
    if (!std::regex_match(move, match, moveRegex)) {
        std::cout << "Received invalid move.\n";
        exit(1);
    }

    Coordinate from(7 - (match[1].str()[1] - '1'), match[1].str()[0] - 'a');
    Coordinate to(7 - (match[2].str()[1] - '1'), match[2].str()[0] - 'a');
    if (!game.makeMove(from, to)) {
        std::cout << "Received invalid move.\n";
        exit(1);
    }
}
