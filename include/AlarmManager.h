#pragma once

#include <Arduino.h>
#include "ConfigManager.h"

class AlarmManager {
public:
    AlarmManager(uint8_t buzzerPin, uint8_t ledPin)
        : buzzerPin_(buzzerPin), ledPin_(ledPin), alarmActive_(false) {}

    void begin() {
        pinMode(buzzerPin_, OUTPUT);
        pinMode(ledPin_, OUTPUT);
        setAlarmState(false);
    }

    void update(float temperature, float humidity, const AlarmSettings& settings) {
        if (isnan(temperature) || isnan(humidity)) {
            setAlarmState(false);
            return;
        }

        const bool tempAlarm = temperature <= settings.tempLow + kTempAlertTolerance ||
                               temperature >= settings.tempHigh - kTempAlertTolerance;
        const bool humidityAlarm = humidity <= settings.humLow + kHumidityAlertTolerance ||
                                   humidity >= settings.humHigh - kHumidityAlertTolerance;
        const bool isAlarm = tempAlarm || humidityAlarm;

        setAlarmState(isAlarm);
    }

private:
    static constexpr float kTempAlertTolerance = 0.5f;
    static constexpr float kHumidityAlertTolerance = 2.0f;

    uint8_t buzzerPin_;
    uint8_t ledPin_;
    bool alarmActive_;

    void setAlarmState(bool active) {
        alarmActive_ = active;

        if (!alarmActive_) {
            noTone(buzzerPin_);
            digitalWrite(ledPin_, LOW);
            return;
        }

        if ((millis() / 500) % 2 == 0) {
            tone(buzzerPin_, 2000);
            digitalWrite(ledPin_, HIGH);
        } else {
            noTone(buzzerPin_);
            digitalWrite(ledPin_, LOW);
        }
    }
};
