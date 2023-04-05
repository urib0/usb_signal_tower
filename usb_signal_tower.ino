#include <Adafruit_NeoPixel.h>

#define PIN 7
#define NUMPIXELS 3
#define STATUS_OK 0
#define VERSION "1.00"

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 300

void setup()
{
	Serial.begin(9600);
	pixels.begin();
	while (!Serial)
		delay(1);
}

void loop()
{
	static unsigned char visible_state[NUMPIXELS] = {0};

	pixels.clear();
	pixels.show();
	delay(DELAYVAL);

	for (int i = 0; i < NUMPIXELS; i++)
	{

		pixels.setPixelColor(i, pixels.Color(5, 5, 5));

		pixels.show();

		delay(DELAYVAL);
	}

	// serial feedback output
	Serial.print("leds=" + String(NUMPIXELS) + ";");
	for (int i = 0; i < NUMPIXELS; i++)
	{
		Serial.print(String(i + 1) + "=" + String(visible_state[i]) + ";");
	}
	Serial.print(";status=" + String(STATUS_OK) + ";VERSIONS=" + String(VERSION) + "\n");
}
