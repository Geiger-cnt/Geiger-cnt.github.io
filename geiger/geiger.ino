#include <SPI.h>

#define LOG_PERIOD 15000    
#define MAX_PERIOD 60000 
#define GM 2

unsigned long counts;

unsigned long cpm;
unsigned int multiplier; 

unsigned long previousMillis;

void tube_impulse(){counts++;}

void setup() {
  cpm = 0;
  counts = 0;
  previousMillis = 0;
  multiplier = MAX_PERIOD / LOG_PERIOD;         
  
  Serial.begin(9600);                                   

  pinMode(GM, INPUT);
  digitalWrite(GM, HIGH);

  attachInterrupt(0, tube_impulse, FALLING);
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis > LOG_PERIOD) {
    previousMillis = currentMillis;
    cpm = counts * multiplier;

    Serial.print(cpm);
    Serial.write(' ');

    counts = 0;
  }
}
