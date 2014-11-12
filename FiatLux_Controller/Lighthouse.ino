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

// search will be done with diagonal thingies. 
// choose a somewhat small offset for theta and phi (if applicable) and do a search. 
// when search is complete we will have an interrupt signal stop the motors. 
// we can do some end stuff here. like blink the led or something.
