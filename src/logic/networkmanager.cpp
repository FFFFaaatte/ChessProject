#include "include/logic/networkmanager.h"

#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

NetworkManager::NetworkManager() : m_socket(-1) {}

NetworkManager::~NetworkManager() {
    closeConnection();
}

int NetworkManager::createSocket() {
    return socket(AF_INET, SOCK_STREAM, 0);
}

bool NetworkManager::setupServer(const std::string& username, int port) {
    m_username = username;
    m_socket = createSocket();
    if (m_socket == -1) {
        std::cout << "Error while creating socket." << std::endl;
        return false;
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port);

    if (bind(m_socket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cout << "Error while binding the socket." << std::endl;
        return false;
    }

    listen(m_socket, 1);
    std::cout << "Waiting for a connection..." << std::endl;

    int clientSocket = accept(m_socket, nullptr, nullptr);
    if (clientSocket < 0) {
        std::cout << "Error while trying to accept connection." << std::endl;
        return false;
    }

    m_socket = clientSocket;
    std::cout << "Connection was accepted." << std::endl;

    char buffer[256];

    // recieve the opponent's username
    if (recv(m_socket, buffer, sizeof(buffer), 0) > 0)
        m_opponentUsername = buffer;

    // send the player's username to the opponent
    send(m_socket, m_username.c_str(), m_username.length()+1, 0);

    return true;
}

bool NetworkManager::connectToServer(const std::string& username, const std::string& ip, int port) {
    m_username = username;
    m_ipAddress = ip;
    m_socket = createSocket();
    if (m_socket == -1) {
        std::cout << "Could not create socket." << std::endl;
        return false;
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(ip.c_str());
    serverAddr.sin_port = htons(port);

    if (connect(m_socket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cout << "Connection failed." << std::endl;
        return false;
    }

    std::cout << "Connected to the server." << std::endl;


    send(m_socket, m_username.c_str(), m_username.length() + 1, 0);

    char buffer[256];
    if (recv(m_socket, buffer, sizeof(buffer), 0) > 0) {
        m_opponentUsername = buffer;
    }

    return true;
}

bool NetworkManager::sendMove(const std::string& move) {
    if (send(m_socket, move.c_str(), move.length()+1, 0) < 0) {
        std::cout << "Sending move was failed." << std::endl;
        return false;
    }
    return true;
}

bool NetworkManager::receiveMove(std::string& move) {
    char buffer[256];
    if (recv(m_socket, buffer, sizeof(buffer), 0) < 0) {
        std::cout << "Recieving move was failed." << std::endl;
        return false;
    }
    move = buffer;
    return true;
}


void NetworkManager::closeConnection() {
    if (m_socket != -1) {
        close(m_socket);
        m_socket = -1;
    }
}

void NetworkManager::printConnectionInfo() const {
    std::cout << "Connected to " << m_opponentUsername << " (" << m_ipAddress << ")" << std::endl;
}


