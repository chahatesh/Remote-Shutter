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

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);

  Serial.begin(115200);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED failed");
    while (true);
  }

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 20);
  display.println("READY");
  display.display();
}

void loop() {
  bool buttonState = digitalRead(buttonPin);

  // Detect button press
  if (buttonState == LOW && lastButtonState == HIGH) {
    recording = !recording;

    if (recording) {
      startTime = millis();
      Serial.println("Recording Started");
    } else {
      Serial.println("Recording Stopped");
    }
  }

  lastButtonState = buttonState;

  // Update OLED
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0, 0);

  if (recording) {
    unsigned long elapsed = (millis() - startTime) / 1000;

    display.println("REC");
    display.setCursor(0, 30);
    display.print(elapsed);
    display.println("s");
  } else {
    display.println("READY");
  }

  display.display();
  delay(100);
}
