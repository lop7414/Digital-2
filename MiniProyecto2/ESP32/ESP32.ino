#include "config.h"

#define RXD2 16
#define TXD2 17
#define SERIAL_8Nl

// this int will hold the current count for our sketch
int DATA = 1;
int Led = 0;

// set up the 'counter' feed
AdafruitIO_Feed *DATASend = io.feed("DATASend");
AdafruitIO_Feed *Estado = io.feed("Estado");

void setup() {

  // start the serial connection
  //  Serial2.begin(9600, SERIAL_8Nl, RXD2, TXD2);
  Serial.begin(115200);
  

  // wait for serial monitor to open
  while(! Serial);

  Serial.print("Connecting to Adafruit IO");

  // connect to io.adafruit.com
  io.connect();

  Estado->onMessage(handleMessage);

  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Estado->get();

  // we are connected
  Serial.println();
  Serial.println(io.statusText());

}

void loop() {

  // io.run(); is required for all sketches.
  // it should always be present at the top of your loop
  // function. it keeps the client connected to
  // io.adafruit.com, and processes any incoming data.
  io.run();

  // Read Serial and save on DATA
  if(Serial.available()>0){
    char DATA = Serial.read();
    Serial.print("sending -> ");
    Serial.println(DATA);
    DATASend->save(DATA);        
  }

  // Adafruit IO is rate limited for publishing, so a delay is required in
  // between feed->save events. In this example, we will wait three seconds
  // (1000 milliseconds == 1 second) during each loop.
  delay(3000);

  

  Serial.write(Led);

}

void handleMessage(AdafruitIO_Data *data) {

  Serial.print("received <- ");
  Serial.println(data->value());

}
