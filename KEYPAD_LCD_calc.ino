// By : partial-arts
// Title : Power Density at a point away from a directional antenna
// P R O G R A M    D E T A I L S
//   Calculates a directional antenna's 
//   power density towards a point away from the antenna,
//   at a certain direction, with distance D away
// INPUTS : 
// Pt = Transmission power in watts
// Gt = Directional Gain of the antenna towards a point at a certain direction D meters away (unitless)
// D = Distance between the said point and antenna (meters)
// OUTPUTS :
// Pd = Power density at that point away the antenna, (watts / square meters)

// INPUT/OUTPUT SCREENS OF THE PROGRAM
// SCREEN 1 : Introduce program function
// INPUT, SCREEN 2 : Input Pt
// INPUT, SCREEN 3 : Input Gt
// INPUT, SCREEN 4 : Input D
// OUTPUT, SCREEN 5 : Output Pd

// Program assumption : User presses one key at a time

// H O W    T O    U S E
// Press the digits 0-9 in keypad to enter the digits for the input values
// Press "C" in keypad to go to the next input/output screen of the LCD
// Press "." in keypad to enter a decimal point

// N O T E
// Upload the version of this code without comments
// in case this heavily-commented code does not fit inside the Arduino memory

//         W I R I N G
//   LCD to Arduino UNO
// LCD's SCL ----- UNO's A5
// LCD's SDA ----- UNO's A4
// LCD's VCC ----- UNO's 5V
// LCD's GND ----- UNO's GND
//         Keypad to Arduino UNO
// Keypad's ROW 1 ----- UNO's D2
// Keypad's ROW 2 ----- UNO's D3
// Keypad's ROW 3 ----- UNO's D4
// Keypad's ROW 4 ----- UNO's D5
// Keypad's COL 1 ----- UNO's D6
// Keypad's COL 2 ----- UNO's D7
// Keypad's COL 3 ----- UNO's D8

// IMPORT LIBRARIES for the LCD and Keypad
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

// Configure Keypad object : Make the Arduino understand
//                           how you feed it information 
//                           from the actual keypad
// source : playground.arduino.cc/Code/Keypad
const byte rows = 4; //four rows
const byte cols = 3; //three columns
// These are the symbols corresponding to
// every button on the keypad
char keys[rows][cols] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'.','0','C'}
};
// PRESS "C" TO PROCEED TO THE NEXT SCREEN
byte rowPins[rows] = {2, 3, 4, 5}; //connect to the row pinouts of the keypad
byte colPins[cols] = {6, 7, 8}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, rows, cols );
// The current key being pressed, stored in a String
String currkey;

// Keypad sentinel variables
int progress = 0;
int dot_counter = 0;

// Configure LCD object : Make the Arduino understand
//                        how to display text output to actual LCD
// source : https://arduinogetstarted.com/tutorials/arduino-lcd-i2c
LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address 0x27, 16 column and 2 rows
// address is 0x27 because of the wiring of LCD as stated  in above comments

// Initialize input variables
// inputs[0] is Pt, inputs[1] is Gt, inputs[2] is D
float inputs[3] = {0,0,0};
// String form of the inputs
String in_txt;
// Initialize output variables
double Pd;

void setup() {
  // put your setup code here, to run once:

  // Configure Keypad object (continued)
  // Add an event listener to let the arduino 
  // watch and then respond to button presses
  keypad.addEventListener(keypadEvent);

  // Configure LCD object (continued)
  lcd.init();       //initialize the lcd
  lcd.backlight();  //open the backlight

  // To let the user start the program loop, 
  // tell them to press the keypad's "C" button
  lcd.clear();
  lcd.setCursor(0, 0);
  //         ................
  lcd.print("Press C twice to");
  lcd.setCursor(0, 1);
  lcd.print("continue");
}

void loop() {
  // put your main code here, to run repeatedly:

  // Keep watching the keys pressed in keypad
  currkey = keypad.getKey();
}

