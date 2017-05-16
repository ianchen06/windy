#include <Arduino.h>
#include <Wire.h>

#include <SI7021.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

SI7021 sensor;
LiquidCrystal_I2C lcd(0x3F, 16, 2);
SoftwareSerial ESPserial(11, 12);

// PWM output @ 25 kHz, only on pins 9 and 10.
// Output value should be between 0 and 320, inclusive.
void analogWrite25k(int pin, int value)
{
  switch (pin) {
    case 9:
    OCR1A = value;
    break;
    case 10:
    OCR1B = value;
    break;
    default:
    // no other pin will work
    break;
  }
}

void setup()
{
  Serial.begin(115200);
  ESPserial.begin(115200);

  sensor.begin();


  lcd.begin();
  lcd.backlight();

  Serial.println("");
  Serial.println("Yo");
  Serial.println("");
  ESPserial.println("from espserial");
  ESPserial.println("Yo2");
  ESPserial.println("zz");

  // Configure Timer 1 for PWM @ 25 kHz.
  TCCR1A = 0;           // undo the configuration done by...
  TCCR1B = 0;           // ...the Arduino core library
  TCNT1  = 0;           // reset timer
  TCCR1A = _BV(COM1A1)  // non-inverted PWM on ch. A
  | _BV(COM1B1)  // same on ch; B
  | _BV(WGM11);  // mode 10: ph. correct PWM, TOP = ICR1
  TCCR1B = _BV(WGM13)   // ditto
  | _BV(CS10);   // prescaler = 1
  ICR1   = 320;         // TOP = 320

  // Set the PWM pins as output.
  pinMode( 9, OUTPUT);
  pinMode(10, OUTPUT);

  //dht.begin();
}

void loop()
{
  // get humidity and temperature in one shot, saves power because sensor takes temperature when doing humidity anyway
  analogWrite25k(10, 210);
  si7021_env data = sensor.getHumidityAndTemperature();
  Serial.println(data.celsiusHundredths/100);
  Serial.println(data.humidityBasisPoints/100);
  lcd.clear();
  lcd.print("Temp: " + String((float) data.celsiusHundredths / 100.0));
  lcd.setCursor(0, 1);
  lcd.print("Humd: " + String((float) data.humidityBasisPoints / 100.0));
  delay(1000);
}
