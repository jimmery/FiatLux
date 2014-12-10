boolean laserSearch()
{
  //Going up on scan grid 
  for(int phi = firstPhi; phi < secondPhi;){ 
    for ( int theta = firstTheta; theta < secondTheta; theta++ )
    {
      botServo.write(theta);
     data = digitalRead(receiver);  //get signal from RF sent from boat 
      Serial.println(data);
      if(RFisHIGH(data)){ //check to see if boat is finding a high
        botServo.write(theta-1);
        return true;
      }
      delay(LASER_DELAY); //change this for speed
    }
  
    phi+=LASER_PHI_OFFSET; //Potential to change phi direction movement
    topServo.write(phi); 
    delay(LASER_DELAY);
    digitalWrite(laserPin, HIGH);
    
    for ( int theta = secondTheta; theta >= firstTheta; theta-- )
    {
      botServo.write(theta);
      data = digitalRead(receiver);  //get signal from RF sent from boat  
      Serial.println(data);
      if(RFisHIGH(data)){ //check to see if boat is finding a high
        botServo.write(theta+1);
        return true;
      }
      delay(LASER_DELAY);
    }
  
    phi+=LASER_PHI_OFFSET;
    topServo.write(phi); //Change this increment for phi direction 
    delay(LASER_DELAY);
    
    //Serial.println(phi);
  }

  firstTheta -= LASER_COMPENSATION;
  secondTheta += LASER_COMPENSATION;
  firstPhi -= PHI_COMPENSATION;
  secondPhi += PHI_COMPENSATION;
  if ( firstTheta < MIN_THETA )
    firstTheta = MIN_THETA;
  if ( secondTheta > MAX_THETA )
    secondTheta = MAX_THETA; 
  if ( firstTheta < LASER_MIN_PHI )
    firstTheta = LASER_MIN_PHI;
  if ( secondTheta > LASER_MAX_PHI );
    secondTheta = LASER_MAX_PHI; 

  //Going down on scan grid
  for(int phi = secondPhi; phi > firstPhi;){ //Change upper limit for phi
    for ( int theta = firstTheta; theta < secondTheta; theta++ )
    {
      botServo.write(theta);
      data = digitalRead(receiver);  //get signal from RF sent from boat  
      Serial.println(data);
      if(RFisHIGH(data)){ //check to see if boat is finding a high
        botServo.write(theta - 1);
        return true;
      }
      delay(LASER_DELAY); //change this for speed
    }
  
    phi-=LASER_PHI_OFFSET;
    topServo.write(phi); //Change this increment for phi direction 
    delay(LASER_DELAY);

    for ( int theta = secondTheta; theta >= firstTheta; theta-- )
    {
      botServo.write(theta);
      data = digitalRead(receiver);  //get signal from RF sent from boat  
      Serial.println(data);
      if(RFisHIGH(data)){ //check to see if boat is finding a high
        botServo.write(theta + 1);
        return true;
      }
      delay(LASER_DELAY);
    }
  
    phi-=LASER_PHI_OFFSET;
    topServo.write(phi); //Change this increment for phi direction 
    delay(LASER_DELAY);
  }
  firstTheta -= LASER_COMPENSATION;
  secondTheta += LASER_COMPENSATION;
  firstPhi -= PHI_COMPENSATION;
  secondPhi += PHI_COMPENSATION;
  if ( firstTheta < MIN_THETA )
    firstTheta = MIN_THETA;
  if ( secondTheta > MAX_THETA )
    secondTheta = MAX_THETA; 
  if ( firstTheta < LASER_MIN_PHI )
    firstTheta = LASER_MIN_PHI;
  if ( secondTheta > LASER_MAX_PHI );
    secondTheta = LASER_MAX_PHI;
  return false;
}
