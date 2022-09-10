
// ----------- STATE -----------
unsigned long lastRead = 0;
unsigned long lastRequest = 0;

void readIncommingMessage() {
  if(millis() - lastRead < 1000) {
    return;
  }
  
  String message = "";
  boolean messageReady = false;
  while(Serial.available()) {
    message = Serial.readString();
    messageReady = true;
  }

  // Only process message if there's one
  if(messageReady) {
    // The only messages we'll parse will be formatted in JSON
    //DynamicJsonDocument doc(2048); // ArduinoJson version 6+
    StaticJsonDocument<200> doc;
    
    // Attempt to deserialize the message
    DeserializationError error = deserializeJson(doc, message);
    
    if(error) {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.c_str());
      lastRead = millis();
      return;
    }

    // request for sensors
    if(doc["type"] == "rqw") {
      doc["type"] = "rsw";
      doc["wifi"] = isWifiConnected;
      serializeJson(doc, Serial);
    }
    // response for wifi 
    else if(doc["type"] == "rss") {
      lightValue = doc["sensors"]["light"];
      temperature = doc["sensors"]["temperature"];
      soundValue = doc["sensors"]["sound"];
    }
  }

  lastRead = millis();
}

/*
 * Send request with delay
 */
void sendRequestMessage(String type) {
  if(millis() - lastRequest < 5000) 
    return;
  StaticJsonDocument<32> doc;
  doc["type"] = type;
  serializeJson(doc, Serial);
  lastRequest = millis();
}

/*
 * Send device request without delay
 */
void sendDeviceRequest(boolean onRelay) {
  StaticJsonDocument<32> doc;
  doc["type"] = "rqd";
  doc["relay"] = onRelay;
  serializeJson(doc, Serial);
  lastRequest = millis();
}



/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
