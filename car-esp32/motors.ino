// ----------- PIN -----------
const int pinIn1 = 16;
const int pinIn2 = 15;
const int pinIn3 = 14;
const int pinIn4 = 13;

// ----------- DATA -----------
int engineBreak = 1000;
unsigned long lastEngineRun = 0;
boolean forwarding = false;
unsigned long lastForwarding = 0;
boolean backwarding = false;
unsigned long lastBackwarding = 0;
boolean turningLeft = false;
unsigned long lastLeft = 0;
boolean right = false;
unsigned long lastRight = 0;

void setupMotors() {
  pinMode(pinIn1, OUTPUT);
  pinMode(pinIn2, OUTPUT);
  pinMode(pinIn3, OUTPUT);
  pinMode(pinIn4, OUTPUT);
}

void loopMotors() {
  while(deliveryPath.length() > 0) {
    String stepStr = pickUpStep();
    if(isDigit(stepStr.charAt(0))) {
      int distance = stepStr.toInt();
      if(goForward(distance)) {
        takeOffStep();
      }
    } else if(stepStr.startsWith("-")) {
      int distance = stepStr.toInt();
      if(goBackward(abs(distance))) {
        takeOffStep();
      }
    } else if(stepStr == "l") {
      if(turnLeft(5)) {
        takeOffStep(); 
      }
    } else if(stepStr == "r") {
      if(turnRight(5)) {
        takeOffStep(); 
      }
    } else {
      Serial.println("unknow " + stepStr);
      takeOffStep();
    }
  }
}

String pickUpStep() {
  if(deliveryPath.length() == 0)
    return "";
  if(deliveryPath.indexOf(",") == -1) {
    return deliveryPath;
  }
  return deliveryPath.substring(0, deliveryPath.indexOf(","));
}

void takeOffStep() {
  if(deliveryPath.length() == 0)
    return;
    
  if(deliveryPath.indexOf(",") == -1) {
    deliveryPath = "";
    Serial.println("stop!");
    printLcd("Arrived", "waiting. . .");
    delay(5000);
  } else {
    deliveryPath = deliveryPath.substring(deliveryPath.indexOf(",") + 1, deliveryPath.length());
    Serial.println("after take off: " + deliveryPath);
  }
}

boolean goForward(int distance) {
  int delayTime = distance * 100;

  if(millis() - lastEngineRun < engineBreak)
    return false;
  
  if(millis() - lastForwarding < delayTime)
    return false;

  forwarding = !forwarding;
  if(forwarding) {
    Serial.println("start go forward");
    digitalWrite(pinIn1, LOW);
    digitalWrite(pinIn2, HIGH);
    digitalWrite(pinIn3, HIGH);
    digitalWrite(pinIn4, LOW);
    lastForwarding = millis();
    lastEngineRun = 0;
  } else {
    Serial.println("stop go forward");
    digitalWrite(pinIn1, LOW);
    digitalWrite(pinIn2, LOW);
    digitalWrite(pinIn3, LOW);
    digitalWrite(pinIn4, LOW);
    lastForwarding = 0;
    lastEngineRun = millis();
  }
  
  return !forwarding;
}

boolean goBackward(int distance) {
  int delayTime = distance * 100;

  if(millis() - lastEngineRun < engineBreak)
    return false;
  
  if(millis() - lastBackwarding < delayTime)
    return false;

  backwarding = !backwarding;
  if(backwarding) {
    Serial.println("start go backward");
    digitalWrite(pinIn1, HIGH);
    digitalWrite(pinIn2, LOW);
    digitalWrite(pinIn3, LOW);
    digitalWrite(pinIn4, HIGH);
    lastBackwarding = millis();
    lastEngineRun = 0;
  } else {
    Serial.println("stop go backward");
    digitalWrite(pinIn1, LOW);
    digitalWrite(pinIn2, LOW);
    digitalWrite(pinIn3, LOW);
    digitalWrite(pinIn4, LOW);
    lastBackwarding = 0;
    lastEngineRun = millis();
  }
  
  return !backwarding;
}

boolean turnRight(int angle) {
  int delayTime = angle * 100;

  if(millis() - lastEngineRun < engineBreak)
    return false;
  
  if(millis() - lastRight < delayTime)
    return false;

  right = !right;
  if(right) {
    Serial.println("start turn right");
    digitalWrite(pinIn1, HIGH);
    digitalWrite(pinIn2, LOW);
    digitalWrite(pinIn3, HIGH);
    digitalWrite(pinIn4, LOW);
    lastRight = millis();
    lastEngineRun = 0;
  } else {
    Serial.println("stop turn right");
    digitalWrite(pinIn1, LOW);
    digitalWrite(pinIn2, LOW);
    digitalWrite(pinIn3, LOW);
    digitalWrite(pinIn4, LOW);
    lastRight = 0;
    lastEngineRun = millis();
  }
  return !right;
}

boolean turnLeft(int angle) {
  int delayTime = angle * 100;

  if(millis() - lastEngineRun < engineBreak)
    return false;
  
  if(millis() - lastLeft < delayTime)
    return false;

  turningLeft = !turningLeft;
  if(turningLeft) {
    Serial.println("start turn left");
    digitalWrite(pinIn1, LOW);
    digitalWrite(pinIn2, HIGH);
    digitalWrite(pinIn3, LOW);
    digitalWrite(pinIn4, HIGH);
    lastLeft = millis();
    lastEngineRun = 0;
  } else {
    Serial.println("stop turn left");
    digitalWrite(pinIn1, LOW);
    digitalWrite(pinIn2, LOW);
    digitalWrite(pinIn3, LOW);
    digitalWrite(pinIn4, LOW);
    lastLeft = 0;
    lastEngineRun = millis();
  }
  return !turningLeft;
}
