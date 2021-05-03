#include <ShiftRegister74HC595.h>


// Constants
//#define DEBUG 1
const int irSensor = A0;     // IR Sensor Analog input.
const int buttonPin = 2;     // the number of the pushbutton pin
#define SDI 7  //Green
#define SCLK 6 //Yellow
#define LOAD 5 //BLUE
#define DIGITS 2
// Variables
int buttonState = 0;         // variable for reading the pushbutton status
int ammo = 40;
int old_ammo = 40;
int selected_ammo = 40;
int irValue = 0;
int brightness = 7;
int sensorThreshold = 200;
bool disabledSensor = false;
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
                      B10010000 //9
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
  //Button setup
  pinMode(buttonPin, INPUT_PULLUP);
  digitalWrite(buttonPin, HIGH);
  #ifdef DEBUG
    Serial.print("Initialized ammo with: ");
    Serial.print(ammo);
    Serial.print("\n");
  #endif
  //Initialize IR sensor pin
  pinMode(irSensor, INPUT);
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
  //Check if button has been pressed.
  buttonState = digitalRead(buttonPin);
  if (buttonState == LOW) {   //Button Pressed
    #ifdef DEBUG
      Serial.print("Buttton pressed\n");
    #endif
    if (ammo == 12){
      #ifdef DEBUG
        Serial.print("Changing ammo to 40\n");
      #endif
      ammo = 40;
      selected_ammo = 40;
    }
    else{
      #ifdef DEBUG
        Serial.print("Changing ammo to 12\n");
      #endif
      ammo = 12;
      selected_ammo = 12;
    }
    delay(500); // Delay a second to avoid extra pressures!
  }
  // Once the button code is cleard out start the proper reading from the IR sensor.
  irValue = analogRead(irSensor);
  #ifdef DEBUG
    Serial.print("Value: ");
    Serial.print(irValue);
    Serial.print("\n");
  #endif
  if (irValue > sensorThreshold){ //Lots of light entering in the IR sensor, could be a ball.
    if(disabledSensor == false){  //Check if the sensor was flooded with light before,if not could be a ball.
      #ifdef DEBUG
        Serial.print("Ball Detected");
        Serial.print("\n");
        Serial.print("Value: ");
        Serial.print(irValue);
        Serial.print("\n");
      #endif
      delayMicroseconds(3000);
      //Second reading for Sun issues, if it is below sensorThreshold then the void is there again!
      irValue = analogRead(irSensor);
      if (irValue < sensorThreshold){ // if it is below the threshold means the ball has passed.
        if (ammo > 0){  //Check the ammo counter.
          ammo = ammo - 1; 
          delay(100); 
        }
        if (ammo == 0){  //Ammo depleted, restart the counted and give some time for reload.
          blinkNumber(ammo);
          ammo = selected_ammo;
        }
      }
      else{ //Second reading indicated that there is lots of light into, not able to see the balls passing by.
        // There is too much light to use the sensor, disabling....
        #ifdef DEBUG
          Serial.println("Too much light, disabling sensor.");
        #endif
        showNumber(88);
        disabledSensor = true;
        delay(250);
      }
   }else{ // The sensor is disabled, it will be reenabled when the light dims
    //Disabled Sensor, too much light, do nothing.
    //Extend the polling
      showNumber(88);
      delay(100);
      #ifdef DEBUG
        Serial.println("Disabled sensor, high readings detected");
      #endif
   }
  }
  else{
    // A low reading re-enables the sensor.
    if(disabledSensor == true){
      showNumber(ammo);
      disabledSensor = false;
    }
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
