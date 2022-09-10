
// ----------- ANALOG PIN -----------
const int pinLight = A0;
const int pinTemp = A1;
const int pinSound = A2;

// ----------- STATE -----------
unsigned long lastReadData = 0;

void readDataFromSensors() {
  if(millis() - lastReadData < 1000)
    return;
  
  // Get the (raw) value of the temperature sensor.
  int val = analogRead(pinTemp);

  // Determine the current resistance of the thermistor based on the sensor value.
  float resistance = (float)(1023-val)*10000/val;

  // Define the B-value of the thermistor.
  // This value is a property of the thermistor used in the Grove - Temperature Sensor,
  // and used to convert from the analog value it measures and a temperature value.
  int B = 3975;
  // Calculate the temperature based on the resistance value.
  temperature = 1/(log(resistance/10000)/B+1/298.15)-273.15;

  // Read the value of the sound sensor.
  soundValue = analogRead(pinSound);

  // Read the value of the light sensor. The light sensor is an analog sensor.
  lightValue = analogRead(pinLight);

//  char buffer[16];
//  sprintf(buffer, "%d %s %d", lightValue, temperature, soundValue);
  writeSecondLine(String(lightValue) 
    + " " + String(temperature) 
    + " " + String(soundValue));

  lastReadData = millis();
}



/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
