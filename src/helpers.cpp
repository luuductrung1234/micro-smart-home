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

String getResponseValue(String response, String keyWord)
{
	return response.substring(keyWord.length(), response.length() - 1);
}
