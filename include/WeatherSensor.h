#include <DHT.h>

class WeatherSensor {
    private:
        DHT dht;
        unsigned long lastReadTime = 0;
        const unsigned long readInterval = 2000; // Read every 2 seconds

    public:
        WeatherSensor(uint8_t pin) : dht(pin, DHT22) {}

        void init() {
            dht.begin();
        }

        float readTemperature() {
            if (millis() - lastReadTime >= readInterval) {
                lastReadTime = millis();
                return dht.readTemperature();
            }
            return NAN;
        }

        float readHumidity() {
            if (millis() - lastReadTime >= readInterval) {
                lastReadTime = millis();
                return dht.readHumidity();
            }
            return NAN;
        }

        float read(float &temperature, float &humidity) {
            if (millis() - lastReadTime >= readInterval) {
                lastReadTime = millis();
                temperature = dht.readTemperature();
                humidity = dht.readHumidity();
                return !isnan(temperature) && !isnan(humidity);
            }
            return false;
        }
};