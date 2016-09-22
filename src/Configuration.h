//
// Created by bensoer on 21/09/16.
//

#ifndef INC_8505_A1_COVERTSOCKETS_CONFIGURATION_H
#define INC_8505_A1_COVERTSOCKETS_CONFIGURATION_H

/**
 * Configuration stores information about the configuration of the client or server. This is passed around
 * the application so as to give context to the various components in terms of what state the application
 * currently is in, and how it should operate under certain parameters
 */
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


#endif //INC_8505_A1_COVERTSOCKETS_CONFIGURATION_H
