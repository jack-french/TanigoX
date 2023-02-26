#include <TFT_eSPI.h> // Hardware-specific library
#include <SPI.h>

enum Screen {
  mainScreen, messagesScreen, contactsScreen, settingsScreen 
};

class Menu {
public:
  Menu(TFT_eSPI *tft);
  void drawMainScreen(int highlight);
  void drawMessagesScreen();
  void drawContactsScreen();
  void drawSettingsScreen();
private:
  TFT_eSPI *tft;
};
