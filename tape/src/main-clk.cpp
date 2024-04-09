// #include <Arduino.h>

// int enablePin = 9;
// int writePin = 10;
// int readPin = 11;
// int clockPin = 12;

// void setup() {
// 	pinMode(enablePin, INPUT);
// 	pinMode(writePin, OUTPUT);
// 	pinMode(readPin, OUTPUT);
// 	pinMode(clockPin, OUTPUT);

// 	digitalWrite(writePin, LOW); // Write
// 	digitalWrite(readPin, LOW); // Read
// 	digitalWrite(clockPin, LOW); // Clock (move sequencer)
// }

// int d = 100; // 100 ms optimal, 80 ms min before unstable

// void doClock() {
// 	digitalWrite(readPin, HIGH);
// 	delay(d / 4);
// 	digitalWrite(writePin, HIGH);
// 	digitalWrite(clockPin, HIGH);
// 	delay(d / 4);
// 	digitalWrite(writePin, LOW);
// 	delay(d / 4);
// 	digitalWrite(readPin, LOW);
// 	digitalWrite(clockPin, LOW);
// 	delay(d / 4);
// }

// void loop()
// {
// 	if (digitalRead(enablePin) == HIGH) {
// 		doClock();
// 	}

// 	if (digitalRead(enablePin) == LOW) {
// 		delay(500);
// 	}
// }
