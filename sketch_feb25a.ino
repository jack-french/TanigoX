#include <TFT_eSPI.h> // Hardware-specific library
#include <SPI.h>
#include "Menu.hpp"

#define version "Tanigox V0.1"

//Wireing defines
#define KNOB_PINA 15
#define KNOB_PINB 14
#define KNOB_DOWN 13

#define tolerance 250 //Time between inputs

TFT_eSPI tft = TFT_eSPI();
Menu menu = Menu(&tft);
Screen currentScreen;
bool hasUpdate = true;

//Tracking last inputs
int knobRotateLTU, knobDownLTU;
int aVal, oldAVal;

int highlight = 1;

void setup(void) {
  tft.init();
  tft.setRotation(1);

  tft.fillScreen(TFT_BLACK);
  tft.setTextSize(18);
  tft.setTextColor(TFT_DARKGREEN, TFT_BLACK);
  tft.setTextDatum(TC_DATUM); 
  tft.drawString("TANIGOX", tft.width() / 2, tft.height() / 2 - tft.fontHeight() / 2);
  delay(1000);
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
      processContactsScreen();
      break;
    case settingsScreen:
      processSettingsScreen();
      break;
  }
}

//Use this to determine what parameters are needed to be passed for different screens
void drawScreen(Screen currentScreen) {
  tft.fillScreen(TFT_BLACK);
  drawVersionInfo();
  switch(currentScreen) {
    case mainScreen:
      menu.drawMainScreen(highlight);
      break;
    case messagesScreen:
      menu.drawMessagesScreen();
      break;
    case contactsScreen:
      menu.drawContactsScreen(highlight);
      break;
    case settingsScreen:
      menu.drawSettingsScreen(highlight);
      break;
  }
}

void drawVersionInfo() {
  tft.setTextColor(TFT_DARKGREEN, TFT_BLACK);
  tft.setTextSize(1);
  tft.drawString(version, 280, 230);  
}

void processMainScreen() {
  if(isKnobDown()) {
    currentScreen = (Screen) (highlight + 1);
    highlight = 0;
    hasUpdate = true;
  }
  checkKnob(2);
}

void processMessageScreen() {
  if(isKnobDown()) {
    currentScreen = mainScreen;
    hasUpdate = true;
  }
}

void processContactsScreen() {
  if(isKnobDown()) {
    switch (highlight) {
      case 0:
        break;
      case 1:
        break;
      case 2:
        break;
      case 3: //Back
        highlight = 0;
        currentScreen = mainScreen;
        break;
    }
    hasUpdate = true;
  }
  checkKnob(3);
}

void processSettingsScreen() {
  if(isKnobDown()) {
    switch (highlight) {
      case 0:
        highlight = 0;
        currentScreen = mainScreen;
        break;
    }
    hasUpdate = true;
  }
  checkKnob(0);
}

//Utility Methods
void checkKnob(int max) {
  if (isKnobRotating()) {
    if (isKnobRotateCW()) {
      highlight++;
    } else {
      highlight --;
    }
    forceHightlightInBounds(max);
    hasUpdate = true;
  }  
}

bool isKnobRotating() {
  aVal = digitalRead(KNOB_PINA);
  if((aVal != oldAVal) && (millis() - knobRotateLTU) > tolerance) {
    knobRotateLTU = millis();
    oldAVal = aVal;
    return true;
  }
  oldAVal = aVal;
  return false;
}

bool isKnobRotateCW() {
  return digitalRead(KNOB_PINB) != aVal;
}

bool isKnobDown() {
  if((digitalRead(KNOB_DOWN) == LOW) && (millis() - knobDownLTU) > tolerance) {
    knobDownLTU = millis();
    return true;
  }
  return false;
}

void forceHightlightInBounds(int max) {
  if(highlight > max) {
    highlight = 0;
  } else if(highlight < 0) {
    highlight = max;
  }
}


