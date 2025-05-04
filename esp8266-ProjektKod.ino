// Smart Flowerpot - Arduino IDE (ESP8266 + TFT ST7789)
// Autor: [Tvoje meno], projekt pre PČOZ maturitu

#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

// TFT display pins
#define TFT_CS   D2
#define TFT_RST  D4
#define TFT_DC   D1
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

// DHT sensor
#define DHTPIN D5
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Water pump control
#define PUMP_PIN D6

// Soil moisture sensor
#define MOISTURE_PIN A0

// Global variables
int wateringAmount = 1000; // ms duration for pump (adjustable)

void setup() {
  Serial.begin(9600);
  pinMode(PUMP_PIN, OUTPUT);
  digitalWrite(PUMP_PIN, LOW);

  dht.begin();

  tft.init(240, 240);
  tft.setRotation(2);
  tft.fillScreen(ST77XX_BLACK);
  
  drawMainMenu();
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  int soil = analogRead(MOISTURE_PIN);

  // Redraw values
  drawSensorData(t, h, soil);

  // Automatic watering condition
  if (soil > 800) {
    digitalWrite(PUMP_PIN, HIGH);
    delay(wateringAmount);
    digitalWrite(PUMP_PIN, LOW);
  }

  delay(5000);
}

void drawMainMenu() {
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(2);
  tft.setCursor(10, 10);
  tft.println("Smart Flowerpot");
  tft.setCursor(10, 40);
  tft.println("Temp / Hum / Soil");
  tft.setCursor(10, 200);
  tft.setTextSize(1);
  tft.println("Auto Watering Enabled");
}

void drawSensorData(float temp, float hum, int soil) {
  tft.fillRect(10, 60, 220, 120, ST77XX_BLACK);
  tft.setCursor(10, 60);
  tft.setTextSize(2);
  tft.setTextColor(ST77XX_GREEN);
  tft.print("T: "); tft.print(temp); tft.println(" C");
  tft.print("H: "); tft.print(hum); tft.println(" %");
  tft.print("S: "); tft.print(soil);
}
// Možnosť neskôr pridať tlačidlá pre nastavenie wateringAmount cez menu

