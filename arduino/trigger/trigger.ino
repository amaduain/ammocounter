// Constants
#define DEBUG 1

//Variables
int wheelRelay = 2;
int triggerRelay=3;
int wheelRelaySignalIn = 4;
int triggerRelaySignalIn = 5;
int wheelRelayOn = false;
int triggerRelayOn = false;
//
//Setup ammo counter.
void setup() {
  #ifdef DEBUG
    Serial.begin(9600); // open the serial port at 9600 bps:
    Serial.print("Initializing...\n");
  #endif
  pinMode(wheelRelay, OUTPUT);
  pinMode(triggerRelay, OUTPUT);
  pinMode(wheelRelaySignalIn, INPUT_PULLUP);
  pinMode(triggerRelaySignalIn, INPUT_PULLUP);
  digitalWrite(wheelRelay, LOW);
  digitalWrite(triggerRelay, LOW);
  digitalWrite(wheelRelaySignalIn, LOW);
  digitalWrite(triggerRelaySignalIn, LOW);
}

void loop() {
  //delay(2000);
  //FlyWheel code
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
  //End of Flywheel code
  //Trigger code
  if(digitalRead(triggerRelaySignalIn) == HIGH){
    #ifdef DEBUG
      Serial.println("Trigger Switch activated.");
    #endif
    if (triggerRelayOn == false){
      #ifdef DEBUG
        Serial.println("Trigger Relay activated.");
      #endif
      digitalWrite(triggerRelay, HIGH);
      triggerRelayOn = true;
      delay(100);
      digitalWrite(triggerRelay, LOW);
    }
  }
  else{
    #ifdef DEBUG
      Serial.println("Trigger Switch Deactivated");
    #endif
    if(triggerRelayOn == true){
       #ifdef DEBUG
        Serial.println("Trigger deactivated.");
      #endif
      triggerRelayOn = false;
    }
  }
  //End of Trigger Code
}
