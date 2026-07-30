#define HISTORY_SIZE 128

class DataTracker {
    public:
        float currentTemperature = 0.0, currentHumidity = 0.0;
        float minTemperature = -40.0, maxTemperature = 40.0;
        float minHumidity = 0.0, maxHumidity = 100.0;

    private:
        float temperatureHistory[HISTORY_SIZE] = {0};
        uint8_t historyIndex = 0;
        uint8_t historyCount = 0;

        void addTemperatureSample(float temperature) {
            temperatureHistory[historyIndex] = temperature;
            historyIndex = (historyIndex + 1) % HISTORY_SIZE; // this is rolling index. if historyIndex reaches HISTORY_SIZE, it wraps around to 0
            if (historyCount < HISTORY_SIZE) {
                historyCount++;
            }
        }

    public:
        bool hasData = false;

        uint8_t getTemperatureHistory(float* outHistory, uint8_t maxCount) const {
            uint8_t count = min(historyCount, maxCount);
            uint8_t startIndex = (historyIndex + HISTORY_SIZE - count) % HISTORY_SIZE;
            for (uint8_t i = 0; i < count; i++) {
                outHistory[i] = temperatureHistory[(startIndex + i) % HISTORY_SIZE];
            }
            return count;
        }

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

            addTemperatureSample(temperature);
        }
};