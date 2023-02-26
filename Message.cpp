#include "Message.hpp"

Message::Message(const char * _message) {
  message = _message;
}

const char * Message::getContents() {
  return message;
}