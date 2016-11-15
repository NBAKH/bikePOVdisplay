#include <Adafruit_DotStar.h>
#include <SPI.h>

#include "rgbwt.h"

#define DATAPIN MOSI
#define CLOCKPIN SCK

//#define uint16_t line_t;

Adafruit_DotStar strip = Adafruit_DotStar(NUM_LEDS, DATAPIN, CLOCKPIN);



//global shit i've stolen
uint8_t  imageNumber   = 0,  // Current image being displayed
         imageType,          // Image type: PALETTE[1,4,8] or TRUECOLOR
        *imagePalette,       // -> palette data in PROGMEM
        *imagePixels,        // -> pixel data in PROGMEM
         palette[16][3];     // RAM-based color table for 1- or 4-bit images
line_t   imageLines,         // Number of lines in active image
         imageLine;          // Current line number in image

void initializePhoto(){
  imageType    = images[imageNumber].type;
  imageLines   = images[imageNumber].lines;
  imageLine    = 0;
  imagePalette = images[imageNumber].palette;
  imagePixels  = images[imageNumber].pixels;
  // if(imageType == PALETTE1)      memcpy_P(palette, imagePalette,  2 * 3);
  // else if(imageType == PALETTE4) memcpy_P(palette, imagePalette, 16 * 3);
  // lastImageTime = millis(); // Save time of image init for next auto-cycle
}

void setup() {
  strip.begin();
  strip.show();
}

void loop() {

}
