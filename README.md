#8505-a1-covertsockets
8505-a1-covertsockets is a recreation of Cragi Rowland's `covert_tcp.c` program written in C++.
 Craig's implementation was poorly coded and only demonstrated some bar minimum basic options
 available when creating covert sockets. This project expands and tidies up Craig's work in C++
 by refactoring his work into a more object-oriented strucutre. Ontop of the that, options to
 send and receive data covertly through additional headers has been added. Craig's implementation
 originaly only allows for transfer via the TCP Sequence Number and the IP ID Header. This implementation
 has added the following additional transmission options:
 
* TCP Source Port
* TCP Destination Port
* TCP Window Size
* TCP Flags
* TCP Acknowledgement Number
* IP Time To Live Header
* IP Type Of Service Header

The implementation of these headers is identical to Craig Rowland's implementation and therefor is strictly
a proof of concept. Each additional header has its advantages and disadvantages. In the `docs` folder you
can view the `Covert Socket Critiques And Improvements` to see an overview of some of the benefits and
setbacks of using each header. Additionaly, you can view Craig Rowlands original work along with a guide
and overview in the `examples` folder. Craig's documentation includes recommendations for improvement on
his own code and some of the benefits and setbacks that exist in his implementation


#Setup
##Prerequisites
`cmake` must be installed on your system and be accessible via the command line to compile the project.
#Installation
1) Clone the Repo
2) Open terminal and `cd` to the project root
3) Execute: `cmake .`
4) The project will then be compiled. Output files are stored in the `/bin` folder

#Usage
##Covert Server
To setup a server to receive covert messages execute the following command within the `/bin` folder
```
sudo ./8505_a1_covertsockets -source <ipofclient> -server -file <filetoprintmessageto>
```
You will need to supply the IP Address of the client that will be sending coverted messages to the server in the
above command along with a file name to output the message to. The server will print each character to the
console and will print the entire message to the file
##Covert Client
To setup a client to send covert messages execute the following command within the `/bin` folder
```
sudo ./8505_a1_covertsockets -source <ipofclient> -dest <ipofserver> -file <filetoreadmessagefrom>
```
The above needs to be supplied an ip of the client machine which the covert messages will be sent out, and IP of
the server which the covert messages will be sent to and a text file which contains the message to be sent. The
text file can be passed as an absolute or relative path. If the filename is only supplied then it will be assumed
it is located within the same directory as the application (in this example the `/bin` folder).
##Using Other Headers
By default the above Covert Server and Covert Client will send via the IP ID header. To use other headers, use the
same setup and parameters as listed above but add the following flags to switch to the appropriate header.

| Header | Flag |
|--------|------|
| TCP Source Port | -usesp |
| TCP Destination Port | -usedp |
| TCP Window Size | -usewin |
| TCP Flags | -useflags |
| TCP Acknowledgement Number | -useack |
| IP Time To Live | -usettl |
| IP Type Of Service | -usetos |

Note when using these other headers, you need to include the flags on *both* the client and the server systems.