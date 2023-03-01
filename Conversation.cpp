#include "Conversation.hpp"

Conversation::Conversation(Contact _contact) {
  contact = _contact;
  numberOfMessages = 0;
}

void Conversation::addMessage(Message _message) {
  if(numberOfMessages < 32) {
    messages[numberOfMessages] = _message;
    numberOfMessages ++;
  } else {
    for(int i = 0; i < numberOfMessages - 1; i++) {
      messages[i] = messages[i + 1];
    }
    messages[numberOfMessages - 1] = _message;
  }
}

Message* Conversation::getMessages() {
  return messages;
}

int Conversation::getNumberOfMessages() {
  return numberOfMessages;
}