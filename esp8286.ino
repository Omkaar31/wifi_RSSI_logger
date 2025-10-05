
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ThingSpeak.h>

// ====== Wi-Fi Credentials ======
const char* ssid = "omrenuka";
const char* password = "ruthuparna";

// ====== ThingSpeak Configuration ======
WiFiClient client;
unsigned long channelNumber = 2979685;
const char* writeAPIKey = "AKPNVN4XXMACN99B";

// ====== Setup ======
void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  ThingSpeak.begin(client);
}

// ====== Loop ======
void loop() {
  long rssi = WiFi.RSSI();

  Serial.print("RSSI: ");
  Serial.println(rssi);

  int response = ThingSpeak.writeField(channelNumber, 1, rssi, writeAPIKey);

  if (response == 200) {
    Serial.println("Data sent to ThingSpeak successfully.");
  } else {
    Serial.print("Error sending data. HTTP error code: ");
    Serial.println(response);
  }

  delay(30000);
}
