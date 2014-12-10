#include <Servo.h> //library

// all the pin values that we used for this project. 
#define receiver 7 //RF receiver
#define laserPin 4
#define signalLEDPin 12
#define bottomServo 9
#define topServoPin 10
#define LEDPin 13

// constants, mainly for the LED search. 
const int delayValue = 25;             // LED search speed. 
const int NOISECONSTANT = 6;           // constant by which less than this value of HIGHS would be considered noise.
const int PHI_OFFSET = 4;              // change in LED phi after a full 180 scan on one phi
const int MIN_PHI = 35;                // minimum LED phi
const int MAX_PHI = 75;                // maximum LED phi
const int MIN_THETA = 0;               // minimum theta (for both)
const int MAX_THETA = 180;             // maximum theta (for both)
const int LOW_RF_THRESHOLD = 100;      // threshold for RF (which was scrapped - this constant is useless)
const int HIGH_PHI_COMPENSATION = 5;   // if phi is high, we add this value to left and right theta.
const int PHI_THRESHOLD = 50;          // above this phi, we consider the phi to be high. 
const int PHI_BUBBLE = 12;             // the bubble in which we guess the phototransistor to be after the LED search.

// constants, mainly for the laser search. 
const int LASER_PHI_OFFSET = 1;        // change in laser phi after a full 180 theta scan.
const int LASER_DELAY = 40;            // laser search speed.
const int LASER_MIN_PHI = 25;          // minimum laser phi.
const int LASER_MAX_PHI = 75;          // maximum laser phi
const int LASER_COMPENSATION = 3;      // increase in theta values if one full search fails
const int PHI_COMPENSATION = 2;        // increase in phi values if one full search fails.

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

