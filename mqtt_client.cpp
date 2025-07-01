#include "mqtt_client.h"
#include <WiFi.h>
#include <PubSubClient.h>

// Configuración del broker MQTT
const char* mqtt_server = "test.mosquitto.org";  // Cambia según tu broker
const int mqtt_port = 1883;                     // Puerto del broker
const char* mqtt_user = "";                     // Usuario (opcional)
const char* mqtt_password = "";                 // Contraseña (opcional)

// Configuración inicial del cliente MQTT
void setup_mqtt(PubSubClient& client) {
    client.setServer(mqtt_server, mqtt_port);
    client.setCallback(mqtt_callback);
}

// Función para manejar mensajes recibidos por MQTT
void mqtt_callback(char* topic, byte* payload, unsigned int length) {
    Serial.print("Mensaje recibido en el tema: ");
    Serial.println(topic);

    String message;
    for (int i = 0; i < length; i++) {
        message += (char)payload[i];
    }

    Serial.print("Mensaje: ");
    Serial.println(message);

    // Aquí puedes manejar los mensajes recibidos, por ejemplo:
    if (String(topic) == "iot/led") {
        if (message == "ON") {
            digitalWrite(2, HIGH);  // Enciende el LED
        } else if (message == "OFF") {
            digitalWrite(2, LOW);   // Apaga el LED
        }
    }
}

// Reconectar al broker MQTT si es necesario
void reconnect_mqtt(PubSubClient& client) {
    while (!client.connected()) {
        Serial.print("Conectando al broker MQTT...");
        if (client.connect("ESP32Client", mqtt_user, mqtt_password)) {
            Serial.println("Conectado!");
            // Suscribirse a temas
            client.subscribe("iot/led");
        } else {
            Serial.print("Falló, rc=");
            Serial.print(client.state());
            Serial.println(" Intentando de nuevo en 5 segundos...");
            delay(5000);
        }
    }
}
