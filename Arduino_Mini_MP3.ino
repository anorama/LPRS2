//Edited by: Anastasija Pejkovic and Mina Savic


  /*---------------------- USED LIBRARIES ----------------------*/
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
  /*---------------------- VARIABLES ----------------------*/
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
  Serial.println(F("Initializing DFPlayer ..."));
  
  if (!myDFPlayer.begin(mySoftwareSerial))    //Use softwareSerial to communicate with mp3
  {
    Serial.println(F("Unable to begin. Please recheck your connection or if the SD card is inserted!"));
    while(true);
  }
  Serial.println(F("DFPlayer Mini activated."));
  
  myDFPlayer.volume(15);  //For volume setting. Choose between 0 and 30
  
  myDFPlayer.play(1);  //Play the first mp3
  isPlaying = true;
}

void loop()
{ 
  /*------------------- MP3 PLAY - BUTTON NEXT -------------------*/
 if (digitalRead(buttonNext) == ACTIVATED)
  {
    if(isPlaying)
    {
      delay(500);
      myDFPlayer.next();
      Serial.println(F("Next song is playing!"));
      delay(500);
    }
  }
  
  /*----------------- MP3 PLAY - BUTTON PREVIOUS -----------------*/
 if (digitalRead(buttonPrevious) == ACTIVATED)
  {
    if(isPlaying)
    {
      delay(500);
      myDFPlayer.previous();
      Serial.println(F("Previous song is playing!"));
      delay(500);
    }
  }
  /*----------------------- PRINT -----------------------*/
  
  if (myDFPlayer.available()) {
    printDetail(myDFPlayer.readType(), myDFPlayer.read()); 
  }
}


  /*----------------------- POSSIBLE ERRORS -----------------------*/
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
