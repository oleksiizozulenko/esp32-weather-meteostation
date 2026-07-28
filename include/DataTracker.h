#define HISTORY_SIZE 128

class DataTracker {
    public:
        float currentTemperature = 0.0, currentHumidity = 0.0;
        float minTemperature = 99.0, maxTemperature = -99.0;
        float minHumidity = 100.0, maxHumidity = -100.0;

        float temperatureHistory[HISTORY_SIZE] = {0};
        uint8_t historyIndex = 0;

        void update(float temperature, float humidity) {
            if(isnan(temperature) || isnan(humidity)) {
                Serial.println("Failed to read from DHT sensor!");
                return;
            }

            currentTemperature = temperature;
            currentHumidity = humidity;

            if (temperature < minTemperature) minTemperature = temperature;
            if (temperature > maxTemperature) maxTemperature = temperature;

            if (humidity < minHumidity) minHumidity = humidity;
            if (humidity > maxHumidity) maxHumidity = humidity;

            temperatureHistory[historyIndex] = temperature;
            historyIndex = (historyIndex + 1) % HISTORY_SIZE;
        }
};