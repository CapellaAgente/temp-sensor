#include <Arduino.h>
#include <max6675.h>

const int sck = 10;
const int cs = 9;
const int so = 8;

MAX6675 ktc(sck, cs, so);

void setup() {
  Serial.begin(9600);
  delay(500);
}

void loop() {
  Serial.print("Temperatura: ");
  Serial.print(ktc.readCelsius());
  Serial.println(" *C");
  delay(500);
}