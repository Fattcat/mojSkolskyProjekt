# Moj projekt pre SOŠ esp8266 smart flowerpot
## zariadenia
- esp8266
- TFT Displej 2.4" 240x320px st7789 (bez dotyku)
- DHT11
- Senzor vlhkosti pôdy


# Pripojenie pinov
## TFT - esp8266

| **Komponent**    | **ESP8266 Pin** | **Popis**                 |
| ---------------- | --------------- | ------------------------- |
| **ST7789 SCK**   | D5 (GPIO14)     | SPI Clock (SCK)           |
| **ST7789 MOSI**  | D7 (GPIO13)     | SPI Data (MOSI)           |
| **ST7789 DC**    | D2 (GPIO4)      | Data/Command (DC)         |
| **ST7789 RESET** | D1 (GPIO5)      | Reset (RESET)             |
| **ST7789 CS**    | D8 (GPIO15)     | Chip Select (CS)          |
| **ST7789 VCC**   | 3.3V            | Napájanie displeja (3.3V) |
| **ST7789 GND**   | GND             | Zem (GND)                 |

## Dht11 - esp8266
| **Komponent**  | **ESP8266 Pin** | **Popis**                |
| -------------- | --------------- | ------------------------ |
| **DHT11 VCC**  | 3.3V            | Napájanie senzora (3.3V) |
| **DHT11 GND**  | GND             | Zem (GND)                |
| **DHT11 Data** | D6 (GPIO12)     | Data pin (DHT11 Data)    |

## Senzor vlhkosti pôdy

| **Komponent**               | **ESP8266 Pin** | **Popis**                |
| --------------------------- | --------------- | ------------------------ |
| **Senzor VCC**              | 3.3V            | Napájanie senzora (3.3V) |
| **Senzor GND**              | GND             | Zem (GND)                |
| **Senzor analogový výstup** | A0              | Analógový pin (A0)       |

## Vodné čerpadlo

| **Komponent**                   | **ESP8266 Pin** | **Popis**                  |
| ------------------------------- | --------------- | -------------------------- |
| **Relé IN**                     | D3 (GPIO0)      | Riadiaci pin pre relé (IN) |
| **Relé NO (Normálne otvorený)** | 12V čerpadlo    | Spustenie čerpadla (NO)    |
| **Relé COM (Spoločný)**         | GND (Zem)       | Spoločný kontakt pre relé  |

