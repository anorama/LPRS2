#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

# define ACTIVATED LOW

SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);

  /*---------------------- BUTTONS ----------------------*/
  const int buttonNext = 2;
  const int buttonPrevious = 3;
  const int buttonStateNext = 0; 
  const int buttonStatePrevious = 0; 
  boolean isPlaying = false;
  /*-----------------------------------------------------*/

void setup()
{
  mySoftwareSerial.begin(9600);
  Serial.begin(115200);
  pinMode(buttonNext, INPUT);
  pinMode(buttonPrevious, INPUT);

  
  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Inicijalizacija DFPlayer-a ..."));
  
  if (!myDFPlayer.begin(mySoftwareSerial)) {        //Koristi se softwareSerial za komunikaciju sa mp3.
    Serial.println(F("Nemoguce pokretanje! Proverite konekciju i SD karticu!"));
    while(true);
  }
  Serial.println(F("DFPlayer Mini online."));
  
  myDFPlayer.volume(15);  //Setovanje jacine zvuka, vrednosti od 0 do 30
  myDFPlayer.play(2);  //Pusti prvu pesmu
  isPlaying = true;
}

void loop()
{
  /*------------------- MP3 PLAY NAREDNA -------------------*/
 if (digitalRead(buttonNext) == ACTIVATED){
    if(isPlaying){
      delay(500);
      myDFPlayer.next();
      Serial.println(F("Pustili ste narednu pesmu!"));
      
    }
  }
  
  /*----------------- MP3 PLAY PRETHODNA -----------------*/
 if (digitalRead(buttonPrevious) == ACTIVATED){
    if(isPlaying){
      delay(500);
      myDFPlayer.previous();
      Serial.println(F("Pustili ste prethodnu pesmu"));
      
    }
  }

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
