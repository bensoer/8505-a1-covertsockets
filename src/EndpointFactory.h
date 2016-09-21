//
// Created by bensoer on 20/09/16.
//

#ifndef INC_8505_A1_COVERTSOCKETS_ENDPOINTFACTORY_H
#define INC_8505_A1_COVERTSOCKETS_ENDPOINTFACTORY_H


#include "IEndpoint.h"
#include "EndpointFactory.h"
#include <iostream>

using namespace std;

struct Configuration {
    int dest_host;
    int source_host;
    char desthost[80];
    char srchost[80];
    char filename[80];

    int source_port;
    int dest_port;

    int seq;
    int ack;
    int ipid;
    int usettl;
    int usesp;
    int usedp;
    int usewin;
    int useflags;
    int usetos;
    int usesrc;
    int useack;
};

class EndpointFactory {

private:

    Configuration configuration;

public:

    EndpointFactory(Configuration configuration);

    IEndpoint * getEndpoint(int isServer);
};


#endif //INC_8505_A1_COVERTSOCKETS_ENDPOINTFACTORY_H
