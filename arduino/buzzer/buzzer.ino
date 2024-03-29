#include <Keyboard.h>
#include "FastLED.h"

// Constants
#define LED_TYPE            WS2811
#define COLOR_ORDER         GRB
#define NUM_LEDS            14
#define BRIGHTNESS          255
#define FRAMES_PER_SECOND   120
#define BUZZER_LOCK_TIMEOUT 2000

// Pin Definition (for Arduino MKR WiFi 1010)
#define BUZZER_LOCK_TIMEOUT_SWITCH 6
#define BUZZER1_LED     0
#define BUZZER1_SWITCH  A0
#define BUZZER2_LED     1
#define BUZZER2_SWITCH  A1
#define BUZZER3_LED     2
#define BUZZER3_SWITCH  A2
#define BUZZER4_LED     3
#define BUZZER4_SWITCH  A3
#define BUZZER5_LED     4
#define BUZZER5_SWITCH  A4
#define BUZZER6_LED     5
#define BUZZER6_SWITCH  A5

CRGB leds[6][NUM_LEDS];
bool buzzerStates[6];

void setup() {
  delay(800);
  pinMode(BUZZER1_SWITCH, INPUT_PULLUP);
  pinMode(BUZZER2_SWITCH, INPUT_PULLUP);
  pinMode(BUZZER3_SWITCH, INPUT_PULLUP);
  pinMode(BUZZER4_SWITCH, INPUT_PULLUP);
  pinMode(BUZZER5_SWITCH, INPUT_PULLUP);
  pinMode(BUZZER6_SWITCH, INPUT_PULLUP);
  pinMode(BUZZER_LOCK_TIMEOUT_SWITCH, INPUT_PULLUP);
  pinMode(BUZZER1_LED, OUTPUT);
  pinMode(BUZZER2_LED, OUTPUT);
  pinMode(BUZZER3_LED, OUTPUT);
  pinMode(BUZZER4_LED, OUTPUT);
  pinMode(BUZZER5_LED, OUTPUT);
  pinMode(BUZZER6_LED, OUTPUT);
}

typedef void (*SimplePatternList[])();
SimplePatternList gPatterns = { rainbow, rainbowWithGlitter, confetti, sinelon, juggle, bpm };

uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current
uint8_t gHue = 0; // rotating "base color" used by many of the patterns

byte currentBuzzer = 0;
unsigned long lastPress = 0;

void loop() {
  // call the current pattern function once, updating the 'leds' array
  gPatterns[gCurrentPatternNumber]();
  EVERY_N_MILLISECONDS( 20 ) { gHue++; } // slowly cycle the "base color" through the rainbow
  EVERY_N_SECONDS( 10 ) { nextPattern(); } // change patterns periodically

  // check button released
  if(digitalRead(BUZZER1_SWITCH) == HIGH)
      buzzerStates[0] = false;
  if(digitalRead(BUZZER2_SWITCH) == HIGH)
      buzzerStates[1] = false;
  if(digitalRead(BUZZER3_SWITCH) == HIGH)
      buzzerStates[2] = false;
  if(digitalRead(BUZZER4_SWITCH) == HIGH)
      buzzerStates[3] = false;
  if(digitalRead(BUZZER5_SWITCH) == HIGH)
      buzzerStates[4] = false;
  if(digitalRead(BUZZER6_SWITCH) == HIGH)
      buzzerStates[5] = false;

  // check button press
  if(lastPress == 0 // if this is the first press since startup...
  || digitalRead(BUZZER_LOCK_TIMEOUT_SWITCH) == LOW // ...or lock timeout ist disabled via switch
  || millis()-lastPress > BUZZER_LOCK_TIMEOUT) { // ...or timeout is lapsed

    // handle buzzer press
    if(digitalRead(BUZZER1_SWITCH) == LOW && !buzzerStates[0]) {
      buzzerStates[0] = true;
      startLed1();
      pressKey('1');
    } else
    if(digitalRead(BUZZER2_SWITCH) == LOW && !buzzerStates[1]) {
      buzzerStates[1] = true;
      startLed2();
      pressKey('2');
    } else
    if(digitalRead(BUZZER3_SWITCH) == LOW && !buzzerStates[2]) {
      buzzerStates[2] = true;
      startLed3();
      pressKey('3');
    } else
    if(digitalRead(BUZZER4_SWITCH) == LOW && !buzzerStates[3]) {
      buzzerStates[3] = true;
      startLed4();
      pressKey('4');
    } else
    if(digitalRead(BUZZER5_SWITCH) == LOW && !buzzerStates[4]) {
      buzzerStates[4] = true;
      startLed5();
      pressKey('5');
    } else
    if(digitalRead(BUZZER6_SWITCH) == LOW && !buzzerStates[5]) {
      buzzerStates[5] = true;
      startLed6();
      pressKey('6');
    }

  } else {

    // buzzer locked - send 'x' instead
    if((digitalRead(BUZZER1_SWITCH) == LOW && !buzzerStates[0])
    || (digitalRead(BUZZER2_SWITCH) == LOW && !buzzerStates[1])
    || (digitalRead(BUZZER3_SWITCH) == LOW && !buzzerStates[2])
    || (digitalRead(BUZZER4_SWITCH) == LOW && !buzzerStates[3])
    || (digitalRead(BUZZER5_SWITCH) == LOW && !buzzerStates[4])
    || (digitalRead(BUZZER6_SWITCH) == LOW && !buzzerStates[5])
    ) {
      if(millis()-lastPress > 400) {
        pressKey('x');
      }
    }

  }

  // LED FX step
  FastLED.show();
  FastLED.delay(1000/FRAMES_PER_SECOND);
}

