#include <Arduino.h>

int dataStart = 2;
int addrPin = 10;
int ramPin = 11;

void setOutput(byte value) {
	for (int j = 0; j < 8; j++) {
		digitalWrite(dataStart + j, (value >> j) & 1);
	}
}

void setup() {
	Serial.begin(115200);

	// Define data output pins
	for (byte i = dataStart; i < dataStart + 8; i++)
	{
		pinMode(i, OUTPUT);
		digitalWrite(i, LOW);
	}
	
	// Define control pins
	pinMode(addrPin, OUTPUT);
	pinMode(ramPin, OUTPUT);

	digitalWrite(addrPin, LOW);
	digitalWrite(ramPin, LOW);

	setOutput(0);
}
unsigned long lastReceivedTime = 0;
const unsigned long RESET_TIMEOUT = 2000;
int addr = 0;
bool reading = false;

void loop()
{
	if (Serial.available() > 0) {
		if (!reading) { 
			digitalWrite(addrPin, HIGH);
			digitalWrite(ramPin, HIGH);
			delay(100);
			digitalWrite(addrPin, LOW);
			digitalWrite(ramPin, LOW);
			delay(20);
		}

		reading = true;
    	lastReceivedTime = millis();
		byte data = Serial.read();
		// digitalWrite(ramPin, HIGH);

		// Set the address register
		setOutput(addr);
		delay(20);
		digitalWrite(addrPin, HIGH);
		delay(20);
		digitalWrite(addrPin, LOW);
		delay(20);

		// Convert each hex value to binary and set corresponding pins as output
		setOutput(data);
		delay(20);
		digitalWrite(ramPin, HIGH);
		delay(20);
		digitalWrite(ramPin, LOW);
		delay(20);
		setOutput(0);
		// delay(20);

		addr++;
		Serial.write(1);
	} else if (millis() - lastReceivedTime > RESET_TIMEOUT && reading) {
		// Serial.flush();
		// digitalWrite(ramPin, LOW);
		reading = false;
		addr = 0;
	}
}
