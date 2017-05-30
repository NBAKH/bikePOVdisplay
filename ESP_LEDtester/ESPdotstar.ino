#include <Adafruit_DotStar.h>
#include <SPI.h>

#define NUMPIXELS 289

#define DATAPIN    MOSI
#define CLOCKPIN   SCK
Adafruit_DotStar strip = Adafruit_DotStar(NUMPIXELS, DATAPIN, CLOCKPIN);

void setup() {
  strip.begin();
  strip.show();
}
int      head  = 0, tail = -10;
uint32_t color = 0x110000;

void loop() {

  strip.setPixelColor(head, color);
  strip.setPixelColor(tail, 0);
  strip.show();
  delay(1);

  if(++head >= NUMPIXELS) {
    head = 0;
    if((color >>= 8) == 0)
      color = 0x110000;
  }
  if(++tail >= NUMPIXELS) tail = 0;
}
