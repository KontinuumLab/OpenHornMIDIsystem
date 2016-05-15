
// Calibration button Variables:
int btnPin1 = 17;
int btnPin2 = 20;
int btnPin3 = 16;
int btn1Read = 1;
int btn2Read = 1;
int btn3Read = 1;
int btn1ReadLast = 1;
int btn2ReadLast = 1;
int btn3ReadLast = 1;


void quickReadCalBtns(){
  btn1Read = digitalRead(btnPin1);
  btn2Read = digitalRead(btnPin2);
  btn3Read = digitalRead(btnPin3);  
}

void readCalButtons(){
  btn1ReadLast = btn1Read;
  btn2ReadLast = btn2Read;
  btn3ReadLast = btn3Read;  
  btn1Read = debounce(btnPin1, btn1ReadLast, 2);
  btn2Read = debounce(btnPin2, btn1ReadLast, 2);
  btn3Read = debounce(btnPin3, btn1ReadLast, 2);
}

//void calibrateBreathHighRez(){
//  int i;
//  for(i = 0; i < breathArraySize; i++){
//    breathTemp = adc->analogRead(breathPin);
//    breathArray[i] = breathTemp;
//  }
//  isort(breathArray,breathArraySize);
//  breathRead = breathArray[breathArraySize / 2];
////  breathRead = map(breathRead, 1023, 0, 0, 1023);
//  if(breathRead > breathMax){
//    breathMax = breathRead;
//  }
//  if(breathRead < breathMin){
//    breathMin = breathRead + breathBuffer;
//  }
//}
//
//void calibrateBend(){
//  potm = adc->analogRead(bendPin);
////  int i;
////  for(i = 0; i < bendArraySize; i++){
////    bendTemp = analogRead(bendPin);
////    bendArray[i] = bendTemp;
////  }
////  isort(bendArray,bendArraySize);
////  potm = bendArray[bendArraySize / 2];
////  
//  if(potm > bendMax){
//    bendMax = potm;
//  }
//  if(potm < bendMin){
//    bendMin = potm;
//  }
//}


//###########################################
// #########  Main calibration call: ########
void calibrationCall(){
  readCalButtons();
  if(btn1Read == 0){
    sensor1Static.hardMax = 0;
    sensor1Static.hardMin = 4095;
//      Serial.println("Calibrating Breath...");
    while(btn1Read == 0){
      readAnalogSensor_CALIBRATE(pSensor1Static);
      readCalButtons();
    }
  }
  
  if(btn2Read == 0){
    int potm = adc->analogRead(sensor2Static.pin);
    pSensor2Static->hardMiddle = potm;
    pSensor2Static->hardMax = 0;
    pSensor2Static->hardMin = 4095;
//      Serial.println("Calibrating Bend...");
    while(btn2Read == 0){
      readAnalogSensor_CALIBRATE(pSensor2Static);
      readCalButtons();
    }
    int bendMidTemp = sensor2Static.hardMiddle;
    potm = adc->analogRead(sensor2Static.pin);
    pSensor2Static->hardMiddle = (potm + bendMidTemp) / 2;
//    Serial.print("bendMid");
//    Serial.println(bendMid);
//    bendLowBuf = bendMid - bendBuffer;
//    bendHighBuf = bendMid + bendBuffer;
//    Serial.print("bendLowBuf = ");
//    Serial.println(bendLowBuf);
//    Serial.print("bendHighBuf = ");
//    Serial.println(bendHighBuf);
//    Serial.print("bendMin = ");
//    Serial.println(bendMin);
//    Serial.print("bendMax = ");
//    Serial.println(bendMax);
  }
  
  
  if(btn3Read == 0){
    if(debugIMU == 0){
    //######################################################
    //########## IMU CALIBRATION ROUTINE: ##################
      debugIMU = 1;
      pitchMin = 85;
      pitchMax = 0;
      rollMin = 90;
      rollMax = -90;
      while(btn3Read == 0){
        updateIMUCalib();
        if(pitch < pitchMin){
          pitchMin = pitch;
        }
        if(pitch > pitchMax){
          pitchMax = pitch;
        }
        if(roll < rollMin){
          rollMin = roll;
        }
        if(roll > rollMax){
          rollMax = roll;
        }
        readCalButtons();
        if(debugIMU != 0){
          debugMPU9250();
        }
      }
      debugIMU = 2;
      delay(2000);
    }
    else if(debugIMU == 2){
      debugIMU = 0;
      delay(2000);
      display.clearDisplay();
      display.display();
    }
  }
}
