#include <Arduino.h>

#include <SoftwareSerial.h>
SoftwareSerial ESPserial(11, 12);

byte byteRead;

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
}

void loop()
{
    // Just an example:
    analogWrite25k(10, 210);
    delay(1000);              // wait for a second
    ESPserial.write("ok");

        // listen for communication from the ESP8266 and then write it to the serial monitor
   if (ESPserial.available()){
    delay(100);
    while (ESPserial.available() > 0) {
      byteRead = ESPserial.read();
      Serial.println(byteRead);
      analogWrite25k(10, byteRead);
    }
    
  }
 
    // listen for user input and send it to the ESP8266
    if ( Serial.available() )       {  ESPserial.write( Serial.read() );  }
}
