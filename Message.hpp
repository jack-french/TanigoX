#ifndef MESSAGE
#define MESSAGE

#include "Contact.hpp"

class Message {
public:
  Message();
  Message(char *message, int messageSize, Contact recipient, Contact sender);
  Message(char *rawMessage);
  char *getContents();
  int getRecipient();
  int getSender();
  void writeSendableMessage(char *dest);
  bool isForMe(int uid);
private:
  char *message;
  int messageSize;
  int recipient, sender;
};

#endif