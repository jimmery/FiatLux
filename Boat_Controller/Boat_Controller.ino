// setup. 
// take ambient light and store it. 


// continue taking in light values. 
// subtract ambient light. 
// experiment with one of these two methods: 
// 1. we can start transmitting RF when detecting a significant change in delta. 
   // we will have to define significant. 
// 2. we do analysis on first two detections to determine an approximate HIGH value and range. 
   // transmit when next HIGH value is detected (within a range). 


// we can consider doing a time delay here, depending on what we decide to do with the lighthouse. 


// when receiving a much higher value (for the laser), transmit a signal to stop the lighthouse. 

#define lightReceiver A0
#define laserPin 2
#define LEDPin 13
#define RFoutput 4


const int SAMPING_NUM = 50;
const int BASELINE_OFFSET = 10; //change based on need
const int LASER_BASELINE = 550; //change value for laser code
const int NOISE_CONSTANT = 0;
int lightData = 0;
int lightBaseline = 0; //this will be set to the averaged ambient value

boolean executeLaserCode = false;
boolean executeLEDCode = true;
boolean LEDHigh = false;
boolean transmitHigh = false;

void setup(){
 pinMode(lightReceiver, INPUT);
 pinMode(LEDPin, OUTPUT);
 pinMode(laserPin, OUTPUT);
 pinMode(RFoutput, OUTPUT);
 
 digitalWrite(laserPin, HIGH);
 digitalWrite(RFoutput, LOW);
 
 for(int i = 0; i< SAMPING_NUM; i++){  //if 50 values is too large we can decrease this so as to not have neg int vals 
    lightData = analogRead(lightReceiver);
    lightBaseline += lightData;
 }
 lightBaseline = lightBaseline/SAMPING_NUM;  //average value
 lightBaseline += BASELINE_OFFSET;
 
 Serial.begin(9600);
}

void loop(){
  delay(100);
  lightData = analogRead(lightReceiver);
  //Serial.println(lightData);

  //Laser code
  if(transmitHigh){
     digitalWrite(RFoutput, HIGH); 
      Serial.println("transmit HIGH");

  }else{
      if(executeLaserCode){
        if(lightData > LASER_BASELINE){
            digitalWrite(RFoutput, HIGH); 
            Serial.println("laser HIGH");

            transmitHigh = true;
          }else{
            digitalWrite(RFoutput, LOW); 
             Serial.println("laser LOW");

          }
      }else if(executeLEDCode){ 
        
  //Once baseline is found we want to check for the LED on the boat and then signal HIGH
      lightData = analogRead(lightReceiver);
      if(lightData > lightBaseline) { //this means we are getting data from non-ambient light
        digitalWrite(RFoutput, HIGH); //transmit high to signal lighthouse that first theta has been found
         Serial.println("led HIGH");

        LEDHigh = true;
      }      
      else{
        if(LEDHigh){
          executeLEDCode = false; 
          executeLaserCode = true;
          LEDHigh = false; 
        } 
         digitalWrite(RFoutput, LOW);  
         Serial.println("led LOW");

      }
     }
    }

 
}

