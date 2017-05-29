#include <Keypad.h>                 // This sketch uses the Keypad.h library
#include <SPI.h>                    // This sketch uses the SPI.h library
#include <MFRC522.h>                // This sketch uses the MFRC522.h library
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#define SS_PIN 10                   // Define SS_PIN of the RC522 RFID Reader to digital pin 10 of the Arduino
#define RST_PIN 9                   // Define RST_PIN of the RC522 RFID Reader to digital pin 9 of the Arduino
#include "pincodes.h"
#include "int.h"
#include "alarm.h"
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance. 



void setup() 

{ 
  lcd.begin(16, 2);
  SPI.begin();                                            // Initialize the SPI bus
  mfrc522.PCD_Init();                                     // Initialize the MFRC522 
  pinMode (RedLed, OUTPUT);                               // Define RedLed as OUTPUT
  pinMode (Buzzer, OUTPUT);                               // Define Buzzer as OUTPUT
  pinMode (Door, OUTPUT);                               // Define Door as OUTPUT
  pinMode (pir, INPUT);                               // Define Door as OUTPUT
  digitalWrite (Door, HIGH);
  lcd.setCursor(4, 0);
  lcd.print("WELCOME");


}
void loop(){

  if (armed == 0 ){
    pirsense();
    scancard(); 
  }
  else if (armed == 1)
  {
    alarm();
   }
    
  
}

void pirsense(){
  sense = digitalRead(pir);
if (sense == HIGH ){
    lcd.backlight();
    }
 else
 {
  if(RightCard == 0){
 lcd.noBacklight();  
 }
 }
}



