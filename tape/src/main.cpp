#include <Arduino.h>

int s = 5;
int d = 150;

void setup() {
	for (int i = 0; i < 6; i++)
	{
		pinMode(2 + i, OUTPUT);
		digitalWrite(2 + i, LOW);
	}
	pinMode(8, INPUT);

	pinMode(9, INPUT_PULLUP);

	pinMode(12, OUTPUT);
	pinMode(13, OUTPUT);
	digitalWrite(12, LOW);
	digitalWrite(13, LOW);

	digitalWrite(s + 2, HIGH);
}

void doClock() {
	digitalWrite(12, HIGH);
	delay(d / 6);
	digitalWrite(13, HIGH);
	delay(d / 6);
	digitalWrite(13, LOW);
	delay(d / 6);
	digitalWrite(12, LOW);
	delay(d / 6);
}

void loop()
{
	if (digitalRead(9) == LOW || digitalRead(8) == HIGH) {
		doClock();

		digitalWrite(s + 2, LOW);
		delay(d / 6);

		s--;
		if (s < 0) {
			s = 5;
		} 
		digitalWrite(s + 2, HIGH);
		delay(d / 6);
	} else {
		// s = 5;
		digitalWrite(13, LOW);
		digitalWrite(12, LOW);
		// for (int i = 0; i < 6; i++)
		// {
		// 	digitalWrite(2 + i, LOW);
		// }
		
		// digitalWrite(s + 2, HIGH);
	}
	if (digitalRead(8) == LOW) {
		delay(500);
	}
}
