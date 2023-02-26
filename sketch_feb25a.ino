/*
  Ellipse drawing example

  This sketch does not use any fonts.
*/
#include <TFT_eSPI.h> // Hardware-specific library
#include <SPI.h>
#include "menu.hpp"

TFT_eSPI tft = TFT_eSPI();       // Invoke custom library
int KNOB_PINA = 15;
int KNOB_PINB = 14;
int KNOB_DOWN = 13;

void setup(void) {
  tft.init();
  tft.setRotation(1);

  tft.fillScreen(TFT_BLACK);
  tft.setTextSize(18);
  tft.setTextColor(TFT_DARKGREEN, TFT_BLACK);
  tft.setTextDatum(TC_DATUM); 
  int xpos = tft.width() / 2; 
  int ypos = tft.height() / 2;
  tft.drawString("TANIGOX", xpos, ypos - tft.fontHeight() / 2);
  delay(3000);
  tft.setTextSize(4);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(KNOB_PINA, INPUT);
  pinMode(KNOB_PINB, INPUT);

}

tanidraw::Screen currentScreen;
bool hasUpdate = true;
int highlight = 1;
int aVal, pinALast, lastUpdateTime;
boolean bCW;

void loop() {
  if(digitalRead(KNOB_DOWN) == LOW) {
    currentScreen = (tanidraw::Screen) (highlight + 1);
    hasUpdate = true;
  }
  //tft.pushImageDMA(int32_t x, int32_t y, int32_t w, int32_t h, uint16_t *data)
  aVal = digitalRead(KNOB_PINA);
  if ((aVal != pinALast) && (millis() - lastUpdateTime) > 250) { // Means the knob is rotating
    // if the knob is rotating, we need to determine direction
    // We do that by reading pin B.
    lastUpdateTime = millis();
    if (digitalRead(KNOB_PINB) != aVal) { // Means pin A Changed first - We're Rotating Clockwise
      bCW = true;
    } else {// Otherwise B changed first and we're moving CCW
      bCW = false;
    }
    if (bCW){
      highlight++;
      if(highlight > 2) {
        highlight = 0;
      }
      hasUpdate = true;
    } else{
      highlight --;
      if(highlight < 0) {
        highlight = 2;
      }
      hasUpdate = true;
    }
  }
  pinALast = aVal;

  //only need to draw the screen if something has changed.
  //other functions should set hasUpdate to true if this is the case.
  if(hasUpdate) {
    hasUpdate = false;
    drawScreen(currentScreen);
  }
}

void drawScreen(tanidraw::Screen currentScreen) {
  tft.fillScreen(TFT_BLACK);
  switch(currentScreen) {
    case tanidraw::mainScreen:
      drawMainScreen();
      break;
    case tanidraw::messagesScreen:
      drawMessagesScreen();
      break;
    case tanidraw::contactsScreen:
      drawContactsScreen();
      break;
    case tanidraw::settingsScreen:
      drawSettingsScreen();
      break;
  }
}

void drawMainScreen() {
  if(highlight == 0) {
    tft.fillRect(55, 30, 200, 50, TFT_DARKGREEN);
    tft.setTextColor(TFT_BLACK, TFT_DARKGREEN);
    tft.drawString("MESSAGES", tft.width() / 2, 40);  
    tft.setTextColor(TFT_DARKGREEN, TFT_BLACK);
  } else {
    tft.drawString("MESSAGES", tft.width() / 2, 40);  
  }

  if(highlight == 1) {
    tft.fillRect(55, 90, 200, 50, TFT_DARKGREEN);
    tft.setTextColor(TFT_BLACK, TFT_DARKGREEN);
    tft.drawString("CONTACTS", tft.width() / 2, 100);
    tft.setTextColor(TFT_DARKGREEN, TFT_BLACK);

  } else {
    tft.drawString("CONTACTS", tft.width() / 2, 100);
  }

  if(highlight == 2) {
    tft.fillRect(55, 150, 200, 50, TFT_DARKGREEN);
    tft.setTextColor(TFT_BLACK, TFT_DARKGREEN);
    tft.drawString("SETTINGS", tft.width() / 2, 160);
    tft.setTextColor(TFT_DARKGREEN, TFT_BLACK);
  } else {
    tft.drawString("SETTINGS", tft.width() / 2, 160);
  }
}

void drawMessagesScreen() {
  tft.drawString("MESSAGES", tft.width() / 2, 100);
}

void drawContactsScreen() {
  tft.drawString("CONTACTS", tft.width() / 2, 100);
}

void drawSettingsScreen() {
  tft.drawString("SETTINGS", tft.width() / 2, 100);
}

