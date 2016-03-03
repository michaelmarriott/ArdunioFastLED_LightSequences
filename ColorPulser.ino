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
   ColorPulserWrapper();
}

void ColorPulserWrapper() {
	for (int i = 0; i < iterations; i++) {
		Serial.println(i, DEC);
		Serial.println("ColorPulserWrapper");
		ColorPulser(ChangeColor(), 1);
	}
}

void ColorPulser(CRGB color, uint8_t wait) {
	Serial.println("ColorPulser");
	random16_add_entropy(random()); 
	int trailOfPulse = random8(4, 12);
	int distanceApart = random8(5, 20);
	int amountOfPulses = random8(4, 25);

	int lengthOfLoop = NUM_LEDS_PER_STRIP + trailOfPulse + (distanceApart*amountOfPulses)
	for (int i = 0; i < lengthOfLoop; i++) {
		//Redraw the pulses
		for (int strip = 0; strip < NUM_STRIPS; strip++) {
			for (int x = 0; x < trailOfPulse; x++){
				for (int y = 0; y < amountOfPulses; y++){
					int item = ((i - x) - (distanceApart * y));
					if (item >= 0 && (item < NUM_LEDS_PER_STRIP)){
						leds[strip][item] = color;
						leds[strip][item].fadeToBlackBy(x * (int)(256 / trailOfPulse));
					}
				}
			}
		}
		//Show
		FastLED.show();
		delay(GetDelay());
		//Dim everything
		for (int strip = 0; strip < NUM_STRIPS; strip++) {
			for (int x = 0; x < trailOfPulse; x++){
				for (int y = 0; y < amountOfPulses; y++){
					int item = ((i - x) - (distanceApart * y));
					if (item >= 0 && (item < NUM_LEDS_PER_STRIP)){
						leds[strip][item].fadeToBlackBy(210);
					}
				}
			}		
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
