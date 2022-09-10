
// ----------- DIGITAL PIN -----------
const int pinLed = 4;
const int pinRelay = 3;
const int pinBtn = 2;

// ----------- STATE -----------
unsigned long lastLedTrigger = 0;
unsigned long lastBtnTrigger = 0;

void setupLedAndButton() {
  pinMode(pinLed, OUTPUT);
  pinMode(pinRelay, OUTPUT);
  pinMode(pinBtn, INPUT);
}

void loopLedAndButton() {
  loopLed();
  loopButton();
}

void loopLed() {
  if(millis() - lastLedTrigger < 500)
    return;
    
  if(digitalRead(pinLed) == LOW) {
    digitalWrite(pinLed,HIGH); 
  } else {
    digitalWrite(pinLed,LOW); 
  }

  lastLedTrigger = millis();
}

void loopButton() {
  if(millis() - lastBtnTrigger < 500)
    return;
  if (digitalRead(pinBtn)){
    isButtonHit = !isButtonHit;
    triggerRelay(isButtonHit);
  }
  lastBtnTrigger = millis();
}

void triggerRelay(boolean isOn) {
  if(isOn)
    digitalWrite(pinRelay, HIGH);
  else
    digitalWrite(pinRelay, LOW);
}



/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
