#include <TFT_eSPI.h> // Hardware-specific library
#include <SPI.h>
#include "Menu.hpp"
#include "Radio.hpp"
#include "Message.hpp"
#include "Conversation.hpp"

#define version "Tanigox V0.1"

//Knob Pins
#define KNOB_PINA 15
#define KNOB_PINB 14
#define KNOB_DOWN 13

//Radio Pins
#define TX 8
#define RX 9
#define AUX 7

#define tolerance 250 //Time between inputs

TFT_eSPI tft = TFT_eSPI();
Menu menu = Menu(&tft);
Screen currentScreen;
bool hasUpdate = true;

//Tracking last inputs
int knobRotateLTU, knobDownLTU;
int aVal, oldAVal;

int highlight = 1;

//char selection
bool isColSelection = true;
int x = 0, y = 0;
char selectionOutput[128];
int currentSelectionPos;

//Contacts
Contact myContact = Contact((char*) "Tani1", 1);
Contact contacts[1] = {Contact((char*) "Tani2", 2)}; //Just for our group a hardcode like this could be a option. I would prefer to have some contact message you can send out though
Conversation conversations[1] = {Conversation(contacts[0])};
int numberOfConversations = 1;

//Radio
Radio radio = Radio();
char recievedContents[512];
Message recievedMessage = Message();

uint32_t dummy;

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
  
  
  pinMode(AUX, INPUT);
  Serial2.setRX(RX);
  Serial2.setTX(TX);
  Serial2.begin(9600);
}

void loop() {
  if(rp2040.fifo.pop_nb(&dummy)) {
    //handleMessage();
  }

  processInputs(currentScreen);

  //only need to draw the screen if something has changed.
  //other functions should set hasUpdate to true if this is the case.
  if(hasUpdate) {
    hasUpdate = false;
    drawScreen(currentScreen);
  }
}

void setup1() {
  delay(5000);
}

void loop1() { //Second core is in charge of recieving any messages
  PinStatus auxStatus = digitalRead(AUX);
  if(auxStatus == LOW) {
    radio.read(recievedContents);
    recievedMessage = Message(recievedContents);
    if(recievedMessage.isForMe(myContact.uid)) {
      int sender = recievedMessage.getSender();
      for(Conversation c : conversations) {
        if(c.getContact().uid == sender) {
          c.addMessage(recievedMessage);
          hasUpdate = true;
          break;
        }
      }
    } else {
      //TODO relay the message
    }
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
    case contactsList:
      processContactsList();
      break;
    case contactsAdd:
      processContactsAdd();
      break;
    case contactsRemove:
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
      menu.drawMessagesScreen(highlight, numberOfConversations, conversations);
      break;
    case contactsScreen:
      menu.drawContactsScreen(highlight);
      break;
    case settingsScreen:
      menu.drawSettingsScreen(highlight);
      break;
    case contactsList:
      menu.drawContactsList(contacts);
      break;
    case contactsAdd:
      menu.drawContactsAdd(x, y);
      break;
    case contactsRemove:
      break;
  }
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
        currentScreen = contactsList;
        break;
      case 1:
        currentScreen = contactsAdd;
        break;
      case 2:
        currentScreen = contactsRemove;
        break;
      case 3: //Back
        currentScreen = mainScreen;
        break;
    }
    highlight = 0;
    hasUpdate = true;
  }
  checkKnob(3);
}

void processSettingsScreen() {
  if(isKnobDown()) {
    switch (highlight) {
      case 0: {
        char dummy[] = "uoooh cunny";
        //memcpy(radio.in, &dummy, 11);
        //radio.send(14);
        break;
      }
      case 1:
        highlight = 0;
        currentScreen = mainScreen;
        break;
    }
    hasUpdate = true;
  }
  checkKnob(1);
}

void processContactsList() {

}

void processContactsAdd() {
  if(isKnobDown()) {
    if(isColSelection) {
      isColSelection = false;
    } else {
      if(y == 4 && x == 7) { //Terminate condition
        currentScreen = contactsScreen;
        selectionOutput[currentSelectionPos] = 0;
        contacts[0] = Contact(&selectionOutput[0], 0);
      } else {
        selectionOutput[currentSelectionPos] = menu.characters[y][x];
        currentSelectionPos++;
        isColSelection = true;
      }
    }
    hasUpdate = true;    
  }

  if (isKnobRotating()) {
    if (isColSelection) {
      if(isKnobRotateCW()) {
        x++;
      } else {
        x--;        
      }
    } else {
      if(isKnobRotateCW()) {
        y++;
      } else {
        y--;
      }
    }
    hasUpdate = true;
  }    
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

void drawVersionInfo() {
  tft.setTextColor(TFT_DARKGREEN, TFT_BLACK);
  tft.setTextSize(1);
  tft.drawString(version, 280, 230);  
}

