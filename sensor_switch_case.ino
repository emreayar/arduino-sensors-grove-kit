#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

const int temptPin = A0;
const int soundPin = A1;
const int lightPin = A2;
const int buttonPin = 2;

int buttonCounter = 0;
const int B = 3975;
int buttonState = 0;
int lastButtonState = 0;


void setup() {

  pinMode(temptPin , INPUT);
  pinMode(soundPin , INPUT);
  pinMode(lightPin , INPUT);
  pinMode(buttonPin , INPUT);

  Serial.begin(9600);
  lcd.begin(16, 2);

}

void loop() {
  lcd.setCursor(0, 0);
  int soundSensorValue = 0;
  int temptValue = 0;
  int lightValue = 0;
  float resistance = 0;
  float temperature = 0;

  int buttonState = digitalRead(buttonPin);


  if (buttonState != lastButtonState) {
    if (buttonState == HIGH) {
      buttonCounter++;
      Serial.println(buttonCounter);
    }
  }

  lastButtonState = buttonState;
  delay(25); //to reduce the renewal of the lcd screen and to prevent too much analog signal entry 
  switch (buttonCounter%3) { //for using to work continuously
    case 0:

      lightValue = analogRead(lightPin);
      Serial.print("Isik degeri:");
      Serial.println(lightValue);
      lcd.print("Isik degeri:");
      lcd.print(lightValue);

      break;

    case 1:
      lcd.clear();
      temptValue = analogRead(temptPin);
      resistance = (float)(1023 - temptValue) * 10000 / temptValue;
      temperature = 1 / (log(resistance / 10000) / B + 1 / 298.15) - 273.15;
      Serial.print("Sicaklik degeri:");
      Serial.println(temperature);
      lcd.print("Sicaklik degeri:");
      lcd.setCursor(0, 1);
      lcd.print(temperature);

      break;

    case 2:
      lcd.clear();
      soundSensorValue = analogRead(soundPin);
      Serial.print("Ses degeri:");
      Serial.println(soundSensorValue);
      lcd.print("Ses degeri:");
      lcd.print(soundSensorValue);

      break;
  }

}









