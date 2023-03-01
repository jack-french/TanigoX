#include "Message.hpp"
#include <cstring>

Message::Message() {

}

Message::Message(char *_message, int _messageSize, Contact _recipient, Contact _sender) {
  message = _message;
  messageSize = _messageSize;
  recipient = _recipient.uid;
  sender = _sender.uid;
}

Message::Message(char *rawMessage) {
  recipient = rawMessage[0];
  sender = rawMessage[1];
  messageSize = rawMessage[2];
  memcpy(message, &rawMessage[3], messageSize);
}

char *Message::getContents() {
  return message;
}

int Message::getRecipient() {
  return recipient;
}

int Message::getSender() {
  return sender;
}

void Message::writeSendableMessage(char *dest) {
  dest[0] = recipient;
  dest[1] = sender;
  dest[2] = messageSize;
  memcpy(dest + 3, message, messageSize);
}

bool Message::isForMe(int _uid) {
  return recipient == _uid;
}