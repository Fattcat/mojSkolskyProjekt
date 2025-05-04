// Smart Flowerpot - Arduino IDE (ESP8266 + TFT ST7789)
// Autor: Dominik, projekt pre PČOZ maturitu

#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

// TFT display pins
#define TFT_CS   4
#define TFT_DC   5
#define TFT_RST  12
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

// Farby
#define DARKCYAN     0x03EF
#define LIGHTGREY    0xC618
#define ST77XX_NAVY  0x000F

// DHT senzor
#define DHTPIN     2
#define DHTTYPE    DHT11
DHT dht(DHTPIN, DHTTYPE);

// Čerpadlo
#define PUMP_PIN   14

// Senzor vlhkosti pôdy
#define MOISTURE_PIN A0

int wateringAmount = 1000;  // ms

// Posledné hodnoty
float lastTemp = NAN;
float lastHumidity = NAN;
int lastSoil = -1;

void setup() {
  Serial.begin(115200);
  pinMode(PUMP_PIN, OUTPUT);
  digitalWrite(PUMP_PIN, LOW);

  dht.begin();

  // TFT
  tft.init(240, 320);
  tft.setRotation(2);
  tft.fillScreen(ST77XX_BLACK);
  tft.invertDisplay(0);

  drawMainMenu();
}

void loop() {
  float humidity = dht.readHumidity();
  float temp     = dht.readTemperature();

  if (isnan(humidity) || isnan(temp)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  int soil = analogRead(MOISTURE_PIN);

  // --- Teplota ---
  if (isnan(lastTemp) || abs(temp - lastTemp) > 0.1) {
    drawSensorBox(10, 60, 100, 60, "Teplota", String(temp, 1) + " C");
    lastTemp = temp;
  }

  // --- Vlhkost vzduchu ---
  if (isnan(lastHumidity) || abs(humidity - lastHumidity) > 0.1) {
    drawSensorBox(130, 60, 100, 60, "Vlhkost", String(humidity, 1) + " %");
    lastHumidity = humidity;
  }

  // --- Pôdna vlhkosť ---
  if (soil != lastSoil) {
    drawSensorBox(10, 130, 220, 60, "Puoda", String(soil));
    lastSoil = soil;
  }

  // Zavlažovanie
  if (soil > 800) {
    tft.setTextColor(ST77XX_RED);
    tft.setTextSize(1);
    tft.fillRect(10, 200, 100, 16, ST77XX_BLACK);
    tft.setCursor(10, 200);
    tft.println("Zavlazujem...");
    digitalWrite(PUMP_PIN, HIGH);
    delay(wateringAmount);
    digitalWrite(PUMP_PIN, LOW);
    tft.fillRect(10, 200, 100, 16, ST77XX_BLACK);  // Vymazanie po zavlazovani
  }

  delay(2000);
}

void drawMainMenu() {
  tft.fillScreen(ST77XX_BLACK);
  tft.fillRoundRect(10, 10, 220, 40, 8, DARKCYAN);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(2);
  tft.setCursor(30, 20);
  tft.println("Smart Kvetinac");
}

// Nakreslenie informačného boxu
void drawSensorBox(int x, int y, int w, int h, const String &label, const String &value) {
  uint16_t bgColor = ST77XX_NAVY;
  tft.fillRect(x, y, w, h, bgColor);
  tft.drawRect(x, y, w, h, ST77XX_WHITE);

  tft.setTextSize(1);
  tft.setTextColor(ST77XX_WHITE);
  int16_t x1, y1;
  uint16_t tw, th;
  tft.getTextBounds(label, 0, 0, &x1, &y1, &tw, &th);
  int labelX = x + (w - tw) / 2;
  int labelY = y + 5;
  tft.setCursor(labelX, labelY);
  tft.print(label);

  uint16_t valueColor = ST77XX_WHITE;
  if (label == "Vlhkost") {
    float hum = value.toFloat();
    if (hum > 75.0) valueColor = ST77XX_RED;
    else if (hum > 60.0) valueColor = ST77XX_ORANGE;
    else valueColor = ST77XX_GREEN;
  } else if (label == "Teplota") {
    float t = value.toFloat();
    if (t > 38.0) valueColor = ST77XX_RED;
    else if (t >= 0.0 && t <= 10.0) valueColor = DARKCYAN;
    else valueColor = ST77XX_WHITE;
  }

  tft.setTextSize(2);
  tft.setTextColor(valueColor);
  tft.getTextBounds(value, 0, 0, &x1, &y1, &tw, &th);
  int valueX = x + (w - tw) / 2;
  int valueY = y + h / 2 - th / 2 + 5;
  tft.setCursor(valueX, valueY);
  tft.print(value);
}
