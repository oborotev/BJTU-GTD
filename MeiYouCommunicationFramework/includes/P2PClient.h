//
// Created by margoul_1 on 08/03/16.
//

#ifndef MEIYOUCOMMUNICATION_P2PCLIENT_H
#define MEIYOUCOMMUNICATION_P2PCLIENT_H

# include <string>
# include <SFML/Network.hpp>

class P2PClient {
public:
    virtual sf::Socket::Status  socketWriteBuild() = 0;
    virtual void                socketWriteDestroy() = 0;
    virtual sf::Socket::Status  socketListenBuild() = 0;
    virtual void                socketListenDestroy() = 0;
    virtual void                setPacketDataSize(const unsigned short &size) = 0;
    virtual void                setRawMode(const bool &mode) = 0;
protected:
    //Client options
    bool                        _consoleMode;
    //Socket informations
    unsigned short              _port;
    sf::IpAddress               _ip;
    //Socket specifications
    std::string                 _rawData;
    sf::Packet                  _packetData;
    sf::Packet                  _clientPacketData;
    void                        *_clientRawData;
    //Socket otions
    std::size_t                 _dataSize;
    short                       _retries;
    unsigned short              _maxRetries;
    bool                        _rawMode;
    std::size_t                 _sizeReceiveData;
    sf::Time                    _timeout;
    //Socket objects
    sf::TcpSocket               _socket;
    sf::TcpListener             _listener;
    sf::TcpSocket               _client;
};

#endif //MEIYOUCOMMUNICATION_P2PCLIENT_H
