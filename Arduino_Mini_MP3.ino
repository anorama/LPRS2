#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

# define ACTIVATED LOW

SoftwareSerial mySoftwareSerial(10, 11); // TX, RX
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);

  /*---------------------- BUTTONS ----------------------*/
  const int buttonNext = 2;
  const int buttonPrevious = 3;
  int buttonStateNext = 0; 
  int buttonStatePrevious = 0; 
  boolean isPlaying = false;
  /*-----------------------------------------------------*/

void setup()
{
  mySoftwareSerial.begin(9600);
  Serial.begin(9600);

  /*--------------- INITIALIZE PUSHBUTTONS ---------------*/
  pinMode(buttonNext, INPUT_PULLUP);
  pinMode(buttonPrevious, INPUT_PULLUP);
  /*------------------------------------------------------*/
  
  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3 to 5 seconds)"));
  
  if (!myDFPlayer.begin(mySoftwareSerial)) {                //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true);
  }
  Serial.println(F("DFPlayer Mini online."));
  
  myDFPlayer.volume(15);  //Set volume value. From 0 to 30
  
  myDFPlayer.play(1);  //Play the first mp3
  isPlaying = true;
}

void loop()
{
  static unsigned long timer = millis();
  /*
  if (millis() - timer > 3000) {
    timer = millis();
    myDFPlayer.next();  //Play next mp3 every 3 second.
  }
  */

  /*---------------------- CHANGED ----------------------*/
  //myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD);  //Set device to SD

  /*------------------- MP3 PLAY NEXT -------------------*/
 if (digitalRead(buttonNext) == ACTIVATED)
  {
    if(isPlaying)
    {
      delay(500);
      myDFPlayer.next();
      Serial.println(F("next!"));
      delay(500);
    }
  }
  
  /*----------------- MP3 PLAY PREVIOUS -----------------*/
 if (digitalRead(buttonPrevious) == ACTIVATED)
  {
    if(isPlaying)
    {
      delay(500);
      myDFPlayer.previous();
      Serial.println(F("previous"));
      delay(500);
    }
  }

  /*-------------------- MP3 PAUSE --------------------*/


  
  /*----------------------- PRINT -----------------------*/
  
  if (myDFPlayer.available()) {
    printDetail(myDFPlayer.readType(), myDFPlayer.read()); 
  }
}

void printDetail(uint8_t type, int value){
  switch (type) {
    case TimeOut:
      Serial.println(F("Time Out!"));
      break;
    case WrongStack:
      Serial.println(F("Stack Wrong!"));
      break;
    case DFPlayerCardInserted:
      Serial.println(F("Card Inserted!"));
      break;
    case DFPlayerCardRemoved:
      Serial.println(F("Card Removed!"));
      break;
    case DFPlayerCardOnline:
      Serial.println(F("Card Online!"));
      break;
    case DFPlayerPlayFinished:
      Serial.print(F("Number:"));
      Serial.print(value);
      Serial.println(F(" Play Finished!"));
      break;
    case DFPlayerError:
      Serial.print(F("DFPlayerError:"));
      switch (value) {
        case Busy:
          Serial.println(F("Card not found"));
          break;
        case Sleeping:
          Serial.println(F("Sleeping"));
          break;
        case SerialWrongStack:
          Serial.println(F("Get Wrong Stack"));
          break;
        case CheckSumNotMatch:
          Serial.println(F("Check Sum Not Match"));
          break;
        case FileIndexOut:
          Serial.println(F("File Index Out of Bound"));
          break;
        case FileMismatch:
          Serial.println(F("Cannot Find File"));
          break;
        case Advertise:
          Serial.println(F("In Advertise"));
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
}
