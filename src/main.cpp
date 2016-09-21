#include<iostream>
#include <zconf.h>
#include <cstring>
#include <dnet.h>

#include "utils/argparser.h"

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



int main(int argc, char * argv[]){

    cout << "CovertSockets - Initalizing" << endl;

    /* Can they run this? */
    if(geteuid() !=0){
        cout << "You Need To Be Root To Run This. Aborting" << endl;
        return 1;
    }

    ArgParcer arguments;

    //lets parse some parameters
    unsigned int source_host = 0;
    unsigned int dest_host = 0;
    unsigned short source_port = (unsigned short)arguments.GetTagVal("-source_port", argv, argc, 0);
    unsigned short dest_port = (unsigned short)arguments.GetTagVal("-dest_port", argv, argc, 80);
    int ipid= arguments.GetTagVal("-ipid", argv, argc, 0);
    int seq= arguments.GetTagVal("-seq", argv, argc, 0);
    int ack= arguments.GetTagVal("-ack", argv, argc, 0);
    int server= arguments.GetTagVal("-server", argv, argc, 0);

    int file=0;
    char filename[80];
    if(arguments.HasTagVal("-file", argv, argc)){
        file = 1;
        string fn = arguments.GetTagData("-file", argv, argc);
        strncpy(filename,&fn, fn.length());
    }

    char srchost[80];
    if(arguments.HasTagVal("-source", argv, argc)){

        source_host=host_convert(arguments.GetTagData("-source", argv, argc).c_str());

        string sh = arguments.GetTagData("-source", argv,argc);
        strncpy(srchost,&sh,sh.length());
    }

    char desthost[80];
    if(arguments.HasTagVal("-dest", argv, argc)){

        dest_host = host_convert(arguments.GetTagData("-dest", argv, argc).c_str());

        string dh = arguments.GetTagData("-dest", argv, argc);
        strncpy(desthost, &dh, dh.length());
    }

    int usettl = arguments.GetTagVal("-usettl", argv,argc, 0);
    int usesp = arguments.GetTagVal("-usesp", argv, argc, 0);
    int usedp = arguments.GetTagVal("-usedp", argv, argc, 0);
    int usewin = arguments.GetTagVal("-usewin", argv, argc, 0);

    int useack = arguments.GetTagVal("-useack", argv, argc, 0);
    int usetos = arguments.GetTagVal("-usetos", argv, argc, 0);
    int usesrc = arguments.GetTagVal("-usesrc", argv, argc, 0);
    int useflags = arguments.GetTagVal("-useflags", argv,argc, 0);


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


    return 0;
}