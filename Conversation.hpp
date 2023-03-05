#ifndef CONVERSATION
#define CONVERSATION

#include "Contact.hpp"
#include "Message.hpp"

class Conversation {
public:
  Conversation();
  Conversation(Contact contact);
  void addMessage(Message message);
  Message* getMessages();
  Message getMessage(int i);
  int getNumberOfMessages();
  Contact getContact();
private:
  Contact contact;
  Message messages[32];
  int numberOfMessages;
};

#endif