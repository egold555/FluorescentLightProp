#include <FastLED.h>

#define NUM_LEDS 70

#define PIN_STRIP_1 10
#define PIN_STRIP_2 11
#define PIN_RELAY 3

CRGB leds1[NUM_LEDS];
CRGB leds2[NUM_LEDS];

#define STRIP_TYPE WS2812
#define STRIP_COLOR_ORDER GRB

void setup()
{

    LEDS.addLeds<STRIP_TYPE, PIN_STRIP_1, STRIP_COLOR_ORDER>(leds1, NUM_LEDS);
    LEDS.addLeds<STRIP_TYPE, PIN_STRIP_2, STRIP_COLOR_ORDER>(leds2, NUM_LEDS);

    //set the strip to green so we know we have booted, and waiting for the plasma ball power up stage (see below)
    //setLedStripColor(0, 255, 0);
    //FastLED.setBrightness(128);
    FastLED.setBrightness(255);

    pinMode(PIN_RELAY, OUTPUT);
    //Random seed
    randomSeed(analogRead(0));
}

void loop()
{

    if (randomBool())
    {
        loop_flicker_test_2(leds1);
    }

    if (randomBool())
    {
        loop_flicker_test_2(leds2);
    }

    //rainbowTest();
    //orangeSpark();
}

uint8_t hue = 0;
uint8_t hue2 = 128;
void rainbowTest()
{
    //FastLED.setBrightness(128);
    fill_rainbow(leds1, NUM_LEDS, hue, 10);
    fill_rainbow(leds2, NUM_LEDS, hue2, 10);
    FastLED.show();

    hue++;
    hue2++;

    if (hue > 255)
    {
        hue = 0;
    }

    if (hue2 > 255)
    {
        hue2 = 0;
    }
}

void fill(CRGB *leds, uint8_t r, uint8_t g, uint8_t b, int start, int end)
{
    for (int i = start; i < end; i++)
    {
        leds[i] = CRGB(r, g, b);
    }
    FastLED.show();
}

void fill(CRGB *leds, uint8_t r, uint8_t g, uint8_t b)
{
    fill(leds, r, g, b, 0, NUM_LEDS);
}

const int delayTimeArr[] = {10, 20, 20, 240, 20, 40, 20, 100, 20, 20, 20, 260, 80, 20, 240, 60, 160, 20, 240, 20, 1000, 20, 20, 40, 100, 20, 2740, 340, 860, 20, 1400, 20, 60, 20};
const int arrSize = *(&delayTimeArr + 1) - delayTimeArr;
int whereAmI = 0;
void loop_flicker_test_2(CRGB *leds)
{

    fill(leds, 255, 147, 41);
    toggleRelay();
    delay(delayTimeArr[whereAmI]);
    fill(leds, 0, 0, 0);
    toggleRelay();

    whereAmI++;
    if (whereAmI > arrSize)
    {
        whereAmI = 0;
        place_start(leds);
        delay(3000);
    }

    delay(delayTimeArr[whereAmI]);
}

void place_start(CRGB *leds)
{
    //FastLED.setBrightness(20);
    fill(leds, 135, 53, 1, 0, 10);
    fill(leds, 135, 53, 1, NUM_LEDS - 10, NUM_LEDS);
    //FastLED.setBrightness(255);
}

void toggleRelay()
{
    digitalWrite(PIN_RELAY, !digitalRead(PIN_RELAY));
}

bool randomBool()
{
    return (random(2) == 1);
}