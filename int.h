int RedLed    = A1;                 // Red LED output is analog pin A3
int Buzzer    = A0;                 // Buzzer output is analog pin A5
int Door      = A2;
int pir       = A3;
int sense;
int calibrationTime = 1; 
unsigned long Timer;                // Variable for the Timer



const byte ROWS = 4;                // Four rows
const byte COLS = 4;                // Three columns

                              
char Keys[ROWS][COLS] = {           // Define the symbols on the buttons of the keypads
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {1, 2, 3, 4};  // Connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 6, 7, 8};    // Connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(Keys), rowPins, colPins, ROWS, COLS); // Initialize an instance of class NewKeypad

int RightCard;                      // Variable for a known Mifare Card
int RightPinCode;                   // Variable for valid key input in combination with a known Mifare Card
int WrongPinCode;                   // Variable for a invalid key input in combination with a known Mifare Card
int PinCodeCounter;                 // Variable Counter for counting the number of pincode inputs on the keypad

int Code1Correct;                   // Variable for the first correct digit (Code) input on the keypad
int Code2Correct;                   // Variable for the second correct digit (Code) input on the keypad
int Code3Correct;                   // Variable for the third correct digit (Code) input on the keypad
int Code4Correct;                   // Variable for the fourth correct digit (Code) input on the keypad
int Code5Correct;                   // Variable for the fifth correct digit (Code) input on the keypad
int Code6Correct;                   // Variable for the sixth correct digit (Code) input on the keypad
int Code7Correct;                   // Variable for the sixth correct digit (Code) input on the keypad
int Code8Correct;                   // Variable for the sixth correct digit (Code) input on the keypad
int Code9Correct;
int Code10Correct;

int Reset;                          // Reset for the loop

int fail = 0;
int armed = 0;




