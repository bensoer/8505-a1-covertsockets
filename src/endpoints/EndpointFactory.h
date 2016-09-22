//
// Created by bensoer on 20/09/16.
//

#ifndef INC_8505_A1_COVERTSOCKETS_ENDPOINTFACTORY_H
#define INC_8505_A1_COVERTSOCKETS_ENDPOINTFACTORY_H


#include "IEndpoint.h"
#include "../Configuration.h"

#include <iostream>

using namespace std;

class EndpointFactory {

private:

    Configuration configuration;

public:

    EndpointFactory(Configuration configuration);

    IEndpoint * getEndpoint(int isServer);
};


#endif //INC_8505_A1_COVERTSOCKETS_ENDPOINTFACTORY_H
