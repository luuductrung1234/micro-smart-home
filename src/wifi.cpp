/*******************************************************************************
 * ESP8266 Wifi module for Arduino.
 *
 * Author: Luu Duc Trung
 * Website: https://github.com/luuductrung1234
 * Email:   s3951127@rmit.edu.vn
 *******************************************************************************/

#include <Arduino.h>
#include <helpers.h>
#include <config.h>

SoftwareSerial esp8266(WIFI_RX, WIFI_TX);
boolean esp8266Initialized = false;

String formatUrl(String url)
{
	url.replace("%", "%25");
	url.replace(" ", "%20");
	url.replace("!", "%21");
	url.replace("\"", "%22");
	url.replace("#", "%23");
	url.replace("$", "%24");
	url.replace("&", "%26");
	url.replace("'", "%27");
	url.replace("(", "%28");
	url.replace(")", "%29");
	url.replace("*", "%2A");
	url.replace("+", "%2B");
	url.replace(",", "%2C");
	url.replace("-", "%2D");
	url.replace(".", "%2E");
	url.replace("/", "%2F");
	url.replace(":", "%3A");
	url.replace(";", "%3B");
	url.replace("<", "%3C");
	url.replace("=", "%3D");
	url.replace(">", "%3E");
	url.replace("?", "%3F");
	url.replace("@", "%40");
	url.replace("[", "%5B");
	url.replace("\\", "%5C");
	url.replace("]", "%5D");
	url.replace("^", "%5E");
	url.replace("_", "%5F");
	url.replace("`", "%60");
	url.replace("{", "%7B");
	url.replace("|", "%7C");
	url.replace("}", "%7D");
	url.replace("~", "%7E");
	return url;
}

/*
 *
 */
void cleanBuffer(boolean debug)
{
	String temp;
	while (esp8266.available())
	{
		char c = esp8266.read();
		temp += c;
		delay(1);
	}
	if (debug)
	{
		Serial.println(temp);
	}
}

boolean sendCommand(String command, const String expected_response, const int timeout, const String debug)
{
	delay(10);

	if (debug == "INFO" || debug == "TRACE")
	{
		Serial.println(command);
	}

	// flush the Rx buffer
	cleanBuffer(false);
	String response = "";

	// send the command and end with "\r\n"
	esp8266.print(command + "\r\n");

	if (expected_response == "")
	{
		Serial.println("Stop, not expect anything.");
		return true;
	}

	// Wait and verify the response.
	boolean result = false;
	long int timestamp = millis();

	while (true)
	{
		if ((unsigned)(timestamp + timeout) < millis())
		{
			Serial.println("timeout with no result.");
			result = false;
			break;
		}

		if (!esp8266.available())
		{
			continue;
		}

		// read until the end of the line
		char c = esp8266.read();
		if (((int)c) <= 0 || ((int)c) == 13 || ((int)c) == 3 || ((int)c) == 4 || ((int)c) == 1 || ((int)c) == 30 || ((int)c) == 28 || ((int)c) == 12 || ((int)c) == 15 || ((int)c) == 25 || ((int)c) == 19 || ((int)c) == 7 || ((int)c) == 6)
			continue;
		else if (((int)c) == 10)
			response += "\r\n";
		else
			response += c;
		if (debug == "TRACE")
		{
			Serial.println((int)c);
			Serial.println(response);
		}
		if (response.indexOf("\r\n") != -1)
		{
			// check if expected response received.
			if (response.substring(0, response.indexOf("\r\n")).indexOf(expected_response) != -1)
			{
				result = true;
				break;
			}

			// if we expected "OK" but "ERROR" is received, do not wait for timeout.
			if (expected_response == "OK")
			{
				if (response.substring(0, response.indexOf("\r\n")).indexOf("ERROR") != -1)
				{
					result = false;
					break;
				}
			}

			// trim the Rx data before loop again.
			response = response.substring(response.indexOf("\r\n") + 2);
		}
	}

	if (debug == "INFO" || debug == "TRACE")
	{
		Serial.println("--- start print debug ---");
		Serial.println(response);
		Serial.println("--- end print debug ---");
	}
	return result;
}

String sendCommandAndGet(String command, const String expected_response, const int timeout, const String debug)
{
	delay(10);

	if (debug == "INFO" || debug == "TRACE")
	{
		Serial.println(command);
	}

	// flush the Rx buffer
	cleanBuffer(false);
	String response = "";

	// send the command and end with "\r\n"
	esp8266.print(command + "\r\n");

	if (expected_response == "")
	{
		Serial.println("Stop, not expect anything.");
		return "";
	}

	// Wait and verify the response.
	boolean result = false;
	long int timestamp = millis();

	while (true)
	{
		if ((unsigned)(timestamp + timeout) < millis())
		{
			Serial.println("timeout with no result.");
			result = false;
			break;
		}

		if (!esp8266.available())
		{
			continue;
		}

		// read until the end of the line
		char c = esp8266.read();
		if (((int)c) <= 0 || ((int)c) == 13 || ((int)c) == 3 || ((int)c) == 4 || ((int)c) == 1 || ((int)c) == 30 || ((int)c) == 28 || ((int)c) == 12 || ((int)c) == 15 || ((int)c) == 25 || ((int)c) == 19 || ((int)c) == 7 || ((int)c) == 6)
			continue;
		else if (((int)c) == 10)
			response += "\r\n";
		else
			response += c;
		if (debug == "TRACE")
		{
			Serial.println((int)c);
			Serial.println(response);
		}
		if (response.indexOf("\r\n") != -1)
		{
			// check if expected response received.
			if (response.substring(0, response.indexOf("\r\n")).indexOf(expected_response) != -1)
			{
				result = true;
				break;
			}

			// if we expected "OK" but "ERROR" is received, do not wait for timeout.
			if (expected_response == "OK")
			{
				if (response.substring(0, response.indexOf("\r\n")).indexOf("ERROR") != -1)
				{
					result = false;
					break;
				}
			}

			// trim the Rx data before loop again.
			response = response.substring(response.indexOf("\r\n") + 2);
		}
	}

	if (debug == "INFO" || debug == "TRACE")
	{
		Serial.println("--- start print debug ---");
		Serial.println(response);
		Serial.println("--- end print debug ---");
	}
	return result ? response : "";
}

