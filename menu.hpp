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
private:
  TFT_eSPI *tft;
  void drawVerticalList(const char ** listValues, int num, int highlight);
};