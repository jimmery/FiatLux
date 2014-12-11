//Takes in ambient light values up to upper limit specification and averages them.
//If greater than baseline, this means LED has hit for the first theta.
//After this state, this means that the LED has started to fall off and this is the second theta. Trasmit a low.
//The code now knows that the laser will be searching for it. When the light value is greater than laser baseline, transmit a constant high.

#define lightReceiver A0
#define laserPin 2
#define LEDPin 13
#define RFoutput 4


const int SAMPING_NUM = 50;     //Number of ambient values to be averaged.
const int BASELINE_OFFSET = 10; //Compensation constant for LED sensor.
const int LASER_BASELINE = 550; //Baseline laser intensity value.
int lightData = 0;              //Variable used for light values.
int lightBaseline = 0;          //Variable set to value of ambient light.

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
 
 for(int i = 0; i< SAMPING_NUM; i++){        //if 50 values is too large we can decrease this so as to not have neg int vals 
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
      //Once baseline is found we want to check for the LED on the boat and then signal HIGH.
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

