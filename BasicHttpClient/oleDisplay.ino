
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setupOled() {
  USE_SERIAL.begin(115200);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    USE_SERIAL.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
}

void updateOled(){
  // Clear the buffer
  display.clearDisplay();

  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 8);
  display.print(F("Temp:"));
  display.println(temperature);
  display.println();
  display.print(F("Hum :"));
  display.println(humidity);
  display.display();      // Show initial text
}

void updateOled11(){
  // Clear the buffer
//  display.clearDisplay();
  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(60, 8);
  display.println("     ");
  display.setCursor(60, 40);
  display.println("     ");
  display.display();      // Show initial text
  delay(2000);
  display.setCursor(60, 8);
  display.println(temperature);
  display.setCursor(60, 40);
  display.println(humidity);
  display.display();      // Show initial text
}
