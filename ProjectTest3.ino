#include <Keypad.h>
#include <Password.h>
#include <Servo.h>
#include <Wire.h>

int i = 0;
int ledPinGreen = 11;
int ledPinRed = 10;
boolean pswdEntered = false;
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

Password pin = Password( "1477" ); //Create the acceptable pin for the keypad

byte rowPins[ROWS] = { 8, 7, 6, 5 };// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins
byte colPins[COLS] = { 4, 3, 2 }; // Connect keypad COL0, COL1 and COL2 to these Arduino pins


Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS ); // Create the Keypad

void setup(){
  Serial.begin(9600); //Set baud rate to 9600 on the Arduino
  keypad.addEventListener(keypadEvent); //add an event listener for this keypad  
  servo.attach(13); // attach the servo on any free digital pin
  Serial.println(pswdEntered);
  pinMode(9, OUTPUT); // set a pin for buzzer output
  pinMode(ledPinGreen, OUTPUT);
  pinMode(ledPinRed, OUTPUT);
}

void loop(){
  fullstop();
  //keypad.getKey();
  keypadEvent(keypad.getKey());
  checkPassword(); 
if(pswdEntered == false)
  {
   digitalWrite(ledPinRed, HIGH); 
   play_tone(9, 200, 500); 
   play_tone(9, 200, 500); 
   play_tone(9, 200, 500); 
   delay(1000); 
   digitalWrite(ledPinRed, LOW);   
    }
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
      pswdEntered = true;  
      Serial.println("Success");
      up();
      digitalWrite(ledPinGreen, HIGH); 
      play_tone(9, 1500, 500); delay(50);
      play_tone(9, 1500, 500); 
      delay(1000);
      fullstop();
      digitalWrite(ledPinGreen, LOW);
      delay(5000);  
      down();
      delay(1050);
      fullstop();
       }else{
         pswdEntered = false;
         i++; 
         digitalWrite(ledPinRed, HIGH); 
         play_tone(9, 200, 500); delay(50);
         play_tone(9, 200, 500); delay(50);
         play_tone(9, 200, 500); 
         delay(700); 
         digitalWrite(ledPinRed, LOW);     
         Serial.println("Incorrect Pin, Press The # and Try Again");
         Serial.println(i);         
         }           
    if(pin.evaluate() != true && i == 3){
      Serial.println("You Have Entered The Wrong Pin To Many Times! The Cops Are Being Notified");
      play_tone(9, 500, 200); delay(50);
      play_tone(9, 500, 200); delay(50);
      play_tone(9, 500, 200); delay(50);
      play_tone(9, 500, 200); delay(50);
      play_tone(9, 500, 200);
      delay(1000); // wait a bit between buzzes 
    }
  }  
}

void play_tone(int pin, int freq, int duration) 
{
  int i = 0;
  int sleep = 1000 / (2*freq);
  int periods = duration / (2 * sleep);
  pinMode(pin, OUTPUT);
  for (i = 0 ; i < periods; i++) {
    digitalWrite(pin, 1);
    delay(sleep);
    digitalWrite(pin, 0);
    delay(sleep);
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
