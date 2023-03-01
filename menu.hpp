#ifndef MENU
#define MENU

#include <TFT_eSPI.h> // Hardware-specific library
#include <SPI.h>
#include "contact.hpp"
#include "Conversation.hpp"

enum Screen {
  mainScreen, messagesScreen, contactsScreen, settingsScreen,
  contactsList, contactsAdd, contactsRemove
};

class Menu {
public:
  Menu(TFT_eSPI *tft);
  void drawMainScreen(int highlight);
  void drawMessagesScreen(int highlight, int numberOfConversations, Conversation *conversations);
  void drawContactsScreen(int highlight);
  void drawSettingsScreen(int highlight);

  void drawContactsList(Contact contacts[]);
  void drawContactsAdd(int x, int y);

  char characters[5][8] = {
    {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'},
    {'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P'},
    {'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X'},
    {'Y', 'Z', '_', ',', '.', '0', '1', '2'},
    {'3', '4', '5', '6', '7', '8', '9', 'X'},
  };
private:
  TFT_eSPI *tft;
  void drawVerticalList(const char ** listValues, int num, int highlight);
  void drawTextEntryScreen(int x, int y);
};

#endif