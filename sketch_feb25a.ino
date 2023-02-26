#include <TFT_eSPI.h> // Hardware-specific library
#include <SPI.h>
#include "Menu.hpp"

//Wireing defines
#define KNOB_PINA 15
#define KNOB_PINB 14
#define KNOB_DOWN 13

#define tolerance 250 //Time between inputs

TFT_eSPI tft = TFT_eSPI();
Menu menu = Menu(&tft);
Screen currentScreen;

//Tracking last inputs
int knobRotateLTU, knobDownLTU;

bool hasUpdate = true;
int highlight = 1;
int aVal, pinALast;
boolean bCW;

void setup(void) {
  tft.init();
  tft.setRotation(1);

  tft.fillScreen(TFT_BLACK);
  tft.setTextSize(18);
  tft.setTextColor(TFT_DARKGREEN, TFT_BLACK);
  tft.setTextDatum(TC_DATUM); 
  tft.drawString("TANIGOX", tft.width() / 2, tft.height() / 2 - tft.fontHeight() / 2);
  delay(3000);
  tft.setTextSize(4);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(KNOB_PINA, INPUT);
  pinMode(KNOB_PINB, INPUT);
}

void loop() {
  processInputs(currentScreen);

  //only need to draw the screen if something has changed.
  //other functions should set hasUpdate to true if this is the case.
  if(hasUpdate) {
    hasUpdate = false;
    drawScreen(currentScreen);
  }
}

void processInputs(Screen currentScreen) {
  switch(currentScreen) {
    case mainScreen:
      processMainScreen();
      break;
    case messagesScreen:
      processMessageScreen();
      break;
    case contactsScreen:
      break;
    case settingsScreen:
      break;
  }
}

//Use this to determine what parameters are needed to be passed for different screens
void drawScreen(Screen currentScreen) {
  tft.fillScreen(TFT_BLACK);
  switch(currentScreen) {
    case mainScreen:
      menu.drawMainScreen(highlight);
      break;
    case messagesScreen:
      menu.drawMessagesScreen();
      break;
    case contactsScreen:
      menu.drawContactsScreen();
      break;
    case settingsScreen:
      menu.drawSettingsScreen();
      break;
  }
}

void processMainScreen() {
  if(isKnobDown()) {
    currentScreen = (Screen) (highlight + 1);
    hasUpdate = true;
  }
  aVal = digitalRead(KNOB_PINA);
  if (isKnobRotating()) {
    bCW = digitalRead(KNOB_PINB) != aVal; //check which way rotate
    if (bCW){
      highlight++;
      if(highlight > 2) {
        highlight = 0;
      }
      hasUpdate = true;
    } else {
      highlight --;
      if(highlight < 0) {
        highlight = 2;
      }
      hasUpdate = true;
    }
  }
  pinALast = aVal;
}

void processMessageScreen() {
  if(isKnobDown()) {
    currentScreen = mainScreen;
    hasUpdate = true;
  }
}

//Utility Methods
bool isKnobRotating() {
  if((digitalRead(KNOB_PINA) != pinALast) && (millis() - knobRotateLTU) > tolerance) {
    knobRotateLTU = millis();
    return true;    
  }
  return false;
}

bool isKnobDown() {
  if((digitalRead(KNOB_DOWN) == LOW) && (millis() - knobDownLTU) > tolerance) {
    knobDownLTU = millis();
    return true;
  }
  return false;
}


