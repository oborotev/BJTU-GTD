//
// Created by storm on 08/03/16.
//

# include "TaiTaiP2PClient.h"

TaiTaiP2PClient::TaiTaiP2PClient(const std::string &ip, const unsigned short &port, const float &timeout,
                                 const unsigned short &retries, const bool &rawMode, const std::size_t sizeReceiveData,
                                 const bool consoleMode, const bool textMode)
{
    _ip = ip;
    _port = port;
    _rawMode = rawMode;
    _sizeReceiveData = sizeReceiveData;
    _timeout = sf::seconds(timeout);
    _consoleMode = consoleMode;
    _textMode = textMode;
    _maxRetries = retries;
    _retries = -1;
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
    std::cout << "Waiting for someone to connect..." << std::endl;
    return (status);
}

TaiTaiP2PClient::States    TaiTaiP2PClient::sendData(const void *data, const std::size_t size, const bool &isText)
{

    this->_packetData.clear();
    this->_packetData.append(data, size);
    return this->_socket.send(_packetData) == sf::Socket::Status::Done ? TaiTaiP2PClient::States::VALID : TaiTaiP2PClient::States::ERROR;
}

TaiTaiP2PClient::States    TaiTaiP2PClient::sendRawData(const void *data)
{
    return this->_socket.send(data, sizeof(data)) == sf::Socket::Status::Done ? TaiTaiP2PClient::States::VALID : TaiTaiP2PClient::States::ERROR;
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
    TaiTaiP2PClient::States    status = TaiTaiP2PClient::States::VALID;

    this->_listener.accept(this->_client);
    std::cout << "New client connected : " << this->_client.getRemoteAddress() << std::endl;
    while (status == TaiTaiP2PClient::States::VALID)
    {
        status = this->receiveData();
        if (status == TaiTaiP2PClient::States::VALID)
            this->_sentence.append((char *)this->_clientPacketData.getData());
        else
            std::cout << "There seem to be a problem with the host... (Host disconnected)" << std::endl;
        if (_textMode)
        {
            //this->_sentence.pop_back();
            std::cout << "Partner wrote : " << this->_sentence.c_str() << std::endl;
            this->_sentence.clear();
        }
        else
            std::cout << "DEBUG : " << this->_sentence << std::endl;
    }
}

int                        TaiTaiP2PClient::consoleMode()
{
    while (this->_rawData != "quit")
    {
        std::getline(std::cin, this->_rawData);
        if (this->_rawData == "quit")
            break;
        this->sendData(this->_rawData.c_str(), (this->_rawData.length() * sizeof(char)) + 1);
        this->_rawData.clear();
    }
    return (0);
}

TaiTaiP2PClient::States    TaiTaiP2PClient::client()
{
    sf::Socket::Status     status;
    sf::Clock              clock;


    if ((status = this->socketListenBuild()) != sf::Socket::Done)
        return status == sf::Socket::NotReady ? TaiTaiP2PClient::States::HOST_NOT_READY : TaiTaiP2PClient::States::ERROR;
    sf::Thread thread(&TaiTaiP2PClient::listenOnClient, this);
    thread.launch();
    while ((status = this->socketWriteBuild()) != sf::Socket::Done && ++this->_retries != this->_maxRetries)
    {
        std::cout << "Couldn't connect to the host... Retrying" << std::endl;
        this->_socket.disconnect();
        sleep(1);
    }
    if (status != sf::Socket::Done)
    {
        std::cout << "The host is unreachable. Closing..." << std::endl;
        this->socketWriteDestroy();
        this->socketListenDestroy();
        thread.terminate();
        return (TaiTaiP2PClient::States::ERROR);
    }
    if (_consoleMode)
        this->consoleMode();
    std::cout << "Quitting..." << std::endl;
    this->socketWriteDestroy();
    this->socketListenDestroy();
    thread.terminate();
    return (TaiTaiP2PClient::States::FINISHED);
}