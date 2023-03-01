#include "Contact.hpp"

class Message {
public:
  Message();
  Message(char *message, int messageSize, Contact recipient);
  Message(char *rawMessage);
  char *getContents();
  Contact getRecipient();
  void writeSendableMessage(char *dest);
  bool isForMe(int uid);
private:
  char *message;
  int messageSize;
  Contact recipient;
};