#include <Arduino.h>

boolean sendCommand(String command, const String expected_response, const int timeout, const String debug);

String getResponse(String start_with_response, const int timeout, const String debug);

boolean initWifiModule();

boolean connectWiFi(String ssid, String password);

boolean isWifiConnected();

String getIpAddress();

String formatUrl(String url);