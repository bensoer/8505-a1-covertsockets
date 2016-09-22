//
// Created by bensoer on 20/09/16.
//

#ifndef INC_8505_A1_COVERTSOCKETS_SERVERENDPOINT_H
#define INC_8505_A1_COVERTSOCKETS_SERVERENDPOINT_H


#include "../IEndpoint.h"

class ServerEndpoint : public IEndpoint{

private:
    Configuration configuration;
public:
    void execute();
    void setConfiguration(Configuration configuration);
};


#endif //INC_8505_A1_COVERTSOCKETS_SERVERENDPOINT_H
