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

void                       TaiTaiP2PClient::socketWriteDestroy()
{
    this->_socket.disconnect();
}

sf::Socket::Status         TaiTaiP2PClient::socketWriteBuild()
{
    return (this->_socket.connect(this->_ip, this->_port, this->_timeout));
}

void                       TaiTaiP2PClient::socketListenDestroy()
{
    this->_listener.close();
}

sf::Socket::Status         TaiTaiP2PClient::socketListenBuild()
{
    sf::Socket::Status     status;

    if ((status = this->_listener.listen(this->_port)) != sf::Socket::Done)
        return (status);
    std::cout << "IT MANAGED TO LISTEN" << std::endl;
    return (status);
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

const TaiTaiP2PClient::States    TaiTaiP2PClient::receiveData()
{
    this->_clientPacketData.clear();
    if (this->_client.receive(this->_clientPacketData) != sf::Socket::Done)
        return (TaiTaiP2PClient::States::ERROR);
    return (TaiTaiP2PClient::States::VALID);
}

const TaiTaiP2PClient::States    TaiTaiP2PClient::receiveRawData()
{
    std::size_t                  received;
    if (this->_client.receive(this->_clientRawData, std::size_t(100), received) != sf::Socket::Done)
        return (TaiTaiP2PClient::States::ERROR);
    return (TaiTaiP2PClient::States::VALID);
}

void                       TaiTaiP2PClient::listenOnClient()
{
    TaiTaiP2PClient::States    status = TaiTaiP2PClient::States::VALID ;

    this->_listener.accept(this->_client);
    std::cout << "ACCEPTED A CLIENT" << std::endl;
    while (status == TaiTaiP2PClient::States::VALID)
    {
        std::cout << "IN THE SHIT" << std::endl;
        status = this->receiveData();
        if (status == TaiTaiP2PClient::States::VALID)
            std::cout << "Partner wrote : " << this->_clientRawData << std::endl;
    }
}

#include <unistd.h>

TaiTaiP2PClient::States    TaiTaiP2PClient::client()
{
    sf::Socket::Status     status;
    sf::Clock              clock;


    if ((status = this->socketListenBuild()) != sf::Socket::Done)
        return status == sf::Socket::NotReady ? TaiTaiP2PClient::States::HOST_NOT_READY : TaiTaiP2PClient::States::ERROR;
    sf::Thread thread(&TaiTaiP2PClient::listenOnClient, this);
    thread.launch();
    while ((status = this->socketWriteBuild()) != sf::Socket::Done)
    {
        std::cout << "Couldn't connect retrying in one second" << std::endl;
        sleep(1000000);
    }
    std::cout << "Both connecned and listen" << std::endl;
    while (this->_rawData != "quit")
    {
        std::cin >> this->_rawData;
        this->sendData(this->_rawData.c_str());
    }
    this->socketWriteDestroy();
    this->socketListenDestroy();
    thread.terminate();
    return (TaiTaiP2PClient::States::FINISHED);
}