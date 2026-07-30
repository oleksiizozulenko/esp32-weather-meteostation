# ESP32 Weather Meteostation

This project is a compact weather station for ESP32 using a DHT temperature/humidity sensor, an SSD1306 OLED display, and a buzzer/LED alarm system.

## What it does

- reads temperature and humidity from a DHT sensor
- displays current weather data and menu screens on a 128x64 OLED
- stores alarm threshold settings in non-volatile storage
- sounds a buzzer and lights an LED when thresholds are exceeded
- supports button navigation for screen switching and alarm adjustment

## Hardware

- ESP32 Feather board (or compatible ESP32 board)
- DHT sensor on GPIO 4
- SSD1306 OLED display on I2C pins 21 (SDA) and 22 (SCL)
- buzzer on GPIO 26
- LED on GPIO 25
- buttons on GPIO 27, 14, and 12

## Software stack

- PlatformIO
- Arduino framework
- `adafruit/DHT sensor library`
- `adafruit/Adafruit SSD1306`

## Project files

- `src/main.cpp` - main firmware entry point and loop
- `include/ConfigManager.h` - alarm threshold configuration persistence
- `include/WeatherSensor.h` - DHT sensor reading logic
- `include/DataTracker.h` - weather value tracking and state
- `include/DisplayUI.h` - OLED rendering and screen navigation
- `include/AlarmManager.h` - buzzer/LED alarm logic
- `platformio.ini` - PlatformIO build configuration
- `diagram.json` - circuit diagram for simulation or documentation
- `wokwi.toml` - Wokwi simulation settings

## Build and upload

1. Install PlatformIO and the VS Code PlatformIO extension.
2. Open this project folder in VS Code.
3. Build the firmware:

```bash
pio run
```

4. Upload to the ESP32 board:

```bash
pio run --target upload
```

## Notes

- The default board environment is `featheresp32` in `platformio.ini`.
- If you change wiring or pins, update the pin definitions in `src/main.cpp`.
- The alarm thresholds are saved automatically when adjusted from the settings screen.

## License

This project is provided for learning and experimentation.
