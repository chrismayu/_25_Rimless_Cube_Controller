
/****************Auto top off********************************************************************************/



void ATO(){ /// Main ATO Program Controller



//Delcarations

float current_time = RTC.hour + ((float)RTC.minute / (float)60) + ((float)RTC.second / (float)3600);

float time_Fault = RTC.hour + ((float)RTC.minute / (float)60) + ((float)RTC.second / (float)3600);

float start_time = RTC.hour + ((float)RTC.minute / (float)60) + ((float)RTC.second / (float)3600);

float Ato_okay_to_run_now;

float Ato_Pump_last_ran;

float Ato_okay_to_run_pump_now;

float Run_Pump_for_only_timer = 0.03;





  if(digitalRead(ATO_High) == HIGH ){

      

      current_status_of_water_level = true; //WaterLevel okay

      ATO_Run_Next_Time = HIGH;

    

     // Serial.println( "LEVEL IS LOW");

    

    S_L_ATO_Screen_text = "H20 Low Run ATO ";

  

    }else{

      

      current_status_of_water_level = false;

      



      digitalWrite(ATO_Valve, HIGH); // turn off ATO Pump



      ATO_Run_Next_Time = LOW;  

   

      ATO_Got_Time = LOW;



      S_L_ATO_Screen_text = "H20 Level = Fine ";

     //Serial.println( "LEVEL IS FINE");    



     Reset_ATO_Fault(); // reset All faults if water level is fine

 



    }

 



/// grabs the time when the ATO ran last



      if(ATO_Got_Time == LOW){

      ATO_ran_last = RTC.hour + ((float)RTC.minute / (float)60) + ((float)RTC.second / (float)3600);

      ATO_Got_Time = HIGH;

      }





/// grabs the time when the ATO Pump ran last



      if(ATO_Got_Time_Pump == LOW){

      Started_ATO = RTC.hour + ((float)RTC.minute / (float)60) + ((float)RTC.second / (float)3600);

      ATO_Got_Time_Pump = HIGH;

      }









// adds a delay between runnings If Water Level is high- so it isn't starting and stopping



float ATO_delay_Water_level = ATO_delay_between_runs + ATO_ran_last;





if(ATO_delay_Water_level >= Ato_okay_to_run_now){



Ato_okay_to_run_now = ATO_delay_Water_level;



}







// Adds a delay if the pump is running for a while

Ato_okay_to_run_pump_now = ATO_delay_between_runs + Ato_Pump_last_ran;



if(Ato_okay_to_run_pump_now >= Ato_okay_to_run_now){



Ato_okay_to_run_now = Ato_okay_to_run_pump_now;



}





 // Watchman_timer Code

 

  if(Watchman_timer_ATO_AT == Started_ATO){

    Serial.print("ATO Faulted");

    ATO_Fault_Count = ATO_Fault_Count + 1;



   

  }





   if(Watchman_timer_ATO_AT <= current_time){



    float Watchman_timer_ATO_AT_timer = ATO_delay_between_runs + current_time;

    

       if(Watchman_timer_ATO_AT_timer >= Ato_okay_to_run_now){



           Ato_okay_to_run_now = Watchman_timer_ATO_AT_timer;



        }



    }







/// ATO Pump Start/Stop Logic



if(current_time >= Ato_okay_to_run_now && ATO_Run_Next_Time == HIGH && ATOfaulted == LOW){









   if(ATO_Got_Time_Pump == HIGH){

    ATO_Got_Time_Pump = LOW;   // Sets up for Started_ATO timer

    }

    Watchman_timer_ATO_AT = Started_ATO + Run_Pump_for_only_timer;

 





     digitalWrite(ATO_Valve, LOW);  //turn ON ATO Pump



 



    ///Tracks when the Atop Pump Ran Last

     Ato_Pump_last_ran = RTC.hour + ((float)RTC.minute / (float)60) + ((float)RTC.second / (float)3600);

   





    /// Screen Display Data

    sprintf(Last_ATO, "ATO RAN: %02d/%02d %02d:%02d", RTC.month, RTC.day, RTC.hour, RTC.minute);

    S_L_ATO_LAST_Screen_text = "ATO PUMP Running";





  }else{





        digitalWrite(ATO_Valve, HIGH);   // Turn OFF Pump





       // Sets up the timer to run again if the water level is low

         ATO_Got_Time = LOW;







        

 



 }



 



 //Started_ATO = RTC.hour + ((float)RTC.minute / (float)60) + ((float)RTC.second / (float)3600);

 

   

//ATO_ran_last = RTC.hour + ((float)RTC.minute / (float)60) + ((float)RTC.second / (float)3600);

 //ATO_delay_between_runs;



 





Serial.print("Ato_okay_to_run_now ");

 Serial.println(Ato_okay_to_run_now);

 

 Serial.print("ATO_ran_last ");

 Serial.println(ATO_ran_last);

 Serial.print(" ");

  

 



/// Fault Logic





      if(ATO_Fault_Count >= 3){

        ATOfaulted = HIGH;

 

        Fault_meessage_to_Reef_Sense();

        

        }else{

 

        sent_ato_fault_message_to_iphone = LOW;

      

        }





}



 







void Screen_ATO(){



        //could move this to screen tab





  // First ATO Screen



  if(small_LCD_Screen == S_L_ATO_Screen){

        //LCDsmall.setCursor(0, 1);

      //LCDsmall.print(S_L_ATO_Screen_text);

    }



  //Second ATO Screen



  if(small_LCD_Screen == S_L_ATO_LAST_Screen){

   //LCDsmall.setCursor(0, 1);

   //LCDsmall.print(S_L_ATO_LAST_Screen_text);

    }

  



}







void Reset_ATO_Fault(){

  ATO_Fault_Count = 0;

  ATOfaulted = LOW;

  

}





void Fault_meessage_to_Reef_Sense(){





 if (sent_ato_fault_message_to_iphone == LOW){



 //Send_message_to_Reef_Sense("ATO System", " Faulted - Check RO Water Supply");

  

  sent_ato_fault_message_to_iphone = HIGH;

  }





}


