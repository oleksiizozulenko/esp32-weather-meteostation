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
        Preferences preferences;

    public:
        AlarmSettings alarmSettings;

        ConfigManager() {
            alarmSettings.tempHigh = 30.0f;
            alarmSettings.tempLow = 5.0f;
            alarmSettings.humHigh = 80.0f;
            alarmSettings.humLow = 20.0f;
        }

        void init() {
            preferences.begin("weather_config", false);

            alarmSettings.tempHigh = preferences.getFloat("t_high", 30.0f);
            alarmSettings.tempLow = preferences.getFloat("t_low", 5.0f);
            alarmSettings.humHigh = preferences.getFloat("h_high", 80.0f);
            alarmSettings.humLow = preferences.getFloat("h_low", 20.0f);

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