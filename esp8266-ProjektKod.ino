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

// DHT sensor
#define DHTPIN     15    // DHT11 Data Pin (GPIO12)
#define DHTTYPE    DHT11
DHT dht(DHTPIN, DHTTYPE);

// Water pump control
#define PUMP_PIN   14    // Pump control pin (GPIO14)

// Soil moisture sensor
#define MOISTURE_PIN A0  // Analog pin A0

// Global variables
int wateringAmount = 1000;   // ms duration for pump

void setup() {
  Serial.begin(115200);
  pinMode(PUMP_PIN, OUTPUT);
  digitalWrite(PUMP_PIN, LOW);

  dht.begin();

  // Initialize TFT display
  tft.init(240, 320);         // Initialize with resolution
  tft.setRotation(2);         // Landscape orientation
  tft.fillScreen(ST77XX_BLACK); // Only once to clear screen initially
  
  // Invert display colors if necessary
  tft.invertDisplay(0);    // Set display to normal colors

  drawMainMenu();  // Draw the main menu once during setup
}

void loop() {
  // Read humidity and temperature from DHT sensor
  float humidity = dht.readHumidity();
  float temp     = dht.readTemperature();
  
  // Check for valid sensor readings
  if (isnan(humidity) || isnan(temp)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Read soil moisture sensor
  int soil = analogRead(MOISTURE_PIN);

  // Update sensor boxes on the display
  drawSensorBox(10,  60, 100, 60, "Temp", String(temp, 1) + " C");
  drawSensorBox(130, 60, 100, 60, "Hum",  String(humidity, 1) + " %");
  drawSensorBox(10, 130, 220, 60, "Soil", String(soil));

  // Automatic watering if soil moisture is low
  if (soil > 800) {
    tft.setTextColor(ST77XX_RED);
    tft.setTextSize(1);
    tft.setCursor(10, 200);
    tft.println("Watering...");
    digitalWrite(PUMP_PIN, HIGH);
    delay(wateringAmount);
    digitalWrite(PUMP_PIN, LOW);
  }

  delay(2000);  // Delay between readings
}

void drawMainMenu() {
  // Title box
  tft.drawRect(5, 5, 230, 40, ST77XX_WHITE);
  tft.fillRect(6, 6, 228, 38, ST77XX_BLACK);
  tft.setTextColor(ST77XX_CYAN);
  tft.setTextSize(2);
  tft.setCursor(15, 15);
  tft.println("Smart Flowerpot");

  // Subtitle
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(1);
  tft.setCursor(15, 35);
  tft.println("Temp  Humidity  Soil");
}

// Draw a labeled box with border, label, and value
void drawSensorBox(int x, int y, int w, int h, const String& label, const String& value) {
  // Clear the previous content of the box before drawing the new one
  tft.fillRect(x+1, y+1, w-2, h-2, ST77XX_BLACK); // Clear the box
  
  // Border
  tft.drawRect(x, y, w, h, ST77XX_WHITE);
  
  // Label background
  tft.fillRect(x+1, y+1, w-2, 12, ST77XX_BLACK);
  
  // Label text
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(1);
  tft.setCursor(x+4, y+3);
  tft.println(label);
  
  // Value text
  tft.setTextColor(ST77XX_GREEN);
  tft.setTextSize(2);
  tft.setCursor(x+4, y+18);
  tft.println(value);
}
