#ifndef MESSAGE
#define MESSAGE

#include "Contact.hpp"

class Message {
public:
  Message();
  Message(char *message, int messageSize, Contact recipient, Contact sender);
  Message(char *rawMessage);
  Message(const Message& m);
  char *getContents();
  int getRecipient();
  int getSender();
  void writeSendableMessage(char *dest);
  int getTotalSizeOfMessage();
  int getSizeOfMessage();
  bool isForMe(int uid);
private:
  char* messageContents;
  int messageSize;
  int recipient, sender;
};

#endif