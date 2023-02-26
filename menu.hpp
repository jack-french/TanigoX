#include <TFT_eSPI.h> // Hardware-specific library
#include <SPI.h>

enum Screen {
  mainScreen, messagesScreen, contactsScreen, settingsScreen,
  contactsList, contactsAdd, contactsRemove
};

class Menu {
public:
  Menu(TFT_eSPI *tft);
  void drawMainScreen(int highlight);
  void drawMessagesScreen();
  void drawContactsScreen(int highlight);
  void drawSettingsScreen(int highlight);

  void drawContactsAdd(int x, int y);
private:
  TFT_eSPI *tft;
  char characters[5][8] = {
    {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'},
    {'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P'},
    {'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X'},
    {'Y', 'Z', '_', ',', '.', '?', '0', '1'},
    {'2', '3', '4', '5', '6', '7', '8', '9'},
  };
  void drawVerticalList(const char ** listValues, int num, int highlight);
  void drawTextEntryScreen(int x, int y);
};