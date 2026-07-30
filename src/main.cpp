#include <Arduino.h>
#include "ConfigManager.h"
#include "WeatherSensor.h"
#include "DataTracker.h"
#include "DisplayUI.h"
#include "AlarmManager.h"


#define BUSSER_PIN  26
#define LED_PIN 25
#define BTN_NEXT_PIN 27
#define BTN_INC_PIN 14
#define BTN_DEC_PIN 12

#define OLED_SDA_PIN 21
#define OLED_SDC_PIN 22

#define DHT_PIN 4


ConfigManager configManager;
WeatherSensor sensor(DHT_PIN);
DataTracker dataTracker;
DisplayUI ui;
AlarmManager alarmManager(BUSSER_PIN, LED_PIN);

void setup() {

    Serial.begin(115200);
    Serial.println("Hello, ESP32!");

    pinMode(BTN_NEXT_PIN, INPUT_PULLUP);
    pinMode(BTN_INC_PIN, INPUT_PULLUP);
    pinMode(BTN_DEC_PIN, INPUT_PULLUP);

    pinMode(LED_PIN, OUTPUT);

    configManager.init();
    sensor.init();
    ui.init();
    alarmManager.begin();

}


void checkAlarms() {
    if (!dataTracker.hasData) {
        alarmManager.update(NAN, NAN, configManager.alarmSettings);
        return;
    }

    alarmManager.update(dataTracker.currentTemperature, dataTracker.currentHumidity, configManager.alarmSettings);
}

void handleButtons() {
    static unsigned long lastButtonPress = 0;
    if (millis() - lastButtonPress < 200) return; // Debounce

    if (digitalRead(BTN_NEXT_PIN) == LOW) {
        ui.nextScreen();
        lastButtonPress = millis();
    }

    if(ui.currentScreen == SCREEN_SETTINGS) {
        if (digitalRead(BTN_INC_PIN) == LOW) {
            configManager.alarmSettings.tempHigh += 0.5;
            configManager.save();
            lastButtonPress = millis();
        }
        if (digitalRead(BTN_DEC_PIN) == LOW) {
            configManager.alarmSettings.tempLow -= 0.5;
            configManager.save();
            lastButtonPress = millis();
        }
    }

}

void loop() {
    float t,h;
    if(sensor.read(t,h)) {
        dataTracker.update(t,h);
    }

    handleButtons();
    checkAlarms();

    ui.render(dataTracker, configManager.alarmSettings);


}

