// Smart Flowerpot - Arduino IDE (ESP8266 + TFT ST7789)
// Autor: [Tvoje meno], projekt pre PČOZ maturitu

#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

// TFT display pins (GPIO numbers)
#define TFT_CS   4    // GPIO4 (D2)
#define TFT_DC   5    // GPIO5 (D1)
#define TFT_RST  12   // GPIO12 (D6)
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

#define DARKCYAN     0x03EF  // tmavá tyrkysová
#define LIGHTGREY    0xC618  // svetlosivá
#define ST77XX_NAVY 0x000F


// DHT sensor
#define DHTPIN     2        // DHT11 Data Pin (GPIO2)
#define DHTTYPE    DHT11
DHT dht(DHTPIN, DHTTYPE);

// Water pump control
#define PUMP_PIN   14       // Pump control pin (GPIO14)

// Soil moisture sensor
#define MOISTURE_PIN A0     // Analog pin A0

// Global variables
int wateringAmount = 1000;  // ms duration for pump

void setup() {
  Serial.begin(115200);
  pinMode(PUMP_PIN, OUTPUT);
  digitalWrite(PUMP_PIN, LOW);

  dht.begin();

  // Initialize TFT display
  tft.init(240, 320);
  tft.setRotation(2);               // Landscape
  tft.fillScreen(ST77XX_BLACK);
  tft.invertDisplay(0);             // Normal colors

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

  drawSensorBox(10,  60, 100, 60, "Teplota", String(temp, 1) + " C");
  drawSensorBox(130, 60, 100, 60, "Vlhkost", String(humidity, 1) + " %");
  drawSensorBox(10, 130, 220, 60, "Puoda", String(soil));

  if (soil > 800) {
    tft.setTextColor(ST77XX_RED);
    tft.setTextSize(1);
    tft.fillRect(10, 200, 100, 16, ST77XX_BLACK);
    tft.setCursor(10, 200);
    tft.println("Zavlazujem...");
    digitalWrite(PUMP_PIN, HIGH);
    delay(wateringAmount);
    digitalWrite(PUMP_PIN, LOW);
  }

  delay(2000);
}

void drawMainMenu() {
  tft.fillScreen(ST77XX_BLACK);
  tft.fillRoundRect(10, 10, 220, 40, 8, DARKCYAN); // alebo ST77XX_CYAN
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(2);
  tft.setCursor(30, 20);
  tft.println("Smart Kvetinac");

  // tft.setTextSize(1);
  // tft.setCursor(15, 55);
  // tft.setTextColor(DARKCYAN);
  // tft.println("Teplota  Vlhkost  Puoda");
}

// Draw a rounded rectangle outline
void drawRoundedRect(int x, int y, int w, int h, uint16_t color) {
  tft.drawPixel(x+1, y+1, color);
  tft.drawPixel(x+w-2, y+1, color);
  tft.drawPixel(x+1, y+h-2, color);
  tft.drawPixel(x+w-2, y+h-2, color);
  tft.drawFastHLine(x+2, y, w-4, color);
  tft.drawFastHLine(x+2, y+h-1, w-4, color);
  tft.drawFastVLine(x, y+2, h-4, color);
  tft.drawFastVLine(x+w-1, y+2, h-4, color);
}

// Draw a styled box with label and centered value
void drawSensorBox(int x, int y, int w, int h, const String &label, const String &value) {
  uint16_t bgColor = ST77XX_NAVY;
  tft.fillRect(x, y, w, h, bgColor);
  tft.drawRect(x, y, w, h, ST77XX_WHITE);

  // -- Label (napr. "Teplota", "Vlhkost") --
  tft.setTextSize(1);
  tft.setTextColor(ST77XX_WHITE);
  int16_t x1, y1;
  uint16_t tw, th;
  tft.getTextBounds(label, 0, 0, &x1, &y1, &tw, &th);
  int labelX = x + (w - tw) / 2;
  int labelY = y + 5;
  tft.setCursor(labelX, labelY);
  tft.print(label);

  // -- Rozhodovanie o farbe hodnoty --
  uint16_t valueColor = ST77XX_WHITE;

  if (label == "Vlhkost") {
    float humidity = value.toFloat();
    if (humidity > 75.0) {
      valueColor = ST77XX_RED;
    } else if (humidity > 60.0) {
      valueColor = ST77XX_ORANGE;
    } else {
      valueColor = ST77XX_GREEN;
    }
  } else if (label == "Teplota") {
    float temp = value.toFloat();
    if (temp > 38.0) {
      valueColor = ST77XX_RED;
    } else if (temp >= 0.0 && temp <= 10.0) {
      valueColor = DARKCYAN;
    } else {
      valueColor = ST77XX_WHITE;
    }
  }

  // -- Hodnota (napr. "23.5 °C") --
  tft.setTextSize(2);
  tft.setTextColor(valueColor);
  tft.getTextBounds(value, 0, 0, &x1, &y1, &tw, &th);
  int valueX = x + (w - tw) / 2;
  int valueY = y + h / 2 - th / 2 + 5;
  tft.setCursor(valueX, valueY);
  tft.print(value);
}
