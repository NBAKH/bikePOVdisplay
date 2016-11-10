// Don't edit this file!  It's software-generated.
// See convert.py script instead.

#define PALETTE1  0
#define PALETTE4  1
#define PALETTE8  2
#define TRUECOLOR 3

#define NUM_LEDS 16

// adafruit.gif ------------------------------------------------------------

const uint8_t PROGMEM palette00[][3] = {
  {   0,   0,   0 },
  {  61,  61,  61 } };

const uint8_t PROGMEM pixels00[] = {
  0X00, 0X7C, 0XE0, 0XFE, 0XF0, 0XFE, 0X70, 0XE6,
  0X70, 0XC6, 0X30, 0XC6, 0X30, 0X66, 0X70, 0X66,
  0XF0, 0XFF, 0XF0, 0XFF, 0XC0, 0XFF, 0X00, 0X00,
  0XC0, 0X3F, 0XE0, 0X7F, 0XF0, 0XFF, 0X70, 0XE0,
  0X70, 0XE0, 0X70, 0XE0, 0X60, 0X60, 0X60, 0X60,
  0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0X00, 0X00,
  0X00, 0X30, 0XE0, 0XFC, 0XF0, 0XFE, 0XF0, 0XEE,
  0X70, 0XC6, 0X30, 0XC6, 0X30, 0X46, 0X70, 0X66,
  0XF0, 0XFF, 0XF0, 0XFF, 0XE0, 0XFF, 0X00, 0X00,
  0XFC, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0X77, 0X00,
  0X73, 0X00, 0X73, 0X00, 0X00, 0X00, 0XE0, 0XFF,
  0XF0, 0XFF, 0XF0, 0XFF, 0XE0, 0X00, 0X60, 0X00,
  0X70, 0X00, 0X70, 0X00, 0X00, 0X00, 0X00, 0X00,
  0XF0, 0X7F, 0XF0, 0XFF, 0XF0, 0XFF, 0X00, 0XE0,
  0X00, 0XE0, 0X00, 0XE0, 0X00, 0X60, 0XF0, 0XFF,
  0XF0, 0XFF, 0XF0, 0XFF, 0X00, 0X00, 0X00, 0X00,
  0XF3, 0XFF, 0XF3, 0XFF, 0XF3, 0XFF, 0X00, 0X00,
  0XF8, 0X3F, 0XF8, 0XFF, 0XFC, 0XFF, 0XF8, 0XFF,
  0X70, 0XE0, 0X70, 0XE0, 0X00, 0X00, 0X00, 0X00,
  0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
  0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
  0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
  0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
  0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
  0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00 };

typedef struct {
  uint8_t        type;    // PALETTE[1,4,8] or TRUECOLOR
  line_t         lines;   // Length of image (in scanlines)
  const uint8_t *palette; // -> PROGMEM color table (NULL if truecolor)
  const uint8_t *pixels;  // -> Pixel data in PROGMEM
} image;

const image PROGMEM images[] = {
  { PALETTE1 ,  100, (const uint8_t *)palette00, pixels00 }
};

#define NUM_IMAGES (sizeof(images) / sizeof(images[0]))
