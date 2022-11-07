#include <TMP36.h>

#define VOLTAGE 3.3

class TemperatureSensor {
  private:
    TMP36 myTMP36;

  public:
    TemperatureSensor(int pin): myTMP36(pin, VOLTAGE) {}

    float readTemp() {
      float celsius = myTMP36.getTempC();

      return celsius;
    }
};