void scancard() {   


//----------------------------------------------Code for the reset function of the loop--------------------------------------------------------------------------------------------------------


if (Reset == 1)                                           // If Reset has value 1 (HIGH) all variables will be reset to 0 and the RC522 RFID reader will be waiting for a new Mifare Card.
{                                                         
  RightCard = 0;
  MifareCard1 = 0; 
  MifareCard2 = 0;                                      
  RightPinCode = 0;
  WrongPinCode = 0;
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
  PinCodeCounter = 0;  
  delay (50);
  digitalWrite (RedLed, HIGH);
  digitalWrite (Door, HIGH);
  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print("Welcome");
  lcd.noBacklight();  
  Reset = 0;
}


//----------------------------------------------Code for the control for a valid pincode within the timelimit of 7 seconds after presenting/offering a valid Mifare Card ---------------------------


if (millis()- Timer > 10000 && RightCard == 1)            // If the Timer will be larger as 7 seconds and a valid Mifare Card is offered, reset value will be high.
   {                                                     // This means that you have after presenting a valid card, 7 seconds to enter a valid code or the loop resets.
    Reset = 1;
    Serial.println("CardAccesOff");
   }



   
//----------------------------------------------Reading the presented/offered Mifare Card at the MFRC522 ----------------------------------------------------------------------------------------- 

 
if   (mfrc522.PICC_IsNewCardPresent() &&                
      mfrc522.PICC_ReadCardSerial())
    {
     

      
//-------------------------------------------------------------------CARD 1 DETECTED FUNCTION----------------------------------------------------------------------------------------
     if                                                  
     (mfrc522.uid.uidByte[0] == 43   &&                // Fill in the first digits of the UID number of your Mifare card
      mfrc522.uid.uidByte[1] == 149   &&                // Fill in the seconds digits of the UID number of your Mifare card              
      mfrc522.uid.uidByte[2] == 119   &&                // Fill in the third digits of the UID number of your Mifare card
      mfrc522.uid.uidByte[3] == 172)                    // Fill in the fourth digits of the UID number of your Mifare card
   
     {
      RightCard = 1;                                     // The offered Mifare Card is known in the database, set variable "RightCard" to 1
      MifareCard1 = 1;                                   // This Mifare Card is known as Mifare Card 2 in the Database, so set variable MifareCard2 to value 1. 
      digitalWrite (RedLed, LOW);
      delay (150);       
      digitalWrite (Buzzer, HIGH);                       // Make a beep for the accepted Mifare Card             
      delay (150);                                       //
      digitalWrite (Buzzer, LOW);                        //
     
      PinCodeCounter = 0;                                // Reset the PinCodeCounter to 0
      Timer =  millis();                                 // Reset the Timer. The 7 seconds limit is running now for a valid PinCode
      lcd.backlight();
      delay (200);
      lcd.setCursor(0, 1);
      lcd.print("Nilava Chowdhury");                     // Print the text "CardAccesOn" to the serial monitor 
      delay (500);                                       // Wait 200 milliseconds
      lcd.clear();
      lcd.setCursor(1, 0);
      lcd.print("Enter Password");
      }

      
//-------------------------------------------------------------------CARD 2 DETECTED FUNCTION----------------------------------------------------------------------------------------
     else if                                                    
     (mfrc522.uid.uidByte[0] == 0xEB   &&                 // Fill in the first digits of the UID number of your Mifare card
      mfrc522.uid.uidByte[1] == 0x70   &&                 // Fill in the seconds digits of the UID number of your Mifare card              
      mfrc522.uid.uidByte[2] == 0xC0   &&                 // Fill in the third digits of the UID number of your Mifare card
      mfrc522.uid.uidByte[3] == 0xBC)                     // Fill in the fourth digits of the UID number of your Mifare card
                                                       
    {     
      RightCard = 1;                                       // If the offered Mifare Card is known in the database, set variable "RightCard" to 1
      MifareCard2 = 1;
      digitalWrite (Buzzer, HIGH);                         // Make a beep for the accepted Mifare Card             
      delay (150);                                         //
      digitalWrite (Buzzer, LOW);                          //
     
      PinCodeCounter = 0;                                  // Reset the PinCodeCounter to 0
      Timer =  millis();                                   // Reset the Timer. The 7 seconds limit is running now for a valid PinCode
      Serial.println("CardAccesOn");                       // Print the text "CardAccesOn" to the serial monitor 
      delay (200);                                         // Wait 200 milliseconds
    } 
//-------------------------------------------------------------------CARD 3 DETECTED FUNCTION----------------------------------------------------------------------------------------
     else if                                                  
     (mfrc522.uid.uidByte[0] == 44   &&                // Fill in the first digits of the UID number of your Mifare card
      mfrc522.uid.uidByte[1] == 149   &&                // Fill in the seconds digits of the UID number of your Mifare card              
      mfrc522.uid.uidByte[2] == 119   &&                // Fill in the third digits of the UID number of your Mifare card
      mfrc522.uid.uidByte[3] == 172)                    // Fill in the fourth digits of the UID number of your Mifare card
   
     {
      RightCard = 1;                                     // The offered Mifare Card is known in the database, set variable "RightCard" to 1
      MifareCard3 = 1;                                   // This Mifare Card is known as Mifare Card 2 in the Database, so set variable MifareCard2 to value 1. 
      digitalWrite (RedLed, LOW);
      delay (150);       
      digitalWrite (Buzzer, HIGH);                       // Make a beep for the accepted Mifare Card             
      delay (150);                                       //
      digitalWrite (Buzzer, LOW);                        //
     
      PinCodeCounter = 0;                                // Reset the PinCodeCounter to 0
      Timer =  millis();                                 // Reset the Timer. The 7 seconds limit is running now for a valid PinCode
      lcd.backlight();
      delay (200);
      lcd.setCursor(0, 1);
      lcd.print("Nilava Chowdhury");                     // Print the text "CardAccesOn" to the serial monitor 
      delay (500);                                       // Wait 200 milliseconds
      lcd.clear();
      lcd.setCursor(1, 0);
      lcd.print("Enter Password");
      }
//-------------------------------------------------------------------CARD 4 DETECTED FUNCTION----------------------------------------------------------------------------------------
     else if                                                  
     (mfrc522.uid.uidByte[0] == 40   &&                // Fill in the first digits of the UID number of your Mifare card
      mfrc522.uid.uidByte[1] == 149   &&                // Fill in the seconds digits of the UID number of your Mifare card              
      mfrc522.uid.uidByte[2] == 119   &&                // Fill in the third digits of the UID number of your Mifare card
      mfrc522.uid.uidByte[3] == 172)                    // Fill in the fourth digits of the UID number of your Mifare card
   
     {
      RightCard = 1;                                     // The offered Mifare Card is known in the database, set variable "RightCard" to 1
      MifareCard4 = 1;                                   // This Mifare Card is known as Mifare Card 2 in the Database, so set variable MifareCard2 to value 1. 
      digitalWrite (RedLed, LOW);
      delay (150);       
      digitalWrite (Buzzer, HIGH);                       // Make a beep for the accepted Mifare Card             
      delay (150);                                       //
      digitalWrite (Buzzer, LOW);                        //
     
      PinCodeCounter = 0;                                // Reset the PinCodeCounter to 0
      Timer =  millis();                                 // Reset the Timer. The 7 seconds limit is running now for a valid PinCode
      lcd.backlight();
      delay (200);
      lcd.setCursor(0, 1);
      lcd.print("Nilava Chowdhury");                     // Print the text "CardAccesOn" to the serial monitor 
      delay (500);                                       // Wait 200 milliseconds
      lcd.clear();
      lcd.setCursor(1, 0);
      lcd.print("Enter Password");
      }

    
    else{
      lcd.backlight();
      lcd.setCursor(2, 0);
      lcd.print("Invalid Card");                     // Print the text "CardAccesOn" to the serial monitor 
      lcd.setCursor(0, 1);
      lcd.print("Wrong Attempt");
      lcd.setCursor(14, 1);
      lcd.print(1 + fail);
      digitalWrite (RedLed, LOW);
      delay (100);  
      digitalWrite (Buzzer, HIGH);
      digitalWrite (RedLed, HIGH);                                  
      delay (150);                                        
      digitalWrite (Buzzer, LOW);
      digitalWrite (RedLed, LOW);
      delay (150);  
      digitalWrite (Buzzer, HIGH);
      digitalWrite (RedLed, HIGH);                                  
      delay (150);                                        
      digitalWrite (Buzzer, LOW);
      digitalWrite (RedLed, LOW);
      Reset = 1;
      fail++;
      if (fail >= 3){
      lcd.backlight();
      lcd.clear();
      lcd.print("****ALARM ON****");  
       armed = 1;
      }
      }

    } 
   

//-----------------------------------------------Code for accepting a valid MifareCard + valid PinCode-------------------------------------------------------------------------------------------------



if (Code6Correct == 1 && RightCard == 1)                    // If the PinCode is the correct and you did enter this within 7 seconds
  {
    RightPinCode = 1;                                       // Variable RightPinCode will be set to 1 
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("Door Unlocked");  
    digitalWrite (Buzzer, HIGH);
    digitalWrite (Door, LOW);
    digitalWrite (RedLed, LOW);//
    delay (150);                                            //
    digitalWrite (Buzzer, LOW);                             //
    delay (50);                                             //
    digitalWrite (Buzzer, HIGH);                            //
    delay (150);                                            //
    digitalWrite (Buzzer, LOW);                             //
    delay (500);                                            //          
    digitalWrite (RedLed, HIGH);
    digitalWrite (Door, HIGH);                          
    fail = 0;
    Reset = 1;                                              // Reset the loop
  }

//-----------------------------------------------Code for refusing a valid MifareCard + invalid PinCode------------------------------------------------------------------------------------------------



if ((Code6Correct == 0) && (PinCodeCounter >= 6) && (RightCard == 1))       // If you offered a valid Mifare Card and the Pincode is not correct and you already entered 6 digitkeys 
  {  
    WrongPinCode = 1;                                                       // Variable WrongPinCode will be set to 1
    lcd.setCursor(3, 1);
    lcd.print("Wrong Pin");
    delay(500); 
    lcd.setCursor(0, 1);
    lcd.print("Wrong Attempt");
    lcd.setCursor(14, 1);
    lcd.print(1 + fail);
    delay(500); 
    Reset = 1;                                                              // Reset the loop
  } 


//-----------------------------------------------Code for refusing a Wrong/Invalid PinCode or the Timer (7seconds) expired----------------------------------------------------------------------------



if ((WrongPinCode == 1) || (millis()- Timer > 10000 && RightCard == 1))      // If you offered a valid Mifare Card and  you entered a wrong PinCode or the timer (7 seconds) expires
  { 
    if((millis()- Timer > 7000 && RightCard == 1)){
    delay(500);
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("Timer Expired");
    digitalWrite (Buzzer, HIGH);                                            // Make a long beep and set the Red LED HIGH for the wrong code or timer expiry
    digitalWrite (RedLed, HIGH);
    delay(1500);                                                            //
    digitalWrite (Buzzer, LOW);                                             //
    }
    fail++;
    if (fail >= 3){
      lcd.clear();
      lcd.print("****ALARM ON****");  
  WrongPinCode = 0;
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
  PinCodeCounter = 0;
  armed = 1;
    }                 
    Reset = 1;                                                              // Reset the loop
  }

if(millis()- Timer > 600000 && fail >= 1){
  Timer =  millis();
  fail = 0;
}

//-----------------------------------------------Code for counting the inputs on the keypad-------------------------------------------------------------------------------------------


char KeyDigit = keypad.getKey();                                           // Get the DigitKey from the keypad

if ((RightCard == 1) &&                                                    // If you offered a valid Mifare Card and any DigitKey on the keypad is pressed
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
    (KeyDigit == 'A')  ||
    (KeyDigit == 'B')  ||
    (KeyDigit == 'C')  ||
    (KeyDigit == 'D')  ||
    (KeyDigit == '*')  || 
    (KeyDigit == '#')))
 
    {                               
      PinCodeCounter++;                                                       // PinCodeCounter value +1 for every press on any Digitkey on the keypad
      lcd.setCursor(4 + PinCodeCounter, 1);
      lcd.print("*");
      digitalWrite (Buzzer, HIGH);                                            // Make a short beep for a DigitKey press on the keypad
      delay (50);                                                             //
      digitalWrite (Buzzer, LOW);                                             //
           
    }




