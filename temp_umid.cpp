#include <Arduino.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <DHT.h>

#define DHTTYPE DHT11

Adafruit_SSD1306 display(128, 64, &Wire, -1);

const int dht11_pino = 2;
DHT dht(dht11_pino, DHTTYPE);

const int led_vermelho = 8;
const int led_amarelo = 9;
const int led_verde = 10;


void setup() {
  Serial.begin(9600);
  //LEDs
  pinMode(led_vermelho, OUTPUT);
  pinMode(led_amarelo, OUTPUT);
  pinMode(led_verde, OUTPUT);
  //Display
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 28);
  display.print("Aguarde...");
  display.display();
  display.clearDisplay();  
  //sensor
  dht.begin();
}

void loop() {
  //Mensagem de Inicialização 
  delay(3000);
  //Leitura do sensor
  dht.read(dht11_pino);
  float temp = dht.readTemperature();
  float umid = dht.readHumidity();
  //Configurações - temperatura
  display.setTextSize(1);
  display.setTextColor(WHITE, BLACK);
  display.setCursor(0, 16);
  display.print("Temperatura: ");
  display.print(temp, 0);
  display.print(" *C");
  display.display();
  //Confirgurações - umidade
  display.setTextSize(1);
  display.setTextColor(WHITE, BLACK);
  display.setCursor(0, 32);
  display.print("Umidade: ");
  display.print(umid, 0);
  display.print(" %");
  display.display();
  //Condições - LEDs
  if (umid <= 30) {
    digitalWrite(led_vermelho, HIGH);
    digitalWrite(led_amarelo, LOW);
    digitalWrite(led_verde, LOW);
  }
  else if (umid > 30 and umid < 50) {
    digitalWrite(led_amarelo, HIGH);
    digitalWrite(led_vermelho, LOW);
    digitalWrite(led_verde, LOW);
  }
  else if (umid >= 50) {
    digitalWrite(led_verde, HIGH);
    digitalWrite(led_amarelo, LOW);
    digitalWrite(led_vermelho, LOW);
  }

  Serial.print(temp, 0);
  Serial.print(",");
  Serial.println(umid, 0);
}