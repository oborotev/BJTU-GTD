//
// Created by storm on 08/03/16.
//

# include "TaiTaiP2PClient.h"

TaiTaiP2PClient::TaiTaiP2PClient(const std::string &ip, const unsigned short &port, const float &timeout)
{
    _ip = ip;
    _port = port;
    _timeout = sf::seconds(timeout);
}

TaiTaiP2PClient::~TaiTaiP2PClient() {
}

void                       TaiTaiP2PClient::setRawMode(const bool &mode)
{
    this->_rawMode = mode;
}

void                       TaiTaiP2PClient::setPacketDataSize(const unsigned short &size)
{
    this->_dataSize = size;
}

void                       TaiTaiP2PClient::socketDestroy()
{
    this->_socket.disconnect();
}

sf::Socket::Status         TaiTaiP2PClient::socketBuild()
{
    return (this->_socket.connect(this->_ip, this->_port, this->_timeout));
}

TaiTaiP2PClient::States    TaiTaiP2PClient::client()
{
    if (this->socketBuild() != sf::Socket::Done)
        return (TaiTaiP2PClient::States::ERROR);
    this->_socket.send("la cantine c'est dégueu putain", strlen("la cantine c'est dégueu putain"));
    this->socketDestroy();
    return (TaiTaiP2PClient::States::FINISHED);
}