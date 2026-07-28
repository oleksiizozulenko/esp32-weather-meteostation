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

        void  init() {
            preferences.begin("weather_config", false);

            if(preferences.isKey("t_high") && preferences.isKey("t_low") &&
               preferences.isKey("h_high") && preferences.isKey("h_low")) {

            alarmSettings.tempHigh = preferences.getFloat("t_high", 40.0);
            alarmSettings.tempLow = preferences.getFloat("t_low", 5.0);
            alarmSettings.humHigh = preferences.getFloat("h_high", 80.0);
            alarmSettings.humLow = preferences.getFloat("h_low", 20.0);
               }
        }

        void save() {
            preferences.putFloat("t_high", alarmSettings.tempHigh);
            preferences.putFloat("t_low", alarmSettings.tempLow);
            preferences.putFloat("h_high", alarmSettings.humHigh);
            preferences.putFloat("h_low", alarmSettings.humLow);
        }
};