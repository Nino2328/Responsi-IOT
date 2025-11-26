#include <WiFi.h>

// --------------------
// WiFi Credentials
// --------------------
const char* ssid = "Modal dong";
const char* password = "12345678";

// --------------------
// Pin Sensor
// --------------------
#define LDR_PIN 32      
#define FLAME_PIN 33    

void setup() {
  Serial.begin(115200);

  pinMode(FLAME_PIN, INPUT);

  Serial.println("Menghubungkan ke WiFi...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi Terhubung!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  Serial.println("Sensor Cahaya + Api Siap!");
}

void loop() {

  // --------------------
  // Baca Sensor Cahaya (LDR)
  // --------------------
  int nilaiCahaya = analogRead(LDR_PIN);  // 0 - 4095
  String kondisiCahaya;

  // -------------------------
  // SENSORMU TERBALIK:
  // nilai besar = gelap
  // nilai kecil = terang
  // -------------------------
  if (nilaiCahaya > 2500) {
    kondisiCahaya = "Gelap";
  } else if (nilaiCahaya > 1000) {
    kondisiCahaya = "Normal / Sedang";
  } else {
    kondisiCahaya = "Terang";
  }

  // --------------------
  // Baca Sensor Api
  // --------------------
  int flameVal = digitalRead(FLAME_PIN);
  bool apiTerdeteksi = (flameVal == LOW);

  // --------------------
  // Output
  // --------------------
  Serial.println("=======================================");
  Serial.print("Nilai Cahaya (LDR): ");
  Serial.print(nilaiCahaya);
  Serial.print(" → ");
  Serial.println(kondisiCahaya);

  if (apiTerdeteksi) {
    Serial.println("🔥 PERINGATAN! API TERDETEKSI!");
  } else {
    Serial.println("✔ Tidak ada api terdeteksi");
  }

  Serial.print("WiFi: ");
  Serial.println(WiFi.status() == WL_CONNECTED ? "Terhubung" : "Terputus");

  delay(1500);
}