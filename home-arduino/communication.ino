
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
    if(doc["type"] == "rqs") {
      doc["type"] = "rss";
      doc["message"] = "Hi, I'm Arduino Uno";
      doc["sensors"]["light"] = lightValue;
      doc["sensors"]["temperature"] = temperature;
      doc["sensors"]["sound"] = soundValue;
      serializeJson(doc, Serial);
    }
    // response for wifi 
    else if(doc["type"] == "rsw") {
      isWifiConnected = doc["wifi"];
      if(isWifiConnected)
        writeFirstLine("Wifi is ready!");
    }
    // response for device
    else if(doc["type"] == "rqd") {
      triggerRelay(doc["relay"]);
    }
  }

  lastRead = millis();
}

void sendRequestMessage(String type) {
  if(isWifiConnected 
    || (millis() - lastRequest < 5000)) 
    return;
  StaticJsonDocument<32> doc;
  doc["type"] = type;
  serializeJson(doc, Serial);
  lastRequest = millis();
}



/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
