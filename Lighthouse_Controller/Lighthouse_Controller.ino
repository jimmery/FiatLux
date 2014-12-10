#include <Servo.h> //library

// all the pin values that we used for this project. 
#define receiver 7 //RF receiver
#define laserPin 4
#define signalLEDPin 12
#define bottomServo 9
#define topServoPin 10
#define LEDPin 13

// constants, mainly for the LED search. 
const int delayValue = 25;
const int NOISECONSTANT = 6;
const int PHI_OFFSET = 4;
const int MIN_PHI = 35;
const int MAX_PHI = 75;
const int MIN_THETA = 0;
const int MAX_THETA = 180;
const int LOW_RF_THRESHOLD = 100;
const int HIGH_PHI_COMPENSATION = 5;
const int PHI_THRESHOLD = 50;
const int PHI_BUBBLE = 12;

// constants, mainly for the laser search. 
const int LASER_PHI_OFFSET = 1;
const int LASER_DELAY = 40;
const int LASER_MIN_PHI = 25;
const int LASER_MAX_PHI = 75;
const int LASER_COMPENSATION = 3;
const int PHI_COMPENSATION = 2;

int data = 0; //data input from RF 

// varying values for the boundaries, which we can optimize for the laser search. 
int firstTheta = MIN_THETA;
int secondTheta = MAX_THETA;
int firstPhi = MIN_PHI;
int secondPhi = MAX_PHI;

// additional booleans that are used across functions. 
boolean searchComplete = false;
boolean ledSearching = true;

// declaring the servos. 
Servo botServo;
Servo topServo;


void setup()
{
  pinMode(LEDPin, OUTPUT);
  pinMode(signalLEDPin, OUTPUT);
  pinMode(laserPin, OUTPUT);
  pinMode(receiver, INPUT);
 
  botServo.attach(bottomServo);
  topServo.attach(topServoPin); 
  
  digitalWrite(signalLEDPin, LOW); //turn on the LED to start getting info from the boat
  digitalWrite(laserPin, LOW);

  Serial.begin(9600);
}

void loop()
{
  while (!thetaSearch());
  digitalWrite(signalLEDPin, LOW);
  Serial.print(firstTheta);
  Serial.print(" ");
  Serial.println(secondTheta);
  delay(4000);
  ledSearching = false;
  while (true)
  {
    if ( !searchComplete )
    {
      searchComplete = laserSearch();
      continue;
    }
    data = digitalRead(receiver);
    Serial.println(data);
    delay(1000);
    // else do nothing. program stops here.
  }
}

boolean RFisHIGH( int value )
{
  return (digitalRead(receiver) == HIGH);
}

// original pseudocode: 
// default condition
// in this condition, the lighthouse will continuously spin until a ship signal comes. 

// spin the light around on the servo. 
// extra: also change the servo in the phi direction. so that it looks cooler. 
// continue while boat is not found. 

// receive signals from the boat. depending on which transmission we chose, we can change our behavior here. 
// lighthouse does analysis to determine whether the light has reached the boat. 

// then we start the laser and turn the LED off. 
// boat will reset essentially to prepare for laser input. 

// laser search. 