String getResponse(String start_with_response, const int timeout, const String debug)
{
	String responseLine = "";
	String rxData = "";
	long int timestamp = millis();

	while (true)
	{
		if ((unsigned)(timestamp + timeout) < millis())
		{
			if (rxData.indexOf(start_with_response) != -1)
			{
				responseLine = rxData;
			}
			break;
		}

		// read until the end of the line
		char c = esp8266.read();
		if (((int)c) <= 0 || ((int)c) == 13 || ((int)c) == 3 || ((int)c) == 4 || ((int)c) == 1 || ((int)c) == 30 || ((int)c) == 28 || ((int)c) == 12 || ((int)c) == 15 || ((int)c) == 25 || ((int)c) == 19 || ((int)c) == 7 || ((int)c) == 6)
			continue;
		else if (((int)c) == 10)
			rxData += "\r\n";
		else
			rxData += c;
		if (debug == "TRACE")
		{
			Serial.println((int)c);
			Serial.println(rxData);
		}
		if (rxData.indexOf("\r\n") != -1)
		{
			// check if expected response received
			if (rxData.substring(0, rxData.indexOf("\r\n")).indexOf(start_with_response) != -1)
			{
				responseLine = rxData.substring(0, rxData.indexOf("\r\n"));

				// trim the Rx data for next call
				rxData = rxData.substring(rxData.indexOf("\r\n") + 2);
				break;
			}

			// trim the Rx data before loop again
			rxData = rxData.substring(rxData.indexOf("\r\n") + 2);
		}
	}

	if (debug == "INFO" || debug == "TRACE")
	{
		Serial.println("--- start print debug ---");
		Serial.println(rxData);
		Serial.println("--- end print debug ---");
	}
	return responseLine;
}

boolean initWifiModule()
{
	esp8266.begin(SERIAL_COMMUNICATION_SPEED);
	esp8266Initialized = false;

	// Restore the ESP8266 factory settings.
	if (sendCommand("AT+RESTORE", "ready", 5000, DEBUG) == false)
	{
		Serial.println("restore ESP8266 failed");
		return false;
	}
	else
		Serial.println("restore ESP8266 successfully");

	// Turn off echo.
	if (sendCommand("ATE0", "OK", 5000, DEBUG) == false)
	{
		Serial.println("turn off echo fail");
		return false;
	}
	else
		Serial.println("turn off echo successfully");

	Serial.println("Wifi initialized successfully");
	// Initialized successfully.
	// Set the flag.
	esp8266Initialized = true;
	return true;
}

boolean connectWiFi(String ssid, String password)
{
	// Set wifi mode.
	if (sendCommand("AT+CWMODE=" + CWMODE, "OK", 1000, DEBUG) == false)
	{
		Serial.println("change wifi mode failed");
		return false;
	}
	else
	{
		Serial.println("change wifi mode successfully");
		delay(1000);
	}

	// Connect to WiFi router.
	if (sendCommand("AT+CWJAP=\"" + ssid + "\",\"" + password + "\"", "OK", 20000, DEBUG) == false)
	{
		Serial.println("connect wifi failed");
		return false;
	}
	else
	{
		Serial.println("connect wifi successfully");
		delay(1000);
	}

	// Set connection mode.
	if (sendCommand("AT+CIPMUX=" + CIPMUX, "OK", 5000, DEBUG) == false)
	{
		Serial.println("change connection mode failed");
		return false;
	}
	else
	{
		Serial.println("change connection mode successfully");
		delay(1000);
	}

	return true;
}

boolean isWifiConnected()
{
	// Get the connection status.
	sendCommand("AT+CIPSTATUS", "STATUS:", 1000, DEBUG);
	return false;
	String status = getResponse("STATUS:", 1000, DEBUG);
	Serial.println("Found " + status);

	// Wait until OK is received.
	String endCommand = getResponse("OK", 1000, DEBUG);

	// Return the WiFi status.
	if (status == "" || status.indexOf("STATUS:2") == -1)
	{
		return false;
	}
	else
	{
		return true;
	}
}

String getIpAddress()
{
	sendCommand("AT+CIFSR", "", 1000, DEBUG);
	String ipAddress = getResponse("+CIFSR:STAIP", 1000, DEBUG);
	ipAddress = getResponseValue(ipAddress, "+CIFSR:STAIP,\"");
	Serial.println("Found " + ipAddress);
	return ipAddress;
}
