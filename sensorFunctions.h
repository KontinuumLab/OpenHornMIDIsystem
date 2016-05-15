
//##################################################################
//############ "COMPLEX" ANALOG READ FUNCTION: #####################

int readAnalogSensor_COMPLEX(ssv sensor, int sensorVal, int *vectorArray){
  int sensorLastVal = sensorVal;
  vectorArray[1] = sensorVal;
  
  int i;
  for(i = 0; i < sensor.arraySize; i++){
    mFilterArray[i] = adc->analogRead(sensor.pin);
  }
  isort(mFilterArray, sensor.arraySize);
  int filteredInt = mFilterArray[sensor.arraySize / 2];

  unsigned int filteredRead;

  // INPUT SLOPE CORRECTION:
  if(sensor.sensorSlope != 0){
    float filteredFloat = fscale(0.0, 4095.0, 0.0, 4095.0, filteredInt, sensor.sensorSlope);
    filteredRead = filteredFloat; // * 100;
  }
  else{
    filteredRead = filteredInt;//  * 100;
  }

  // OUTPUT SLOPE CORRECTION:
  if(sensor.outSlope != 0){
    float outMap = fscale(float(sensor.hardMin), float(sensor.hardMax), float(sensor.hardMin), float(sensor.hardMax), float(filteredRead), sensor.outSlope);
    filteredRead = outMap;
  }

  // FINAL VALUE MAPPING:
  int finalRead;
  int bufLow = sensor.hardMiddle - sensor.buffer;
  int bufHigh = sensor.hardMiddle + sensor.buffer;
//  Serial.println(filteredRead);

  if(filteredRead <= sensor.hardMin){
    finalRead = sensor.outMin;
  }
  else if(filteredRead >= sensor.hardMax){
    finalRead = sensor.outMax;
  }
  else{  
    if(sensor.sensorMode == 1){
      finalRead = map(filteredRead, sensor.hardMin, sensor.hardMax, sensor.outMin, sensor.outMax);
      //    finalTemp = finalTemp / 100;
      //    final = int(finalTemp);
    }
    else if(sensor.sensorMode == 2){
      if(filteredRead > bufLow && filteredRead < bufHigh){
        finalRead = sensor.outMiddle;
      }
      else if(filteredRead <= bufLow){
        finalRead = map(filteredRead, sensor.hardMin, bufLow, sensor.outMin, sensor.outMiddle);
      }
      else if(filteredRead >= bufHigh){
        finalRead = map(filteredRead, bufHigh, sensor.hardMax, sensor.outMiddle, sensor.outMax);
      }

//      finalRead = map(filteredRead, sensor.hardMin, sensor.hardMax, sensor.outMin, sensor.outMax);
      //    finalTemp = finalTemp / 100;
      //    final = int(finalTemp);
    }
  }    

  //##############################
  // VECTOR PART:

  int l;
  int m;
  int vectorFull = 0;
  int vectorEnd = 0;
  int vectorSingle = 0;
  int vectorCount = 0;

  //  if(sensor1Val != sensor1LastVal){
  //Move over array 1 place:
  for(l = 0; l < sensor.vectorArraySize - 1; l++){
    vectorArray[l] = vectorArray[l + 1];
  }
  // Enter new reading:
  vectorArray[sensor.vectorArraySize - 1] = finalRead;

  //Calculate vectors:
  for(m = 0; m < sensor.vectorArraySize - 1; m++){
    int lastvectorSingle = vectorSingle;
    vectorSingle = vectorArray[m + 1] - vectorArray[m];
    if(vectorSingle > 0){
      if(lastvectorSingle <= 0){
        vectorCount = 0;
        vectorEnd = 0;
      }
      else{
        vectorCount ++;
        vectorEnd = vectorEnd + vectorSingle;
      }
    }
    else if(vectorSingle < 0){
      if(lastvectorSingle >= 0){
        vectorCount = 0;
        vectorEnd = 0;
      }
      else{
        vectorCount ++;
        vectorEnd = vectorEnd + vectorSingle;
      }
    }
    else if(vectorSingle == 0){
      vectorEnd = 0;
      if(lastvectorSingle != 0){
        vectorCount = 0;
      }
      else{
        vectorCount ++;
      }
    }
    vectorFull = vectorFull + vectorSingle;
  }
  //  }

  //Apply smoothing:
  vectorEnd = vectorEnd / vectorCount;
  int vectorAccel = vectorCount + (sensor.vectorSmoother / vectorCount);
  if(vectorAccel >= sensor.vectorArraySize){
    vectorAccel = sensor.vectorArraySize;
  }
  else if(vectorAccel <= 1){
    vectorAccel = 1;
  }

  vectorFull = ((vectorFull + (vectorEnd / 2)) / (sensor.vectorArraySize / vectorAccel));

  //  if(lastFinal != sensor1OutMin && lastFinal != sensor1OutMax){
  sensorVal = sensorLastVal + vectorFull;
  //  }
  //  else{
  //    finalVal = lastFinal + vectorEnd;
  //  }

  if(sensorVal <= sensor.outMin){
    sensorVal = sensor.outMin;
  }
  else if(sensorVal >= sensor.outMax){
    sensorVal = sensor.outMax;
  }
  return(sensorVal);

  //  Serial.println(millis());
//  return(finalVal);
}


