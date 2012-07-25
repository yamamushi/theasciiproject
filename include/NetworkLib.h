#include <arpa/inet.h>   /* ntohl htonl */
#include <string.h>      /* memcpy */

class Packet {
    int senderId;
    int sequenceNumber;
    char data[MaxDataSize];
    
public:
    void* Serialize();
    void Deserialize(char *message);
};



