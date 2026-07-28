#define HISTORY_SIZE 128

class DataTracker {
    public:
        float currentTemperature = 0.0, currentHumidity = 0.0;
        float minTemperature = -40.0, maxTemperature = 40.0;
        float minHumidity = 0.0, maxHumidity = 100.0;

        float temperatureHistory[HISTORY_SIZE] = {0};
        uint8_t historyIndex = 0;
        bool hasData = false;

        void update(float temperature, float humidity) {
            if(isnan(temperature) || isnan(humidity)) {
                Serial.println("Failed to read from DHT sensor!");
                return;
            }

            currentTemperature = temperature;
            currentHumidity = humidity;
            hasData = true;

            if (temperature < minTemperature) minTemperature = temperature;
            if (temperature > maxTemperature) maxTemperature = temperature;

            if (humidity < minHumidity) minHumidity = humidity;
            if (humidity > maxHumidity) maxHumidity = humidity;

            temperatureHistory[historyIndex] = temperature;
            historyIndex = (historyIndex + 1) % HISTORY_SIZE;
        }
};