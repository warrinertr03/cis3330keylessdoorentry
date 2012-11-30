#include <Keypad.h>
#include <Wire.h>
#include <Servo.h>

Servo servo;
int ledPinGreen = 11;
int ledPinRed = 10;

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] =
{
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = { 8, 7, 6, 5 }; //connect to the row pinouts of the keypad
byte colPins[COLS] = { 4, 3, 2, }; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

char PIN[4]={'1','2','3','4'}; // our secret (!) number
char attempt[4]={
  0,0,0,0}; // used for comparison
int z=0;

void setup()
{
  Serial.begin(9600);
  servo.attach(13);
  fullstop();
  pinMode(9, OUTPUT);
  pinMode(ledPinGreen, OUTPUT);
  pinMode(ledPinRed, OUTPUT);
  startingPIN();
}

void startingPIN() // this is how the LED's will start off
{
  digitalWrite(ledPinRed, HIGH); 
  digitalWrite(ledPinGreen, LOW);
}

void correctPIN() // do this if correct PIN entered
{
  Serial.println("Correct Pin");
  digitalWrite(ledPinGreen, HIGH); 
  digitalWrite(ledPinRed, LOW); 
  play_tone(9, 500, 1000); delay(10);
  up(); delay(4000);
  fullstop(); delay(70);
  play_tone(9, 500, 150); delay(10);
  delay(2000);
  play_tone(9, 500, 150); delay(100);
  down(); delay(4000);
  fullstop();
  play_tone(9, 100, 100); delay(10);
  startingPIN();
}

void incorrectPIN() // do this if incorrect PIN entered
{
  Serial.println("Incorrect Pin, Press The # and Try Again");
  digitalWrite(ledPinRed, HIGH); 
  digitalWrite(ledPinGreen, LOW);
  play_tone(9, 100, 500); delay(20);
  play_tone(9, 100, 500); 
}

void checkPIN()
{
  int correct=0;
  for (int q=0; q<4; q++)
  {
    if (attempt[q]==PIN[q])
    {
      correct++;
    }
  }
  if (correct==4)
  {
    correctPIN();
  } else
  {
    incorrectPIN();
  }
  for (int zz=0; zz<4; zz++) // wipe attempt
  {
    attempt[zz]=0;
  }
}

void readKeypad()
{
  char key = keypad.getKey();
  if (key != NO_KEY)
  {
    switch(key)
    {
    case '*':
      z=0;
      break;
    case '#':
      delay(100); 
      checkPIN();
      break;
    default:
      attempt[z]=key;
      z++;
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

void loop()
{
  readKeypad();
}
