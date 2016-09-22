//
// Created by bensoer on 20/09/16.
//

#include <cstring>
#include "EndpointFactory.h"
#include "ClientEndpoint.h"
#include "ServerEndpoint.h"

EndpointFactory::EndpointFactory(Configuration configuration) {
    this->configuration = configuration;
}

IEndpoint * EndpointFactory::getEndpoint(int isServer) {

    if (isServer == 0) {
        //this is the client then

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

        ClientEndpoint * client = new ClientEndpoint();
        return client;


    //then this is a server were creating
    }else{


        if (this->configuration.source_host == 0 && this->configuration.source_port == 0){
            printf("You need to supply a source address and/or source port for server mode.\n");
            exit(1);
        }

        if(this->configuration.dest_host == 0){ /* if not host given, listen for anything.. */
            strcpy(this->configuration.desthost, "Any Host");
        }
        if(this->configuration.source_host == 0){
            strcpy(this->configuration.srchost, "Any Host");
            printf("Listening for data from IP: %s\n",this->configuration.srchost);
        }

        if(this->configuration.source_port == 0){
            printf("Listening for data bound for local port: Any Port\n");
        }else{
            printf("Listening for data bound for local port: %u\n",this->configuration.source_port);
            printf("Decoded Filename: %s\n",this->configuration.filename);
        }

        if(this->configuration.ipid == 1){

            printf("Decoding Type Is: IP packet ID\n");

        }else if(this->configuration.seq == 1){

            printf("Decoding Type Is: IP Sequence Number\n");

        }else if(this->configuration.ack == 1){

            printf("Decoding Type Is: IP ACK field bounced packet.\n");
            printf("\nServer Mode: Listening for data.\n\n");
        }else if(this->configuration.usettl == 1){
            printf("Decoding Type Is: TTL\n");
        }else if(this->configuration.usedp == 1){
            printf("Decoding Type Is: Dest Port\n");
        }else if(this->configuration.usesp == 1){
            printf("Decoding Type Is: Source Port\n");
        }else if(this->configuration.usewin == 1){
            printf("Decoding Type Is: Windows\n");
        }else if(this->configuration.useflags == 1){
            printf("Decoding Type Is: Flags\n");
        }else if(this->configuration.useack == 1){
            printf("Decoding Type Is: Ack Number\n");
        }else if(this->configuration.usetos == 1){
            printf("Decoding Type Is: TOS\n");
        }else if(this->configuration.usesrc == 1){
            printf("Decoding Type Is: Src Address\n");
        }


        ServerEndpoint * server = new ServerEndpoint();
        return server;

    }
}