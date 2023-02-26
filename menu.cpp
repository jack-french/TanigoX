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

void Menu::drawMainScreen(int highlight) {
  const char *listValues[] = { "MESSAGES", "CONTACTS", "SETTINGS" };
  drawVerticalList(listValues, 3, highlight);
}

void Menu::drawMessagesScreen() {
  tft->drawString("MESSAGES", tft->width() / 2, 100);
}

void Menu::drawContactsScreen(int highlight) {
  const char *listValues[] = { "LIST", "ADD", "REMOVE", "BACK" };
  drawVerticalList(listValues, 4, highlight);
}

void Menu::drawSettingsScreen(int highlight) {
  const char *listValues[] = { "BACK" };
  drawVerticalList(listValues, 1, highlight);
}