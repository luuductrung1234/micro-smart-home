#include <WiFi.h>

const char* ssid     = "Tom Luu";
const char* password = "Trung1997";

const char* host = "microsmartdemo-env.eba-nudppsiw.ap-southeast-1.elasticbeanstalk.com";

// ----------- STATE -----------
unsigned long lastGetDelivery = 0;

void setupWifi() {
  delay(1000);
  WiFi.begin(ssid, password);
  delay(1000);
  
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }

  Serial.println("");
  isWifiConnected = true;
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loopWifi() {
  getDeliveryPath();
}

void getDeliveryPath () {
  if(!isWifiConnected
    || deliveryPath.length() > 0
    || (millis() - lastGetDelivery < 5000)) 
    return;
  
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
      Serial.println("connection failed");
      return;
  }

  // We now create a URI for the request
  String url = "/api/v1/tickets/:pickAndProcess";
  
  Serial.print("Requesting URL: ");
  Serial.println(url);

  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
    "Host: " + host + "\r\n" +
    "Connection: close\r\n\r\n");
  
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      lastGetDelivery = millis();
      return;
    }
  }

  String dataStr = "";
  while(client.available()) {
    String line = client.readStringUntil('\r');
    dataStr += line;
  }

  lastGetDelivery = millis();
  if(dataStr.indexOf("HTTP/1.1 404") != -1) {
    printLcd("No ticket found", "waiting. . .");
  } else {
    Serial.println(dataStr);
    deliveryPath = dataStr;
    printLcd("Ticket found!", "deliverying. . .");
  }
  
  Serial.println();
  Serial.println("closing connection");
}


// =============================================================================================
// END FILE
// =============================================================================================
