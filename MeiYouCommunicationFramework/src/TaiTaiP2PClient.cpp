//
// Created by storm on 08/03/16.
//

# include "TaiTaiP2PClient.h"

TaiTaiP2PClient::TaiTaiP2PClient(const std::string &ip, const int &port)
{
    _ip = ip;
    _port = port;
}

TaiTaiP2PClient::~TaiTaiP2PClient() {
}

void                       TaiTaiP2PClient::socketDestroy()
{
    this->_socket.disconnect();
}

sf::Socket::Status         TaiTaiP2PClient::socketBuild()
{
    return (this->_socket.connect(this->_ip, this->_port));
}

TaiTaiP2PClient::States    TaiTaiP2PClient::client()
{
    if (this->socketBuild() != sf::Socket::Done)
        return (TaiTaiP2PClient::States::ERROR);
    this->_socket.send("la cantine c'est dégueu putain", strlen("la cantine c'est dégueu putain"));
    this->socketDestroy();
    return (TaiTaiP2PClient::States::FINISHED);
}