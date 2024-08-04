#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <string>

class NetworkManager {
public:
    NetworkManager();
    ~NetworkManager();
    bool setupServer(const std::string& username, int port);
    bool connectToServer(const std::string& username, const std::string& ip, int port);
    bool sendMove(const std::string& move);
    bool receiveMove(std::string& move);
    void closeConnection();
    void printConnectionInfo() const;

private:
    int createSocket();


    int m_socket;
    std::string m_username;
    std::string m_opponentUsername;
    std::string m_ipAddress;
};

#endif // NETWORKMANAGER_H
