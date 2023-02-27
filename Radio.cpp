#include "Radio.hpp"
#define TX 8
#define RX 9
#define AUX 7

Radio::Radio() {
  in;
  out;
  hasData = false;
}

void Radio::send(int bytes) {
  if(digitalRead(AUX) == 1) {
    Serial2.write(in, 512); //should this be 14 or 14 * sizeof(char)?
    Serial2.write(in, 512);
    Serial2.write(in, 512);
    Serial2.write(in, 512);
    Serial2.write(in, 512);
  }
}