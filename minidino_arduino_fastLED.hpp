#include "FastLED.h"

#define NUM_LEDS 26
#define PIN 3

byte bright = 50;
byte rate = 0;
byte w = 1;
byte baza = 0;

boolean button1WasUp = true;

CRGB leds[NUM_LEDS];

void setup() {
  pinMode(2, INPUT_PULLUP);

  FastLED.addLeds <WS2812, PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(bright);
}

void knopka () {
  boolean button1IsUp = digitalRead(2);

  if (button1WasUp && !button1IsUp) {
    delay(10);
    button1IsUp = digitalRead(2);
    if (!button1IsUp) { w++; if (w > 7) { w = 1; }
    }
  }
  button1WasUp = button1IsUp;
}

void loop() {

  while (w == 1) {
    knopka(); 
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CHSV(baza+ i * 5, 255, 255);
    }
    baza++;
    FastLED.setBrightness(bright);
    FastLED.show();
    delay(50 - rate);
  }

  while (w == 2) {
    knopka();
    static uint8_t starthue = 0;
    fill_rainbow( leds + 5, NUM_LEDS - 5, --starthue, rate);
    uint8_t secs = (millis() / 1000) % (rate * 2);
    if (secs < rate) { FastLED.setTemperature( Tungsten100W ); leds[0] = Tungsten100W; }
    else { FastLED.setTemperature( OvercastSky ); leds[0] = OvercastSky; }
    FastLED.setBrightness(bright);
    FastLED.show();
  }

  while (w == 3) {
    knopka();
    fadeToBlackBy(leds, NUM_LEDS, (rate + 1) * 2);
    int pos = random16(NUM_LEDS);
    leds[pos] += CHSV(baza++ + random8(64), 200, 255);
    FastLED.setBrightness(bright);
    FastLED.show();
  }

  while (w == 4) {
    knopka();
    fadeToBlackBy(leds, NUM_LEDS, (rate + 1) * 2);
    int pos = beatsin16(13, 0, NUM_LEDS - 1);
    leds[pos] += CHSV(baza++, 255, 192);
    FastLED.setBrightness(bright);
    FastLED.show();
  }

  while (w == 5) {
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i].nscale8(250);
      }
    for (int i = 0; i < NUM_LEDS; i++) {
      knopka();
      leds[i] = CHSV(baza++, 255, 255);
      FastLED.setBrightness(bright);
      FastLED.show();
      delay(rate);
    }
  }

  while (w == 6) {
    knopka();
    fadeToBlackBy(leds, NUM_LEDS, (rate + 1) * 2);
    for (int i = 0; i < 8; i++) {
      leds[beatsin16(i + 7, 0, NUM_LEDS - 1)] |= CHSV(baza+=16, 200, 255);
    }
    FastLED.setBrightness(bright);
    FastLED.show();
    delay(10);
  }

  while (w == 7) {
    knopka();
    fill_rainbow( leds, NUM_LEDS, baza++, 7);
    if (random8() < 80) { leds[ random16(NUM_LEDS) ] += CRGB::White; }
    FastLED.setBrightness(bright);
    FastLED.show();
    delay(50 - rate);
  }
}