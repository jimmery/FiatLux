#include <Servo.h>

#define ServoPin 9
#define LEDPin 13
Servo myServo;

void setup()
{
  pinMode(ServoPin, OUTPUT);
  pinMode(LEDPin, OUTPUT);
  
  myServo.attach(ServoPin);
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

  for ( int i = 0; i < 180; i++ )
  {
    myServo.write(i);
    delay(15);
  }
  
  for ( int i = 180; i >= 0; i-- )
  {
    myServo.write(i);
    delay(15);
  }  
}
