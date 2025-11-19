#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>

// Credenciales WiFi
const char* ssid = "iPhone";
const char* password = "123456789";


// Broker MQTT seguro
const char* mqtt_server = "broker.hivemq.com";
const int mqtt_port = 8883;   // <--- Puerto seguro TLS
const char* root_ca = \
"-----BEGIN CERTIFICATE-----\n"
"NO_HAY_CERT_AQUI\n"
"-----END CERTIFICATE-----\n";


WiFiClientSecure espClient;
PubSubClient client(espClient);

void setup_wifi() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi conectado");
}

void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Mensaje recibido: ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
  }
  Serial.println();
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Conectando a MQTT...");
    if (client.connect("ESP32TestTLS")) {
      Serial.println("Conectado!");
      client.subscribe("prueba/esp32");
    } else {
      Serial.print("Fallo, rc=");
      Serial.print(client.state());
      delay(2000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();

 // Activar verificación
// (pero aún no tenemos certificado)
espClient.setCACert(root_ca);   // <-- root_ca NO existe aún

  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  client.publish("prueba/esp32", "Mensaje desde ESP32 sin cert");
  delay(3000);
}
