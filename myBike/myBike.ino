//works great
#include "lab.h"

#include <Adafruit_DotStar.h>
#include <SPI.h>
#include <Ticker.h>

Ticker draw;

/*extern "C" {
#include "user_interface.h"
  uint16 readvdd33(void);
  bool wifi_set_sleep_type(sleep_type_t);
  sleep_type_t wifi_get_sleep_type(void);
}*/
#define DATAPIN MOSI
#define CLOCKPIN SCK

Adafruit_DotStar strip = Adafruit_DotStar(NUM_LEDS+1, DATAPIN, CLOCKPIN);

//global shit i've stolen
uint8_t  imageType,          // Image type: PALETTE[1,4,8] or TRUECOLOR
         imagePalette,       // -> palette data in PROGMEM
         imagePixels,        // -> pixel data in PROGMEM
         imageLines,         // Number of lines in active image2
         imageLine;          // Current line number in image

const int interruptPin = D2;
unsigned long time1;
unsigned long animationTime;
unsigned long wheelTime;
unsigned long animationResult;
unsigned long wheelResult;
unsigned long delayTime;

void initializePhoto(){
  imageType = paletteType;
  switch (imageType) {
    case 0:
      imageLines = sizeof(pixels00)*8/NUM_LEDS;
    break;
    case 1:
      imageLines = sizeof(pixels00)*2/NUM_LEDS;
    break;
    case 2:
      imageLines = sizeof(pixels00)/NUM_LEDS;
    break;
    case 3:
      imageLines = sizeof(pixels00)/NUM_LEDS/3;
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

void tickerTime(){
  time1 = micros();
  if(animationResult+10000<time1 - wheelTime){
    wheelResult = time1 - wheelTime;
    wheelTime = time1;
    Serial.print("Wheel time: ");
    Serial.println(wheelResult);
    delayTime = (wheelResult-animationResult)/imageLines;
    Serial.print("----- delay time: ");
    Serial.println(delayTime);
  }
  unsigned long timer = delayTime/1000;
  draw.attach_ms(timer, animation);
}

void animation(){
  //detachInterrupt(interruptPin);
  Serial.println("start animation loop");
  //attachInterrupt(interruptPin, animation, FALLING);
  switch (imageType) {
    case 0:

    break;
    case 1:
      uint8_t p1, p2, pixelNum;//*ptr = (uint8_t*)&pixels00[];
      for(pixelNum = 0; pixelNum<NUM_LEDS;){

        p2  = pixels00[pixelNum%16+(imageLine*NUM_LEDS/2)];
        p1 = p2 >> 4;
        p2 &= 0x0F;
        //Serial.println(pixelNum+(imageLine*NUM_LEDS/2));

        strip.setPixelColor(1+pixelNum++,
          palette00[p1][0],palette00[p1][1],palette00[p1][2]);

        strip.setPixelColor(1+pixelNum++,
          palette00[p2][0],palette00[p2][1],palette00[p2][2]);
      }
      imageLine++;
      if(imageLine>=imageLines) imageLine=0;
      strip.show();
    break;
    case 2:
      uint16_t o;
      for(int pixelNum = 0; pixelNum<NUM_LEDS;){
        o = pixels00[pixelNum+(imageLine*NUM_LEDS)];
        strip.setPixelColor(1+pixelNum++,
        palette00[o][0],palette00[o][1],palette00[o][2]);
      }
      imageLine++;
      strip.show();
      if(imageLine>=imageLines){
        imageLine=0;
      }
    break;
    case 3:
      uint8_t p, r, g, b;
      p = 0;
      for(int pixelNum = 0; pixelNum<NUM_LEDS*3;){

        r = pixels00[pixelNum++];
        g = pixels00[pixelNum++];
        b = pixels00[pixelNum++];
        strip.setPixelColor(p,r,g,b);
        p++;
        if(p>imageLines){
          p==0;
        }
      }
    break;
  }
}

void timeCalc(){
  animationTime=micros();
  while(imageLine<=imageLines){
    switch (imageType) {
      case 0:

      break;
      case 1:
        uint8_t p1, p2, pixelNum;//*ptr = (uint8_t*)&pixels00[];
        for(pixelNum = 0; pixelNum<NUM_LEDS;){

          p2  = pixels00[pixelNum%16+(imageLine*NUM_LEDS/2)];
          p1 = p2 >> 4;
          p2 &= 0x0F;
          //Serial.println(pixelNum+(imageLine*NUM_LEDS/2));

          strip.setPixelColor(1+pixelNum++,
            palette00[p1][0],palette00[p1][1],palette00[p1][2]);

          strip.setPixelColor(1+pixelNum++,
            palette00[p2][0],palette00[p2][1],palette00[p2][2]);
        }
        imageLine++;
        if(imageLine>=imageLines) imageLine=0;
        strip.show();
      break;
      case 2:
        uint16_t o;
          for(int pixelNum = 0; pixelNum<NUM_LEDS;){
            o = pixels00[pixelNum+(imageLine*NUM_LEDS)];
            strip.setPixelColor(1+pixelNum++,
              palette00[o][0],palette00[o][1],palette00[o][2]);
            //pixelNum++;
          }
        imageLine++;
        strip.show();
      break;
      case 3:
        uint8_t p, r, g, b;
        p = 0;
        for(int pixelNum = 0; pixelNum<NUM_LEDS*3;){

          r = pixels00[pixelNum++];
          g = pixels00[pixelNum++];
          b = pixels00[pixelNum++];
          strip.setPixelColor(p,r,g,b);
          p++;
          if(p>imageLines){
            p==0;
          }
        }
      break;
    }
  }
  imageLine=0;
  strip.clear();
  time1=micros();
  animationResult = time1-animationTime;
  Serial.print("one cycle: ");
  Serial.println(animationResult);
  animationTime= time1;
}

void setup() {
  //wifi_set_sleep_type(MODEM_SLEEP_T);
  Serial.begin(115200);
  Serial.println("Begin strip");
  strip.begin();
  Serial.println("Begin show");
  strip.show();
  initializePhoto();
  time1 = micros();
  animationTime = time1;
  wheelTime = time1;
  pinMode(interruptPin, INPUT);
  attachInterrupt(interruptPin, tickerTime, FALLING);
  timeCalc();
  draw.attach_ms(1000, animation);
}

void loop() {
  //delay(500);
}
