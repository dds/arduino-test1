#include <stdint.h>

#define SWITCH_PIN 8
#define POT_PIN 0
#define LED_PIN_1 2
#define LED_PIN_2 13
#define LED_PIN_3 5
#define LAST_LED 0xff

static uint8_t ledPins[] = {LED_PIN_1, LED_PIN_2, LED_PIN_3, LAST_LED};
static uint8_t *currentLedPin = &ledPins[0];

void setup(void) {
  pinMode(SWITCH_PIN, INPUT);
  for (uint8_t i = 0; ledPins[i] != LAST_LED; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

int blinkDelay(void) {
  int potVal = analogRead(POT_PIN);
  return map(potVal, 0, 1023, 400, 50);
}

void blinkStep(void) {
  digitalWrite(*currentLedPin++, LOW);
  if (*currentLedPin == LAST_LED) {
    currentLedPin = &ledPins[0];
  }
  digitalWrite(*currentLedPin, HIGH);
}

void flash(void) {
  for (uint8_t i = 0; ledPins[i] != LAST_LED; i++) {
    digitalWrite(ledPins[i], HIGH);
  }
  delay(100);
  for (uint8_t i = 0; ledPins[i] != LAST_LED; i++) {
    digitalWrite(ledPins[i], LOW);
  }
  delay(100);
}

void loop(void) {
  if (digitalRead(SWITCH_PIN) == HIGH) {
    blinkStep();
    delay(blinkDelay());
  }
}
