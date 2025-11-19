# Protocolo-TLS-y-certificados


objetivo :


Hacer 3 experimentos en tu ESP32:

- Conexión MQTT con puerto seguro (TLS)
Normalmente funciona, porque aunque es seguro, aún no validamos certificados.

- Activar la validación del certificado del servidor (setCACert)
   Debe fallar, porque no has cargado ningún certificado.

- Agregar el certificado Root CA al código del ESP32
   Debe funcionar nuevamente.
  
## prueba 1

```
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>

// Credenciales WiFi
const char* ssid = "iPhone";
const char* password = "123456789";

// Broker MQTT seguro
const char* mqtt_server = "broker.hivemq.com";
const int mqtt_port = 8883;   // <--- Puerto seguro TLS

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

  // NO VALIDAMOS CERTIFICADO TODAVÍA
  espClient.setInsecure();   // <--- IMPORTANTE

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
``` 
<img width="519" height="153" alt="image" src="https://github.com/user-attachments/assets/d5caced1-4b8c-4181-b6b7-e0711f4c2c6b" />


## Prueba 2
```
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
``` 
<img width="870" height="77" alt="image" src="https://github.com/user-attachments/assets/112fc1c4-f90b-46ad-8052-0e277d674875" />


