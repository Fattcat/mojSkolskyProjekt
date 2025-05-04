# Môj projekt pre SOŠ: ESP8266 Smart Flowerpot

## Zariadenia
- ESP8266 (NodeMCU alebo iný modul)
- TFT displej 2.4" ST7789 (240×320 px, bez dotyku)
- DHT11 senzor (teplota + vlhkosť)
- Senzor vlhkosti pôdy (analógový)
- Vodné čerpadlo + relé modul

## Pripojenie pinov

### 1. TFT ST7789 – ESP8266
| Komponent          | ESP8266 pin     | Popis                             |
|--------------------|-----------------|-----------------------------------|
| **SCK**            | D5 (GPIO14)     | SPI Clock                         |
| **MOSI**           | D7 (GPIO13)     | SPI MOSI                          |
| **DC (Data/Cmd)**  | D1 (GPIO5)      | Data/Command riadiaci vstup       |
| **RESET**          | D4 (GPIO2)      | Hardvérový reset displeja         |
| **CS (Chip Sel.)** | D2 (GPIO4)      | Chip-Select                       |
| **VCC**            | 3.3 V           | Napájanie displeja                |
| **GND**            | GND             | Zem                               |

> **Upozornenie:** v pôvodnom kóde si mal  
> ```cpp
> #define TFT_CS   D2
> #define TFT_RST  D4
> #define TFT_DC   D1
> ```  
> takže som tiež D4 označil ako RESET a D1 ako DC. Ak používaš iné piny, uprav ich v kóde aj tu.

---

### 2. DHT11 – ESP8266
| Komponent    | ESP8266 pin | Popis                         |
|--------------|-------------|-------------------------------|
| **VCC**      | 3.3 V       | Napájanie                     |
| **GND**      | GND         | Zem                           |
| **DATA**     | D6 (GPIO12)| Digitálny výstup dát          |

> V kóde:  
> ```cpp
> #define DHTPIN D6
> #define DHTTYPE DHT11
> ```

---

### 3. Senzor vlhkosti pôdy
| Komponent              | ESP8266 pin | Popis                         |
|------------------------|-------------|-------------------------------|
| **VCC**                | 3.3 V       | Napájanie                     |
| **GND**                | GND         | Zem                           |
| **Analógový výstup**   | A0          | Analógový vstup ESP8266       |

---

### 4. Čerpadlo (12 V) + relé modul
| Komponent            | ESP8266 pin  | Popis                          |
|----------------------|--------------|--------------------------------|
| **Relé IN**          | D3 (GPIO0)   | Riadiaci pin relé              |
| **Relé COM**         | +12 V zdroj  | Napájanie čerpadla (spoločný)  |
| **Relé NO**          | Vodné čerpadlo | Spína sa pri aktivácii relé  |
| **Relé GND**         | GND          | Zem relé modulu                |

> V pôvodnom kóde si mal čerpadlo na `D6` – ak chceš ponechať `#define PUMP_PIN D6`, nastav tu Relé IN na D6 a v kóde zmeň `D3` na `D6`.

---

## Tipy na doladenie
1. **EEPROM** – môžeš si uložiť nastavenie `wateringAmount` a načítať ho po reštarte.  
2. **Tlačidlá** – pridaj 2–3 tlačidlá (UP/DOWN/ENTER) napr. na D8, D0, D3 a umožni meniť množstvo vody cez menu.  
3. **Debug výpis** – `Serial.println()` ti pomôže overiť, či čítaš správne hodnoty senzorov a ovládaš relé.
