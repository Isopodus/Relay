#include <Arduino.h>

#define IN_LEFT A0
#define IN_RIGHT A1
#define OUT_LEFT 5
#define OUT_RIGHT 6

void setup()
{
	pinMode(IN_LEFT, INPUT);
	pinMode(IN_RIGHT, INPUT);
	pinMode(OUT_LEFT, OUTPUT);
	pinMode(OUT_RIGHT, OUTPUT);
	pinMode(13, OUTPUT);
	pinMode(2, INPUT_PULLUP);

	analogWrite(OUT_LEFT, 0);
	analogWrite(OUT_RIGHT, 0);
	digitalWrite(13, 0);

	// TCCR0B = 0b00000010; // x8
	// TCCR0A = 0b00000011; // phase correct

	Serial.begin(9600);
}

void writeByte(byte data)
{
	for (byte i = 0; i < 8; i++)
	{
		bool bit = data >> i & 0b00000001;

		analogWrite(OUT_RIGHT, 128 * !bit);
		analogWrite(OUT_LEFT, 128 * bit);
		delay(20);
		analogWrite(OUT_RIGHT, 0);
		analogWrite(OUT_LEFT, 0);
		delay(20);
	}
}

byte getWord(bool b[8])
{
	byte number = 0;
	for (int i = 0; i < 8; i++)
	{
		number += b[i] ? pow(2, i) : 0;
	}
	return number;
}

int onesCount = 0;
int zerosCount = 0;
bool bitDone = false;
int bitsCount = 0;
byte res = 0;

double avgCount = 30; // Last N readings

void loop()
{
	if (digitalRead(2) == HIGH)
	{
		double avgL = 0;
		double avgR = 0;
		double rmsL = 0;
		double rmsR = 0;
		for (int i = 0; i < avgCount; i++)
		{
			double left = analogRead(IN_LEFT);
			double right = analogRead(IN_RIGHT);
			avgL += left;
			avgR += right;
			rmsL += left * left;
			rmsR += right * right;
		}
		avgL /= avgCount;
		avgR /= avgCount;
		rmsL = sqrt(rmsL / avgCount);
		rmsR = sqrt(rmsR / avgCount);

		// Serial.print(avgL);
		// Serial.print(' ');
		// Serial.print(avgR);
		// Serial.print(' ');
		// Serial.print(rmsL);
		// Serial.print(' ');
		// Serial.print(rmsR);
		// Serial.print(' ');
		// Serial.print(rmsL - avgL > 5);
		// Serial.print(' ');
		// Serial.println(rmsR - avgR > 5);

		bool left = rmsL - avgL > 5;
		bool right = rmsR - avgR > 5;

		bool bit, clockLow = false;
		if (right)
		{
			bit = false;
		}
		else if (left)
		{
			bit = true;
		}
		else
		{
			clockLow = true;
		}

		if (!clockLow && !bitDone)
		{
			if (bit)
			{
				res += 1 << bitsCount;
			}

			bitsCount++;
			bitDone = true;

			// Serial.print(bit);
		} else if (clockLow) {
			bitDone = false;
		}

		if (bitsCount >= 8)
		{
			bitsCount = 0;
			// Serial.print('\t');
			Serial.print((char) res);
			// Serial.println();
			res = 0;
		}
	}
	else
	{
		char *data = "iVBORw0KGgoAAAANSUhEUgAAACAAAAAgCAYAAABzenr0AAAABHNCSVQICAgIfAhkiAAAAUhJREFUWIXtljGOwjAQRT+rLRLOEiklkVzQuOAKnCFtJJfxJbhAGkp3KIVrIF1G4i5JEWm2ht3EQ4QWivz6j+d5bM94xcyMN+rrnckXgAVgAQCA75CBiFDXNQBgt9shTdOgN+S7E0+obVvWWjMABsBlWY56m6bhJEmCvkdNHkHXdTifz6KNnE4n3G432a6lFWBmvl6vbIxhYwy3bTtZLaUUr9drvlwu4gqsmF83C4gIfd9js9mIY14KMEdvf4YLwALwuQBEBCKavbA0fhTAOYeiKGZBEBGKooBzLmwOtVat9WQL/itOa81KKVFccBo+A/FscmbBLCAi5HmOOI6htQYAbLdbZFn2y2uthfceh8NB/B8QzQIiwvF4BAAMw4CqqpDnOaIouvN576GUgrVWlFwM8KimaUYv2H6/l/+G5gK8Up/biBaA/9IPm+g5oa1lo2MAAAAASUVORK5CYII=";

		for (int i = 0; i < 536; i++)
		{
			writeByte(data[i]);
		}

		// writeByte(9);
		// writeByte(9);  // 10010000
		// writeByte(37); // 10100100
		// writeByte(12); // 00110000
		// writeByte(45); // 10110100

		// analogWrite(OUT_LEFT, 128);
		// delay(1000);
		// analogWrite(OUT_LEFT, 0);
		// delay(1000);
		// analogWrite(OUT_RIGHT, 128);
		// delay(1000);
		// analogWrite(OUT_RIGHT, 0);
		// delay(1000);

		digitalWrite(13, 1);
		delay(10000);
	}
}