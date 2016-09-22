//
// Created by bensoer on 20/09/16.
//

#ifndef INC_8505_A1_COVERTSOCKETS_IENDPOINT_H
#define INC_8505_A1_COVERTSOCKETS_IENDPOINT_H

#include "../Configuration.h"

class IEndpoint {

protected:

    unsigned short in_cksum(unsigned short *ptr, int nbytes);

public:
    virtual void execute() = 0;
    virtual void setConfiguration(Configuration configuration) = 0;

};


#endif //INC_8505_A1_COVERTSOCKETS_IENDPOINT_H