//-----------------------------------------------Code for determine the correct PinCode for CARD-1 ----------------------------------------------------------------------------------------------------------





if ((KeyDigit == Code1MifareCard1) && (RightCard == 1) && (Code1Correct == 0) && (MifareCard1 == 1))           // If you offered the valid MifareCard1, first PinCode and you did not entered it before (Otherwise we conflict with same KeyDigits)
    {
      Code1Correct = 1;                                                                                        // Variable Code1Correct is set to 1
      return;                                                                                                  // Return to begin loop
    } 
      
if ((KeyDigit == Code2MifareCard1) && (Code1Correct == 1) && (Code2Correct == 0) && (MifareCard1 == 1))        // If you offered the valid MifareCard1, second PinCode and you did not entered it before (Otherwise we conflict with same KeyDigits)
    {
      Code2Correct = 1;                                                                                        // Variable Code2Correct is set to 1
      return;                                                                                                  // Return to begin loop
    } 
    
if ((KeyDigit == Code3MifareCard1) && (Code2Correct == 1) && (Code3Correct == 0) && (MifareCard1 == 1))         // If you offered the valid MifareCard1, third PinCode and you did not entered it before (Otherwise we conflict with same KeyDigits)
    {
      Code3Correct = 1;                                                                                         // Variable Code3Correct is set to 1
      return;                                                                                                   // Return to begin loop
    } 
     
