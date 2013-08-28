 

boolean debounce99(boolean last)
{
  boolean current = digitalRead(mode99pb);
  if (last != current)
  {
    delay(5);
    current = digitalRead(mode99pb);
  }
  return current;
}

boolean debounce100(boolean last)
{
  boolean current = digitalRead(mode100pb);
  if (last != current)
  {
    delay(5);
    current = digitalRead(mode100pb);
  }
  return current;
}

boolean debounce101(boolean last)
{
  boolean current = digitalRead(mode101pb);
  if (last != current)
  {
    delay(5);
    current = digitalRead(mode101pb);
  }
  return current;
}
boolean debounce102(boolean last)
{
  boolean current = digitalRead(mode102pb);
  if (last != current)
  {
    delay(5);
    current = digitalRead(mode102pb);
  }
  return current;
}

boolean debounce103(boolean last)
{
  boolean current = digitalRead(mode103pb);
  if (last != current)
  {
    delay(5);
    current = digitalRead(mode103pb);
  }
  return current;
}

boolean debounce104(boolean last)
{
  boolean current = digitalRead(mode104pb);
  if (last != current)
  {
    delay(5);
    current = digitalRead(mode104pb);
  }
  return current;
}

 

void checkmode()
{
 


  //int mode = 100;

  currentButton99 = debounce99(lastButton99);
  if (lastButton99 == LOW && currentButton99 == HIGH)
  {
    
    Reset_ATO_Fault();
 
  }

  lastButton99 = currentButton99;


  currentButton100 = debounce100(lastButton100);
  if (lastButton100 == LOW && currentButton100 == HIGH)
  {
 

   Serial.println("PB pushed");
   if (shelf_lightsrunning == 1){
      shelf_lights = 1; //turn off feeding mode
      Serial.println("Turn off light");
    }
    else
    {
      shelf_lights = 3; //turn ON feeding mode
      Serial.println("Turn ON light");
    }
  }


  lastButton100 = currentButton100;



  currentButton101 = debounce101(lastButton101);


  if (lastButton101 == LOW && currentButton101 == HIGH)
  {
 

    //mode = 101;
    Serial.print("101 pb pushed - ato");
    if (checklevel_ATOrunning == 1){
      checklevel_ATOrunning = 0; //turn off ATO mode
      checklevel_ATO = 3;
      //LCD.Clear();
    }
    else
    {
      checklevel_ATO = 1; //turn ON waterchange mode
    }
  }
  lastButton101 = currentButton101;




  currentButton102 = debounce102(lastButton102);
  if (lastButton102 == LOW && currentButton102 == HIGH)
  {

 /*
    Serial.println("102 pressed w/c mode");
    // mode = 102;

    if (waterchangemoderunning == 1){
      waterchangemoderunning = 0; //turn off waterchange mode
      //LCD.Clear();
    }
    else
    {
      waterchangemode = 1; //turn ON waterchange mode
    }
*/

  }
  lastButton102 = currentButton102;

}
 
 
  
