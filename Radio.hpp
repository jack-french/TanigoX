#include <TFT_eSPI.h> // Hardware-specific library
#include <SPI.h>


class Radio {
public:
  Radio();
  char in[512];
  char out[512];
  bool hasData;
  void send(int bytes);
};