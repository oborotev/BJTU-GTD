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
    enum class States {FINISHED = 0, ERROR = 1, WARNING = 2};
public:
    TaiTaiP2PClient(const std::string &ip, const unsigned short &port, const float &timeout = 10);
    virtual ~TaiTaiP2PClient();
    virtual States              client();
    virtual sf::Socket::Status  socketBuild();
    virtual void                socketDestroy();
    virtual void                setPacketDataSize(const unsigned short &size);
    virtual void                setRawMode(const bool &mode);
};


#endif //MEIYOUCOMMUNICATION_TAITAIP2PCLIENT_H
