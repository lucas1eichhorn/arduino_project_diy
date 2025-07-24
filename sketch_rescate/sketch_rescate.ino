void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  // Inicia Serial con tiempo límite de espera
  Serial.begin(9600);
  unsigned long start = millis();
  while (!Serial && millis() - start < 3000); // Espera máx. 3s

  Serial.println("✅ Arduino R4 Minima funcionando.");
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println("💡 LED encendido");
  delay(500);
  digitalWrite(LED_BUILTIN, LOW);
  Serial.println("💤 LED apagado");
  delay(500);
}
