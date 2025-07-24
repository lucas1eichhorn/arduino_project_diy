#define NUM_SENSORS 4
const int SIGNAL_PINS[NUM_SENSORS] = {A1, A2, A3, A4};
const int RELAY_PINS[NUM_SENSORS]  = {2, 3, 4, 5};
const char* SENSOR_ID[NUM_SENSORS] = {"1", "2", "3","4"};

// Stores the last watering time for each sensor
unsigned long lastWateringTime[NUM_SENSORS] = {0, 0, 0, 0};

void setup() {
  Serial.begin(9600);
  unsigned long start = millis();
  while (!Serial && millis() - start < 3000); // Wait max. 3s for Serial to initialize

  for (int i = 0; i < NUM_SENSORS; i++) {
    pinMode(RELAY_PINS[i], OUTPUT);
    digitalWrite(RELAY_PINS[i], HIGH); // Ensure relay is OFF at startup (HIGH = OFF)
  }

  Serial.println("✅ Arduino R4 Minima running.");
}

void loop() {
  for (int i = 0; i < NUM_SENSORS; i++) {
    int value = read_humidity(i);
    check_and_water(i, value);
     delay(3000); // Water for 3 seconds (adjustable)
  }

  delay(5000); // Run the loop every N second
}

int read_humidity(int sensor_num) {
  int pin = SIGNAL_PINS[sensor_num];
  int value = analogRead(pin);

  Serial.print("Sensor ");
  Serial.print(SENSOR_ID[sensor_num]);
  Serial.print(" → humidity = ");
  Serial.println(value);
  return value;
}

void check_and_water(int sensor_num, int value) {
  unsigned long now = millis();

  if (value < 10) {
    Serial.println("⚠️  Reading error.");
    digitalWrite(RELAY_PINS[sensor_num], HIGH); // Turn relay OFF for safety
    return;
  }

  if (value > 400) { // Sensor reads dry soil
      Serial.print("🌵 Sensor ");
      Serial.print(SENSOR_ID[sensor_num]);
      Serial.println(" is dry → watering now.");
      water_once(sensor_num);
      lastWateringTime[sensor_num] = now;
  } else {
    Serial.print("💧 Sensor ");
    Serial.print(SENSOR_ID[sensor_num]);
    Serial.println(" is wet → no watering needed.");
    digitalWrite(RELAY_PINS[sensor_num], HIGH); // OFF
  }
}

void water_once(int sensor_num) {
  digitalWrite(RELAY_PINS[sensor_num], LOW);  // ON
  delay(2000); // Water for 3 seconds (adjustable)
  digitalWrite(RELAY_PINS[sensor_num], HIGH); // OFF
}
