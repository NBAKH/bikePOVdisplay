#include "rgbwt.h"

#include <Adafruit_DotStar.h>
#include <SPI.h>

#define DATAPIN MOSI
#define CLOCKPIN SCK

#define PALETTE1  0
#define PALETTE4  1
#define PALETTE8  2
#define TRUECOLOR 3

//typedef uint16_t line_t; //Is in the config file

// #define MY_TYPE int
// typedef int My_Type;

Adafruit_DotStar strip = Adafruit_DotStar(NUM_LEDS, DATAPIN, CLOCKPIN);

//global shit i've stolen
uint8_t  imageType,          // Image type: PALETTE[1,4,8] or TRUECOLOR
         imagePalette,       // -> palette data in PROGMEM
         imagePixels,        // -> pixel data in PROGMEM
         imageLines,         // Number of lines in active image2
         imageLine;          // Current line number in image

void initializePhoto(){
  imageType    = paletteType;
  if(paletteType == 1){
    imageLines   = sizeof(pixels00)*2/NUM_LEDS;
    Serial.print("Image lines: ");
    Serial.println(imageLines);
  }

  imageLine   = 0;
  // imagePalette = palette00[0];
  // imagePixels  = pixels00[0];


  // if(imageType == PALETTE1)      memcpy_P(palette, imagePalette,  2 * 3);
  // else if(imageType == PALETTE4) memcpy_P(palette, imagePalette, 16 * 3);
  // lastImageTime = millis(); // Save time of image init for next auto-cycle
}

void setup() {
  Serial.begin(115200);
  strip.begin();
  strip.show();
  initializePhoto();
}

void loop() {
  switch (imageType) {
    case 1:
      uint8_t p1, p2, pixelNum;//*ptr = (uint8_t*)&pixels00[];
      for(pixelNum = 0; pixelNum<NUM_LEDS;){

        p2  = pixels00[pixelNum%16+(imageLine*NUM_LEDS/2)];
        p1 = p2 >> 4;
        p2 &= 0x0F;
        Serial.println(pixelNum+(imageLine*NUM_LEDS/2));

        strip.setPixelColor(pixelNum++,
          palette00[p1][0],palette00[p1][1],palette00[p1][2]);

        strip.setPixelColor(pixelNum++,
          palette00[p2][0],palette00[p2][1],palette00[p2][2]);
      }
      imageLine++;
      if(imageLine>imageLines) imageLine=0;
      strip.show();
    break;
  }
  // delay(500);
}
