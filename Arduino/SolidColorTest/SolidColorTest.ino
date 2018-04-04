#include <FastLED.h>

#define DATA_PIN_1    12
//#define DATA_PIN_1    27
#define DATA_PIN_2    18
#define NUM_LEDS    200
#define BRIGHTNESS  64
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
CRGB leds1[NUM_LEDS];
CRGB leds2[NUM_LEDS];
int ledPin = 4;



void setup() {

    pinMode(ledPin, OUTPUT);
    delay( 1000 ); // power-up safety delay
    FastLED.addLeds<LED_TYPE, DATA_PIN_1, COLOR_ORDER>(leds1, NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.addLeds<LED_TYPE, DATA_PIN_2, COLOR_ORDER>(leds2, NUM_LEDS).setCorrection( TypicalLEDStrip );
  
    //FastLED.setBrightness(  BRIGHTNESS );
    FastLED.setMaxPowerInVoltsAndMilliamps (5, 2000);
    
    fill_solid(leds1,NUM_LEDS, CRGB::White);
    fill_solid(leds2,NUM_LEDS, CRGB::White);
    FastLED.show();

    FastLED.setDither( 0 );

    digitalWrite(ledPin, HIGH); 
    
}


void loop()
{
   fill_solid(leds1,NUM_LEDS, CRGB::White);
   fill_solid(leds2,NUM_LEDS, CRGB::White);
   FastLED.show();
}
