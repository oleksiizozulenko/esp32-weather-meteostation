#include <Arduino.h>
#include "ConfigManager.h"
#include "WeatherSensor.h"
#include "DataTracker.h"
#include "DisplayUI.h"


#define BUSSER_PIN  26
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

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Hello, ESP32!");

  pinMode(BTN_NEXT_PIN, INPUT_PULLUP);
  pinMode(BTN_INC_PIN, INPUT_PULLUP);
  pinMode(BTN_DEC_PIN, INPUT_PULLUP);



  pinMode(BUSSER_PIN, OUTPUT);

    configManager.init();
    sensor.init();
    ui.init();

}


void checkAlarms() {
    if (!dataTracker.hasData) {
        noTone(BUSSER_PIN);
        return;
    }

   bool isAlarm = (dataTracker.currentTemperature > configManager.alarmSettings.tempHigh ||
                    dataTracker.currentTemperature < configManager.alarmSettings.tempLow ||
                    dataTracker.currentHumidity > configManager.alarmSettings.humHigh ||
                    dataTracker.currentHumidity < configManager.alarmSettings.humLow);


                    Serial.printf("Temp: %.2f C, Hum: %.2f %%\n", dataTracker.currentTemperature, dataTracker.currentHumidity);
                    Serial.printf("Min Temp: %.2f C, Max Temp: %.2f C\n", dataTracker.minTemperature, dataTracker.maxTemperature);
                    Serial.printf("Min Hum: %.2f %%, Max Hum: %.2f %%\n", dataTracker.minHumidity, dataTracker.maxHumidity);


    if (isAlarm) {
        if ((millis() / 500) % 2 == 0) {
            tone(BUSSER_PIN, 2000); // 2000 Гц
        } else {
            noTone(BUSSER_PIN);
        }
    } else {
        noTone(BUSSER_PIN);
    }
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

