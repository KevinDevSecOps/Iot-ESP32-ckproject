#include <WiFi.h>
#include <PubSubClient.h>
#include "mqtt/mqtt_client.h"
#include "sensors/sensor_dht.h"

// Configuración WiFi
const char* ssid = "TU_SSID";
const char* password = "TU_PASSWORD";

// Cliente WiFi y cliente MQTT
WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
    // Configuración inicial
    Serial.begin(115200);
    pinMode(2, OUTPUT);  // LED integrado

    // Conexión WiFi
    Serial.println("Conectando al WiFi...");
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
    Serial.println("\nWiFi conectado!");
    Serial.print("Dirección IP: ");
    Serial.println(WiFi.localIP());

    // Configurar sensor DHT
    setup_dht();

    // Configurar cliente MQTT
    setup_mqtt(client);
}

void loop() {
    // Reconectar al broker MQTT si es necesario
    if (!client.connected()) {
        reconnect_mqtt(client);
    }
    client.loop();

    // Leer datos del sensor DHT
    float temperature = read_temperature();
    float humidity = read_humidity();

    // Publicar datos del sensor en MQTT
    if (temperature != -1 && humidity != -1) {
        char tempString[8];
        char humString[8];
        dtostrf(temperature, 1, 2, tempString);
        dtostrf(humidity, 1, 2, humString);

        client.publish("iot/temperature", tempString);
        client.publish("iot/humidity", humString);

        Serial.print("Temperatura publicada: ");
        Serial.println(tempString);
        Serial.print("Humedad publicada: ");
        Serial.println(humString);
    }

    delay(5000); // Espera 5 segundos antes del siguiente envío
}
