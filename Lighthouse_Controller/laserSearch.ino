boolean laserSearch()
{
  //Going up on scan grid 
  for(int phi = MIN_PHI; phi < MAX_PHI;){ 
    for ( int theta = firstTheta; theta < secondTheta; theta++ )
    {
      botServo.write(theta);
     data = digitalRead(receiver);  //get signal from RF sent from boat 
      Serial.println(data);
      if(RFisHIGH(data)){ //check to see if boat is finding a high
        return true;
      }
      delay(delayValue); //change this for speed
    }
  
    phi+=PHI_OFFSET; //Potential to change phi direction movement
    topServo.write(phi); 
    delay(delayValue);
    
    for ( int theta = secondTheta; theta >= firstTheta; theta-- )
    {
      botServo.write(theta);
      data = digitalRead(receiver);  //get signal from RF sent from boat  
      Serial.println(data);
      if(RFisHIGH(data)){ //check to see if boat is finding a high
        return true;
      }
      delay(delayValue);
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
      if(RFisHIGH(data)){ //check to see if boat is finding a high
        return true;
      }
      delay(delayValue); //change this for speed
    }
  
    phi-=PHI_OFFSET;
    topServo.write(phi); //Change this increment for phi direction 
    delay(delayValue);

    for ( int theta = secondTheta; theta >= firstTheta; theta-- )
    {
      botServo.write(theta);
      data = digitalRead(receiver);  //get signal from RF sent from boat  
      Serial.println(data);
      if(RFisHIGH(data)){ //check to see if boat is finding a high
        return true;
      }
      delay(delayValue);
    }
  
    phi-=PHI_OFFSET;
    topServo.write(phi); //Change this increment for phi direction 
  }
  return false;
}
