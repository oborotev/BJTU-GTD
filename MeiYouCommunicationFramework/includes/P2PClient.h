//
// Created by margoul_1 on 08/03/16.
//

#ifndef MEIYOUCOMMUNICATION_P2PCLIENT_H
#define MEIYOUCOMMUNICATION_P2PCLIENT_H

# include <string>
# include <SFML/Network.hpp>

class P2PClient {
public:
    virtual sf::Socket::Status  socketBuild() = 0;
    virtual void                socketDestroy() = 0;
protected:
    int                         _port;
    std::string                 _ip;
    char                        *_data;
    sf::TcpSocket               _socket;
    sf::TcpListener             _listener;
};

#endif //MEIYOUCOMMUNICATION_P2PCLIENT_H
