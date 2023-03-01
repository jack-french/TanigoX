#include <TFT_eSPI.h> // Hardware-specific library
#include <SPI.h>

class Radio {
public:
  Radio();
  bool hasData;
  void send(char *message, int numberOfBytes);
  void read(char *dest);
};