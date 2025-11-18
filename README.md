# Protocolo-TLS-y-certificados


objetivo :


Hacer 3 experimentos en tu ESP32:

- Conexión MQTT con puerto seguro (TLS)
Normalmente funciona, porque aunque es seguro, aún no validamos certificados.

- Activar la validación del certificado del servidor (setCACert)
   Debe fallar, porque no has cargado ningún certificado.

- Agregar el certificado Root CA al código del ESP32
   Debe funcionar nuevamente.
