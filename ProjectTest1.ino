 // LED pattern blink

int ledPin5 = 10;
int ledPin3 = 11;
//int sound = 9;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.    
  pinMode(ledPin5, OUTPUT);       
  pinMode(ledPin3, OUTPUT);    
//  pinMode(sound, OUTPUT);
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

// the loop routine runs over and over again forever:
void loop() 
{
  flash();
  play_tone(9, 220, 500);
  delay(10000);

}

void flash()
{
  digitalWrite(ledPin5, HIGH);  delay(500); 
  digitalWrite(ledPin5, LOW); 
  digitalWrite(ledPin3, HIGH);  delay(500);            
  digitalWrite(ledPin3, LOW); 
  delay(1000);
}

void buzz(long frequency, long length) 
{
    digitalWrite(9 ,HIGH); // write the buzzer pin high to push out the diaphram
    delayMicroseconds(500); // wait for the calculated delay value
    digitalWrite(9 ,LOW); // write the buzzer pin low to pull back the diaphram
    delayMicroseconds(500); // wait againf or the calculated delay value
}
