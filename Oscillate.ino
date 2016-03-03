#include "FastLED.h"
#define NUM_STRIPS 4
#define NUM_LEDS_PER_STRIP 150

CRGB leds[NUM_STRIPS][NUM_LEDS_PER_STRIP];
uint16_t iterations = 40;
uint16_t delayOfTranistions = 0;

void setup() {
  delay(1000);//Safe Gaurd
  Serial.begin(9600);
  Serial.println("It has begun...");
  FastLED.addLeds<WS2812, 4, GRB>(leds[0], NUM_LEDS_PER_STRIP); 
  FastLED.addLeds<WS2812, 5, GRB>(leds[1], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<WS2812, 6, GRB>(leds[2], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<WS2812, 7, GRB>(leds[3], NUM_LEDS_PER_STRIP);
}

void loop()
{
   Serial.println("loop");
   OscialateWrapper();
}

void OscialateWrapper() {
  Serial.println("OscialateWrapper");
  int middle = NUM_LEDS_PER_STRIP / 2;
  ResetAll();
  FastLED.show(); // display this frame
  delay(GetDelay());

  for (int y = 0; y < iterations; y++) {
		Serial.println("Oscialate");
		Oscialate(middle);
  }
}

void Oscialate(int middle) {
	CRGB wcolor = CRGB::WhiteSmoke;
	int lengthOfOscilation = random8(16, middle - 1); 
    
	//Got Out
    CRGB color = ChangeColor();
    for (int z = 0; z < lengthOfOscilation; z++) {
      for (int i = 0; i < NUM_STRIPS; i++) {
		  leds[i][middle - z] = wcolor;
		  leds[i][middle + z] = wcolor;
      }
      FastLED.show(); // display this frame
	  delay(GetDelay());
      for (int i = 0; i < NUM_STRIPS; i++) {
        leds[i][middle - z] = color;
		leds[i][middle + z] = color;
      }
    }

    //Go In
    for (int z = lengthOfOscilation; z > 0; z--) {
      for (int i = 0; i < NUM_STRIPS; i++) {
		  leds[i][middle - z] = wcolor;
		  leds[i][middle + z] = wcolor;
      }
      FastLED.show(); // display this frame
	  FastLED.delay(GetDelay());
      for (int i = 0; i < NUM_STRIPS; i++) {
		  leds[i][middle - z] = color;
		  leds[i][middle + z] = color;
      }
    }
}

uint16_t GetDelay() {
	return delayOfTranistions;
}

CRGB ChangeColor(){
	random16_add_entropy(random());
	return CRGB(random8(), random8(), random8());
}

void ResetAll(){
 for (int x = 0; x < NUM_STRIPS; x++) {
    for (int y = 0; y < NUM_LEDS_PER_STRIP; y++) {
      leds[x][y] = CRGB::Black;
    }
  }
}
