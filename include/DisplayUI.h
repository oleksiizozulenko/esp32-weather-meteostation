#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include <DataTracker.h>
#include <ConfigManager.h>

#define SCREEN_ADDR 0x3C

enum ScreenState {
    SCREEN_MAIN,
    SCREEN_SETTINGS,
   SCREEN_MINMAX, SCREEN_GRAPH
};

class DisplayUI {
    private:
        Adafruit_SSD1306 display;

    public:
        ScreenState currentScreen = SCREEN_MAIN;

        DisplayUI() : display(128, 64, &Wire, SCREEN_ADDR) {}

        void init() {
            if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDR)) {
                Serial.println(F("SSD1306 allocation failed"));
                for(;;);
            }
            display.clearDisplay();
            display.setTextColor(SSD1306_WHITE);
        }

        void nextScreen() {
            currentScreen = static_cast<ScreenState>((currentScreen + 1) % 4);
        }

        void render(const DataTracker &tracker, const AlarmSettings &alarmSettings) {
            display.clearDisplay();
            display.setCursor(0, 0);

            switch (currentScreen) {
                case SCREEN_MAIN:
                    display.setTextSize(1);
                    display.println("Main Screen");
                    display.setTextSize(2);
                    display.printf("Temp: %.2f C\n", tracker.currentTemperature);
                    display.printf("Hum: %.2f %%\n", tracker.currentHumidity);
                    break;
                case SCREEN_SETTINGS:
                    display.setTextSize(1);
                    display.println("Settings Screen");
                    display.setTextSize(2);
                    display.printf("Temp High: %.2f C\n", alarmSettings.tempHigh);
                    display.printf("Temp Low: %.2f C\n", alarmSettings.tempLow);
                    display.printf("Hum High: %.2f %%\n", alarmSettings.humHigh);
                    display.printf("Hum Low: %.2f %%\n", alarmSettings.humLow);
                    break;
                case SCREEN_MINMAX:
                    display.setTextSize(1);
                    display.println("Min/Max Screen");
                    display.setTextSize(2);
                    display.printf("Min Temp: %.2f C\n", tracker.minTemperature);
                    display.printf("Max Temp: %.2f C\n", tracker.maxTemperature);
                    display.printf("Min Hum: %.2f %%\n", tracker.minHumidity);
                    display.printf("Max Hum: %.2f %%\n", tracker.maxHumidity);
                    break;
                case SCREEN_GRAPH:
                    display.setTextSize(1);
                    display.println("Graph Screen");
                    // Here you would implement graph rendering logic
                    for (int x = 0; x < 127; x++) {
                    int idx = (tracker.historyHead + x) % HISTORY_SIZE;
                    int y = map(constrain(tracker.tempHistory[idx], 10, 40), 10, 40, 63, 16);
                    display.drawPixel(x, y, SSD1306_WHITE);
                }
                    break;
            }

            display.display();
        }
};