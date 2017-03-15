/*
  Basic Ticker usage

  Ticker is an object that will call a given function with a certain period.
  Each Ticker calls one function. You can have as many Tickers as you like,
  memory being the only limitation.

  A function may be attached to a ticker and detached from the ticker.
  There are two variants of the attach function: attach and attach_ms.
  The first one takes period in seconds, the second one in milliseconds.

  An LED connected to GPIO1 will be blinking. Use a built-in LED on ESP-01
  or connect an external one to TXD on other boards.
*/

#include <Ticker.h>

Ticker flipper;

int count = 0;
static int state = 0;

void flip()
{
  count++;
  if (count == 20)
  {
    flipper.attach_ms(100, flip);
  }
  // when the counter reaches yet another value, stop blinking
  else if (count == 120)
  {
    flipper.detach();
  }
  Serial.println(count);
}

void setup() {
  pinMode(BUILTIN_LED, OUTPUT);
  digitalWrite(BUILTIN_LED, LOW);
  Serial.begin(115200);
  // flip the pin every 0.3s
  flipper.attach_ms(1000, flip);
}

void loop() {
}
