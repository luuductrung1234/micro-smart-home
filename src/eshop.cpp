/*******************************************************************************
 * EShop API client.
 *
 * Author: Luu Duc Trung
 * Website: https://github.com/luuductrung1234
 * Email:   s3951127@rmit.edu.vn
 *******************************************************************************/

#include <Arduino.h>
#include <config.h>
#include <helpers.h>
#include <wifi.h>

const String IP_NETWORK = "2"; // 1: preferred resolution of IPv4 address, 2: resolve IPv4 address only, 3: resolve IPv6 address only

const String ESHOP_API_URL = "microsmartdemo-env.eba-nudppsiw.ap-southeast-1.elasticbeanstalk.com";
const String ESHOP_API_URL_FALLBACK = "18.136.9.106";

boolean eshopRequestSent = false;

String resolveDomainName()
{
	// Make sure the WiFi is connected.
	if (isWifiConnected() == false)
	{
		Serial.println("Wifi is not connected - Fail to make a request to EShop");
		return "";
	}

	delay(1000);

	if (sendCommand("AT+CIPDOMAIN=\"" + ESHOP_API_URL + "\"," + IP_NETWORK, "", 1000, DEBUG) == false)
	{
		Serial.println("Fail to resolve a Domain Name - Fail to make a request to EShop");
		return "";
	}
	String eShopIp = getResponse("+CIPDOMAIN", 1000, DEBUG);
	eShopIp = getResponseValue(eShopIp, "+CIPDOMAIN:\"");
	Serial.println("EShop IP: " + eShopIp);
	return eShopIp;
}

String pickRequest()
{
	// Reset the upload successful flag.
	eshopRequestSent = false;

	// String eShopIp = resolveDomainName();
	String eShopIp = ESHOP_API_URL_FALLBACK;

	delay(1000);

	// Connect to server. Return if failed.
	if (sendCommand("AT+CIPSTART=\"TCP\",\"" + eShopIp + "\",80", "CONNECT", 10000, DEBUG) == false)
	{
		sendCommand("AT+CIPCLOSE", "OK", 1000, DEBUG);
		Serial.println("Fail to establish TCP connection - Fail to make a request to EShop");
		return "";
	}

	// Construct the data to send.
	String data = "GET /api/v1/tickets/:pick";

	// Send the data.
	String dataLength = String(data.length() + 2);
	sendCommand("AT+CIPSEND=" + dataLength, "OK", 5000, DEBUG);
	sendCommand(data, "", 1000, DEBUG);

	// Return if "SEND OK" is not received.
	String sentStatus = getResponse("SEND OK", 1000, DEBUG);
	if (sentStatus == "")
	{
		// Close the connection and return.
		sendCommand("AT+CIPCLOSE", "OK", 1000, DEBUG);
		Serial.println("Fail to send request - Fail to make a request to EShop");
		return "";
	}

	// Return if Sample API response is not 200.
	String response = getResponse("+IPD", 10000, DEBUG);
	if (response == "")
	{
		// Close the connection and return.
		sendCommand("AT+CIPCLOSE", "OK", 1000, DEBUG);
		Serial.println("Nothing has been responsed - Fail to make a request to EShop");
		return "";
	}

	// Close the connection.
	sendCommand("AT+CIPCLOSE", "OK", 1000, DEBUG);

	// Set the upload successful flag and return.
	eshopRequestSent = true;
	if (response.indexOf(":") == -1)
		return "";
	String splittedResponse = response.substring(response.indexOf(":"), response.length() - 1);
	return splittedResponse;
}