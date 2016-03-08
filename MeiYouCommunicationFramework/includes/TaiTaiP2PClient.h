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
    enum class States {FINISHED, ERROR};
public:
    TaiTaiP2PClient(const std::string &ip, const int &port);
    virtual ~TaiTaiP2PClient();
    virtual States              client();
    virtual sf::Socket::Status  socketBuild();
    virtual void                socketDestroy();
};


#endif //MEIYOUCOMMUNICATION_TAITAIP2PCLIENT_H
