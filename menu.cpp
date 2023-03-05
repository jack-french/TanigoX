#include "Menu.hpp"

Menu::Menu(TFT_eSPI *_tft) {
  this->tft = _tft;
}

void Menu::drawVerticalList(const char ** listValues, int num, int highlight) {
  tft->setTextDatum(MC_DATUM);
  tft->setTextSize(4);
  tft->setTextColor(TFT_DARKGREEN, TFT_BLACK);
  for(int i = 0; i < num; i++) {
    int ypos = (i + 1) * (240 / (num + 1));
    if(highlight == i) {
      int width = tft->textWidth(listValues[i]);
      tft->fillRect(153 - width / 2, ypos - 27, width + 10, 50, TFT_DARKGREEN);
      tft->setTextColor(TFT_BLACK, TFT_DARKGREEN);
      tft->drawString(listValues[i], tft->width() / 2, ypos);  
      tft->setTextColor(TFT_DARKGREEN, TFT_BLACK);
    } else {
      tft->drawString(listValues[i], tft->width() / 2, ypos);  
    }
  }
}

void Menu::drawTextEntryScreen(int x, int y) {
  tft->setTextDatum(MC_DATUM);
  tft->setTextSize(4);
  tft->setTextColor(TFT_DARKGREEN, TFT_BLACK);
  for(int j = 0; j < 5; j++) {
    for(int i = 0; i < 8; i++) {
      if(j == y && i == x) {
        tft->drawChar(40 * i + 10, 48 * j, characters[j][i], TFT_BLACK, TFT_DARKGREEN, 4);
      } else {
        tft->drawChar(characters[j][i], 40 * i + 10, 48 * j);
      }
    }
  }
}

void Menu::drawMainScreen(int highlight) {
  const char *listValues[] = { "MESSAGES", "CONTACTS", "SETTINGS" };
  drawVerticalList(listValues, 3, highlight);
}

void Menu::drawMessagesScreen(int highlight, int numberOfConversations, Conversation *conversations) {
  char *conversationNames[numberOfConversations];
  for(int i = 0; i < numberOfConversations; i++) {
    conversationNames[i] = conversations[i].getContact().name;
  }
  drawVerticalList((const char**) conversationNames, numberOfConversations, highlight);
}

void Menu::drawConversationScreen(Conversation conversation) {
  Serial.print("Drawing Conversation");
  int numberOfMessages = conversation.getNumberOfMessages();
  Serial.print(numberOfMessages);
  Serial.print(conversation.getMessage(0).getTotalSizeOfMessage());
  Serial.print(conversation.getMessage(0).getContents());
  //char* messageTexts = new char[numberOfMessages][256];
  char **messageTexts = new char*[numberOfMessages];
  Serial.print("initalized");
  for(int i = 0; i < numberOfMessages; i++) {
    Serial.print("Got to loop");
    messageTexts[i] = new char[conversation.getMessage(i).getSizeOfMessage()];
    memcpy(messageTexts[i], conversation.getMessage(i).getContents(), conversation.getMessage(i).getSizeOfMessage());
  }
  Serial.print("Got to draw");
  drawVerticalList((const char**) messageTexts, numberOfMessages, 0);
  delete messageTexts;
}

void Menu::drawContactsScreen(int highlight) {
  const char *listValues[] = { "LIST", "ADD", "REMOVE", "BACK" };
  drawVerticalList(listValues, 4, highlight);
}

void Menu::drawSettingsScreen(int highlight) {
  const char *listValues[] = { "TEST SEND", "BACK" };
  drawVerticalList(listValues, 2, highlight);
}

void Menu::drawContactsList(Contact *contacts) {
  tft->setTextDatum(MC_DATUM);
  tft->setTextSize(4);
  tft->setTextColor(TFT_DARKGREEN, TFT_BLACK);
  tft->drawString(contacts[0].name, tft->width() / 2, 100);  
}

void Menu::drawContactsAdd(int x, int y) {
  drawTextEntryScreen(x, y);  
}