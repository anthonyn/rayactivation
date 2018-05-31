/***************************************************
  This is a library for our I2C LED Backpacks

  Designed specifically to work with the Adafruit LED Matrix backpacks
  ----> http://www.adafruit.com/products/872
  ----> http://www.adafruit.com/products/871
  ----> http://www.adafruit.com/products/870

  These displays use I2C to communicate, 2 pins are required to
  interface. There are multiple selectable I2C addresses. For backpacks
  with 2 Address Select pins: 0x70, 0x71, 0x72 or 0x73. For backpacks
  with 3 Address Select pins: 0x70 thru 0x77

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include <Wire.h>

#include <SparkFun_GridEYE_Arduino_Library.h>

#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

#define HOT 40
#define COLD 20

int heatThreshold = 40;

int pixelTable[64];
GridEYE grideye;

boolean dotTable[64];

Adafruit_8x8matrix matrix = Adafruit_8x8matrix();
static const uint8_t PROGMEM
smile_bmp[] =
{ B00111100,
  B01000010,
  B10100101,
  B10000001,
  B10100101,
  B10011001,
  B01000010,
  B00111100
},
neutral_bmp[] =
{ B00111100,
  B01000010,
  B10100101,
  B10000001,
  B10111101,
  B10000001,
  B01000010,
  B00111100
},
frown_bmp[] =
{ B00111100,
  B01000010,
  B10100101,
  B10000001,
  B10011001,
  B10100101,
  B01000010,
  B00111100
};

void setup() {
  Serial.begin(9600);
  Serial.println("8x8 LED Matrix Test");

  matrix.begin(0x70);  // pass in the address

  // Library assumes "Wire" for I2C but you can pass something else with begin() if you like
  grideye.begin();
  // Pour a bowl of serial
  Serial.begin(115200);

  matrix.clear();
  matrix.drawBitmap(0, 0, smile_bmp, 8, 8, LED_ON);
  matrix.writeDisplay();
}


void loop() {

  // loop through all 64 pixels on the device and map each float value to a number
  // between 0 and 3 using the HOT and COLD values we set at the top of the sketch
  for (unsigned char i = 0; i < 64; i++) {
    pixelTable[i] = map(grideye.getPixelTemperature(i), COLD, HOT, 0, 3);
  }


  // loop through the table of mapped values and print a character corresponding to each
  // pixel's temperature. Add a space between each. Start a new line every 8 in order to
  // create an 8x8 grid
  for (unsigned char i = 0; i < 64; i++) {
    if (pixelTable[i] == 0) {
      Serial.print(".");
    }
    else if (pixelTable[i] == 1) {
      Serial.print("o");
    }
    else if (pixelTable[i] == 2) {
      Serial.print("0");
    }
    else if (pixelTable[i] == 3) {
      Serial.print("O");
    }
    Serial.print(" ");
    if ((i + 1) % 8 == 0) {
      Serial.println();
    }

    matrix.clear();
    matrix.setRotation(1);
    //convert ever heat value over a threshold to a dot on the matrix
    for (int i = 0; i < 64; i++) {
      if (pixelTable[i] >= 1) {
        //dotTable[i] = true;
        matrix.drawPixel(i % 8, i / 8, LED_ON);
      }
      else {

      }
    }
    matrix.writeDisplay();
  }

  //write to matrix
  //matrix.clear();
  //matrix.drawBitmap(0, 0, dotTable, 8, 8, LED_ON);


  // in between updates, throw a few linefeeds to visually separate the grids. If you're using
  // a serial terminal outside the Arduino IDE, you can replace these linefeeds with a clearscreen
  // command
  Serial.println();
  // toss in a delay because we don't need to run all out
  delay(100);
}


