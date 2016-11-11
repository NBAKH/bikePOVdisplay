/*------------------------------------------------------------------------
  POV LED bike wheel sketch.  Uses the following Adafruit parts:

  - Pro Trinket 5V (www.adafruit.com/product/2000)
    (NOT Trinket or 3V Pro Trinket)
  - Waterproof 3xAA battery holder with on/off switch (#771)
  - 144 LED/m DotStar strip (#2328 or #2329) ONE is enough for
    both sides of one bike wheel
  - Tactile switch button (#1119) (optional)

  Needs Adafruit_DotStar library: github.com/adafruit/Adafruit_DotStar

  Full instructions: https://learn.adafruit.com/bike-wheel-pov-display

  This project is based on Phil B's Genesis Poi:
  learn.adafruit.com/genesis-poi-dotstar-led-persistence-of-vision-poi
  and has been adapted to the Pro Trinket to accomodate more and larger
  images than Trinket.

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Phil Burgess / Paint Your Dragon for Adafruit Industries.
  MIT license, all text above must be included in any redistribution.
  See 'COPYING' file for additional notes.
  ------------------------------------------------------------------------*/

#include <Arduino.h> //maybe that includes pgmspace
#include <Adafruit_DotStar.h>
//#include <avr/power.h>
//#include <avr/sleep.h>
#include <SPI.h> // Enable this line on Pro Trinket

#ifdef ESP8266
  #include <pgmspace.h>
#else
  #include <avr/pgmspace.h>
#endif

#ifdef __AVR_ATtiny85__
typedef uint8_t  line_t; // Max 255 lines/image on Trinket
#else
typedef uint16_t line_t; // Bigger images OK on other boards
#endif

// CONFIGURABLE STUFF ------------------------------------------------------

#include "pixels.h" // Graphics data is contained in this header file.
// It's generated using the 'convert.py' Python script.  Various image
// formats are supported, trading off color fidelity for PROGMEM space
// (particularly limited on Trinket).  Handles 1-, 4- and 8-bit-per-pixel
// palette-based images, plus 24-bit truecolor.  1- and 4-bit palettes can
// be altered in RAM while running to provide additional colors, but be
// mindful of peak & average current draw if you do that!  Power limiting
// is normally done in convert.py (keeps this code relatively small & fast).
// 1/4/8/24 were chosen because the AVR can handle these operations fairly
// easily (have idea for handing arbitrary bit depth w/328P, but this margin
// is too narrow to contain).

// Ideally you use hardware SPI as it's much faster, though limited to
// specific pins.  If you really need to bitbang DotStar data & clock on
// different pins, optionally define those here:
#ifdef ESP8266
  #define LED_DATA_PIN  MOSI //changed to fit ESP8266 modules. look in ESPdotstar
  #define LED_CLOCK_PIN SCK // same
#else
  #define LED_DATA_PIN 11
  #define LED_CLOCK_PIN 12
#endif

Adafruit_DotStar strip = Adafruit_DotStar(NUM_LEDS,LED_DATA_PIN, LED_CLOCK_PIN, DOTSTAR_BRG);

void     imageInit(void);

void setup() {
  strip.begin();                // Allocate DotStar buffer, init SPI
  strip.clear();                // Make sure strip is clear
  strip.show();                 // before measuring battery

  imageInit(); // Initialize pointers for default image
}

// GLOBAL STATE STUFF ------------------------------------------------------

uint32_t lastImageTime = 0L; // Time of last image change
uint8_t  imageNumber   = 0,  // Current image being displayed
         imageType,          // Image type: PALETTE[1,4,8] or TRUECOLOR
        *imagePalette,       // -> palette data in PROGMEM
        *imagePixels,        // -> pixel data in PROGMEM
         palette[16][3];     // RAM-based color table for 1- or 4-bit images
line_t   imageLines,         // Number of lines in active image
         imageLine;          // Current line number in image
#ifdef SELECT_PIN
uint8_t  debounce      = 0;  // Debounce counter for image select pin
#endif

void imageInit() { // Initialize global image state for current imageNumber
  imageType    = images[imageNumber].type;
  imageLines   = images[imageNumber].lines;

  imageLine    = 0;
  imagePalette = (uint8_t *)(&images[imageNumber].palette);
  imagePixels  = (uint8_t *)(&images[imageNumber].pixels);
  // 1- and 4-bit images have their color palette loaded into RAM both for
  // faster access and to allow dynamic color changing.  Not done w/8-bit
  // because that would require inordinate RAM (328P could handle it, but
  // I'd rather keep the RAM free for other features in the future).
  if(imageType == PALETTE1)      (palette, imagePalette,  2 * 3);
  else if(imageType == PALETTE4) (palette, imagePalette, 16 * 3);
  lastImageTime = millis(); // Save time of image init for next auto-cycle
}

void nextImage(void) {
  if(++imageNumber >= NUM_IMAGES) imageNumber = 0;
  imageInit();
}

// MAIN LOOP ---------------------------------------------------------------

void loop() {

  // Transfer one scanline from pixel data to LED strip:

  // If you're really pressed for graphics space and need just a few extra
  // scanlines, and know for a fact you won't be using certain image modes,
  // you can comment out the corresponding blocks below.  e.g. PALETTE8 and
  // TRUECOLOR are somewhat impractical on Trinket, and commenting them out
  // can free up nearly 200 bytes of extra image storage.

  switch(imageType) {
    case PALETTE4: { // 4-bit (16 color) palette-based image
      uint8_t  pixelNum, p1, p2,
              ptr = imagePixels[imageLine * NUM_LEDS / 2];
      for(pixelNum = 0; pixelNum < NUM_LEDS; ) {
        p2  = ptr++; // Data for two pixels...
        p1  = p2 >> 4;              // Shift down 4 bits for first pixel
        p2 &= 0x0F;                 // Mask out low 4 bits for second pixel
        strip.setPixelColor(pixelNum++,
          palette[p1][0], palette[p1][1], palette[p1][2]);
        strip.setPixelColor(pixelNum++,
          palette[p2][0], palette[p2][1], palette[p2][2]);
      }
      break;
    }
  }

  strip.show(); // Refresh LEDs
#if !defined(LED_DATA_PIN) && !defined(LED_CLOCK_PIN)
  delayMicroseconds(900);  // Because hardware SPI is ludicrously fast
#endif
  if(++imageLine >= imageLines) imageLine = 0; // Next scanline, wrap around
}
