const int raindropPin = A0; // Analog pin connected to the raindrop sensor
int buzzer = 8; 

// Notas musicales (frecuencia en Hz)
#define NOTE_C4  262
#define NOTE_D4  294
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_G4  392
#define NOTE_A4  440
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_D5  587
#define NOTE_E5  659
#define NOTE_G5  784
#define NOTE_AS4 466

void setup() {
  Serial.begin(9600);
  unsigned long start = millis();
  while (!Serial && millis() - start < 3000); // Espera máx. 3s
  pinMode(buzzer, OUTPUT);  // define buzzer output
  Serial.println("✅ Arduino R4 Minima funcionando.");
  
}

void loop() {
  int raindropValue = analogRead(raindropPin); // Read analog value from the sensor
  Serial.print("Raindrop Value: ");
  Serial.println(raindropValue); // Print the value to the serial monitor
  if (raindropValue > 800) {
    Serial.println("🌞 Sensor seco");
    digitalWrite(buzzer, LOW);
} else if (raindropValue > 400) {
    Serial.println("🌦️ Sensor húmedo");
    playBirthdaySong();
    //digitalWrite(buzzer, HIGH); //Make a sound
    //delay(500);
    //digitalWrite(buzzer, LOW);
    //delay(500);
    //digitalWrite(buzzer, HIGH); //Make a sound
    //delay(500);
    //digitalWrite(buzzer, LOW);
} else {
    Serial.println("🌧️ Lluvia detectada");
    playBirthdaySong();
    //digitalWrite(buzzer, HIGH); //Make a sound
    //digitalWrite(buzzer, HIGH); //Make a sound
    //delay(200);
    //digitalWrite(buzzer, LOW);
    //delay(200);
    //digitalWrite(buzzer, HIGH); //Make a sound
    //delay(200);
    //digitalWrite(buzzer, LOW);
}
  delay(1000); // Delay for stability
}

void playMelody() {
  // Melodía: DO – RE – MI – RE – DO
  tone(buzzer, NOTE_C4, 200);
  delay(250);
  tone(buzzer, NOTE_D4, 200);
  delay(250);
  tone(buzzer, NOTE_E4, 300);
  delay(350);
  tone(buzzer, NOTE_D4, 200);
  delay(250);
  tone(buzzer, NOTE_C4, 400);
  delay(450);
  noTone(buzzer);
}

void playTone(int note, int duration) {
  if (note == 0) {
    noTone(buzzer);
    delay(duration);
  } else {
    tone(buzzer, note, duration);
    delay(duration * 1.1); // pequeña pausa entre notas
  }
}

void playCucaracha() {
  // 🎵 “La cucaracha, la cucaracha, ya no puede caminar…”
  playTone(NOTE_G4, 300);
  playTone(NOTE_G4, 300);
  playTone(NOTE_G4, 300);
  playTone(NOTE_E4, 300);
  playTone(NOTE_C4, 600);

  playTone(NOTE_G4, 300);
  playTone(NOTE_G4, 300);
  playTone(NOTE_G4, 300);
  playTone(NOTE_E4, 300);
  playTone(NOTE_C4, 600);

  playTone(NOTE_E4, 300);
  playTone(NOTE_F4, 300);
  playTone(NOTE_G4, 300);
  playTone(NOTE_G4, 300);
  playTone(NOTE_F4, 300);
  playTone(NOTE_E4, 300);
  playTone(NOTE_D4, 300);
  playTone(NOTE_C4, 600);
}

void playBirthdaySong() {
  // 🎶 Cumpleaños Feliz
  playTone(NOTE_C4, 300);
  playTone(NOTE_C4, 300);
  playTone(NOTE_D4, 600);
  playTone(NOTE_C4, 600);
  playTone(NOTE_F4, 600);
  playTone(NOTE_E4, 800);

  // 🎶 Te deseamos a ti
  playTone(NOTE_C4, 300);
  playTone(NOTE_C4, 300);
  playTone(NOTE_D4, 600);
  playTone(NOTE_C4, 600);
  playTone(NOTE_G4, 600);
  playTone(NOTE_F4, 800);

  // 🎶 Feliz cumpleaños [nombre]
  playTone(NOTE_C4, 300);
  playTone(NOTE_C4, 300);
  playTone(NOTE_C5, 600);
  playTone(NOTE_A4, 600);
  playTone(NOTE_F4, 600);
  playTone(NOTE_E4, 600);
  playTone(NOTE_D4, 800);

  // 🎶 Que los cumplas feliz
  playTone(NOTE_AS4, 300);  // La sostenido
  playTone(NOTE_AS4, 300);
  playTone(NOTE_A4, 600);
  playTone(NOTE_F4, 600);
  playTone(NOTE_G4, 600);
  playTone(NOTE_F4, 800);

  noTone(buzzer); // Apagar buzzer
}