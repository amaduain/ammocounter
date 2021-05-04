#include <ShiftRegister74HC595.h>


// Constants
//#define DEBUG 1
const int triggerPin = 3;
#define SDI 7  //Green
#define SCLK 6 //Yellow
#define LOAD 5 //BLUE
#define DIGITS 2
// Variables
int triggerState = 0;
int ammo = 12;
int old_ammo = 12;
int selected_ammo = 12;
int brightness = 7;
bool disabledTrigger = false;
int value,digit1,digit2,digit3,digit4; 
uint8_t  digits[] = {B11000000, //0
                      B11111001, //1 
                      B10100100, //2
                      B10110000, //3 
                      B10011001, //4
                      B10010010, //5
                      B10000010, //6 
                      B11111000, //7
                      B10000000, //8
                      B10010000, //9
                      B10001001, //H
                      B10000110, //E
                      B10101011, //n
                      B10100011 //o
                     };

//Objects
ShiftRegister74HC595 sr (DIGITS, SDI, SCLK, LOAD); 

//Setup ammo counter.
void setup() {
  #ifdef DEBUG
    Serial.begin(9600); // open the serial port at 9600 bps:
    Serial.print("Initializing...\n");
  #endif
  //Screen setup
   showNumber(ammo);
   //Trigger Setup
  pinMode(triggerPin, INPUT_PULLUP);
  digitalWrite(triggerPin, HIGH);
  #ifdef DEBUG
    Serial.print("Initialized ammo with: ");
    Serial.print(ammo);
    Serial.print("\n");
  #endif
}

void loop() {
  //Check if the ammo has changed.
  if (old_ammo != ammo){
    #ifdef DEBUG
      Serial.print("Ammo Counter is ");
      Serial.print(ammo);
      Serial.print("\n");
    #endif
    old_ammo = ammo;
    showNumber(ammo);
  }

  triggerState = digitalRead(triggerPin);
  if (triggerState == LOW){ //Trigger has been activated!
    if (disabledTrigger == false){
      disabledTrigger = true;
      if (ammo > 0){  //Check the ammo counter.
        ammo = ammo - 1; 
        delay(100); 
      }
      if (ammo == 0){  //Ammo depleted, restart the counted and give some time for reload.
        showLetterH();
        ammo = selected_ammo;
      }
    }
   }else{ 
      if (disabledTrigger == true){ // Enable the trigger again!
        disabledTrigger = false;
        delay(100);
      }
      #ifdef DEBUG
        Serial.println("Trigger not activated.");
      #endif
   }
}

//Functions
void blinkNumber(int num){
  int times = 5;
  for(int i=0;i<times;i++){
    showNumber(num);
    delay(250); 
    sr.setAllHigh();  
    delay(250); 
  }
}
void showNumber(int num)
{
    digit2=num % 10 ;
    digit1=(num / 10) % 10 ;
    //Send them to 7 segment displays
    uint8_t numberToPrint[]= {digits[digit2],digits[digit1]};
    sr.setAll(numberToPrint);  
}
void showLetterH()
{
  int times = 10;
  uint8_t numberToPrint[]= {digits[12],digits[13]};
  for(int i=0;i<times;i++){
    sr.setAll(numberToPrint);  
    delay(250); 
    sr.setAllHigh();  
    delay(250);
  } 
}
