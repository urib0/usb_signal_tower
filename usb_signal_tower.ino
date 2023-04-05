#include <Adafruit_NeoPixel.h>

#define PIN 7

#define NUMPIXELS 3

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 300

void setup()
{
	pixels.begin();
}

void loop()
{
	pixels.clear();
	pixels.show();
	delay(DELAYVAL);

	for (int i = 0; i < NUMPIXELS; i++)
	{

		pixels.setPixelColor(i, pixels.Color(5, 5, 5));

		pixels.show();

		delay(DELAYVAL);
	}
}
