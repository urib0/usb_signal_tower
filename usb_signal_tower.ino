#include <Adafruit_NeoPixel.h>

#define PIN 7
#define NUMPIXELS 3
#define STATUS_OK 0
#define VERSION "1.00"

static char sc_colors[NUMPIXELS][3] = {
	{50, 0, 0},
	{60, 60, 0},
	{0, 60, 0}};

static char sc_colors_weak[NUMPIXELS][3] = {
	{15, 0, 0},
	{20, 20, 0},
	{0, 20, 0}};

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 1000

void setup()
{
	Serial.begin(9600);
	pixels.begin();
	while (!Serial)
		delay(1);

	pixels.clear();
	pixels.show();
}

void loop()
{
	static unsigned char visible_state[NUMPIXELS] = {0};
	unsigned char uc_visible_tmp[NUMPIXELS] = {0};
	unsigned char tmp = 0;
	unsigned char recv_cnt = 0;
	static unsigned int interval_cnt = 0;

	// check input
	while (Serial.available() > 0)
	{
		tmp = Serial.read();
		Serial.print(tmp);
		if ((tmp == '0') || tmp == '1')
		{
			uc_visible_tmp[recv_cnt] = tmp - '0';
			recv_cnt++;
		}
		else
		{
			break;
		}
	}
	if (recv_cnt == NUMPIXELS)
	{
		for (int i = 0; i < NUMPIXELS; i++)
		{
			visible_state[i] = uc_visible_tmp[i];
		}
	}

	// neopixles output
	for (int i = 0; i < NUMPIXELS; i++)
	{
		if (visible_state[i] == 1)
		{
			pixels.setPixelColor(i, pixels.Color(sc_colors[i][0], sc_colors[i][1], sc_colors[i][2]));
		}
		else
		{
			pixels.setPixelColor(i, pixels.Color(sc_colors_weak[i][0], sc_colors_weak[i][1], sc_colors_weak[i][2]));
		}
	}
	pixels.show();

	if (interval_cnt >= DELAYVAL)
	{
		interval_cnt = 0;
		// serial feedback output
		Serial.print("leds=" + String(NUMPIXELS) + ";");
		for (int i = 0; i < NUMPIXELS; i++)
		{
			Serial.print(String(i + 1) + "=" + String(visible_state[i]) + ";");
		}
		Serial.print(";status=" + String(STATUS_OK) + ";VERSIONS=" + String(VERSION) + "\n");
	}
	interval_cnt++;
	delay(1);
}
