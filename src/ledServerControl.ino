/*
 * Arduino - led controlled by NodeJs server
 * Using Arduino board UNO 3R
 * ------------------------------------------
 *
 * Arduino connected to the server by serial port (USB)
 * NodeJs server send arduino the led number to be on [availible leds: 10,11,12,13]
 *
 * Using port COM3
 * Bit rate 115200
 */

// pin of the led we would like to light
int ledPinToLigh = 0;
int ledStatus = 0;
int ledStatusFactor = 10;
int led = 0;

// declare wich digital pins we are going to use
int ledPin10 = 10;
int ledPin11 = 11;
int ledPin12 = 12;
int ledPin13 = 13;

// whether we got the required led to light from nodejs server
boolean isRequestComplete = false;

/**
 *
 * arduino board setup
 *
 */

void setup()
{
  // opens serial port, sets data rate to 115200 bps
  Serial.begin(115200);
  // sets the digital pin as output
  pinMode(ledPin10, OUTPUT);
  pinMode(ledPin11, OUTPUT);
  pinMode(ledPin12, OUTPUT);
  pinMode(ledPin13, OUTPUT);
}

/**
 *
 * Default arduino loop function
 * it runs over and over again
 *
 */

void loop()
{
    gettingSerialEventFromUsb();
    digitalWrite(led,ledStatus);
}


// gettingSerialEventFromUsb occurs whenever a new data comes in the hardware serial RX.
void gettingSerialEventFromUsb() {
 while (Serial.available() > 0) {
  // get the required led number to light with additional digit 0 or 1
  // 0 for turn off
  // 1 for turn on
  // example: 101 -> will turn on led 10; 100 -> will turn off led 10
  ledPinToLigh = Serial.parseInt();
  // determine the required operation (on or off) according to the last digit (0 or 1)
  ledStatus = ledPinToLigh % ledStatusFactor;
  // determine the requested led
  led = ledPinToLigh / ledStatusFactor;
   if (Serial.read() == '\n') {
    isRequestComplete = true;
   }
 }
}
