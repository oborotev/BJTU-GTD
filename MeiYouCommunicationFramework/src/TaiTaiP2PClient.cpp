//
// Created by storm on 08/03/16.
//

# include "TaiTaiP2PClient.h"

TaiTaiP2PClient::TaiTaiP2PClient(const std::string &ip, const unsigned short &port, const float &timeout,
                                const bool &rawMode)
{
    _ip = ip;
    _port = port;
    _rawMode = rawMode;
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

TaiTaiP2PClient::States    TaiTaiP2PClient::sendRawData(const void *data)
{
    return this->_socket.send(data, sizeof(data)) == sf::Socket::Status::Done ? TaiTaiP2PClient::States::VALID : TaiTaiP2PClient::States::ERROR;
}

TaiTaiP2PClient::States    TaiTaiP2PClient::sendData(const void *data, const bool &isText)
{

    this->_packetData.clear();
    this->_packetData.append(data, sizeof(data));
    return this->_socket.send(_packetData) == sf::Socket::Status::Done ? TaiTaiP2PClient::States::VALID : TaiTaiP2PClient::States::ERROR;
}

TaiTaiP2PClient::States    TaiTaiP2PClient::client()
{
    sf::Socket::Status     status;

    if ((status = this->socketBuild()) != sf::Socket::Done)
        return status == sf::Socket::NotReady ? TaiTaiP2PClient::States::HOST_NOT_READY : TaiTaiP2PClient::States::ERROR;

    while (this->_rawData != "quit")
    {
        std::cin >> this->_rawData;
        this->sendData(this->_rawData.c_str());
    }
    this->socketDestroy();
    return (TaiTaiP2PClient::States::FINISHED);
}