#include <Servo.h> //library

#define receiver 7 //RF receiver
#define laserPin 4
#define signalLEDPin 12
#define bottomServo 9
#define topServoPin 10
#define LEDPin 13

const int delayValue = 25;
const int NOISECONSTANT = 6;
const int PHI_OFFSET = 2;
const int MIN_PHI = 35;
const int MAX_PHI = 75;
const int MIN_THETA = 0;
const int MAX_THETA = 180;
const int LOW_RF_THRESHOLD = 100;
const int HIGH_PHI_COMPENSATION = 5;
const int PHI_THRESHOLD = 50;
const int PHI_BUBBLE = 10;

const int LASER_PHI_OFFSET = 1;
const int LASER_DELAY = 40;
const int LASER_MIN_PHI = 25;
const int LASER_MAX_PHI = 75;
const int LASER_COMPENSATION = 3;
const int PHI_COMPENSATION = 2;
 
int data = 0; //data input from RF 

int firstTheta = MIN_THETA;
int secondTheta = MAX_THETA;
int firstPhi = MIN_PHI;
int secondPhi = MAX_PHI;

boolean searchComplete = false;
boolean ledSearching = true;

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
// botServo.write(45);
// digitalWrite(LEDPin, HI
//  delay(1000);
//  digitalWrite(LEDPin, LOW);
// botServo.write(0);
  //digitalWrite(signalLEDPin, HIGH);
  while (!thetaSearch());
  digitalWrite(signalLEDPin, LOW);
  Serial.print(firstTheta);
  Serial.print(" ");
  Serial.println(secondTheta);
  delay(4000);
  //digitalWrite(laserPin, HIGH);
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

//  data = analogRead(receiver);
//  Serial.print(data);
//  Serial.print("\t");
//  if(data < LOW_RF_THRESHOLD)
//  {
//    Serial.println("LOW");
//    digitalWrite(laserPin, LOW);
//  }
//  else
//  {
//    Serial.println("HIGH");
//    digitalWrite(laserPin, HIGH);
//  }    
//  delay(4000);
}

boolean RFisHIGH( int value )
{
  return (digitalRead(receiver) == HIGH);
}


