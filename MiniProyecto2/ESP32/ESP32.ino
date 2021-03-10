// Adafruit IO Publish Example
//
// Adafruit invests time and resources providing this open source code.
// Please support Adafruit and open source hardware by purchasing
// products from Adafruit!
//
// Written by Todd Treece for Adafruit Industries
// Copyright (c) 2016 Adafruit Industries
// Licensed under the MIT license.
//
// All text above must be included in any redistribution.

/************************** Configuration ***********************************/

// edit the config.h tab and enter your Adafruit IO credentials
// and any additional configuration needed for WiFi, cellular,
// or ethernet clients.
#include "config.h"


#define RXD2 16
#define TXD2 17

#define LED_PIN 2


// Variables
int DATA = 0;
int Cont = 0;
String Estado = "0";
int LED1 = 1;
int LED2 = 0;

AdafruitIO_Feed *DATAFeed = io.feed("datasend");
AdafruitIO_Feed *ContFeed = io.feed("counter");
AdafruitIO_Feed *EstadoFeed = io.feed("estado");

void setup() {

  pinMode(LED_PIN, OUTPUT);

  // start the serial connection
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);

  // wait for serial monitor to open
  while(! Serial);

  Serial.print("Connecting to Adafruit IO");

  // connect to io.adafruit.com
  io.connect();

  EstadoFeed->onMessage(handleMessage);

  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    Serial.println(io.statusText());
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());
  EstadoFeed->get();

}

void loop() {

  // io.run(); is required for all sketches.
  // it should always be present at the top of your loop
  // function. it keeps the client connected to
  // io.adafruit.com, and processes any incoming data.
  io.run();

  // save count to the 'counter' feed on Adafruit IO

  DATAFeed->save(DATA);

  // increment the count by 1
  DATA++;

  // Adafruit IO is rate limited for publishing, so a delay is required in
  // between feed->save events. In this example, we will wait three seconds
  // (1000 milliseconds == 1 second) during each loop.
  delay(3000);

  while (Serial2.available()) {
    // read the incoming byte:
    Cont = Serial2.read();
  }
  ContFeed->save(Cont);

  // Adafruit IO is rate limited for publishing, so a delay is required in
  // between feed->save events. In this example, we will wait three seconds
  // (1000 milliseconds == 1 second) during each loop.
  delay(3000);

}

void handleMessage(AdafruitIO_Data *data) {
  
  Estado = data->toString();

  if(Estado == "1"){
    digitalWrite(LED_PIN, HIGH);
    Serial2.print(LED1);
  }
  else{
    digitalWrite(LED_PIN, LOW);
    Serial2.print(LED2);
  }
  
//  if(data->toPinLevel() == HIGH)
//    Serial.println("HIGH");
//  else
//    Serial.println("LOW");
}
