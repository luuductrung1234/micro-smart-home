
// ----------- DATA -----------
boolean isWifiConnected = false;
String deliveryPath = "";

void setup()
{
  // Serial monitor setup
  Serial.begin(115200);

  setupMotors();

  setupWifi();

  setupLcd();
}

void loop()
{
  loopWifi();
  loopMotors();
}



// =============================================================================================
// END FILE
// =============================================================================================
