
#include <ArduinoJson.h>

// ----------- DATA -----------
float temperature = 0;
int soundValue = 0;
int lightValue = 0;
boolean isButtonAHit = false;
boolean isButtonBHit = false;
boolean isWifiConnected = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);

  setupLedAndButton();

  setupWifi();
  //getDeliveryPath();
}

void loop() {
  // put your main code here, to run repeatedly:
  loopLedAndButton();

  // request for sensors
  sendRequestMessage("rqs");
  
  readIncommingMessage();
  
  loopWifi();
}



/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
