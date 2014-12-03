#include <Servo.h>

#define bottomServo 9
#define topServoPin 10
#define LEDPin 13

const int PHI = 16;
const int THETA = 180;

Servo botServo;
Servo topServo;


void setup()
{
 // pinMode(ServoPin, OUTPUT);
  pinMode(LEDPin, OUTPUT);
  
  botServo.attach(bottomServo);
  topServo.attach(topServoPin); 
//  myServo.write(0);
}


void loop()
{
//  //analogWrite(myPWM, 100);
//  myServo.write(180);
//  digitalWrite(LEDPin, HIGH);
//  delay(1000);
//  //analogWrite(myPWM, 0);
//  myServo.write(0);
//  digitalWrite(LEDPin, LOW);
//  delay(1000);

//Going up on scan grid 
for(int phi = 0; phi < PHI;){ //Change upper limit for phi
  for ( int i = 0; i < THETA; i++ )
  {
    botServo.write(i);
    delay(15); //change this for speed
    
  
  }
  
  phi+=2;
  topServo.write(phi); //Change this increment for phi direction 
  
  for ( int i = THETA; i >= 0; i-- )
  {
    botServo.write(i);
    delay(15);
   
  }  
  
  phi+=2;
  topServo.write(phi); //Change this increment for phi direction 
}  




//Going down on scan grid
for(int phi = PHI; phi >0;){ //Change upper limit for phi
  for ( int i = 0; i < THETA; i++ )
  {
    botServo.write(i);
    delay(15); //change this for speed
    
  
  }
  
  phi-=2;
  topServo.write(phi); //Change this increment for phi direction 
  
  for ( int i = THETA; i >= 0; i-- )
  {
    botServo.write(i);
    delay(15);
   
  }  
  
  phi-=2;
  topServo.write(phi); //Change this increment for phi direction 
}  
 
}


