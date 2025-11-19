#Investigación

## **1. ¿Qué es el protocolo TLS?**

TLS (*Transport Layer Security*) es un protocolo criptográfico que asegura la comunicación entre dos sistemas.
Sus funciones principales son:

* Cifrar los datos para que nadie pueda leerlos.
* Verificar la identidad del servidor (y opcionalmente del cliente).
* Garantizar la integridad de los datos.

TLS es la evolución de SSL y es lo que usa HTTPS actualmente.

---

## **2. ¿Cuál es su importancia?**

TLS protege información sensible como contraseñas, tarjetas de crédito y datos personales.
Sin TLS, la comunicación viaja en texto plano y puede ser interceptada o manipulada.

---

## **3. Riesgos si no se usa TLS**

* Intercepción (**sniffing**) de datos.
* Suplantación (**spoofing**) de servidores.
* Manipulación de datos (ataque **Man-in-the-Middle**).
* Robo de credenciales.

---

## **4. ¿Qué es un certificado digital?**

Un certificado contiene:

* La **clave pública** del servidor.
* Su **identidad** (dominio, organización, país).
* La **firma digital** de una CA.

Es como una *cédula digital* para el servidor.

---

## **5. ¿Qué es una CA (Certificate Authority)?**

Es una entidad de confianza que firma certificados digitales.
Ejemplos: Let's Encrypt, DigiCert, GlobalSign.

---

## **6. Cadena de certificados y vigencia**

Una cadena típica es:
**Certificado del servidor → CA intermedia → CA raíz**

Vigencias:

* Certificado del servidor: 3 meses–2 años
* CA intermedia: 5–10 años
* CA raíz: 10–25 años

---

## **7. Keystore y Certificate Bundle**

* **Keystore:** archivo donde se almacenan claves privadas + certificados (Java/Android/IoT).

  * Ej.: `keystore.jks`, `key.pem`
* **Certificate bundle:** varios certificados juntos (`.pem` o `.crt`).

---

## **8. ¿Qué es la autenticación mutua (mTLS)?**

Ambos: cliente y servidor presentan certificados.
Muy usado en IoT y entornos corporativos.

---

## **9. Validación de certificados en ESP32**

Ejemplo:

```cpp
WiFiClientSecure client;
client.setCACert(root_ca);
```

---

## **10. Múltiples dominios en ESP32 con distintas CAs**

Opciones:

1. Cargar varios certificados raíz.
2. Usar un bundle concatenado.
3. Omitir validación (NO recomendado).
4. Verificación dinámica si hay memoria suficiente.

---

## **11. ¿Cómo obtener un certificado para un dominio?**

* Let's Encrypt (gratis, con Certbot).
* CA comercial (DigiCert, Sectigo, GoDaddy).

---

## **12. Llave pública vs. llave privada**

* **Pública:** se comparte, sirve para cifrar/verificar firmas.
* **Privada:** se mantiene secreta, sirve para descifrar/firmar.

---

## **13. ¿Qué pasa cuando un certificado expira?**

* El cliente rechaza la conexión.
* Debes renovarlo y actualizarlo en el ESP32 si está incrustado en código.

---

## **14. Base matemática de la criptografía moderna**

* Teoría de números
* Aritmética modular
* RSA (factores primos)
* Diffie-Hellman (logaritmo discreto)
* ECC (curvas elípticas)

---

## **15. Computación cuántica e implicaciones**

Rompería RSA y ECC usando el algoritmo de Shor.
Por esto se crea la **criptografía post–cuántica**, basada en retículas, códigos y funciones hash.

---
