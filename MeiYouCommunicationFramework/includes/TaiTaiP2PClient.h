//
// Created by storm on 08/03/16.
//

#ifndef MEIYOUCOMMUNICATION_TAITAIP2PCLIENT_H
#define MEIYOUCOMMUNICATION_TAITAIP2PCLIENT_H

# include <iostream>
# include <string.h>
# include <unistd.h>
# include "P2PClient.h"

class TaiTaiP2PClient : protected P2PClient {
public:
    enum class States {VALID = 0, FINISHED = 0, ERROR = 1, WARNING = 2, HOST_NOT_READY = 3};
public:
    TaiTaiP2PClient(const std::string &ip, const unsigned short &port, const float &timeout = 10,
                    const unsigned short &retries = 10, const bool &rawMode = true, const std::size_t sizeReceiveData = std::size_t(100),
                    const bool consoleMode = true);
    virtual ~TaiTaiP2PClient();
    virtual States              client();
    virtual sf::Socket::Status  socketWriteBuild();
    virtual void                socketWriteDestroy();
    virtual sf::Socket::Status  socketListenBuild();
    virtual void                socketListenDestroy();
    virtual void                setPacketDataSize(const unsigned short &size);
    virtual void                setRawMode(const bool &mode);
    virtual States              sendRawData(const void *data);
    virtual States              sendData(const void *data, const bool &isText = true);
    virtual const States        receiveData();
    virtual const States        receiveRawData();
    virtual void                listenOnClient();
    virtual int                 consoleMode();
};


#endif //MEIYOUCOMMUNICATION_TAITAIP2PCLIENT_H
