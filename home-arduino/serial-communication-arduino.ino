#include <ArduinoJson.h>

#define SERIAL_COMMUNICATION_SPEED 115200

// ----------- STATE -----------
float temperature = 0;
int soundValue = 0;
int lightValue = 0;
boolean isButtonHit = false;
boolean isWifiConnected = false;

void setup() {
  Serial.begin(SERIAL_COMMUNICATION_SPEED);
  
  setupLedAndButton();
  
  setupLcd();
  
  writeFirstLine("I'm ready!");
  Serial.println("I'm ready!");
}

void loop() {
  loopLedAndButton();

  readDataFromSensors();
  
  // request for wifi
  sendRequestMessage("rqw");
  
  readIncommingMessage();
}



/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
