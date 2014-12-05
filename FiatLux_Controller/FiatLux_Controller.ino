#include <Servo.h>

#define receiver A0 //RF receiver
#define laserPin 2
#define signalLEDPin 4
#define bottomServo 9
#define topServoPin 10
#define LEDPin 13

const int MAX_PHI = 16;
const int MAX_THETA = 180;
const int LOW_RF_THRESHOLD = 100;
const int HIGH_RF_THRESHOLD = 150;

unsigned int MIN_THETA = 0; 
unsigned int data = 0; //data input from RF 
unsigned int firstTheta = 0;
unsigned int secondTheta = MAX_THETA;


Servo botServo;
Servo topServo;


void setup()
{
  pinMode(LEDPin, OUTPUT);
  pinMode(signalLEDPin, OUTPUT);
  
  botServo.attach(bottomServo);
  topServo.attach(topServoPin); 
}


void loop()
{


  while (!thetaSearch());



 
 
}


