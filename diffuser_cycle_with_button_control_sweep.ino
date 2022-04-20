an/*
MECHANICAL FLOWER - PROJECT MISTY
Prototype for HCIN5300 Final Project.
Coding by Kazma Chaudhry, with help from Brandon Marshall.
Additional credit to Sebastian Navarro for generously providing components from his "security scent diffuser" project.

*/

#include <Servo.h>       //library of servo motor controls is included.

const int Fan = 2;       //pin 2 will be used for diffuser fan.
const int Misty = 5;     //pin 5 will be used for diffuser mist maker.
const int Button = 7;    //pin 7 has push button attached.  Press to initiate action.
const int Led = 3;       //pin 3 has the status indicator LED.  LED lights while device is active.
Servo Motor;             //including one servo motor.
int pos = 0;             //variable containing servo motor position.
int ButtonState;         //variable containing current state of pushbutton.

void setup() {            //Setup loop (runs once to initialize hardware).
pinMode(Fan, OUTPUT);     //pin assignments are indicated here.
pinMode(Misty, OUTPUT);
pinMode(Button, INPUT);
pinMode(Led, OUTPUT);
Motor.attach(10);        //servo motor is connected to pin 10.
Motor.write(0);          //Motor home position.

}

void loop() {                                // Main loop, iterates continuously during operation.

int ButtonState = digitalRead(Button);      //Read current value of pushbutton.

if (ButtonState == HIGH) {     //Control Structure.  IF Button is pressed, Run diffusion cycle.
  digitalWrite(Led,HIGH);      //Status indicator LED ON.
  CycleBegin();
  digitalWrite(Led,LOW);       //Status indicator LED OFF.
  delay(50);                 //
  }
}



//ADDITIONAL FUNCTIONS DEFINED BELOW

void CycleBegin(){               //Cycle
digitalWrite(Fan,LOW);           //[1st phase] mist maker is ON, fan is OFF, servo is at home position.   In this phase, vapour builds in the diffusion chamber.
digitalWrite(Misty,HIGH);
Motor.write(0);
delay(5000);                     //duration of first phase. Values are in milliseconds. 

digitalWrite(Fan,HIGH);          //[2nd phase] mist maker is ON, fan is ON, servo is at mid position.   In this phase, diffusion begins.
digitalWrite(Misty,HIGH);

for(pos = 0; pos <= 180; pos += 1){  //Slowly move servo motor to active position. 
  Motor.write(pos);
  delay(50);
}

delay(5000);                     //duration of second phase. 

digitalWrite(Fan,HIGH);          //[3rd phase] mist maker is OFF, fan is ON, servo is at home position.     In this phase, vapour in chamber empties.
digitalWrite(Misty,LOW);
Motor.write(180);                 //
delay(8000);                    //duration of third phase. 

digitalWrite(Fan,LOW);           //End of diffusion cycle, Turn OFF both fan and mist maker.  Motor returns to home position.
digitalWrite(Misty,LOW);

for (pos = 180; pos >= 0; pos -= 1) {      //Slowly return servo motor to home position. 
    Motor.write(pos);              
    delay(50);                       
}

delay(250);                //Additional delay for stability.
}

void CycleEnd(){               // Function to turn OFF all components. 
  digitalWrite(Fan,LOW);       //
  digitalWrite(Misty,LOW);
  Motor.write(0);
  digitalWrite(Led,LOW);
 
}
