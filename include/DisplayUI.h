#include <Adafruit_SSD1306.h>


#define SCREEN_ADDR 0x3C
#define OLED_SDA 21
#define OLED_SCL 22
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64


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

        DisplayUI() : display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1) {}

        void init() {
            Wire.begin(OLED_SDA, OLED_SCL);

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

                    float history[HISTORY_SIZE];
                    uint8_t drawCount = tracker.getTemperatureHistory(history, SCREEN_WIDTH);
                    if (drawCount == 0) {
                        display.setCursor(0, 16);
                        display.println("No data yet");
                        break;
                    }

                    for (uint8_t x = 0; x < drawCount; x++) {
                        int y = map(constrain(history[x], 10, 40), 10, 40, 63, 16);
                        display.drawPixel(x, y, SSD1306_WHITE);
                    }
                    break;
            }

            display.display();
        }
};