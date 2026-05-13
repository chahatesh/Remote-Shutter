# ESP32 Remote Shutter Project (OLED + Button)

## Overview

This project is a very simple camera shutter controller built using a standard ESP32 Dev Kit

It has only two inputs/outputs:

* A physical push button to trigger recording/shutter action
* An OLED display that shows recording status and elapsed time

There are no sensors, no battery system, and no expandable modules. It is designed to be simple, fast, and reliable for camera control projects.

---

## Features

* Push-button shutter/record trigger
* OLED display (SSD1306 I2C)
* Shows recording status
* Shows elapsed recording time
* USB powered via ESP32 Dev Kit
* Lightweight and minimal design

---

## Parts List

| Part                 | Description                  |
| -------------------- | ---------------------------- |
| ESP32 Dev Kit        | Main controller              |
| SSD1306 OLED Display | Status + timer display       |
| Push Button          | Start/stop recording trigger |
| Jumper Wires         | Connections                  |
| Breadboard or PCB    | Mounting                     |
| USB Cable            | Power + programming          |

---

## Wiring

### Button

| Button Pin | ESP32   |
| ---------- | ------- |
| One side   | GPIO 19 |
| Other side | GND     |

### OLED (I2C)

| OLED Pin | ESP32   |
| -------- | ------- |
| VCC      | 3.3V    |
| GND      | GND     |
| SDA      | GPIO 21 |
| SCL      | GPIO 22 |

---

## Required Libraries

Install these in Arduino IDE:

* Adafruit SSD1306
* Adafruit GFX Library

---

## Main Code

This code toggles recording state when the button is pressed and shows elapsed time on the OLED.

```cpp
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int buttonPin = 19;
bool recording = false;
bool lastButtonState = HIGH;

unsigned long startTime = 0;

void setup()
{
  pinMode(buttonPin, INPUT_PULLUP);

  Serial.begin(115200);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
    while(true);
  }

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 20);
  display.println("Ready");
  display.display();
}

void loop()
{
  bool buttonState = digitalRead(buttonPin);

  if(buttonState == LOW && lastButtonState == HIGH)
  {
    recording = !recording;

    if(recording)
    {
      startTime = millis();
    }
  }

  lastButtonState = buttonState;

  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0, 0);

  if(recording)
  {
    unsigned long elapsed = (millis() - startTime) / 1000;

    display.println("REC");
    display.setTextSize(2);
    display.setCursor(0, 30);
    display.print(elapsed);
    display.println("s");
  }
  else
  {
    display.println("READY");
  }

  display.display();
  delay(100);
}
```

---

## How It Works

* Press button once → recording starts
* OLED shows REC + elapsed seconds
* Press button again → recording stops
* OLED returns to READY state

---

## Build Notes

* Make sure OLED is set to address `0x3C`
* Use internal pull-up for button
* Keep wiring short for stable button input
* Powered directly through USB

---


## License

MIT License

---

## Credits

Built by Chahatesh Killada using ESP32 Dev Kit and Arduino IDE
