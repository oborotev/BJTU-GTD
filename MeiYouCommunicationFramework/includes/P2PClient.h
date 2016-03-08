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
    virtual void                setPacketDataSize(const unsigned short &size) = 0;
    virtual void                setRawMode(const bool &mode) = 0;
protected:
    //Socket informations
    unsigned short              _port;
    sf::IpAddress               _ip;
    //Socket specifications
    char                        *_rawData;
    sf::Packet                  _packetData;
    //Socket otions
    std::size_t                 _dataSize;
    bool                        _rawMode;
    sf::Time                    _timeout;
    //Socket objects
    sf::TcpSocket               _socket;
    sf::TcpListener             _listener;
};

#endif //MEIYOUCOMMUNICATION_P2PCLIENT_H
