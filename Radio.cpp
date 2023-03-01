#include "Radio.hpp"
#define TX 8
#define RX 9
#define AUX 7

Radio::Radio() {
  in;
  out;
  hasData = false;
}

void Radio::send(int numberOfBytes) {
  if(digitalRead(AUX) == 1) {
    Serial2.write(in, numberOfBytes); //should this be 14 or 14 * sizeof(char)?
  }
}

void Radio::read() {
  if (Serial2.available() > 0) {
    Serial2.readBytes(out, 512);
  }
}