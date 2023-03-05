#include <TFT_eSPI.h> // Hardware-specific library
#include <SPI.h>
#include "Message.hpp"

class Radio {
public:
  Radio();
  bool hasData;
  void send(Message message);
  void read(char *dest);
};