#include "headers.h"


void* Packet::Serialize() {
    struct SerializedPacket *s = new SerializedPacket();
    s->senderId = htonl(this->senderId);
    s->sequenceNumber = htonl(this->sequenceNumber);
    memcpy(s->data, this->data, MaxDataSize);
    return s;
}

void Packet::Deserialize(char *message) {
    struct SerializedPacket *s = (struct SerializedPacket*)message;
    this->senderId = ntohl(s->senderId);
    this->sequenceNumber = ntohl(s->sequenceNumber);
    memcpy(this->data, s->data, MaxDataSize);
}