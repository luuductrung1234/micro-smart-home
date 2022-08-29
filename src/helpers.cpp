#include <Arduino.h>

void sliceLines(String data, char delimeter)
{
	String remainingData = data;
	Serial.println(remainingData);
	while (true)
	{
		if (remainingData.indexOf(delimeter) == -1)
		{
			break;
		}
		String line = remainingData.substring(0, remainingData.indexOf(delimeter));
		Serial.println(line);
		remainingData = remainingData.substring(remainingData.indexOf(delimeter), remainingData.length() - 1);
	}
}

String escapeUnreadableCharacter(int decimalChar)
{
	Serial.println(decimalChar);
	if ((decimalChar >= 0 && decimalChar <= 9) || decimalChar < 0 || (decimalChar > 10 && decimalChar <= 31))
	{
		return "";
	}
}

String getResponseValue(String response, String keyWord)
{
	return response.substring(keyWord.length(), response.length() - 1);
}
