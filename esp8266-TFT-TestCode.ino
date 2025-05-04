#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>

#define TFT_CS   4    // GPIO4 (D2)
#define TFT_DC   5    // GPIO5 (D1)
#define TFT_RST  12   // GPIO12 (D6)

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

void setup() {
  Serial.begin(115200);
  
  // Inicializácia TFT displeja
  tft.init(240, 320); // 240x320 rozlíšenie
  tft.invertDisplay(0); // číslo 0 je tu pre to, ak nastane inverzia farieb ! - inak je to číslo defaultne na "1"
  tft.fillScreen(ST77XX_BLACK);
  
  // Nastavenie textu
  tft.setTextSize(2);
  tft.setTextColor(ST77XX_RED);
  tft.setCursor(50, 50);
  tft.println("Hello, World!");

  delay(2000);
}

void loop() {
  // Tu môžeš pridať akúkoľvek logiku pre tvoj projekt.
}
