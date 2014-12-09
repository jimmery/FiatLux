boolean laserSearch()
{
  //Going up on scan grid 
  for(int phi = LASER_MIN_PHI; phi < LASER_MAX_PHI;){ 
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

  if ( firstTheta > 0 )
    firstTheta--;
  if ( secondTheta < MAX_THETA )
    secondTheta++;  

  //Going down on scan grid
  for(int phi = LASER_MAX_PHI; phi > LASER_MIN_PHI;){ //Change upper limit for phi
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
  if ( firstTheta > 0 )
    firstTheta--;
  if ( secondTheta < MAX_THETA )
    secondTheta++;
  return false;
}
