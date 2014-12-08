// default condition
// in this condition, the lighthouse will continuously spin until a ship signal comes. 

// spin the light around on the servo. 
// extra: also change the servo in the phi direction. so that it looks cooler. 
// continue while boat is not found. 

// receive signals from the boat. depending on which transmission we chose, we can change our behavior here. 
// 1. if the boat does analysis, we just have to make sure we stop the motors before an offset.
// 2. if the boat does no analysis, the lighthouse will have to do analysis. 
//    but we can include some phi angle approximation here. 

// then we start the laser and turn the LED off. 
// boat will reset essentially to prepare for laser input. 

// laser search. 

boolean thetaSearch()
{
  bool minAngFound = false; //use this to get out of loops when angles are found
  bool maxAngFound = false;
  
  firstTheta = MIN_THETA;
  secondTheta = MAX_THETA;
  
  //Going up on scan grid 
  for(int phi = MIN_PHI; phi < MAX_PHI;){ 
    for ( int theta = firstTheta; theta < secondTheta; theta++ )
    {
      botServo.write(theta);
     data = analogRead(receiver);  //get signal from RF sent from boat 
      Serial.println(data);
      if(RFisHIGH(data) && !minAngFound){ //check to see if boat is finding a high
        digitalWrite(laserPin, HIGH);
        firstTheta = theta;
        minAngFound = true;
      }
      else if(!RFisHIGH(data) && minAngFound && !maxAngFound ){
        if ( theta - firstTheta <= NOISECONSTANT )
        {
          minAngFound = false;
          firstTheta = MIN_THETA;
        }
        else
        {
          digitalWrite(laserPin, LOW);
          secondTheta = theta;
          maxAngFound = true;
          return true;
        }
      }
      delay(delayValue); //change this for speed
    }
    
    if ( minAngFound && firstTheta < MAX_THETA - NOISECONSTANT)
    {
      return true;
    }
  
    phi+=PHI_OFFSET; //Potential to change phi direction movement
    topServo.write(phi); 
    delay(delayValue);
//
//   Serial.print(firstTheta);
//   Serial.print(" ");
//   Serial.println(secondTheta);

   
    for ( int theta = secondTheta; theta >= firstTheta; theta-- )
    {
//     Serial.print(theta);
//     Serial.print(" ");
//   Serial.println(firstTheta);
      botServo.write(theta);
      
      
      data = analogRead(receiver);  //get signal from RF sent from boat  
      Serial.println(data);
      if(RFisHIGH(data) && !maxAngFound){ //check to see if boat is finding a high
        digitalWrite(laserPin, HIGH);
        secondTheta = theta;
        maxAngFound = true;
      }
      else if(!RFisHIGH(data) && maxAngFound && !minAngFound ){
        if ( secondTheta - theta <= NOISECONSTANT )
        {
          maxAngFound = false;
          secondTheta = MAX_THETA;
        }
        else
        {
          digitalWrite(laserPin, LOW);
          firstTheta = theta;
          minAngFound = true;
          return true;
        }
      }
      delay(delayValue);
    }
    
    if ( maxAngFound && secondTheta > NOISECONSTANT)
    {
      //Serial.println("hi");
      return true;
    }
  
    phi+=PHI_OFFSET;
    topServo.write(phi); //Change this increment for phi direction 
    delay(delayValue);
    
    //Serial.println(phi);
  }  

  //Going down on scan grid
  for(int phi = MAX_PHI; phi > MIN_PHI;){ //Change upper limit for phi
    for ( int theta = MIN_THETA; theta < MAX_THETA; theta++ )
    {
      botServo.write(theta);
      data = analogRead(receiver);  //get signal from RF sent from boat  
      Serial.println(data);
      if(RFisHIGH(data) && !minAngFound){ //check to see if boat is finding a high
        digitalWrite(laserPin, HIGH);
        firstTheta = theta;
        minAngFound = true;
      }
      else if(!RFisHIGH(data) && minAngFound && !maxAngFound ){
        if ( theta - firstTheta <= NOISECONSTANT )
        {
          minAngFound = false;
          firstTheta = MIN_THETA;
        }
        else
        {
          digitalWrite(laserPin, LOW);
          secondTheta = theta;
          maxAngFound = true;
          return true;
        }
      }
      delay(delayValue); //change this for speed
    }
    
    if ( minAngFound && firstTheta < MAX_THETA - NOISECONSTANT)
    {
      return true;
    }
  
    phi-=PHI_OFFSET;
    topServo.write(phi); //Change this increment for phi direction 
    delay(delayValue);

    for ( int theta = secondTheta; theta >= firstTheta; theta-- )
    {
      botServo.write(theta);
      data = analogRead(receiver);  //get signal from RF sent from boat  
      Serial.println(data);
      if(RFisHIGH(data) && !maxAngFound){ //check to see if boat is finding a high
        digitalWrite(laserPin, HIGH);
        secondTheta = theta;
        maxAngFound = true;
      }
      else if(!RFisHIGH(data) && maxAngFound && !minAngFound ){
        if ( secondTheta - theta <= NOISECONSTANT )
        {
          maxAngFound = false;
          secondTheta = MAX_THETA;
        }
        else
        {
          digitalWrite(laserPin, LOW);
          firstTheta = theta;
          minAngFound = true;
          return true;
        }
      }
      delay(delayValue);
    }
    
    if ( maxAngFound && secondTheta > NOISECONSTANT)
      return true;  
  
    phi-=PHI_OFFSET;
    topServo.write(phi); //Change this increment for phi direction 
  }
  return false;
}

// search will be done with diagonal thingies. 
// choose a somewhat small offset for theta and phi (if applicable) and do a search. 
// when search is complete we will have an interrupt signal stop the motors. 
// we can do some end stuff here. like blink the led or something.
