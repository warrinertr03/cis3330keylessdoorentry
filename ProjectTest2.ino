#include <Keypad.h>
#include <Password.h>
#include <Servo.h>
#include <Wire.h>

int i = 0;
int ledPinGreen = 11;
int ledPinRed = 10;

Servo servo;  // create servo object

const byte ROWS = 4; // Four rows
const byte COLS = 3; //  columns
// Define the Keymap
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'} 
};

Password pin = Password( "1234" ); //Create the acceptable pin for the keypad
Password pin2 = Password( "4567" ); //Create the pin to lock the system

byte rowPins[ROWS] = { 2, 3, 4, 5 };// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins
byte colPins[COLS] = { 6, 7, 8 }; // Connect keypad COL0, COL1 and COL2 to these Arduino pins

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS ); // Create the Keypad

void setup(){
  Serial.begin(9600); //Set baud rate to 9600 on the Arduino
  keypad.addEventListener(keypadEvent); //add an event listener for this keypad  
  servo.attach(13); // attach the servo on any free digital pin
  pinMode(9, OUTPUT); // set a pin for buzzer output
//  pinMode(analogPin, INPUT);
  pinMode(ledPinGreen, OUTPUT);
  pinMode(ledPinRed, OUTPUT);
}

void loop(){
 // keypad.getKey();
  digitalWrite(ledPinGreen, HIGH);  delay(1000); 
  digitalWrite(ledPinRed, HIGH);  delay(1000); 
  
  digitalWrite(ledPinGreen, LOW); 
  digitalWrite(ledPinRed, LOW); 
  // here we might need an if OR statement for if they open the gate or have an invaild password
  up();
  delay(2000);
  down();
  delay(2000);
          buzz(4, 2500, 500); // buzz the buzzer on pin 4 at 2500Hz for 500 milliseconds
          delay(1000); // wait a bit between buzzes 
  }
 

//take care of some special events
void keypadEvent(KeypadEvent eKey){
  switch (keypad.getState()){
    case PRESSED:
Serial.print("Pressed: ");
Serial.println(eKey);
switch (eKey){
 case '*': checkPassword(); break;
 case '#': pin.reset(); break;
 default: pin.append(eKey);
     }
  }
}

void checkPassword()
{ 
  if(i < 4)
  { 
    if(pin.evaluate())
    {     
      Serial.println("Success");
      up();
       }else{
         i++;       
         Serial.println("Incorrect Pin, Press The # and Try Again");
         Serial.println(i);         
         }           
    if(pin.evaluate() != true && i == 3){
      Serial.println("You Have Entered The Wrong Pin To Many Times! The Cops Are Being Notified");
      buzz(4, 2500, 500); // buzz the buzzer on pin 4 at 2500Hz for 500 milliseconds
      delay(1000); // wait a bit between buzzes 
    }
  }  
}

void buzz(int targetPin, long frequency, long length) {
  long delayValue = 1000000/frequency/2; // calculate the delay value between transitions
  //// 1 second's worth of microseconds, divided by the frequency, then split in half since
  //// there are two phases to each cycle
  long numCycles = frequency * length/ 1000; // calculate the number of cycles for proper timing
  //// multiply frequency, which is really cycles per second, by the number of seconds to 
  //// get the total number of cycles to produce
  for (long i=0; i < numCycles; i++){ // for the calculated length of time...
    digitalWrite(targetPin,HIGH); // write the buzzer pin high to push out the diaphram
    delayMicroseconds(delayValue); // wait for the calculated delay value
    digitalWrite(targetPin,LOW); // write the buzzer pin low to pull back the diaphram
    delayMicroseconds(delayValue); // wait againf or the calculated delay value
  }
}


void up() 
{
  servo.write(90);
}

void down()
{
  servo.write(100);
}

void fullstop()
{
  servo.write(95);
}
