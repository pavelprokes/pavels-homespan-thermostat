#include <Wire.h>
#include "SparkFunHTU21D.h"

class HTUTemperatureSensor {
  private:
    HTU21D mujHTU; //sensor vlevo nA IIC smernici s displayem

  public:
    HTUTemperatureSensor(int pin) {
      mujHTU.begin();
    }

    float readTemp() {
      float temperature = mujHTU.readTemperature();

      if (temperature > 125) {
        LOG1("Error with sensor HTU21D!");
      } else {
        return temperature;
      }
    }
};