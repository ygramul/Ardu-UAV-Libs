#include <Kalman.h>

Kalman kalman;
double randNumber;

void setup() {
  kalman.init1D(0.0625, 4.0, 0.469725, 0.0);
  Serial.begin(115200);
  randomSeed(analogRead(0));
}

void loop() {
  randNumber = random(300);
  Serial.print(randNumber);
  Serial.print('\t');
  Serial.println(kalman.update1D(randNumber));
  delay(100);
}
