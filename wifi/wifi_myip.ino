const char* ssid = "ssid";
const char* password = "pass";

// Configuración del host y endpoint
//String host = "api.ipify.org";
//String endpoint = "/?format=json";
String host = "api.openweathermap.org";
String endpoint = "/data/2.5/weather?q=Madrid&appid=API_KEY";


unsigned long lastRequestTime = 0;
const unsigned long requestInterval = 15000; // 15 segundos
String bufferRespuesta = "";

void enviarComando(const String& cmd, unsigned long espera = 1000) {
  Serial.print(">> ");
  Serial.println(cmd);
  Serial1.println(cmd);
  delay(espera);
}

bool esperarRespuesta(const char* esperado, unsigned long timeout = 5000) {
  unsigned long start = millis();
  String respuesta = "";
  while (millis() - start < timeout) {
    while (Serial1.available()) {
      char c = Serial1.read();
      respuesta += c;
    }
    if (respuesta.indexOf(esperado) != -1) {
      Serial.print("Respuesta esperada recibida: ");
      Serial.println(esperado);
      return true;
    }
    delay(100);
  }
  Serial.print("Timeout esperando: ");
  Serial.println(esperado);
  Serial.print("Respuesta recibida: ");
  Serial.println(respuesta);
  return false;
}

void resetESP() {
  Serial.println("Reiniciando ESP8266...");
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
  delay(50);
  digitalWrite(2, HIGH);
  delay(1000);
}

bool conectarWiFi() {
  enviarComando("AT+CWMODE=1");
  if (!esperarRespuesta("OK")) {
    Serial.println("Error configurando modo estación");
    return false;
  }

  String cmdWiFi = "AT+CWJAP=\"" + String(ssid) + "\",\"" + String(password) + "\"";
  enviarComando(cmdWiFi, 8000);
  if (!esperarRespuesta("GOT IP", 15000)) {
    Serial.println("Error conectando al WiFi");
    return false;
  }
  Serial.println("Conectado a WiFi!");
  return true;
}

bool abrirConexionTCP() {
  String cmd = "AT+CIPSTART=\"TCP\",\"" + host + "\",80";
  enviarComando(cmd, 4000);
  if (!esperarRespuesta("OK", 5000)) {
    Serial.println("Error iniciando conexión TCP");
    return false;
  }
  return true;
}

bool enviarSolicitud(const String& solicitud) {
  enviarComando("AT+CIPSEND=" + String(solicitud.length()));
  if (!esperarRespuesta(">", 5000)) {
    Serial.println("Error: No se recibió prompt '>' para enviar datos");
    return false;
  }
  Serial.print("Enviando solicitud HTTP:\n");
  Serial.println(solicitud);
  Serial1.print(solicitud);
  return true;
}

void cerrarConexion() {
  enviarComando("AT+CIPCLOSE", 1000);
}

void setup() {
  Serial.begin(115200);
  Serial1.begin(115200);

  resetESP();

  Serial.println("Esperando respuesta OK...");
  if (!esperarRespuesta("OK", 3000)) {
    Serial.println("Error: No se recibió OK inicial del ESP.");
  }

  Serial.println("Comprobando comunicación con ESP...");
  while (true) {
    Serial1.println("AT");
    if (esperarRespuesta("OK", 2000)) break;
    Serial.println("Reintentando comando AT...");
  }

  if (!conectarWiFi()) {
    Serial.println("Fallo al conectar WiFi, reiniciando...");
    while (1);
  }
}

void loop() {
  unsigned long now = millis();
  if (now - lastRequestTime >= requestInterval) {
    lastRequestTime = now;
    bufferRespuesta = "";

    if (!abrirConexionTCP()) {
      Serial.println("Reintentando conexión en el próximo ciclo");
      return;
    }

    String httpRequest = "GET " + endpoint + " HTTP/1.1\r\nHost: " + host + "\r\nConnection: close\r\n\r\n";
    if (!enviarSolicitud(httpRequest)) {
      cerrarConexion();
      Serial.println("Reintentando solicitud en el próximo ciclo");
      return;
    }

    // Esperar y leer respuesta
    unsigned long startTime = millis();
    while (millis() - startTime < 7000) {
      while (Serial1.available()) {
        char c = Serial1.read();
        bufferRespuesta += c;
      }
    }

    cerrarConexion();

    Serial.println("Respuesta completa:");
    Serial.println(bufferRespuesta);

    // Parsear el campo "ip" del JSON
    int idx = bufferRespuesta.indexOf("\"ip\":\"");
    if (idx != -1) {
      idx += 6;
      int idxFin = bufferRespuesta.indexOf("\"", idx);
      if (idxFin != -1) {
        String ip = bufferRespuesta.substring(idx, idxFin);
        Serial.println("Tu IP pública es:");
        Serial.println(ip);
      } else {
        Serial.println("No se encontró el final del valor del campo 'ip'");
      }
    } else {
      Serial.println("No se encontró el campo 'ip' en la respuesta");
    }
  }
}
