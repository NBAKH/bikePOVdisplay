//interupt test on wemos, getting nodemcu's tomorrow

const int pin = D3;

void toggle() {
  static int state = 0;
  state = !state;
  digitalWrite(BUILTIN_LED, state);
  Serial.print("changed to ");
  Serial.println(state);
}

void setup() {
  Serial.begin(115200);
  pinMode(BUILTIN_LED, OUTPUT);
  pinMode(pin, INPUT);//_PULLUP);
  attachInterrupt(pin, toggle, CHANGE);
  toggle();
}

void loop() {

}
