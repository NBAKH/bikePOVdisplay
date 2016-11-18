// Don't edit this file!  It's software-generated.
// See convert.py script instead.

#define PALETTE1  0
#define PALETTE4  1
#define PALETTE8  2
#define TRUECOLOR 3

#define NUM_LEDS 32
#define paletteType PALETTE4

// rgbwt.png ---------------------------------------------------------------

const uint8_t palette00[][3] = {
  {   6,   0,  62 },
  {  62,   0,   0 },
  {  39,   0,  62 },
  {   0,  62,   0 },
  {  62,   0,  44 },
  {  44,  62,   0 },
  {   0,  62,  57 },
  {  62,   0,   5 },
  {   8,  62,   0 },
  {   0,  62,  17 },
  {   0,  62,   1 },
  {  62,  38,   0 },
  {  62,   4,   0 },
  {   0,   0,  62 },
  {   0,  25,  62 },
  {   0,   1,  62 }  };

const uint8_t pixels00[] = {
  0X1C, 0XB5, 0X83, 0XA9, 0X6E, 0XFD, 0X02, 0X47 };


// typedef struct {
//   const uint8_t type;    // PALETTE[1,4,8] or TRUECOLOR
//   const uint8_t lines;   // Length of image (in scanlines)
//   const uint8_t palette; // -> PROGMEM color table (NULL if truecolor)
//   const uint8_t pixels;  // -> Pixel data in PROGMEM
// } image;
//
// const image images[] = {
//   { PALETTE4 ,  5, palette00, pixels00 }
// };

//#define NUM_IMAGES (sizeof(images) / sizeof(images[0]))
