// Constants
#define DEBUG 1

//Variables
int wheelRelay = 2;
int wheelRelaySignalOut = 3;
int wheelRelaySignalIn = 4;
int wheelRelayOn = false;
//
//Setup ammo counter.
void setup() {
  #ifdef DEBUG
    Serial.begin(9600); // open the serial port at 9600 bps:
    Serial.print("Initializing...\n");
  #endif
  pinMode(wheelRelay, OUTPUT);
  pinMode(wheelRelaySignalIn, INPUT_PULLUP);
  pinMode(wheelRelaySignalOut, OUTPUT);
  digitalWrite(wheelRelaySignalOut, HIGH);
  digitalWrite(wheelRelay, LOW);
  digitalWrite(wheelRelaySignalIn, LOW);
}

void loop() {
  //delay(2000);
  if(digitalRead(wheelRelaySignalIn) == HIGH){
    #ifdef DEBUG
      Serial.println("Wheel Switch activated.");
    #endif
    if (wheelRelayOn == false){
      #ifdef DEBUG
        Serial.println("Relay activated.");
      #endif
      digitalWrite(wheelRelay, HIGH);
      wheelRelayOn = true;
      delay(100);
    }
  }
  else{
    #ifdef DEBUG
      Serial.println("Wheel Switch Deactivated");
    #endif
    if(wheelRelayOn == true){
       #ifdef DEBUG
        Serial.println("Relay deactivated.");
      #endif
      digitalWrite(wheelRelay, LOW);
      wheelRelayOn = false;
      delay(100);
    }
  }
  
}
