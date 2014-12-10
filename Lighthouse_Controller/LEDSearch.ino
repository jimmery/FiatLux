// purely does the entire theta search. 
// takes the modified and saved theta and phi values and loops through there. 
// each spot we search and listen for inputs. 
// then we return true if it's found, and saves the theta values it has.
// also does some compensation based on the values that it gets.
// otherwise we increase the grid area and continue searching. 
boolean thetaSearch()
{
  boolean minAngFound = false; //use this to get out of loops when angles are found
  boolean maxAngFound = false;
  
  firstTheta = MIN_THETA;
  secondTheta = MAX_THETA;
  
  //Going up on scan grid 
  for(int phi = MIN_PHI; phi < MAX_PHI;){ 
    for ( int theta = firstTheta; theta < secondTheta; theta++ )
    {
      botServo.write(theta);
      data = digitalRead(receiver);  //get signal from RF sent from boat 
      Serial.println(data);
      if(RFisHIGH(data) && !minAngFound){ //check to see if boat is finding a high
        firstTheta = theta;
        if ( phi > PHI_THRESHOLD )
        {
          firstTheta -= HIGH_PHI_COMPENSATION;
          if ( firstTheta < 0 )
            firstTheta = 0;
        }
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
          secondTheta = theta;
          maxAngFound = true;
          highPhiCompensation(phi);
          findPhiBubble(phi);
          return true;
        }
      }
      delay(delayValue); //change this for speed
    }
    
    if ( minAngFound )
    {
      highPhiCompensation(phi);
      findPhiBubble(phi);
      return true;
    }
  
    phi+=PHI_OFFSET; //Potential to change phi direction movement
    topServo.write(phi); 
    delay(delayValue);
    
    digitalWrite(signalLEDPin, HIGH); // we don't write high until the it finishes resetting. 

    for ( int theta = secondTheta; theta >= firstTheta; theta-- )
    {
      botServo.write(theta);
      data = digitalRead(receiver);  //get signal from RF sent from boat  
      Serial.println(data);
      if(RFisHIGH(data) && !maxAngFound){ //check to see if boat is finding a high
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
          firstTheta = theta;        
          minAngFound = true;
          highPhiCompensation(phi);
          findPhiBubble(phi);
          return true;
        }
      }
      delay(delayValue);
    }
    
    if ( maxAngFound )
    {
      highPhiCompensation(phi);
      findPhiBubble(phi);
      return true;
    }
  
    phi+=PHI_OFFSET;
    topServo.write(phi); //Change this increment for phi direction 
    delay(delayValue);
    
    //Serial.println(phi);
  }  

  //Going down on scan grid
  for(int phi = MAX_PHI; phi >0;){ //Change upper limit for phi
    for ( int theta = MIN_THETA; theta < MAX_THETA; theta++ )
    {
      botServo.write(theta);
      data = digitalRead(receiver);  //get signal from RF sent from boat  
      Serial.println(data);
      if(RFisHIGH(data) && !minAngFound){ //check to see if boat is finding a high
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
          secondTheta = theta;
          maxAngFound = true;
          highPhiCompensation(phi);
          findPhiBubble(phi);
          return true;
        }
      }
      delay(delayValue); //change this for speed
    }
    
    if ( minAngFound )
    {
      highPhiCompensation(phi);
      findPhiBubble(phi);
      return true;
    }
  
    phi-=PHI_OFFSET;
    topServo.write(phi); //Change this increment for phi direction 
    delay(delayValue);

    for ( int theta = secondTheta; theta >= firstTheta; theta-- )
    {
      botServo.write(theta);
      data = digitalRead(receiver);  //get signal from RF sent from boat  
      Serial.println(data);
      if(RFisHIGH(data) && !maxAngFound){ //check to see if boat is finding a high
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
          firstTheta = theta;
          highPhiCompensation(phi);
          minAngFound = true;
          findPhiBubble(phi);
          return true;
        }
      }
      delay(delayValue);
    }
    
    if ( maxAngFound )
    {
      highPhiCompensation(phi);
      findPhiBubble(phi);
      return true;  
    }
    phi-=PHI_OFFSET;
    topServo.write(phi); //Change this increment for phi direction 
  }
  return false;
}

// when phi is high, we expect the theta distances to be relatively small. 
// to compensate, we add a little bit to the first, second theta to make sure that our search area
// contains the desired point. 
void highPhiCompensation( int phi )
{
  if ( phi > PHI_THRESHOLD )
  {
    firstTheta -= HIGH_PHI_COMPENSATION;
    secondTheta += HIGH_PHI_COMPENSATION;
    if ( firstTheta < MIN_THETA )
      firstTheta = MIN_THETA;
    if ( secondTheta > MAX_THETA )
      secondTheta = MAX_THETA;
  }
}

// this is an optimization that finds a "phi bubble" in which the phototransistor is likely to be. 
// this makes it so that in the laser search we do not have to scan continuously from 
// min_phi to max_phi, and instead has a smaller range to search, increasing efficiency. 
void findPhiBubble( int phi )
{
  firstPhi = phi - PHI_BUBBLE;
  secondPhi = phi + PHI_BUBBLE;
  if ( firstPhi < LASER_MIN_PHI )
    firstPhi = LASER_MIN_PHI;
  if ( secondPhi > LASER_MAX_PHI )
    secondPhi = LASER_MAX_PHI;
}
