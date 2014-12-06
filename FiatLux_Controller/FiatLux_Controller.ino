#include <Servo.h>

#define receiver A0 //RF receiver
#define laserPin 2
#define signalLEDPin 4
#define bottomServo 9
#define topServoPin 10
#define LEDPin 13

const int delayValue = 15;
const int PHI_OFFSET = 2;
const int MAX_PHI = 16;
const int MAX_THETA = 180;
const int LOW_RF_THRESHOLD = 500;
const int HIGH_RF_THRESHOLD = 500;

int MIN_THETA = 0; 
int data = 0; //data input from RF 

 int firstTheta = 0;
 int secondTheta = 180;




Servo botServo;
Servo topServo;


void setup()
{
  pinMode(LEDPin, OUTPUT);
  pinMode(signalLEDPin, OUTPUT);
  
  
  
  botServo.attach(bottomServo);
  topServo.attach(topServoPin); 
  
  Serial.begin(9600);
}



void loop()
{
// botServo.write(45);
// digitalWrite(LEDPin, HI
//  delay(1000);
//  digitalWrite(LEDPin, LOW);
// botServo.write(0);

  while (!thetaSearch());

}


