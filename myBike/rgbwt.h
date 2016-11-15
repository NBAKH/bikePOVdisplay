// Don't edit this file!  It's software-generated.
// See convert.py script instead.

#define PALETTE1  0
#define PALETTE4  1
#define PALETTE8  2
#define TRUECOLOR 3

#define NUM_LEDS 32

// rgbwt.png ---------------------------------------------------------------

const uint8_t palette00[][3] = {
  {  29,   0,   0 },
  {   0,  15,  15 },
  {   0,  29,   0 },
  {   0,   0,  29 },
  {  29,  29,  29 } };

const uint8_t pixels00[] = {
  0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
  0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
  0X22, 0X22, 0X22, 0X22, 0X22, 0X22, 0X22, 0X22,
  0X22, 0X22, 0X22, 0X22, 0X22, 0X22, 0X22, 0X22,
  0X33, 0X33, 0X33, 0X33, 0X33, 0X33, 0X33, 0X33,
  0X33, 0X33, 0X33, 0X33, 0X33, 0X33, 0X33, 0X33,
  0X44, 0X44, 0X44, 0X44, 0X44, 0X44, 0X44, 0X44,
  0X44, 0X44, 0X44, 0X44, 0X44, 0X44, 0X44, 0X44,
  0X11, 0X11, 0X11, 0X11, 0X11, 0X11, 0X11, 0X11,
  0X11, 0X11, 0X11, 0X11, 0X11, 0X11, 0X11, 0X11 };

typedef struct {
  uint8_t        type;    // PALETTE[1,4,8] or TRUECOLOR
  //line_t         lines;   // Length of image (in scanlines)
  const uint8_t *palette; // -> PROGMEM color table (NULL if truecolor)
  const uint8_t *pixels;  // -> Pixel data in PROGMEM
} image;

const image images[] = {
  { PALETTE4 ,  /*  5, */(const uint8_t *)palette00, pixels00 }
};

#define NUM_IMAGES (sizeof(images) / sizeof(images[0]))
