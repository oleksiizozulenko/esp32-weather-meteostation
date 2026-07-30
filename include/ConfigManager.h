#pragma once

#include <Preferences.h>

struct AlarmSettings {
    float tempHigh;
    float tempLow;
    float humHigh;
    float humLow;
};

class ConfigManager {
    private:
        static constexpr float kDefaultTempHigh = 30.0f;
        static constexpr float kDefaultTempLow = 5.0f;
        static constexpr float kDefaultHumHigh = 80.0f;
        static constexpr float kDefaultHumLow = 20.0f;

        Preferences preferences;

        void applyDefaults() {
            alarmSettings.tempHigh = kDefaultTempHigh;
            alarmSettings.tempLow = kDefaultTempLow;
            alarmSettings.humHigh = kDefaultHumHigh;
            alarmSettings.humLow = kDefaultHumLow;
        }

    public:
        AlarmSettings alarmSettings;

        ConfigManager() {
            applyDefaults();
        }

        void init() {
            preferences.begin("weather_config", false);

            alarmSettings.tempHigh = preferences.getFloat("t_high", kDefaultTempHigh);
            alarmSettings.tempLow = preferences.getFloat("t_low", kDefaultTempLow);
            alarmSettings.humHigh = preferences.getFloat("h_high", kDefaultHumHigh);
            alarmSettings.humLow = preferences.getFloat("h_low", kDefaultHumLow);

            preferences.end();
        }

        void save() {
            preferences.begin("weather_config", false);
            preferences.putFloat("t_high", alarmSettings.tempHigh);
            preferences.putFloat("t_low", alarmSettings.tempLow);
            preferences.putFloat("h_high", alarmSettings.humHigh);
            preferences.putFloat("h_low", alarmSettings.humLow);
            preferences.end();
        }
};