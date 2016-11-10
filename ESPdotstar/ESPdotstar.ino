#include <Adafruit_DotStar.h>
#include <SPI.h>

#define NUMPIXELS 20

#define DATAPIN    MOSI
#define CLOCKPIN   SCK
Adafruit_DotStar strip = Adafruit_DotStar(NUMPIXELS, DATAPIN, CLOCKPIN);

void setup() {
  Serial.begin(115200);
  Serial.println("print is working great...");
  strip.begin();
  strip.show();
  delay(2000);
  Serial.println("I mean really great");
}
int      head  = 0, tail = -10;
uint32_t color = 0xFF0000;

void loop() {
  Serial.println("loop start");
  strip.setPixelColor(head, color);
  strip.setPixelColor(tail, 0);
  strip.show();
  delay(10);

  if(++head >= NUMPIXELS) {
    head = 0;
    if((color >>= 8) == 0)
      color = 0xFF0000;
  }
  if(++tail >= NUMPIXELS) tail = 0;
}
