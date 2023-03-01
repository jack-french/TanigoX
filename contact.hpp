#ifndef CONTACT
#define CONTACT

class Contact {
public:
  Contact();
  Contact(char *name, int uid);
  char *name;
  int uid;
};

#endif