if ((KeyDigit == Code4MifareCard1) && (Code3Correct == 1) && (Code4Correct == 0) && (MifareCard1 == 1))         // If you offered the valid MifareCard1, fourth PinCode and you did not entered it before (Otherwise we conflict with same KeyDigits)
    {
      Code4Correct = 1;                                                                                         // Variable Code4Correct is set to 1
      return;                                                                                                   // Return to begin loop
    }  
if ((KeyDigit == Code5MifareCard1) && (Code4Correct == 1) && (Code5Correct == 0) && (MifareCard1 == 1))         // If you offered the valid MifareCard1, fifth PinCode and you did not entered it before (Otherwise we conflict with same KeyDigits)
    {
      Code5Correct = 1;                                                                                         // Variable Code5Correct is set to 1
      return;                                                                                                   // Return to begin loop
    } 

if ((KeyDigit == Code6MifareCard1) && (Code5Correct == 1) && (Code6Correct == 0) && (MifareCard1 == 1))         // If you offered the valid MifareCard1, sixth PinCode and you did not entered it before (Otherwise we conflict with same KeyDigits)
    {
      Code6Correct = 1;                                                                                         // Variable Code6Correct is set to 1
      return;                                                                                                   // Return to begin loop
    }


    

//-----------------------------------------------Code for determine the correct PinCode for CARD-2 ----------------------------------------------------------------------------------------------------------



    

