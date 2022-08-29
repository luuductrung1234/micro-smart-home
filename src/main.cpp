#include <Arduino.h>
#include <config.h>
#include <wifi.h>
#include <eshop.h>

void setup()
{
	// put your setup code here, to run once:
	Serial.begin(SERIAL_COMMUNICATION_SPEED);

	if (!initWifiModule())
	{
		Serial.println("Stop because fail to init wifi module");
		return;
	}

	delay(500);

	if (!connectWiFi(WIFI_SSID, WIFI_PASSWORD))
	{
		Serial.println("Stop because fail to connect wifi");
		return;
	}

	delay(500);

	if (isWifiConnected())
	{
		Serial.println("Hello World!");
	}
	else
	{
		Serial.println("You are not connected to the Internet!");
		return;
	}

	delay(500);
	Serial.println("IP Address: " + getIpAddress());

	delay(500);
	Serial.println("Delivery Path: " + pickRequest());
}

void loop()
{
	// put your main code here, to run repeatedly:
	// put your main code here, to run repeatedly:
	// potVal = analogRead(potPin);
	// Serial.println(potVal);
	// analogWrite(ledPin, potVal / 4);
	// delay(500);
}