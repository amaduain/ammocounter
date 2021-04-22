#include <TM1637.h>


// Constants
//#define DEBUG 1
const int irSensor = A0;     // IR Sensor Analog input.
const int buttonPin = 2;     // the number of the pushbutton pin
const int CLK = 4;
const int DIO = 5;

// Variables
int buttonState = 0;         // variable for reading the pushbutton status
int ammo = 12;
int old_ammo = 12;
int selected_ammo = 12;
int irValue = 0;
int brightness = 5;
int sensorThreshold = 200;
bool disabledSensor = false;

//Objects
TM1637 tm(CLK,DIO);

//Setup ammo counter.
void setup() {
  #ifdef DEBUG
    Serial.begin(9600); // open the serial port at 9600 bps:
    Serial.print("Initializing...\n");
  #endif
  //Screen setup
  tm.init();
  tm.set(brightness);
  displayNumber(ammo);
  //Button setup
  pinMode(buttonPin, INPUT);
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
    displayNumber(ammo);
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
    delay(1000); // Delay a second to avoid extra pressures!
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
          for (int i = 0; i < 5; i++) {
            tm.init();
            tm.set(brightness);
            delay(500);
            displayNumber(ammo);
            delay(500);
          }
          ammo = selected_ammo;
        }
      }
      else{ //Second reading indicated that there is lots of light into, not able to see the balls passing by.
        // There is too much light to use the sensor, disabling....
        #ifdef DEBUG
          Serial.println("Too much light, disabling sensor.");
        #endif
        disabledSensor = true;
      }
   }else{ // The sensor is disabled, it will be reenabled when the light dims
    //Disabled Sensor, too much light, do nothing.
    //Extend the polling
      displayNumber(8888);
      delay(100);
      #ifdef DEBUG
        Serial.println("Disabled sensor, high readings detected");
      #endif
   }
  }
  else{
    // A low reading re-enables the sensor.
    if(disabledSensor == true){
      displayNumber(ammo);
      disabledSensor = false;
    }
  }
}

//Functions
void displayNumber(int num){   
    tm.display(3, num % 10);   
    tm.display(2, num / 10 % 10);   
    tm.display(1, num / 100 % 10);   
    tm.display(0, num / 1000 % 10);
}
