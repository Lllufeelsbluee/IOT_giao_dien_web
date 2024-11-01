#include <WiFi.h>
#include <HTTPClient.h>
#include "ThingSpeak.h"
#include "DHTesp.h"
#include <ArduinoJson.h>

#define REFERENCE_URL "https://lab3-bt2-default-rtdb.firebaseio.com/"

const int DHT_PIN = 15;
const char* WIFI_NAME = "Wokwi-GUEST";
const char* WIFI_PASSWORD = "";
const int myChannelNumber = 2567415;
const char* myApiKey = "I7GEEC022SUST1DG";
const char* server = "api.thingspeak.com";

// hc-sr04
#define TRIGGER_PIN 13 
#define ECHO_PIN 12


// Firebase credentials
const char* FIREBASE_HOST = "https://lab3-bt2-default-rtdb.firebaseio.com/";
const char* FIREBASE_AUTH = "AIzaSyAFhLAEW_5t5m1bV_G0muekV1nXjodwXSc";
const char* FIREBASE_PATH = "/sensor_data.json"; 

DHTesp dhtSensor;
WiFiClient client;
HTTPClient http;

long duration;
float distance;

// Hàm đo khoảng cách bằng cảm biến HC-SR04
float measureDistance() {
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH);
  distance = duration * 0.034 / 2;

  return distance;
}

// Hàm cập nhật dữ liệu lên Firebase
void updateFirebaseData(float temperature, float humidity, int distance) {
  StaticJsonDocument<200> data;
  data["temperature"] = temperature;
  data["humidity"] = humidity;
  data["distance"] = distance;


  String url = String(FIREBASE_HOST) + String(FIREBASE_PATH) + "?auth=" + String(FIREBASE_AUTH);
  http.begin(url);  // Khởi tạo HTTPClient với URL Firebase

  // Chuyển đổi JSON thành chuỗi
  String jsonStr;
  serializeJson(data, jsonStr);

  http.addHeader("Content-Type", "application/json");

  // Gửi yêu cầu PUT đến Firebase
  int httpResponseCode = http.PUT(jsonStr);

  if (httpResponseCode > 0) {
    String response = http.getString();
    Serial.print("Firebase response (PUT): ");
    Serial.println(httpResponseCode);
    Serial.println("Response: " + response);
  } else {
    Serial.print("Error updating Firebase: ");
    Serial.println(httpResponseCode);
  }

  http.end();
}

void setup() {
  Serial.begin(115200);
  dhtSensor.setup(DHT_PIN, DHTesp::DHT22);
 
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  
  WiFi.begin(WIFI_NAME, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Wifi not connected");
  }
  Serial.println("Wifi connected!");
  Serial.println("Local IP: " + String(WiFi.localIP()));
  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);
}

void loop() {
  TempAndHumidity data = dhtSensor.getTempAndHumidity();

  // Đo khoảng cách bằng HC-SR04
  distance = measureDistance();
  Serial.println("Distance: " + String(distance, 2) + " cm");

  // Đọc giá trị cảm biến

  Serial.println("Temp: " + String(data.temperature, 2) + "°C");
  Serial.println("Humidity: " + String(data.humidity, 1) + "%");

  // Cập nhật dữ liệu lên ThingSpeak
  ThingSpeak.setField(1, data.temperature);
  ThingSpeak.setField(2, data.humidity);
  
  ThingSpeak.setField(4, distance);   

  int x = ThingSpeak.writeFields(myChannelNumber, myApiKey);
  if (x == 200) {
    Serial.println("Data pushed successfully to ThingSpeak");
  } else {
    Serial.println("Push error: " + String(x));
  }

  // Cập nhật dữ liệu lên Firebase
  updateFirebaseData(data.temperature, data.humidity, distance); 

  Serial.println("---");
  delay(2000);  // Gửi dữ liệu mỗi 2s
}
