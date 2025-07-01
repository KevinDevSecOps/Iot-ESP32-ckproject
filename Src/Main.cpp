#include <WiFi.h>
#include <DHT.h>

// Configuración del WiFi
const char* ssid = "TU_SSID";
const char* password = "TU_PASSWORD";

// Configuración de DHT
#define DHTPIN 4        // Pin donde está conectado el sensor
#define DHTTYPE DHT11   // Tipo de sensor: DHT11 o DHT22
DHT dht(DHTPIN, DHTTYPE);

// Variables globales
WiFiServer server(80);

void setup() {
    Serial.begin(115200);

    // Inicializar el sensor DHT
    dht.begin();

    // Conexión WiFi
    Serial.println("Conectando al WiFi...");
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
    Serial.println("\nConexión WiFi exitosa!");
    Serial.print("Dirección IP: ");
    Serial.println(WiFi.localIP());

    // Inicia el servidor
    server.begin();
}

void loop() {
    // Lee datos del sensor DHT
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();

    if (isnan(temperature) || isnan(humidity)) {
        Serial.println("Error al leer los datos del sensor!");
        return;
    }

    Serial.print("Temperatura: ");
    Serial.print(temperature);
    Serial.println(" °C");

    Serial.print("Humedad: ");
    Serial.print(humidity);
    Serial.println(" %");

    // Manejo de clientes en el servidor
    WiFiClient client = server.available();
    if (client) {
        Serial.println("Cliente conectado!");
        client.println("HTTP/1.1 200 OK");
        client.println("Content-Type: text/html");
        client.println();
        client.println("<!DOCTYPE HTML>");
        client.println("<html>");
        client.println("<h1>Datos del sensor DHT</h1>");
        client.print("<p>Temperatura: ");
        client.print(temperature);
        client.println(" °C</p>");
        client.print("<p>Humedad: ");
        client.print(humidity);
        client.println(" %</p>");
        client.println("</html>");
        client.stop();
        Serial.println("Cliente desconectado.");
    }

    delay(2000); // Espera 2 segundos antes de la siguiente lectura
}
