// ----------- PIN -----------
int led1Pin = 14;
int led2Pin = 12;
int btn1Pin = 4;
int btn2Pin = 5;

// ----------- STATE -----------
unsigned long lastLedTrigger = 0;
unsigned long lastBtnTrigger = 0;

void setupLedAndButton() {
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  pinMode(btn1Pin, INPUT);
  pinMode(btn2Pin, INPUT);
}


void loopLedAndButton() {
  loopLed();
  loopButton();
}

void loopLed() {
  if(millis() - lastLedTrigger < 500)
    return;
    
  if(digitalRead(led1Pin) == LOW) {
    digitalWrite(led1Pin,HIGH); 
  } else {
    digitalWrite(led1Pin,LOW); 
  }

  lastLedTrigger = millis();
}

void loopButton() {
  if(millis() - lastBtnTrigger < 500)
    return;
  if(digitalRead(btn1Pin)) {
    isButtonAHit = !isButtonAHit;
    sendDeviceRequest(isButtonAHit);
  }
  if(digitalRead(btn2Pin)) {
    isButtonBHit = !isButtonBHit;
    if(isButtonBHit)
      digitalWrite(led2Pin,HIGH);
    else
      digitalWrite(led2Pin,LOW); 
  }
  lastBtnTrigger = millis();
}



/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
