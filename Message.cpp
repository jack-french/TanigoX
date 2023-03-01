#include "Message.hpp"
#include <cstring>

Message::Message() {

}

Message::Message(char *_message, int _messageSize, Contact _recipient) {
  message = _message;
  messageSize = _messageSize;
  recipient = _recipient;
}

Message::Message(char *rawMessage) {

}

char *Message::getContents() {
  return message;
}

Contact Message::getRecipient() {
  return recipient;
}

void Message::writeSendableMessage(char *dest) {
  dest[0] = recipient.uid;
  memcpy(dest + 1, message, messageSize);
}

bool Message::isForMe(int uid) {
  return false;
}