//##################################################################
//############ "CALIBRATION" ANALOG READ FUNCTION: #################

void readAnalogSensor_CALIBRATE(ssv *sensor){
  int i;
  int tempRead;
  int calRead;
  // Modified Median filter / read function (to get around hardMin and hardMax)
  for(i = 0; i < sensor->arraySize; i++){
    tempRead = adc->analogRead(sensor->pin);
    mFilterArray[i] = tempRead;
  }
  isort(mFilterArray, sensor->arraySize);
  calRead = mFilterArray[sensor->arraySize / 2];
  
  // set new Min and Max:
  if(calRead > sensor->hardMax){
   sensor->hardMax = calRead;
  }
  if(calRead < sensor->hardMin){
    sensor->hardMin = calRead;
  }
}



// ENCODER VARIABLES:
int rotEncPin1 = 13;
int rotEncPin2 = 14;
int rotEncButtonPin = 15;


int rotEncDir; 
boolean currentEncButton = 0;
boolean newValueBool = 0;

int rotEncCounter; 
int lastEncCounter;

int rotEncVal1 = 0;
int rotEncVal2 = 0;
int rotEncLastVal1 = 0;
int rotEncLastVal2 = 0;
int rotEncButtonVal = 0;
int rotEncButtonLastVal = 0;

boolean rotEncButtonPressed = 0;
boolean rotEncButtonReleased = 0;


//#################################################################
//######### Read encoder: ####################################
void rotEncRead(){
  int m;
  rotEncDir = 0;
  int n = debounce(rotEncPin1, rotEncLastVal1, 1);
  if((rotEncLastVal1 == LOW) && (n == HIGH)){
    m = debounce(rotEncPin2, rotEncLastVal2, 1);
    if(m == LOW ){
      rotEncDir = -1;
    }
    else{
      rotEncDir = 1;
    }
    newValueBool = 1;
  }
  rotEncLastVal1 = n;
  rotEncLastVal2 = m;
}
//
////#################################################################
////######### Read encoder: ####################################
//void rotEncRead(){
//  int m;
//  rotEncDir = 0;
//  int n = debounce(rotEncPin2, rotEncLastVal2, 2);
//  if((rotEncLastVal2 == HIGH) && (n == LOW)){
//    m = debounce(rotEncPin1, rotEncLastVal1, 2);
//    if(m == HIGH ){
//      rotEncDir = -1;
//    }
//    else{
//      rotEncDir = 1;
//    }
//    newValueBool = 1;
//  }
//  rotEncLastVal2 = n;
//  rotEncLastVal1 = m;
//}


//#################################################################
//######### Read encoder button: ############################
void rotEncButtonRead(){
//  rotEncButtonVal = debounce(rotEncButtonPin, rotEncButtonLastVal, 2);
  rotEncButtonVal = debounce(rotEncButtonPin, rotEncButtonLastVal, 1);
  if(rotEncButtonVal == 1 && rotEncButtonLastVal == 0){
    rotEncButtonPressed = 0;
    rotEncButtonReleased = 1;
  }
  else if(rotEncButtonVal == 0 && rotEncButtonLastVal == 1){
    rotEncButtonReleased = 0;
    rotEncButtonPressed = 1;
  }
  else{
    rotEncButtonPressed = 0;
    rotEncButtonReleased = 0;
  }
  rotEncButtonLastVal = rotEncButtonVal;
}

