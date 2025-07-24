#include <SoftwareSerial.h>

SoftwareSerial espSerial(2, 3);  // RX, TX
#define ESP_RESET_PIN 4

const char* ssid = "ssid";
const char* password = "pass";

const char* host = "api.chucknorris.io";
const char* path = "/jokes/random";
const int port = 80;

unsigned long intervalo = 10000;
unsigned long tiempoAnterior = 0;

void resetESP8266() {
  pinMode(ESP_RESET_PIN, OUTPUT);
  digitalWrite(ESP_RESET_PIN, LOW);
  delay(200);
  digitalWrite(ESP_RESET_PIN, HIGH);
  delay(1000);
}

void enviarComando(String cmd, int esperar = 2000) {
  espSerial.println(cmd);
  delay(esperar);
  while (espSerial.available()) {
    char c = espSerial.read();
    Serial.write(c);
  }
}

bool conectarWiFi() {
  Serial.println("Estableciendo modo estación...");
  enviarComando("AT+CWMODE=1");

  Serial.print("Conectando a WiFi ");
  Serial.print(ssid);
  Serial.println("...");
  String comando = "AT+CWJAP=\"" + String(ssid) + "\",\"" + String(password) + "\"";
  espSerial.println(comando);
  delay(8000);

  String respuesta = "";
  unsigned long t0 = millis();
  while (millis() - t0 < 10000) {
    if (espSerial.available()) {
      char c = espSerial.read();
      respuesta += c;
    }
  }

  Serial.println(respuesta);
  return respuesta.indexOf("WIFI CONNECTED") != -1 || respuesta.indexOf("OK") != -1;
}

void hacerSolicitud() {
  Serial.println("🔌 Abriendo conexión TCP...");
  String cmd = "AT+CIPSTART=\"TCP\",\"" + String(host) + "\"," + String(port);
  espSerial.println(cmd);

  unsigned long t0 = millis();
  bool connected = false;
  while (millis() - t0 < 5000) {
    if (espSerial.available()) {
      String resp = espSerial.readStringUntil('\n');
      Serial.print("ESP responde: ");
      Serial.println(resp);
      if (resp.indexOf("OK") != -1 || resp.indexOf("CONNECT") != -1) {
        connected = true;
        break;
      }
      if (resp.indexOf("ERROR") != -1) {
        Serial.println("❌ Error al conectar TCP");
        break;
      }
    }
  }

  if (!connected) {
    Serial.println("❌ No se pudo establecer conexión TCP");
    return;
  }

  String solicitud = "GET " + String(path) + " HTTP/1.1\r\nHost: " + String(host) + "\r\nConnection: close\r\n\r\n";
  int longitud = solicitud.length();

  cmd = "AT+CIPSEND=" + String(longitud);
  espSerial.println(cmd);

  t0 = millis();
  bool readyToSend = false;
  while (millis() - t0 < 3000) {
    if (espSerial.available()) {
      String resp = espSerial.readStringUntil('\n');
      Serial.print("ESP responde: ");
      Serial.println(resp);
      if (resp.indexOf(">") != -1) {
        readyToSend = true;
        break;
      }
    }
  }

  if (!readyToSend) {
    Serial.println("⚠️ Error: no se recibió '>' para enviar datos");
    return;
  }

  espSerial.print(solicitud);
  delay(5000);

  Serial.println("📨 Respuesta del servidor:");
  while (espSerial.available()) {
    char c = espSerial.read();
    Serial.write(c);
  }

  enviarComando("AT+CIPCLOSE", 1000);
}

void setup() {
  Serial.begin(9600);
  espSerial.begin(9600);
  delay(2000);

  Serial.println("♻️ Reiniciando ESP8266...");
  resetESP8266();

  Serial.println("🔎 Verificando comunicación...");
  enviarComando("AT");

  if (!conectarWiFi()) {
    Serial.println("❌ No se pudo conectar al WiFi.");
    return;
  }

  Serial.println("✅ Conectado al WiFi.");
}

void loop() {
  unsigned long ahora = millis();
  if (ahora - tiempoAnterior >= intervalo) {
    tiempoAnterior = ahora;
    hacerSolicitud();
  }
}
