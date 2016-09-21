//
// Created by bensoer on 20/09/16.
//

#include "EndpointFactory.h"

EndpointFactory::EndpointFactory(Configuration configuration) {
    this->configuration = configuration;
}

IEndpoint * EndpointFactory::getEndpoint(int isServer) {

    if (isServer == 0) {

        if (this->configuration.source_host == 0 && this->configuration.dest_host == 0) {

            cout << "\n\nYou need to supply a source and destination address for client mode.\n\n";
            return nullptr;
        } else if (this->configuration.ack == 1) {
            printf("\n\n-ack decoding can only be used in SERVER mode (-server)\n\n");
            return nullptr;
        } else {


            printf("Destination Host: %s\n", this->configuration.desthost);
            printf("Source Host     : %s\n", this->configuration.srchost);

            if (this->configuration.source_port == 0) {

                printf("Originating Port: random\n");

            } else {

                printf("Originating Port: %u\n", this->configuration.source_port);
                printf("Destination Port: %u\n", this->configuration.dest_port);
                printf("Encoded Filename: %s\n", this->configuration.filename);

            }

            if (this->configuration.usettl == 1) {
                printf("Encoding Type   : TTL\n");
            }

            if (this->configuration.usesp == 1) {
                printf("Encoding Type    : Source Port\n");
            }

            if (this->configuration.usedp == 1) {
                printf("Encoding Type     : Dest Port\n");
            }

            if (this->configuration.usewin == 1) {
                printf("Encoding Type      : Window\n");
            }

            if (this->configuration.useflags == 1) {
                printf("Encoding Type       : Flags\n");
            }

            if (this->configuration.useack == 1) {
                printf("Encoding Type        : Ack Number\n");
            }

            if (this->configuration.usetos == 1) {
                printf("Encoding Type         : TOS\n");
            }

            if (this->configuration.usesrc == 1) {
                printf("Encoding Type          : Source Address");
            }

            if (this->configuration.ipid == 1) {

                printf("Encoding Type   : IP ID\n");

            } else if (this->configuration.seq == 1) {

                printf("Encoding Type   : IP Sequence Number\n");
                printf("\nClient Mode: Sending data.\n\n");

            }
        }


    //then this is a client were creating
    }else{




    }
}