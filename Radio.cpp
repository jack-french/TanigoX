#include "Radio.hpp"
#define TX 8
#define RX 9
#define AUX 7

Radio::Radio() {
  hasData = false;
}

void Radio::send(char *message, int numberOfBytes) {
  if(digitalRead(AUX) == 1) {
    Serial2.write(message, numberOfBytes);
  }
}

void Radio::read(char *dest) {
  if (Serial2.available() > 0) {
    Serial2.readBytes(dest, 512); //other Serial2.read... methods may be better choice
  }
}