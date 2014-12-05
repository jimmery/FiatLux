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
unsigned int secondTheta = 0;


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
bool leaveLoop1 = false; //use this to get out of loops when angles are found
bool leaveLoop2 = false;

//Going up on scan grid 
for(int phi = 0; phi < MAX_PHI;){ 
  for ( int theta = MIN_THETA; theta < MAX_THETA; theta++ )
  {
    digitalWrite(signalLEDPin, HIGH); //turn on the LED to start getting info from the boat
    data = analogRead(receiver);  //get signal from RF sent from boat 
    botServo.write(theta);
    if(data > HIGH_RF_THRESHOLD){ //check to see if boat is finding a high
      firstTheta = theta;
      leaveLoop1 = true;
    }
    else if(data < LOW_RF_THRESHOLD){
      secondTheta = theta;
      leaveLoop2 = true;
    }    
   
    delay(15); //change this for speed
  }
  
   if(leaveLoop1 && leaveLoop2){ //both theta angles have been found, leave the loop
       break;
   }  
  
  phi+=2; //Potential to change phi direction movement
  topServo.write(phi); 
  
  for ( int theta = MAX_THETA; theta >= MIN_THETA; theta-- )
  {
    botServo.write(theta);
    delay(15);
   
  }  
  
  phi+=2;
  topServo.write(phi); //Change this increment for phi direction 
}  


if(leaveLoop1 && leaveLoop2){  //if theta values have been found, use these as the new limits
  MIN_THETA = firstTheta;
  MAX_THETA = secondTheta;
}



//Going down on scan grid
for(int phi = MAX_PHI; phi >0;){ //Change upper limit for phi
  for ( int theta = MIN_THETA; theta < MAX_THETA; theta++ )
  {
    botServo.write(theta);
    delay(15); //change this for speed
  }
  
  phi-=2;
  topServo.write(phi); //Change this increment for phi direction 
  
  for ( int theta = MAX_THETA; theta >= MIN_THETA; theta-- )
  {
    botServo.write(theta);
    delay(15);
  }  
  
  phi-=2;
  topServo.write(phi); //Change this increment for phi direction 
}  
 
 
}


