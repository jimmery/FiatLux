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
  
  //Going up on scan grid 
  for(int phi = 0; phi < MAX_PHI;){ 
    for ( int theta = firstTheta; theta < secondTheta; theta++ )
    {
      digitalWrite(signalLEDPin, HIGH); //turn on the LED to start getting info from the boat
      botServo.write(theta);
      data = analogRead(receiver);  //get signal from RF sent from boat 
      if(data > HIGH_RF_THRESHOLD && !minAngFound){ //check to see if boat is finding a high
        firstTheta = theta;
        minAngFound = true;
      }
      else if(data < LOW_RF_THRESHOLD && minAngFound && !maxAngFound ){
        secondTheta = theta;
        maxAngFound = true;
        return true;
      }
      delay(15); //change this for speed
    }
    
    if ( minAngFound )
    {
      return true;
    }
  
    phi+=2; //Potential to change phi direction movement
    topServo.write(phi); 
  
    for ( int theta = MAX_THETA; theta >= MIN_THETA; theta-- )
    {
      botServo.write(theta);
      data = analogRead(receiver);  //get signal from RF sent from boat 
      if(data > HIGH_RF_THRESHOLD && !maxAngFound){ //check to see if boat is finding a high
        secondTheta = theta;
        maxAngFound = true;
      }
      else if(data < LOW_RF_THRESHOLD && maxAngFound && !minAngFound ){
        firstTheta = theta;
        minAngFound = true;
        return true;
      }
      delay(15);
    }
    
    if ( maxAngFound )
      return true;
  
    phi+=2;
    topServo.write(phi); //Change this increment for phi direction 
  }  

  //Going down on scan grid
  for(int phi = MAX_PHI; phi >0;){ //Change upper limit for phi
    for ( int theta = MIN_THETA; theta < MAX_THETA; theta++ )
    {
      botServo.write(theta);
      data = analogRead(receiver);  //get signal from RF sent from boat 
      if(data > HIGH_RF_THRESHOLD && !minAngFound){ //check to see if boat is finding a high
        firstTheta = theta;
        minAngFound = true;
      }
      else if(data < LOW_RF_THRESHOLD && minAngFound && !maxAngFound ){
        secondTheta = theta;
        maxAngFound = true;
        return true;
      }
      delay(15); //change this for speed
    }
    
    if ( minAngFound )
    {
      return true;
    }
  
    phi-=2;
    topServo.write(phi); //Change this increment for phi direction 
  
    for ( int theta = MAX_THETA; theta >= MIN_THETA; theta-- )
    {
      botServo.write(theta);
      data = analogRead(receiver);  //get signal from RF sent from boat 
      if(data > HIGH_RF_THRESHOLD && !maxAngFound){ //check to see if boat is finding a high
        secondTheta = theta;
        maxAngFound = true;
      }
      else if(data < LOW_RF_THRESHOLD && maxAngFound && !minAngFound ){
        firstTheta = theta;
        minAngFound = true;
        return true;
      }
      delay(15);
    }
    
    if ( maxAngFound )
      return true;  
  
    phi-=2;
    topServo.write(phi); //Change this increment for phi direction 
  }
  return false;
}

// search will be done with diagonal thingies. 
// choose a somewhat small offset for theta and phi (if applicable) and do a search. 
// when search is complete we will have an interrupt signal stop the motors. 
// we can do some end stuff here. like blink the led or something.