if ((KeyDigit == Code1MifareCard2) && (RightCard == 1) && (Code1Correct == 0) && (MifareCard2 == 1))              // If you offered a the valid MifareCard2, first PinCode and you did not entered it before (Otherwise we conflict with same KeyDigits)
    {
      Code1Correct = 1;                                                                                           // Variable Code1Correct is set to 1
      return;                                                                                                     // Return to begin loop
    } 
      
if ((KeyDigit == Code2MifareCard2) && (Code1Correct == 1) && (Code2Correct == 0) && (MifareCard2 == 1))           // If you offered a the valid MifareCard2, second PinCode and you did not entered it before (Otherwise we conflict with same KeyDigits)
    {
      Code2Correct = 1;                                                                                           // Variable Code2Correct is set to 1
      return;                                                                                                     // Return to begin loop
    } 
    
if ((KeyDigit == Code3MifareCard2) && (Code2Correct == 1) && (Code3Correct == 0) && (MifareCard2 == 1))           // If you offered a the valid MifareCard2, third PinCode and you did not entered it before (Otherwise we conflict with same KeyDigits)
    {
      Code3Correct = 1;                                                                                           // Variable Code3Correct is set to 1
      return;                                                                                                     // Return to begin loop
    } 
     
if ((KeyDigit == Code4MifareCard2) && (Code3Correct == 1) && (Code4Correct == 0) && (MifareCard2 == 1))          // If you offered a the valid MifareCard2, fourth PinCode and you did not entered it before (Otherwise we conflict with same KeyDigits)
    {
      Code4Correct = 1;                                                                                          // Variable Code4Correct is set to 1
      return;                                                                                                    // Return to begin loop
    }  
if ((KeyDigit == Code5MifareCard2) && (Code4Correct == 1) &&  (Code5Correct == 0) && (MifareCard2 == 1))         // If you offered a the valid MifareCard2, fifth PinCode and you did not entered it before (Otherwise we conflict with same KeyDigits)
    {
      Code5Correct = 1;                                                                                          // Variable Code5Correct is set to 1
      return;                                                                                                    // Return to begin loop
    } 

if ((KeyDigit == Code6MifareCard2) && (Code5Correct == 1) &&  (Code6Correct == 0) && (MifareCard2 == 1))         // If you offered a the valid MifareCard2, sixth PinCode and you did not entered it before (Otherwise we conflict with same KeyDigits)
    {
      Code6Correct = 1;                                                                                          // Variable Code6Correct is set to 1
      return;                                                                                                    // Return to begin loop
    } 
   

//-----------------------------------------------Code for determine the correct PinCode for CARD-3 ----------------------------------------------------------------------------------------------------------



    

if ((KeyDigit == Code1MifareCard3) && (RightCard == 1) && (Code1Correct == 0) && (MifareCard3 == 1))              // If you offered a the valid MifareCard2, first PinCode and you did not entered it before (Otherwise we conflict with same KeyDigits)
    {
      Code1Correct = 1;                                                                                           // Variable Code1Correct is set to 1
      return;                                                                                                     // Return to begin loop
    } 
      
if ((KeyDigit == Code2MifareCard3) && (Code1Correct == 1) && (Code2Correct == 0) && (MifareCard3 == 1))           // If you offered a the valid MifareCard2, second PinCode and you did not entered it before (Otherwise we conflict with same KeyDigits)
    {
      Code2Correct = 1;                                                                                           // Variable Code2Correct is set to 1
      return;                                                                                                     // Return to begin loop
    } 
    
if ((KeyDigit == Code3MifareCard3) && (Code2Correct == 1) && (Code3Correct == 0) && (MifareCard3 == 1))           // If you offered a the valid MifareCard2, third PinCode and you did not entered it before (Otherwise we conflict with same KeyDigits)
    {
      Code3Correct = 1;                                                                                           // Variable Code3Correct is set to 1
      return;                                                                                                     // Return to begin loop
    } 
     
