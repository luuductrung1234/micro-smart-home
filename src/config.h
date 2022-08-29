#include <Arduino.h>
#include <SoftwareSerial.h>

#define SERIAL_COMMUNICATION_SPEED 115200
#define DEBUG "TRACE"

// ----------- SERIAL -----------
const int WIFI_RX = 2;
const int WIFI_TX = 3;
const String CWMODE = "1"; // Wifi Mode - CWMODE 1=STATION, 2=APMODE, 3=BOTH
const String CIPMUX = "0"; // Connection Mode - CWMODE 0=Single Connection, 1=Multiple Connections
const String WIFI_SSID = "Tom Luu";
const String WIFI_PASSWORD = "Trung1997";

// ----------- PIN -----------
const int ledPin = 4;
const int potPin = A0;

// ----------- INPUT PIN VALUE -----------
const int potVal = 0;