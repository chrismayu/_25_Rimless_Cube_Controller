/****************Auto top off********************************************************************************/ 


void ATO(){   /// Main ATO Program Controller 

  if(digitalRead(ATO_High) == HIGH ){ 
      
      current_status_of_water_level = true;
  
    } 
    else{ 
      current_status_of_water_level = false;
       // testing git controll
    }
  // start the ATO on the correct time - allows it to only run between 8 am and 8:30 
  
  float start_time = RTC.hour + ((float)RTC.minute / (float)60) + ((float)RTC.second / (float)3600); 
  
 if(start_time == ATO_time){ 
    ATOmoderun = HIGH; 
  } 

  float stop_time = ATO_time + 3.00; 


 if(start_time == stop_time){ 
    ATOmoderun = LOW; 
  } 




   // Start Logic 

 // if(feedmoderun == HIGH || waterchangemode == 1 || waterchangemoderunning == 1 ){ 
        //Do not Run ATO - Feedmode or Waterchange mode is active 
   //   S_L_ATO_Screen_text = "ATO:  Disabled  "; 
  

 // } else{ 

    if(digitalRead(ATO_High) == HIGH ){ 
      
      ATO_Run_Next_Time = HIGH; 
    // Serial.println( "LEVEL IS LOW"); 
    S_L_ATO_Screen_text = "H20 Low Run ATO "; 

    } 
    else{ 
      ATO_Run_Next_Time = LOW; 
   
      ATO_Got_Time = LOW; 
      S_L_ATO_Screen_text = "H20 Level = Fine "; 
     //Serial.println( "LEVEL IS FINE"); 
    } 
 // } 


  // Fault Code 

  float time_Fault = RTC.hour + ((float)RTC.minute / (float)60) + ((float)RTC.second / (float)3600); 


  if(time_Fault == Fault_ATO_AT){ 
    Serial.print("ATO Faulted"); 
    ATO_Fault_Count = ATO_Fault_Count + 1; 
  } 

  Run_ATO(); 

} 

void Run_ATO(){ 

  /// Code to run the ATO 
  //Capture the Time and turn on the ATO if BOOL is high turn off when times up 
  /// fill till float = but if no limit is hit with in a certain time - fauletd out  - display on screen and resetable via the reset button 


  if(ATO_Run_Next_Time == HIGH){ /// && ATOmoderun == HIGH && ATOfaulted == LOW){ 


    if(ATO_Got_Time == LOW){ 
      Started_ATO = RTC.hour + ((float)RTC.minute / (float)60) + ((float)RTC.second / (float)3600); 
      ATO_Got_Time = HIGH; 
    } 

    Fault_ATO_AT = Started_ATO + 0.03; 

    digitalWrite(ATO_Valve, LOW); 

    sprintf(Last_ATO, "ATO RAN:  %02d/%02d %02d:%02d", RTC.month, RTC.day, RTC.hour, RTC.minute); 

  // strcpy(S_L_ATO_LAST_Screen_text, "ATO PUMP Running"); 
     S_L_ATO_LAST_Screen_text = "ATO PUMP Running"; 
   
   
  } 
  else{ 
    digitalWrite(ATO_Valve, HIGH); 

        if(ATO_Fault_Count >= 6){ 
        ATOfaulted = HIGH;
      // strcpy(S_L_ATO_LAST_Screen_text, "ATO RAN" + Last_ATO);   sprintf("Wait %d second(s)", i) 
        S_L_ATO_LAST_Screen_text = "ATO Faulted    ";
        Fault_meessage_to_iphone(); 
        
        }else{ 
        S_L_ATO_LAST_Screen_text = Last_ATO;  
        
        sent_ato_fault_message_to_iphone = LOW; 
        } 

  } 
  
  
  
  
} //ATOfaulted



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
  
} 


void Fault_meessage_to_iphone(){ 


 if (sent_ato_fault_message_to_iphone == LOW){ 
 //Send_message_to_iphone("ATO System", " Faulted - Check RO Water Supply"); 
  
 sent_ato_fault_message_to_iphone = HIGH; 
} 


} 