if ((KeyDigit == Code4MifareCard3) && (Code3Correct == 1) && (Code4Correct == 0) && (MifareCard3 == 1))          // If you offered a the valid MifareCard2, fourth PinCode and you did not entered it before (Otherwise we conflict with same KeyDigits)
    {
      Code4Correct = 1;                                                                                          // Variable Code4Correct is set to 1
      return;                                                                                                    // Return to begin loop
    }  
if ((KeyDigit == Code5MifareCard3) && (Code4Correct == 1) &&  (Code5Correct == 0) && (MifareCard3 == 1))         // If you offered a the valid MifareCard2, fifth PinCode and you did not entered it before (Otherwise we conflict with same KeyDigits)
    {
      Code5Correct = 1;                                                                                          // Variable Code5Correct is set to 1
      return;                                                                                                    // Return to begin loop
    } 

if ((KeyDigit == Code6MifareCard3) && (Code5Correct == 1) &&  (Code6Correct == 0) && (MifareCard3 == 1))         // If you offered a the valid MifareCard2, sixth PinCode and you did not entered it before (Otherwise we conflict with same KeyDigits)
    {
      Code6Correct = 1;                                                                                          // Variable Code6Correct is set to 1
      return;                                                                                                    // Return to begin loop
    } 

   

//-----------------------------------------------Code for determine the correct PinCode for CARD-4 ----------------------------------------------------------------------------------------------------------



    

if ((KeyDigit == Code1MifareCard4) && (RightCard == 1) && (Code1Correct == 0) && (MifareCard4 == 1))              // If you offered a the valid MifareCard2, first PinCode and you did not entered it before (Otherwise we conflict with same KeyDigits)
    {
      Code1Correct = 1;                                                                                           // Variable Code1Correct is set to 1
      return;                                                                                                     // Return to begin loop
    } 
      
if ((KeyDigit == Code2MifareCard4) && (Code1Correct == 1) && (Code2Correct == 0) && (MifareCard4 == 1))           // If you offered a the valid MifareCard2, second PinCode and you did not entered it before (Otherwise we conflict with same KeyDigits)
    {
      Code2Correct = 1;                                                                                           // Variable Code2Correct is set to 1
      return;                                                                                                     // Return to begin loop
    } 
    
if ((KeyDigit == Code3MifareCard4) && (Code2Correct == 1) && (Code3Correct == 0) && (MifareCard4 == 1))           // If you offered a the valid MifareCard2, third PinCode and you did not entered it before (Otherwise we conflict with same KeyDigits)
    {
      Code3Correct = 1;                                                                                           // Variable Code3Correct is set to 1
      return;                                                                                                     // Return to begin loop
    } 
     
if ((KeyDigit == Code4MifareCard4) && (Code3Correct == 1) && (Code4Correct == 0) && (MifareCard4 == 1))          // If you offered a the valid MifareCard2, fourth PinCode and you did not entered it before (Otherwise we conflict with same KeyDigits)
    {
      Code4Correct = 1;                                                                                          // Variable Code4Correct is set to 1
      return;                                                                                                    // Return to begin loop
    }  
if ((KeyDigit == Code5MifareCard4) && (Code4Correct == 1) &&  (Code5Correct == 0) && (MifareCard4 == 1))         // If you offered a the valid MifareCard2, fifth PinCode and you did not entered it before (Otherwise we conflict with same KeyDigits)
    {
      Code5Correct = 1;                                                                                          // Variable Code5Correct is set to 1
      return;                                                                                                    // Return to begin loop
    } 

if ((KeyDigit == Code6MifareCard4) && (Code5Correct == 1) &&  (Code6Correct == 0) && (MifareCard4 == 1))         // If you offered a the valid MifareCard2, sixth PinCode and you did not entered it before (Otherwise we conflict with same KeyDigits)
    {
      Code6Correct = 1;                                                                                          // Variable Code6Correct is set to 1
      return;                                                                                                    // Return to begin loop
    }         
}
