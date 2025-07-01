#ifndef MQTT_CLIENT_H
#define MQTT_CLIENT_H

#include <PubSubClient.h>

// Prototipos de funciones
void setup_mqtt(PubSubClient& client);
void reconnect_mqtt(PubSubClient& client);
void mqtt_callback(char* topic, byte* payload, unsigned int length);

#endif
