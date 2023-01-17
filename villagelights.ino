#include <FastLED.h>

#define LED_PIN 6
#define COLOR_ORDER RGB
#define CHIPSET WS2811
#define NUM_LEDS 100

#define BRIGHTNESS 255
#define FRAMES_PER_SECOND 60

CRGB leds[NUM_LEDS];

int incomingByte = 0; // for incoming serial data
CRGB red = CRGB::Red;
CRGB green = CRGB::Green;
CRGB blue = CRGB::Blue;
CRGB ledColour = red;

void setup() {
    delay(3000);
    Serial.begin(57600); 
    FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness( BRIGHTNESS );
}


void loop()
{

    if (Serial.available() > 0) {
        // read the incoming byte:
        incomingByte = Serial.read();

        // prints the received data
        Serial.print("I received: ");
        Serial.println(incomingByte);
    }

    if (incomingByte == 103) {
        ledColour = green;
    } else if (incomingByte == 114) {
        ledColour = red;
    } else if (incomingByte == 98) {
        ledColour = blue;
    }

    for( int i = 0; i < NUM_LEDS; i++) {
        leds[i] = ledColour;
        FastLED.show(); // display this frame
    }
    
    FastLED.delay(1000 / FRAMES_PER_SECOND);
}