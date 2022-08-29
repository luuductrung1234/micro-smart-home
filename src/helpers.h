#include <Arduino.h>

void sliceLines(String data, char delimeter);

String escapeUnreadableCharacter(int decimalChar);

String getResponseValue(String response, String keyWord);