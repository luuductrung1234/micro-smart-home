#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266WebServer.h>

#include <ESP8266HTTPClient.h>

#include <WiFiClient.h>

ESP8266WiFiMulti WiFiMulti;
ESP8266WebServer server;

const char* ssid     = "Tom Luu";
const char* password = "Trung1997";

const String host = "http://microsmartdemo-env.eba-nudppsiw.ap-southeast-1.elasticbeanstalk.com";
const int userCredential = 2;


// ----------- STATE -----------
unsigned long lastSendEnv = 0;
unsigned long lastGetDelivery = 0;
unsigned long lastGetDevice = 0;

void setupWifi() {
  delay(100);
  
  for (uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(ssid, password);

  Serial.println("");
  if ((WiFiMulti.run(5000) == WL_CONNECTED)) {
    isWifiConnected = true;
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    server.on("/", handleIndex);
    server.begin();
  } else {
    isWifiConnected = false;
    Serial.println("WiFi not connected!");
  }
}

void loopWifi() {
  if(isButtonBHit) {
    sendEnvironmentCondition();
    getDevice();
  }
  
  server.handleClient();
}

void handleIndex()
{
  String output = "light: " + String(lightValue) + "\n" 
    + "temperature: " + String(temperature) + "\n"
    + "sound: " + String(soundValue) + "\n";
  // Serve the data as plain text, for example
  server.send(200,"text/plain", output);
}

void sendEnvironmentCondition() {
  if(!isWifiConnected
    || (millis() - lastSendEnv < 5000)) 
    return;
  
  WiFiClient client;
  HTTPClient http;

  String queryStr = String(userCredential) + "/environment/:update?light=" + String(lightValue) 
    + "&temperature=" + String(temperature)
    + "&sound=" + String(soundValue);

  if (http.begin(client, host + "/api/v1/users/" + queryStr)) {  // HTTP
    // start connection and send HTTP header
    int httpCode = http.GET();

    // httpCode will be negative on error
    if (httpCode > 0) {
      // file found at server
      if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
        String payload = http.getString();
        //Serial.println(payload);
      }
    } else {
      Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();
  } else {
    Serial.printf("[HTTP} Unable to connect\n");
  }

  lastSendEnv = millis();
}

void getDevice() {
  if(!isWifiConnected
    || (millis() - lastGetDevice < 5000)) 
    return;
  
  WiFiClient client;
  HTTPClient http;

  String queryStr = String(userCredential) + "/devices";

  if (http.begin(client, host + "/api/v1/users/" + queryStr)) {  // HTTP
    // start connection and send HTTP header
    int httpCode = http.GET();

    // httpCode will be negative on error
    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled

      // file found at server
      if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
        String payload = http.getString();
        String deviceValue = payload.substring(payload.indexOf(":") + 1, payload.length());
        //Serial.println(payload);
        sendDeviceRequest(deviceValue == "true");
      }
    } else {
      Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();
  } else {
    Serial.printf("[HTTP} Unable to connect\n");
  }

  lastGetDevice = millis();
}

String getDeliveryPath() {
  if(!isWifiConnected
    || (millis() - lastGetDelivery < 5000)) 
    return "";
  
  WiFiClient client;
  HTTPClient http;

  Serial.print("[HTTP] begin...\n");
  if (http.begin(client, host + "/api/v1/tickets/:pick")) {  // HTTP
    Serial.print("[HTTP] GET...\n");
    // start connection and send HTTP header
    int httpCode = http.GET();

    // httpCode will be negative on error
    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTP] GET... code: %d\n", httpCode);

      // file found at server
      if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
        String payload = http.getString();
        Serial.println(payload);
        lastGetDelivery = millis();
        http.end();
        return payload;
      }
    } else {
      Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();
  } else {
    Serial.printf("[HTTP} Unable to connect\n");
  }

  lastGetDelivery = millis();
  return "";
}



/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
