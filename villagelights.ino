// In this version connect the control pin of the serial board directly to ground. Using a pin to select wasn't working for some reason and is frankly not important

#include <FastLED.h>

#define LED_PIN1 6
#define LED_PIN2 7
#define LED_PIN3 8
#define LED_PIN4 9
#define COLOR_ORDER GRB // GRB for WS2812, RGB for WS2811
#define CHIPSET WS2812 // remember to set this for the correct lights
#define NUM_LEDS 12

#define BRIGHTNESS 50 // 0-255
#define FRAMES_PER_SECOND 20

const unsigned int MAX_MESSAGE_LENGTH = 12;

CRGB leds1[NUM_LEDS];
CRGB leds2[NUM_LEDS];
CRGB leds3[NUM_LEDS];
CRGB leds4[NUM_LEDS];

CHSV red = CHSV(0, 255, 127);
CHSV green = CHSV(80,255, 127);
CHSV blue = CHSV(160, 255, 127);
CHSV orange = CHSV(32, 255, 127);
CHSV pink = CHSV(224, 255, 127);
CHSV yellow = CHSV(64, 255, 127);

CHSV ledColour1 = red;
CHSV ledColour2 = blue;
CHSV ledColour3 = orange;
CHSV ledColour4 = yellow;

void setup() {
    Serial.begin(9600); 
    Serial.println("started");
    FastLED.addLeds<CHIPSET, LED_PIN1, COLOR_ORDER>(leds1, NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.addLeds<CHIPSET, LED_PIN2, COLOR_ORDER>(leds2, NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.addLeds<CHIPSET, LED_PIN3, COLOR_ORDER>(leds3, NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.addLeds<CHIPSET, LED_PIN4, COLOR_ORDER>(leds4, NUM_LEDS).setCorrection( TypicalLEDStrip );

    FastLED.setBrightness( BRIGHTNESS );
}


void loop(){

    unsigned int sineTest = sin8(2);
    Serial.println(sineTest);

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
        return;
    }
    }

        showLights(-1);

}

void showLights(int lightControl){
    Serial.println("banana");
    Serial.println(lightControl);
    if (lightControl == 0) {
            ledColour1 = green;
            ledColour2 = blue;
            ledColour3 = red;
            ledColour4 = pink;
        } else if (lightControl == 1) {
            ledColour2 = green;
            ledColour3 = blue;
            ledColour4 = red;
            ledColour1 = pink;
        } else if (lightControl == 2) {
            ledColour3 = green;
            ledColour4 = blue;
            ledColour1 = red;
            ledColour2 = pink;
        }

        int dark = 50;
        int bright = 255;

        for( int i = 0; i < NUM_LEDS; i++) {
            // ledColour1.s = random(150, 255);
            ledColour1.v = random(dark, bright);
            leds1[i] = ledColour1;
            ledColour2.v = random(dark, bright);
            leds2[i] = ledColour2;
            ledColour3.v = random(dark, bright);
            leds3[i] = ledColour3;
            ledColour4.v = random(dark, bright);
            leds4[i] = ledColour4;
        }
        
        FastLED.show(); // display this frame
        FastLED.delay(1000 / FRAMES_PER_SECOND); 
}