void startLed1() {
  currentBuzzer = 0;
  FastLED.clear(true);
  FastLED.addLeds<LED_TYPE,BUZZER1_LED,COLOR_ORDER>(leds[currentBuzzer], NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
}
void startLed2() {
  currentBuzzer = 1;
  FastLED.clear(true);
  FastLED.addLeds<LED_TYPE,BUZZER2_LED,COLOR_ORDER>(leds[currentBuzzer], NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
}
void startLed3() {
  currentBuzzer = 2;
  FastLED.clear(true);
  FastLED.addLeds<LED_TYPE,BUZZER3_LED,COLOR_ORDER>(leds[currentBuzzer], NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
}
void startLed4() {
  currentBuzzer = 3;
  FastLED.clear(true);
  FastLED.addLeds<LED_TYPE,BUZZER4_LED,COLOR_ORDER>(leds[currentBuzzer], NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
}
void startLed5() {
  currentBuzzer = 4;
  FastLED.clear(true);
  FastLED.addLeds<LED_TYPE,BUZZER5_LED,COLOR_ORDER>(leds[currentBuzzer], NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
}
void startLed6() {
  currentBuzzer = 5;
  FastLED.clear(true);
  FastLED.addLeds<LED_TYPE,BUZZER6_LED,COLOR_ORDER>(leds[currentBuzzer], NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
}

void pressKey(char key) {
  Keyboard.press(key);
  delay(10);
  Keyboard.releaseAll();
  lastPress = millis();
}

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

void nextPattern() {
  // add one to the current pattern number, and wrap around at the end
  gCurrentPatternNumber = (gCurrentPatternNumber + 1) % ARRAY_SIZE(gPatterns);
}

void rainbow() {
  // FastLED's built-in rainbow generator
  fill_rainbow( leds[currentBuzzer], NUM_LEDS, gHue, 7);
}

void rainbowWithGlitter() {
  // built-in FastLED rainbow, plus some random sparkly glitter
  rainbow();
  addGlitter(80);
}

void addGlitter( fract8 chanceOfGlitter) {
  if( random8() < chanceOfGlitter) {
    leds[currentBuzzer][ random16(NUM_LEDS) ] += CRGB::White;
  }
}

void confetti() {
  // random colored speckles that blink in and fade smoothly
  fadeToBlackBy( leds[currentBuzzer], NUM_LEDS, 10);
  int pos = random16(NUM_LEDS);
  leds[currentBuzzer][pos] += CHSV( gHue + random8(64), 200, 255);
}

void sinelon() {
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy( leds[currentBuzzer], NUM_LEDS, 20);
  int pos = beatsin16(13,0,NUM_LEDS);
  leds[currentBuzzer][pos] += CHSV( gHue, 255, 192);
}

void bpm() {
  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
  uint8_t BeatsPerMinute = 62;
  CRGBPalette16 palette = PartyColors_p;
  uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
  for( int i = 0; i < NUM_LEDS; i++) { //9948
    leds[currentBuzzer][i] = ColorFromPalette(palette, gHue+(i*2), beat-gHue+(i*10));
  }
}

void juggle() {
  // eight colored dots, weaving in and out of sync with each other
  fadeToBlackBy( leds[currentBuzzer], NUM_LEDS, 20);
  byte dothue = 0;
  for( int i = 0; i < 8; i++) {
    leds[currentBuzzer][beatsin16(i+7,0,NUM_LEDS)] |= CHSV(dothue, 200, 255);
    dothue += 32;
  }
}
