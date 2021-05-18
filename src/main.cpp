#include <Arduino.h>
#include <FastLED.h>
#include <EEPROM.h>

#define LED_PIN PB0

CRGB leds[3];

int patternIndex;
const int numPatterns = 4;

CRGB cols[] = {
    CRGB::Red,
    CRGB::Green,
    CRGB::Blue
};

void hueCycle();
void pulseHueCycle();
void pulsePurple();
void pulseBlue();
void (*patternFuncs[])() = {hueCycle, pulseHueCycle, pulsePurple, pulseBlue };

void setup()
{
    FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, 3).setCorrection( TypicalLEDStrip );
    FastLED.showColor(CRGB::Black);
    //FastLED

    delay(500);
    
    EEPROM.get(0,patternIndex);
    if(patternIndex>=numPatterns){
        patternIndex = 0;
    }
    EEPROM.put(0,patternIndex+1);
    
}

void loop()
{
    patternFuncs[patternIndex]();
    delay(30);
    
}

uint16_t gHue;
uint16_t t;

void hueCycle()
{

    gHue += 128;
    CHSV hsv( gHue>>8, 255, 255); // pure blue in HSV Rainbow space
    CRGB rgb;
    hsv2rgb_rainbow( hsv, rgb);
    FastLED.showColor(rgb);
}

void pulsePurple()
{
    CRGB rgb(255,20,255);
    rgb.fadeToBlackBy(sin8(t>>8));
    t+=512;
    FastLED.showColor(rgb);
}

void pulseBlue()
{
    CRGB rgb(255,255,20);
    rgb.fadeToBlackBy(sin8(t>>8));
    t+=512;
    FastLED.showColor(rgb);
}

void pulseHueCycle()
{

    gHue += 33;
    t+=512;
    CHSV hsv( gHue>>8, 255, sin8(t>>8)); // pure blue in HSV Rainbow space
    CRGB rgb;
    hsv2rgb_rainbow( hsv, rgb);
    FastLED.showColor(rgb);
}