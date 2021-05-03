
# Ammo counter Experiment
This code is to make a nerf ammo counter using the following:
 - Arduino Nano
 - 74HC595 2 Led digits (Testing with TM1637)
 - IR Sensor CNY70
 - Microbutton
 
 The whole idea is to put a IR sensor in the muzzle of the nerf and check for  balls passing by.
 


Connections:

TM1637      ARDUINO    
    CLK  --> PIN4
    DIO  --> PIN5 (PWN)
    VCC  --> 5V
    GRND --> GRND

IR Sensor (CNY70) ARDUINO    
    DIODE VCC  --> 5V
    DIODE GRND --> 220 OHMs (RED-RED-BROWN-GOLD) --> GRND
    Sensor VCC --> 5V
    Sensor OUT --> A0
                    |
                    |-> 10K Ohms (Brown-Black-Orange-Gold) --> GRND   
    
Microbutton --> ARDUINO    
    VCC --> 5V
    GRD --> Resistor + GRND
    PIN --> PIN2
  
    
Zeus Motors: SRC-360S-3160

21 amp Microswitch: D48x

https://imgur.com/a/subfrxy
https://www.reddit.com/r/Nerf/comments/9y4v3c/super_zeus_arduino_controlled_solenoid_trigger/
http://nerfhaven.com/forums/topic/26606-nerf-rival-zeus-cronos-mod-semi-auto-reboud-burst-and-fu/


