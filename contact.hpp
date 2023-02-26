#include "Message.hpp"

class Contact {
public:
  Contact();
  Contact(char * name);
  char * name;
  int uid;
  Message * messagesRecieved;
};