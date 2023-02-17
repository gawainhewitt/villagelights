// In this version connect the control pin of the serial board directly to ground. Using a pin to select wasn't working for some reason and is frankly not important

#include <FastLED.h>

#define LED_PIN 6
#define COLOR_ORDER GRB // GRB for WS2812, RGB for WS2811
#define CHIPSET WS2812 // remember to set this for the correct lights
#define NUM_LEDS 12

#define BRIGHTNESS 50 // 0-255
#define FRAMES_PER_SECOND 60

const unsigned int MAX_MESSAGE_LENGTH = 12;

CRGB leds[NUM_LEDS];

CRGB red = CRGB::Red;
CRGB green = CRGB::Green;
CRGB blue = CRGB::Blue;
CRGB ledColour = red;

void setup() {
    Serial.begin(9600); 
    Serial.println("started");
    FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness( BRIGHTNESS );
}


void loop(){

    //Check to see if anything is available in the serial receive buffer
    while (Serial.available() > 0)
    {
    //Create a place to hold the incoming message
    static char message[MAX_MESSAGE_LENGTH];
    static unsigned int message_pos = 0;

    //Read the next available byte in the serial receive buffer
    char inByte = Serial.read();

    //Message coming in (check not terminating character) and guard for over message size
    if ( inByte != '\n' && (message_pos < MAX_MESSAGE_LENGTH - 1) )
    {
        //Add the incoming byte to our message
        message[message_pos] = inByte;
        message_pos++;
    }
    //Full message received...
    else
    {
        //Add null character to string
        message[message_pos] = '\0';

        //Print the message (or do other things)

        Serial.println(message);

        int lightControl = atoi(message);

        showLights(lightControl);


        //Reset for the next message
        message_pos = 0;
    }
    }
}

void showLights(int lightControl){
    Serial.println("banana");
    Serial.println(lightControl);
    if (lightControl == 0) {
            ledColour = green;
        } else if (lightControl == 1) {
            ledColour = red;
        } else if (lightControl == 98) {
            ledColour = blue;
        }

        for( int i = 0; i < NUM_LEDS; i++) {
            leds[i] = ledColour;
        }
        
        FastLED.show(); // display this frame
        FastLED.delay(1000 / FRAMES_PER_SECOND);
}

