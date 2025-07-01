#include "sensor_dht.h"

// Configuración del sensor DHT
#define DHTPIN 4        // Pin donde está conectado el sensor
#define DHTTYPE DHT11   // Tipo de sensor: DHT11 o DHT22
DHT dht(DHTPIN, DHTTYPE);

// Inicializar el sensor DHT
void setup_dht() {
    dht.begin();
}

// Leer temperatura desde el sensor DHT
float read_temperature() {
    float temperature = dht.readTemperature();
    if (isnan(temperature)) {
        Serial.println("Error al leer la temperatura!");
        return -1;
    }
    return temperature;
}

// Leer humedad desde el sensor DHT
float read_humidity() {
    float humidity = dht.readHumidity();
    if (isnan(humidity)) {
        Serial.println("Error al leer la humedad!");
        return -1;
    }
    return humidity;
}
