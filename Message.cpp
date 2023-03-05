#include <string.h>
#include "Message.hpp"
#include <cstring>

Message::Message() {

}

Message::Message(char *_message, int _messageSize, Contact _recipient, Contact _sender) {
  messageSize = _messageSize;
  messageContents = new char[_messageSize];
  memcpy(messageContents, _message, messageSize);
  recipient = _recipient.uid;
  sender = _sender.uid;
}

Message::Message(char *rawMessage) {
  recipient = rawMessage[0];
  sender = rawMessage[1];
  messageSize = rawMessage[2];
  messageContents = new char[messageSize];
  memcpy(messageContents, &rawMessage[3], messageSize);
}

Message::Message(const Message& m) {
  recipient = m.recipient;
  sender = m.sender;
  messageSize = m.messageSize;
  messageContents = new char[m.messageSize];
  memcpy(messageContents, m.messageContents, m.messageSize);

}

char* Message::getContents() {
  return messageContents;
}

int Message::getRecipient() {
  return recipient;
}

int Message::getSender() {
  return sender;
}

void Message::writeSendableMessage(char *dest) {
  dest[0] = (char) recipient;
  dest[1] = (char) sender;
  dest[2] = (char) messageSize;
  memcpy(dest + 3, messageContents, messageSize);
}

int Message::getSizeOfMessage() {
  return messageSize;
}

int Message::getTotalSizeOfMessage() {
  return messageSize + 3;
}

bool Message::isForMe(int _uid) {
  return recipient == _uid;
}