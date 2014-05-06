




///-------------------REFUGE Light--------------------------------------

void RunFugelight()

{

  float time = current_time;

  if(time >= FugeLightOn && time <= FugeLightOff)

  {

    // Turn refugelight On

    set_refugelight_output_to = true;

  } 
  else  {

    // Turn refugelight Off

    set_refugelight_output_to = false;



  }



}


void Light_shelf_Controller(){




  float turn_off_light_shelf_when;

  if(top_relays.digitalRead(relay_shelf_light) == LOW && light_shelf_is_on == false){

    light_shelf_is_on = true;

    light_shelf_delay_start_time = current_time;
    light_shelf_delay_bool = true;

  }

  else{


  }


  if(top_relays.digitalRead(relay_shelf_light) == HIGH ){

    light_shelf_is_on = false;

  }





  if (light_shelf_delay_bool == true ){

    turn_off_light_shelf_when = light_shelf_delay_start_time + light_shelf_delay_time;

  }




  if (current_time >= turn_off_light_shelf_when){

    if (light_shelf_delay_bool == true ){

      // set_light_shelf_output_to = true;

      if (DEBUG_Shelf_light) Serial.println("Turning Off light");

      top_relays.digitalWrite(relay_shelf_light, HIGH);

      light_shelf_delay_bool = false;

    }


  } 
  else{
    if (DEBUG_Shelf_light) Serial.println("Turning On light");
    top_relays.digitalWrite(relay_shelf_light, LOW);
  }


  if(top_relays.digitalRead(relay_shelf_light) == LOW ){

    if (DEBUG_Shelf_light) Serial.print("-----  LIGHT START ---------- ");
    if (DEBUG_Shelf_light) Serial.print("relay_shelf_light out status: ");   
    if (DEBUG_Shelf_light) Serial.println(top_relays.digitalRead(relay_shelf_light));
    if (DEBUG_Shelf_light) Serial.print("turn_off_light_shelf_when ");
    if (DEBUG_Shelf_light) Serial.println(turn_off_light_shelf_when);
    if (DEBUG_Shelf_light) Serial.print("Current Time ");
    if (DEBUG_Shelf_light) Serial.println(current_time);
    if (DEBUG_Shelf_light) Serial.print("Will Run in: ");
    if (DEBUG_Shelf_light) Serial.println(current_time - turn_off_light_shelf_when);
    if (DEBUG_Shelf_light) Serial.print("light_shelf_delay_bool ");
    if (DEBUG_Shelf_light) Serial.println(light_shelf_delay_bool);
    if (DEBUG_Shelf_light) Serial.print("light_shelf_is_on ");
    if (DEBUG_Shelf_light) Serial.println(light_shelf_is_on);
    if (DEBUG_Shelf_light) Serial.print(" ");
    if (DEBUG_Shelf_light) Serial.print("-----  LIGHT END ---------- ");

  }

}







void turn_on_shelf_light(){

  turn_on_light_shelf = true;
  top_relays.digitalWrite(relay_shelf_light, LOW);
  if (DEBUG_Shelf_light) Serial.println("Trying to Turn On light");

}





