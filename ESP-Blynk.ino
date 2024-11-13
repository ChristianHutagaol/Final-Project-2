#define BLYNK_PRINT Serial

#define BLYNK_TEMPLATE_ID "TMPL6kvGwcXTU"
#define BLYNK_TEMPLATE_NAME "yyhhh"
#define BLYNK_AUTH_TOKEN "8uOch9-3n_P28yNnh6Gn8iY6f5ipRRqd"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// WiFi credentials
char ssid[] = "Christ";
char pass[] = "christfreya18";

void setup() {
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, 13, 12); // D1 -> GPIO 16, D2 -> GPIO 17

  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");

  Serial.println("Connecting to Blynk...");
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop() {
  if (Serial2.available() > 0) {
    String data = Serial2.readStringUntil('\n');
    Serial.println(data); // Cetak data yang diterima untuk verifikasi

    int comma1Pos = data.indexOf(',');
    int comma2Pos = data.indexOf(',', comma1Pos + 1);
    float phValue = data.substring(0, comma1Pos).toFloat();
    float tdsValue = data.substring(comma1Pos + 1, comma2Pos).toFloat();

    // Kirim nilai ke Blynk
    Blynk.virtualWrite(V27, phValue);
    Blynk.virtualWrite(V25, tdsValue);
    
  }

  Blynk.run();


  delay(100); // Jeda singkat sebelum iterasi berikutnya
}