// Arduino displays the input/output in LCD in response to button presses
// by responding to this event below
void keypadEvent(KeypadEvent currkey)
{
  // UPDATE PROGRAM STATE BASED ON KEY PRESSED
  if (keypad.getState() == PRESSED)
  {
  switch (currkey)
    {
      case 'C':
        if (progress == 1)
        {
          // STEP 1 : Make the user know what this calculator does
          //               part 1/3
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Dir. Antenna");
          lcd.setCursor(0, 1);
          lcd.print("Power Density");
          delay(1000);
          //               part 2/3
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("IN =  Pt, Gt, D");
          lcd.setCursor(0, 1);
          lcd.print("units  W      m");
          delay(1000);
          //               part 3/3
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("OUT =  Pd");
          lcd.setCursor(0, 1);
          lcd.print("units   W/m^2");
          delay(1000);
        }
        // save the inputted data into the inputs array
        if (progress == 2)
        {
          inputs[0] = in_txt.toFloat();
        }
        if (progress == 3)
        {
          inputs[1] = in_txt.toFloat();
        }
        if (progress == 4)
        {
          inputs[2] = in_txt.toFloat();
        }
        // increment the progress only after the inputted data was saved
        progress = progress + 1;
        // Clean the temporary variables for the next input.
        dot_counter = 0;
        in_txt = "";
        break;
      case '.':
        // append that decimal point to the currently inputted data
        dot_counter = dot_counter + 1;
        in_txt = in_txt + String(currkey);
        break;
      default:
        // append the digits to the currently inputted data
        in_txt = in_txt + String(currkey);
        break;
    }
  
    // CHECK IF INVALID INPUT
    // NOTIFY USER IF INVALID INPUT AND ERASE THE CURRENTLY INPUTTED DATA
    // TO MAKE THE INPUT STRING VALID AGAIN
    
    // CHECK IF THERE ARE MORE THAN ONE DECIMAL POINTS
    if (dot_counter > 1)
    {
      // MAKE THE INVALID INPUT, VALID AGAIN
      dot_counter = 1;
      in_txt = in_txt.substring(0, in_txt.length()-1);
      
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("INVALID INPUT");
      lcd.setCursor(0, 0);
      lcd.print(">1 dec. points");
      delay(1000);
    }
    // CHECK IF THE INPUT STRING LENGTH EXCEEDS SCREEN WIDTH
    if (in_txt.length() > 16)
    {
      // MAKE THE INVALID INPUT, VALID AGAIN
      in_txt = in_txt.substring(0, in_txt.length()-1);
      // NOTIFY THE USER ABOUT INVALID INPUT
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("INVALID INPUT");
      lcd.setCursor(0, 0);
      lcd.print("Input too long");
      delay(1000);
    }
  
    // UPDATE THE LCD BASED ON THE PROGRESS
    // OF THE USER'S CALCULATION
    if (progress == 2)
    {
      // prompt the user to input the
      // transmitter antenna power
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("INPUT Pt (watt):");
      lcd.setCursor(0, 1);
      lcd.print(in_txt);
    }
    if (progress == 3)
    {
      // prompt the user to input the
      // transmitter antenna gain at a certain direction away the antenna
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("INPUT Gt:");
      lcd.setCursor(0, 1);
      lcd.print(in_txt);
    }
    if (progress == 4)
    {
      // prompt the user to input the
      // distance of the point to the antenna towards a certain direction
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("INPUT D (m) :");
      lcd.setCursor(0, 1);
      lcd.print(in_txt);
    }
    if (progress == 5)
    {
      // show the calculation result to the user 
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Pd (W/m^2) = ");
      lcd.setCursor(0, 1);
      lcd.print(String(calc_Pd()));
      progress = 1;
    }
  }

}

// function to calculate the power density
double calc_Pd()
{
  Pd = (inputs[0] * inputs[1])/(4 * 3.14159 * inputs[2] * inputs[2]);
  return Pd;
}
