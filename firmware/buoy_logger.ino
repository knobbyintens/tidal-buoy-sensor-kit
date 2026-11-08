// Tidal buoy logger - low power sampling loop
#include <SD.h>
#include <OneWire.h>
#include <DallasTemperature.h>

const uint8_t kCsPin = 10;
const uint8_t kOneWirePin = 4;
const uint16_t kSampleCount = 240;

OneWire oneWire(kOneWirePin);
DallasTemperature probes(&oneWire);
File logFile;

float readPressure() {
  int raw = analogRead(A0);
  return 0.42f * raw + 1120.0f;
}

void startLog() {
  logFile = SD.open("buoy.csv", FILE_WRITE);
  if (!logFile) {
    Serial.println("SD open failed");
  } else {
    logFile.println("ms,pressure,temp");
  }
}

void logSample(uint32_t ms) {
  probes.requestTemperatures();
  float pressure = readPressure();
  float temp = probes.getTempCByIndex(0);
  if (logFile) {
    logFile.print(ms);
    logFile.print(',');
    logFile.print(pressure, 2);
    logFile.print(',');
    logFile.print(temp, 2);
    logFile.println();
  }
}

void setup() {
  Serial.begin(115200);
  probes.begin();
  if (!SD.begin(kCsPin)) {
    Serial.println("SD init failed");
  }
  startLog();
}

void loop() {
  uint32_t start = millis();
  for (uint16_t i = 0; i < kSampleCount; i++) {
    logSample(millis() - start);
    delay(250);
  }
  if (logFile) {
    logFile.close();
  }
  ESP.deepSleep(3600e6);
}
