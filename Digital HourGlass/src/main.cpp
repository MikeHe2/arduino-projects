#include <Arduino.h>

const int switchPin = 8;
unsigned long previousTime = 0;
int switchState = 0;
int prevSwitchState = 0;
int led = 2;
int direction = 1;
long interval = 1000;

void resetHourglass(int state) {
  for (int x = 2; x < 8; x++) {
    digitalWrite(x, LOW);
  }
  if (state == HIGH) {
    direction = 1;
    led = 2;
  } else {
    direction = -1;
    led = 7;
  }
}

void setup() {
  for (int x = 2; x < 8; x++) {
    pinMode(x, OUTPUT);
  }
  pinMode(switchPin, INPUT);
  switchState = digitalRead(switchPin);
  prevSwitchState = switchState;
  resetHourglass(switchState);
}

void loop() {
  unsigned long currentTime = millis();
  switchState = digitalRead(switchPin);

  if (switchState != prevSwitchState) {
    resetHourglass(switchState);
    previousTime = currentTime;
    prevSwitchState = switchState;
  }

  if (currentTime - previousTime > interval) {
    previousTime = currentTime;
    digitalWrite(led, HIGH);
    led += direction;
    if (led > 7 || led < 2) {
      // Time is up
    }
  }
}
