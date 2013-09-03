


///-------------------REFUGE Light--------------------------------------
void RunFugelight()
{

  RTC.getTime();
  // led on time
  float time = RTC.hour + ((float)RTC.minute / (float)60) + ((float)RTC.second / (float)3600);
  if(time >= FugeLightOn && time <= FugeLightOff)
  {
    // Turn refugelight On       
    set_refugelight_output_to = true;       

  }

  else
  {
    // Turn refugelight Off       
    set_refugelight_output_to = false;       

  } 



} 




void Light_shelf_Controller(){

  float current_time  = RTC.hour + ((float)RTC.minute / (float)60) + ((float)RTC.second / (float)3600); 
  float turn_off_light_shelf_when;

  if (light_shelf_delay_bool == true ){
    turn_off_light_shelf_when = light_shelf_delay_start_time + light_shelf_delay_time;
  }



  if (current_time  >= turn_off_light_shelf_when){
    if (light_shelf_delay_bool == true ){


     // set_light_shelf_output_to = true; 
     
      Serial.println("Turning Off light");
      digitalWrite(relay_shelf_light, HIGH);
      light_shelf_delay_bool = false; 

    
    }

 
  } else{
      
       Serial.println("Turning On light");
    digitalWrite(relay_shelf_light, LOW);
 
  }


}



void turn_on_shelf_light(){
 
  
  RTC.getTime();
  light_shelf_delay_start_time = RTC.hour + ((float)RTC.minute / (float)60) + ((float)RTC.second / (float)3600); 
  light_shelf_delay_bool = true;
  
  Serial.println("Trying to Turn On light");




}

