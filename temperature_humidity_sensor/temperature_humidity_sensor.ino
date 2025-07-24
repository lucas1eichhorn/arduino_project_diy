#include "DHT.h"

#define DHT11_PIN 2
DHT dht11(DHT11_PIN, DHT11);

void setup() {
  Serial.begin(9600);
  unsigned long start = millis();
  while (!Serial && millis() - start < 3000); // máximo 3 segundos de espera
  dht11.begin();

  Serial.println("DHT11 sensor iniciado.");
}

void loop() {
  delay(2000);  // DHT11 necesita mínimo 1 segundo entre lecturas

  float humi  = dht11.readHumidity();
  float tempC = dht11.readTemperature();
  float tempF = dht11.readTemperature(true);

  if (isnan(humi) || isnan(tempC) || isnan(tempF)) {
    Serial.println("Error: No se pudo leer del sensor DHT11.");
    return;  // Sal del loop sin hacer nada más
  }

  Serial.print("💧 Humedad: ");
  Serial.print(humi);
  Serial.print("%\t Temperatura: ");
  Serial.print(tempC);
  Serial.print("°C / ");
  Serial.print(tempF);
  Serial.println("°F");
}