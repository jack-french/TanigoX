#include "Menu.hpp"

Menu::Menu(TFT_eSPI *_tft) {
  this->tft = _tft;
}

void Menu::drawMainScreen(int highlight) {
  tft->setTextSize(4);
  tft->setTextColor(TFT_DARKGREEN, TFT_BLACK);
  if(highlight == 0) {
    tft->fillRect(55, 30, 200, 50, TFT_DARKGREEN);
    tft->setTextColor(TFT_BLACK, TFT_DARKGREEN);
    tft->drawString("MESSAGES", tft->width() / 2, 40);  
    tft->setTextColor(TFT_DARKGREEN, TFT_BLACK);
  } else {
    tft->drawString("MESSAGES", tft->width() / 2, 40);  
  }

  if(highlight == 1) {
    tft->fillRect(55, 90, 200, 50, TFT_DARKGREEN);
    tft->setTextColor(TFT_BLACK, TFT_DARKGREEN);
    tft->drawString("CONTACTS", tft->width() / 2, 100);
    tft->setTextColor(TFT_DARKGREEN, TFT_BLACK);

  } else {
    tft->drawString("CONTACTS", tft->width() / 2, 100);
  }

  if(highlight == 2) {
    tft->fillRect(55, 150, 200, 50, TFT_DARKGREEN);
    tft->setTextColor(TFT_BLACK, TFT_DARKGREEN);
    tft->drawString("SETTINGS", tft->width() / 2, 160);
    tft->setTextColor(TFT_DARKGREEN, TFT_BLACK);
  } else {
    tft->drawString("SETTINGS", tft->width() / 2, 160);
  }
}

void Menu::drawMessagesScreen() {
  tft->drawString("MESSAGES", tft->width() / 2, 100);
}

void Menu::drawContactsScreen() {
  tft->drawString("CONTACTS", tft->width() / 2, 100);
}

void Menu::drawSettingsScreen() {
  tft->drawString("SETTINGS", tft->width() / 2, 100);
}