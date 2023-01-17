#include <FastLED.h>

#define LED_PIN 6
#define COLOR_ORDER RGB
#define CHIPSET WS2811
#define NUM_LEDS 100

#define BRIGHTNESS 255
#define FRAMES_PER_SECOND 60

CRGB leds[NUM_LEDS];

void setup() {
    delay(3000);
    FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness( BRIGHTNESS );
}


void loop()
{

    for( int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Purple;
        FastLED.show(); // display this frame
    }
    
    FastLED.delay(1000 / FRAMES_PER_SECOND);
}