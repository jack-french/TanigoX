#include "Radio.hpp"
#define TX 8
#define RX 9
#define AUX 7

Radio::Radio() {
  hasData = false;
}

void Radio::send(Message message) {
  if(digitalRead(AUX) == 1) {
    char sendable[message.getTotalSizeOfMessage()];
    message.writeSendableMessage(sendable);
    Serial2.write(sendable, message.getTotalSizeOfMessage());
  }
}

void Radio::read(char *dest) {
  int numberToRead = 3; //To find the actual number
  int numBytesRead = 0;
  while(digitalRead(AUX) != HIGH) {
    if (Serial2.available() > 0) {
      numBytesRead += Serial2.readBytes(dest + numBytesRead, numberToRead - numBytesRead);
      if(numBytesRead == 3) {
        numberToRead += dest[2];
      }
    }
  }
}