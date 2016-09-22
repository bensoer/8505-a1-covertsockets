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
and overview in the `examnples` folder. Craig's documentation includes recommendations for improvement on
his own code and some of the benefits and setbacks that exist in his implementation