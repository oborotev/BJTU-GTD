//
// Created by storm on 08/03/16.
//

#ifndef MEIYOUCOMMUNICATION_TAITAIP2PCLIENT_H
#define MEIYOUCOMMUNICATION_TAITAIP2PCLIENT_H

# include <iostream>
# include <string.h>
# include "P2PClient.h"

class TaiTaiP2PClient : protected P2PClient {
public:
    enum class States {VALID = 0, FINISHED = 0, ERROR = 1, WARNING = 2, HOST_NOT_READY = 3};
public:
    TaiTaiP2PClient(const std::string &ip, const unsigned short &port, const float &timeout = 10, const bool &rawMode = true);
    virtual ~TaiTaiP2PClient();
    virtual States              client();
    virtual sf::Socket::Status  socketBuild();
    virtual void                socketDestroy();
    virtual void                setPacketDataSize(const unsigned short &size);
    virtual void                setRawMode(const bool &mode);
    virtual States              sendRawData(const void *data);
    virtual States              sendData(const void *data, const bool &isText = true);
};


#endif //MEIYOUCOMMUNICATION_TAITAIP2PCLIENT_H
