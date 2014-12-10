// purely does the entire laser search. 
// takes the modified and saved theta and phi values and loops through there. 
// each spot we search and listen for inputs. 
// then we return true if it's found,
// otherwise we increase the grid area and continue searching. 
boolean laserSearch()
{
  //Going up on scan grid 
  for(int phi = firstPhi; phi < secondPhi;){ 
    for ( int theta = firstTheta; theta < secondTheta; theta++ )
    {
      if (searchAtTheta(theta))
        return true;
      delay(LASER_DELAY); //change this for speed
    }
  
    phi+=LASER_PHI_OFFSET; //Potential to change phi direction movement
    topServo.write(phi); 
    delay(LASER_DELAY);
    digitalWrite(laserPin, HIGH);
    
    for ( int theta = secondTheta; theta >= firstTheta; theta-- )
    {
      if (searchAtTheta(theta))
        return true;
      delay(LASER_DELAY);
    }
  
    phi+=LASER_PHI_OFFSET;
    topServo.write(phi); //Change this increment for phi direction 
    delay(LASER_DELAY);
  }

  increaseScanGrid();

  //Going down on scan grid
  for(int phi = secondPhi; phi > firstPhi;){ //Change upper limit for phi
    for ( int theta = firstTheta; theta < secondTheta; theta++ )
    {
      if (searchAtTheta(theta))
        return true;
      delay(LASER_DELAY); //change this for speed
    }
  
    phi-=LASER_PHI_OFFSET;
    topServo.write(phi); //Change this increment for phi direction 
    delay(LASER_DELAY);

    for ( int theta = secondTheta; theta >= firstTheta; theta-- )
    {
      if (searchAtTheta(theta))
        return true;
      delay(LASER_DELAY);
    }
  
    phi-=LASER_PHI_OFFSET;
    topServo.write(phi); //Change this increment for phi direction 
    delay(LASER_DELAY);
  }
  increaseScanGrid();
  return false; // indicates that we should continue searching. 
}

// this increases the area of our scan area. 
// this ensures that even under some sort of search failure, 
// we can still get back to a state where the item can be found
// eventually. 
void increaseScanGrid()
{
  firstTheta -= LASER_COMPENSATION;
  secondTheta += LASER_COMPENSATION;
  firstPhi -= PHI_COMPENSATION;
  secondPhi += PHI_COMPENSATION;
  if ( firstTheta < MIN_THETA )
    firstTheta = MIN_THETA;
  if ( secondTheta > MAX_THETA )
    secondTheta = MAX_THETA; 
  if ( firstPhi < LASER_MIN_PHI )
    firstPhi = LASER_MIN_PHI;
  if ( secondPhi > LASER_MAX_PHI )
    secondPhi = LASER_MAX_PHI;
}

// writes theta and checks boat for inputs. 
// returns true when there is an input, and therefore the laser has found the boat.
// otherwise returns false, indicating the code to continue searching. 
boolean searchAtTheta( int theta )
{
  botServo.write(theta);
  data = digitalRead(receiver);  //get signal from RF sent from boat  
  Serial.println(data);
  if(RFisHIGH(data)){ //check to see if boat is finding a high
    return true;
  }
  return false;
}
