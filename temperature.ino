#include <math.h>

#define CLOCK_PIN 2
#define RESET_PIN 3
#define SOUND_PIN 4
#define TEMPERATURE_PIN 0

void resetNumber() {
  digitalWrite(RESET_PIN, HIGH);
  digitalWrite(RESET_PIN, LOW);
}

void showNumber(int value) {
  resetNumber();
  
  while (value--) {
    digitalWrite(CLOCK_PIN, HIGH);
    digitalWrite(CLOCK_PIN, LOW);
  }
}

double thermister(int rawADC) {
  double Temp;
  Temp = log(((10240000/rawADC) - 10000));
  Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp ))* Temp );
  Temp = Temp - 273.15;            // Convert Kelvin to Celcius
  return Temp;
}

void setup() {
  pinMode(RESET_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(SOUND_PIN, OUTPUT);
  resetNumber();
  delay(1000);
  Serial.begin(9600);
}

int inValue = 0;
int therm;
int pr = 0;

void loop() {
    inValue = int(thermister(analogRead(TEMPERATURE_PIN)));
    Serial.print("I received: ");
    Serial.println(inValue, DEC);
    
    if (inValue >= 0 && inValue <= 99) {
      if (inValue != pr) {
        tone(SOUND_PIN, 262, 1000/4);
        pr = inValue;
      }
      showNumber(inValue);
    }
    else {
      Serial.println("Only numbers from 0 to 99 are supported.");
    }
    delay(2000);
}
