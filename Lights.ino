 


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
   
   
   
   
void Shelf_Light(){

  //Pump mode 4 
  //Feed Mode Settings mode 10
   
// Serial.print("shelf_lightsrun");
 // Serial.println(shelf_lightsrun);
 // Serial.print("shelf_lightsrunning");
 // Serial.println(shelf_lightsrunning);
 //   Serial.print("shelf_lights");
  //Serial.println(shelf_lights);


  if(shelf_lights == 1){ 
    shelf_lights_off = 10;
    shelf_lights_on_second = RTC.second;
    if(RTC.minute + shelf_light_time > 59){
      shelf_lights_on_minute = (RTC.minute + shelf_light_time) % 60;
      shelf_lights_on_hour = RTC.hour + 1;
    }
    else{
      shelf_lights_on_minute = RTC.minute + shelf_light_time;
      shelf_lights_on_hour = RTC.hour;
    }

    if(shelf_lights_on_hour > 23){
      shelf_lights_on_hour = shelf_lights_on_hour - 24;
    }

  }

  if(shelf_lights == 3 && shelf_lightsrunning == 1){
    shelf_lights_off = -10;  
  }
  
  
  
  
 //Serial.println(shelf_lights_off);
 // Serial.println(RTC.minute);
 // Serial.println(shelf_lights_on_minute);
  
  if((shelf_lights_on_hour == RTC.hour  && shelf_lights_on_minute == RTC.minute  && shelf_lights_on_second <= RTC.second) || shelf_lights_off == -10){

  
      // Serial.println("Turning Off light");
       digitalWrite(relay_shelf_light, HIGH);
    
    shelf_lightsrunning = 0;
    shelf_lights_off = -10;

  }
  else{ 
     // Serial.println("Turning On light");
     digitalWrite(relay_shelf_light, LOW);
    }
    shelf_lightsrun = HIGH;
    shelf_lightsrunning = 1;

  //Display when normal operation will resume*******************
  if(shelf_lights_off != -10){
    
    
    if(shelf_lights_on_minute >= RTC.minute){
      shelf_lights_off_second = shelf_lights_on_second - RTC.second + shelf_light_time * 60 + shelf_lights_on_minute * 60 - RTC.minute * 60 - shelf_light_time * 60;
    }
    else{
      shelf_lights_on = RTC.minute - 60;
      shelf_lights_off_second = shelf_lights_on_second - RTC.second + shelf_light_time * 60 + shelf_lights_on_minute * 60 - shelf_lights_on * 60 - shelf_light_time * 60;
    }
    shelf_lights_off_minute = shelf_lights_off_second / 60;
  }
  else{

    if(shelf_lightsrun == HIGH){
     
      shelf_lightsrun = LOW;
    }

    

  }

  shelf_lights = 0;
}




