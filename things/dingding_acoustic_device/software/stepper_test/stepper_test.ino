#include <AccelStepper.h>

int ledPin = 13;

int stepEnablePin = 32;
int stepMs1Pin = 31;
int stepMs2Pin = 30;
int stepRxPin = 29;
int stepTxPin = 28;
int stepClkPin = 27;
int stepStepPin = 26;
int stepDirPin = 25;

AccelStepper stepper(1, stepStepPin, stepDirPin); // pin 3 = step, pin 6 = direction

void setup() {

    pinMode(32, OUTPUT);
    pinMode(31, OUTPUT);
    pinMode(30, OUTPUT);
    pinMode(29, OUTPUT);
    pinMode(28, OUTPUT);
    pinMode(27, OUTPUT);
    pinMode(26, OUTPUT);
    pinMode(25, OUTPUT);

    digitalWrite(stepMs1Pin, LOW); 
    digitalWrite(stepMs2Pin, HIGH); 
    digitalWrite(stepRxPin, LOW); 


  stepper.setMaxSpeed(40000);
  stepper.setAcceleration(120000);
  stepper.moveTo(20000);
  
}

void loop() {  
   stepper.run();
}

