const int Code1alarm = '1';              
const int Code2alarm = '1';              
const int Code3alarm = '1';              
const int Code4alarm = '1';              
const int Code5alarm = '1';              
const int Code6alarm = '1';              
const int Code7alarm = '1';              
const int Code8alarm = '1';              
const int Code9alarm = '1';  
const int Code10alarm = '1'; 
 
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);



void alarm(){
   
  char KeyDigit = keypad.getKey();    

  if ((armed == 1) &&                                                    
    ((KeyDigit == '1') || 
    (KeyDigit == '2')  || 
    (KeyDigit == '3')  || 
    (KeyDigit == '4')  || 
    (KeyDigit == '5')  || 
    (KeyDigit == '6')  || 
    (KeyDigit == '7')  || 
    (KeyDigit == '8')  || 
    (KeyDigit == '9')  || 
    (KeyDigit == '0')  || 
    (KeyDigit == '*')  || 
    (KeyDigit == '#')))
 
    {  
                                
      PinCodeCounter++;                                                       // PinCodeCounter value +1 for every press on any Digitkey on the keypad
      digitalWrite (Buzzer, HIGH);                                            // Make a short beep for a DigitKey press on the keypad
      delay (50);                                                             //
      digitalWrite (Buzzer, LOW);                                             //
           
    }
    if ((Code10Correct == 1) && (armed == 1) && (KeyDigit == '#'))                    
  {
    fail = 0;                                      
    digitalWrite (Buzzer, HIGH);
    digitalWrite (RedLed, LOW);//
    delay (150);                                            //
    digitalWrite (Buzzer, LOW);                             //
    delay (50);                                             //
    digitalWrite (Buzzer, HIGH);                            //
    delay (150);                                            //
    digitalWrite (Buzzer, LOW);                             //
    delay (500);                                            //          
    digitalWrite (RedLed, HIGH);                          
    Serial.println("Correct PinCode");                        
    armed = 0;                                            
  }
 if ((Code10Correct == 0) && (PinCodeCounter > 10) && (armed == 1) && (KeyDigit == '#'))       
  {
    WrongPinCode = 1;
    PinCodeCounter = 0; 
    Code1Correct = 0;
    Code2Correct = 0;
    Code3Correct = 0;
    Code4Correct = 0;
    Code5Correct = 0;
    Code6Correct = 0;
    Code7Correct = 0;                
    Code8Correct = 0;
    Code9Correct = 0;
    Code10Correct = 0;
    } 
 if ((WrongPinCode == 1)  && (armed == 1))      
  { 
    digitalWrite (Buzzer, HIGH);     
    digitalWrite (RedLed, HIGH);
    delay(1500);                                                         
    digitalWrite (Buzzer, LOW);
                
    Serial.println("WrongCode or Timer expired");                                 
    WrongPinCode = 0;                                                       
  }




//-----------------------------------------------Code for determine the correct PinCode for ALARM ----------------------------------------------------------------------------------------------------------





if ((KeyDigit == Code1alarm) && (Code1Correct == 0) && (armed = 1))           // If you offered the valid alarm, first PinCode and you did not entered it before (Otherwise we conflict with same KeyDigits)
    {
      
      Code1Correct = 1;                                                                                        // Variable Code1Correct is set to 1
      return;                                                                                                  // Return to begin loop
    } 
      
if ((KeyDigit == Code2alarm) && (Code1Correct == 1) && (Code2Correct == 0) && (armed = 1))        // If you offered the valid alarm, second PinCode and you did not entered it before (Otherwise we conflict with same KeyDigits)
    {
      
      Code2Correct = 1;                                                                                        // Variable Code2Correct is set to 1
      return;                                                                                                  // Return to begin loop
    } 
    
if ((KeyDigit == Code3alarm) && (Code2Correct == 1) && (Code3Correct == 0) && (armed = 1))         // If you offered the valid alarm, third PinCode and you did not entered it before (Otherwise we conflict with same KeyDigits)
    {
      
      Code3Correct = 1;                                                                                         // Variable Code3Correct is set to 1
      return;                                                                                                   // Return to begin loop
    } 
     
if ((KeyDigit == Code4alarm) && (Code3Correct == 1) && (Code4Correct == 0) && (armed = 1))         // If you offered the valid alarm, fourth PinCode and you did not entered it before (Otherwise we conflict with same KeyDigits)
    {
      
      Code4Correct = 1;                                                                                         // Variable Code4Correct is set to 1
      return;                                                                                                   // Return to begin loop
    }  
if ((KeyDigit == Code5alarm) && (Code4Correct == 1) && (Code5Correct == 0) && (armed = 1))         // If you offered the valid alarm, fifth PinCode and you did not entered it before (Otherwise we conflict with same KeyDigits)
    {

      Code5Correct = 1;                                                                                         // Variable Code5Correct is set to 1
      return;                                                                                                   // Return to begin loop
    } 

if ((KeyDigit == Code6alarm) && (Code5Correct == 1) && (Code6Correct == 0) && (armed = 1))         // If you offered the valid alarm, sixth PinCode and you did not entered it before (Otherwise we conflict with same KeyDigits)
    {

      Code6Correct = 1;                                                                                         // Variable Code6Correct is set to 1
      return;                                                                                                   // Return to begin loop
    }
if ((KeyDigit == Code7alarm) && (Code6Correct == 1) && (Code7Correct == 0) && (armed = 1))         // If you offered the valid alarm, sixth PinCode and you did not entered it before (Otherwise we conflict with same KeyDigits)
    {

      Code7Correct = 1;                                                                                         // Variable Code6Correct is set to 1
      return;                                                                                                   // Return to begin loop
    }  

if ((KeyDigit == Code8alarm) && (Code7Correct == 1) && (Code8Correct == 0) && (armed = 1))         // If you offered the valid alarm, sixth PinCode and you did not entered it before (Otherwise we conflict with same KeyDigits)
    {

      Code8Correct = 1;                                                                                         // Variable Code6Correct is set to 1
      return;                                                                                                   // Return to begin loop
    }      
if ((KeyDigit == Code9alarm) && (Code8Correct == 1) && (Code9Correct == 0) && (armed = 1))         // If you offered the valid alarm, sixth PinCode and you did not entered it before (Otherwise we conflict with same KeyDigits)
    {

      Code9Correct = 1;                                                                                         // Variable Code6Correct is set to 1
      return;                                                                                                   // Return to begin loop
    }  
if ((KeyDigit == Code10alarm) && (Code9Correct == 1) && (Code10Correct == 0) )         // If you offered the valid alarm, sixth PinCode and you did not entered it before (Otherwise we conflict with same KeyDigits)
    {

      Code10Correct = 1;                                                                                         // Variable Code6Correct is set to 1
      return;                                                                                                   // Return to begin loop
    }          

}



