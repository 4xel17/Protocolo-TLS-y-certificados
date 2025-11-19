# Protocolo-TLS-y-certificados
por:

Sara Zuluaga
Maria Jose Garcia
Axel Bedoya

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

## prueba 3 
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
"MIIEXjCCA0agAwIBAgITB3MSTyqVLj7Rili9uF0bwM5fJzANBgkqhkiG9w0BAQsF\n" 
"ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6\n" 
"b24gUm9vdCBDQSAxMB4XDTIyMDgyMzIyMjYzNVoXDTMwMDgyMzIyMjYzNVowPDEL\n" 
"MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEcMBoGA1UEAxMTQW1hem9uIFJT\n" 
"QSAyMDQ4IE0wNDCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAM3pVR6A\n" 
"lQOp4xe776FdePXyejgA38mYx1ou9/jrpV6Sfn+/oqBKgwhY6ePsQHHQayWBJdBn\n" 
"v4Wz363qRI4XUh9swBFJ11TnZ3LqOMvHmWq2+loA0QPtOfXdJ2fHBLrBrngtJ/GB\n" 
"0p5olAVYrSZgvQGP16Rf8ddtNyxEEhYm3HuhmNi+vSeAq1tLYJPAvRCXonTpWdSD\n" 
"xY6hvdmxlqTYi82AtBXSfpGQ58HHM0hw0C6aQakghrwWi5fGslLOqzpimNMIsT7c\n" 
"qa0GJx6JfKqJqmQQNplO2h8n9ZsFJgBowof01ppdoLAWg6caMOM0om/VILKaa30F\n" 
"9W/r8Qjah7ltGVkCAwEAAaOCAVowggFWMBIGA1UdEwEB/wQIMAYBAf8CAQAwDgYD\n" 
"VR0PAQH/BAQDAgGGMB0GA1UdJQQWMBQGCCsGAQUFBwMBBggrBgEFBQcDAjAdBgNV\n" 
"HQ4EFgQUH1KSYVaCVH+BZtgdPQqqMlyH3QgwHwYDVR0jBBgwFoAUhBjMhTTsvAyU\n" 
"lC4IWZzHshBOCggwewYIKwYBBQUHAQEEbzBtMC8GCCsGAQUFBzABhiNodHRwOi8v\n" 
"b2NzcC5yb290Y2ExLmFtYXpvbnRydXN0LmNvbTA6BggrBgEFBQcwAoYuaHR0cDov\n" 
"L2NydC5yb290Y2ExLmFtYXpvbnRydXN0LmNvbS9yb290Y2ExLmNlcjA/BgNVHR8E\n" 
"ODA2MDSgMqAwhi5odHRwOi8vY3JsLnJvb3RjYTEuYW1hem9udHJ1c3QuY29tL3Jv\n" 
"b3RjYTEuY3JsMBMGA1UdIAQMMAowCAYGZ4EMAQIBMA0GCSqGSIb3DQEBCwUAA4IB\n" 
"AQA+1O5UsAaNuW3lHzJtpNGwBnZd9QEYFtxpiAnIaV4qApnGS9OCw5ZPwie7YSlD\n" 
"ZF5yyFPsFhUC2Q9uJHY/CRV1b5hIiGH0+6+w5PgKiY1MWuWT8VAaJjFxvuhM7a/e\n" 
"fN2TIw1Wd6WCl6YRisunjQOrSP+unqC8A540JNyZ1JOE3jVqat3OZBGgMvihdj2w\n"
"Y23EpwesrKiQzkHzmvSH67PVW4ycbPy08HVZnBxZ5NrlGG9bwXR3fNTaz+c+Ej6c\n" 
"5AnwI3qkOFgSkg3Y75cdFz6pO/olK+e3AqygAcv0WjzmkDPuBjssuZjCHMC56oH3\n" 
"GJkV29Di2j5prHJbwZjG1inU\n" 
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
  client.publish("prueba/esp32", "Mensaje desde ESP32 con certificado");
  delay(3000);
}

```

<img width="1404" height="632" alt="image" src="https://github.com/user-attachments/assets/fad601da-60a5-49c6-9371-fdff44a264f1" />

<img width="607" height="108" alt="image" src="https://github.com/user-attachments/assets/8c4686e1-30a1-4723-9357-97cf023dec80" />


