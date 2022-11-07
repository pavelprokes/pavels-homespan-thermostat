#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     -1 // https://github.com/adafruit/Adafruit_SSD1306/blob/master/examples/ssd1306_128x64_i2c/ssd1306_128x64_i2c.ino
#define SCREEN_ADDRESS 0x3C

class OLEDDisplay {
  private:
    Adafruit_SSD1306 display;

  public:
    OLEDDisplay(): display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET) {
      if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        Serial.println(F("SSD1306 allocation failed"));
        for(;;);
      }

      display.display(); 
      display.clearDisplay();
    }

    void setTempAndStatus(float temp, float targetTemp, float targetMinTemp, float targetMaxTemp, int targetState, bool heaterState) {
      display.clearDisplay();

      display.setTextSize(3);
      display.setTextColor(WHITE);

      // show temp
      display.setCursor(12, 4);
      display.print(temp, 1);
      display.print((char)247);
      display.print("C");

      // show target or min&max temp
      if (targetState == 3) {
        display.setTextSize(2);
        display.setCursor(21, 30);
        display.print(targetMinTemp, 0);
        display.print("-");
        display.print(targetMaxTemp, 0);
        display.print((char)247);
        display.print("C");
      } else if (targetState == 1) {
        display.setTextSize(2);
        display.setCursor(38, 30);
        display.print(targetTemp, 0);
        display.print((char)247);
        display.print("C");
      }

      // show target state
      /*
        OFF = 0,
        HEAT = 1,
        AUTO = 3
      */
      display.setTextSize(2);
      display.setCursor(40, 49);
      switch (targetState) {
        case 0:
          display.print("OFF");
          break;
        case 1:
          display.print("HEAT");
          break;
        case 3:
        default:
          display.print("AUTO");
      }

      display.invertDisplay(heaterState);

      display.display(); 
    }
};