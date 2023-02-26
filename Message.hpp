class Message {
public:
  Message(const char * message);
  const char * getContents();
private:
  const char * message;
};