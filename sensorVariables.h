
int mFilterArray[100];  //array for storing readings for the median filter during initial reading. ### USED FOR ALL SENSORS!! ###


struct SENSOR_STATIC_VALS{   // Declare "SENSOR_STATIC_VALS" struct type
int pin;  //(2 bytes)
int hardMin;   // lowest reading at calibration. //(2 bytes)
int hardMiddle; // start/end/middle point at calibration. //(2 bytes) 
int buffer; // Buffer "dead space" around the start or middle point, depending on type of mapping. //(2 bytes)
int hardMax; // highest reading at calibration. //(2 bytes)
byte vectorArraySize; //  //(1 bytes)
byte vectorSmoother;  // Highest smoothing: "1" //(1 bytes)
byte arraySize;  //number of readings in the median filter array. Max 100. //(1 bytes)
float sensorSlope;   //slope applied to the input values. (4 bytes)
int outMin;     //0 - 127 / 0 - 4095 / ?? - ??. //(2 bytes)
int outMiddle;  // Middle point for "centered" output mapping. For example: pitchbend (0-64, 64-127) //(2 bytes)
                // Set to "outMin" or Outmax to for combined mapping with another sensor
int outMax;  //0 - 127 / 0 - 4095 / ?? - ??. //(2 bytes)
float outSlope;  //slope applied to the output values. //(4 bytes)
byte sensorMode; // "0" is off, "1" maps from the lowest up, "2" maps around a central point (outMiddle), using the buffer. //(1 byte)
// "3" maps as the lower half of a two sensor setup, "4" maps as the upper half, "5" uses multiplier, "6" uses divisor, "7" uses additive, "8" uses subtractive".
byte multiplier; // Which of the other sensors to use as an effector. 1 - 11. "0" is off   (1 byte) 
byte otherHalf;  // Which of the other sensors to combine with to make a 2-sensor, "middle mapping" setup. "0" is off. 
                 //This sensor (the one with "other half" activated) maps to the upper half. (1 byte) {
};

//30 bytes of eeprom needed in total for each sensor.


 

typedef struct SENSOR_STATIC_VALS ssv;


//           EXAMPLE: (pin, hardMin, hardMiddle, buffer, hardMax, vectorArraySize, vectorSmoother, arraySize, sensorSlope, outMin, outMiddle, outMax, outSlope, sensorMode, multiplier, otherHalf)
//ssv sensor1Static = { 26,   1800,       0,       0,     3000,          10,              1,            50,        0.0,       0,       0,       127,     0.0,       1,            0,        0};

//##################### SENSOR 1 VARIABLES: ###########################
ssv sensor1Static = {A10, 75, 0, 0, 225, 7, 1, 35, 0.0, 0, 0, 127, 0.0, 1, 0, 0};
ssv *pSensor1Static = &sensor1Static;
// Dynamic values:
int sensor1Val;
int sensor1LastVal;
int sensor1VectorArray[50];
boolean sensor1VectorEndOn = 0;



//##################### SENSOR 2 VARIABLES: ###########################
ssv sensor2Static = {A12, 260, 310, 15, 370, 9, 1, 25, -1.0, 0, 64, 127, 0.0, 2, 0, 0};
ssv *pSensor2Static = &sensor2Static;
// Dynamic values:
int sensor2Val;
int sensor2LastVal;
int sensor2VectorArray[50];
boolean sensor2VectorEndOn = 0;


//##################### SENSOR 3 VARIABLES: ###########################
ssv sensor3Static = {12, 0, 0, 0, 4095, 10, 1, 50, 0.0, 0, 0, 127, 0.0, 0, 0, 0};
ssv *pSensor3Static = &sensor3Static;
// Dynamic values:
int sensor3Val;
int sensor3LastVal;
int sensor3VectorArray[50];
boolean sensor3VectorEndOn = 0;


//##################### SENSOR 4 VARIABLES: ###########################
ssv sensor4Static = {12, 0, 0, 0, 4095, 10, 1, 50, 0.0, 0, 0, 127, 0.0, 0, 0, 0};
ssv *pSensor4Static = &sensor4Static;
// Dynamic values:
int sensor4Val;
int sensor4LastVal;
int sensor4VectorArray[50];
boolean sensor4VectorEndOn = 0;


//##################### SENSOR 5 VARIABLES: ###########################
ssv sensor5Static = {12, 0, 0, 0, 4095, 10, 1, 50, 0.0, 0, 0, 127, 0.0, 0, 0, 0};
ssv *pSensor5Static = &sensor5Static;
// Dynamic values:
int sensor5Val;
int sensor5LastVal;
int sensor5VectorArray[50];
boolean sensor5VectorEndOn = 0;


//##################### SENSOR 6 VARIABLES: ###########################
ssv sensor6Static = {12, 0, 0, 0, 4095, 10, 1, 50, 0.0, 0, 0, 127, 0.0, 0, 0, 0};
ssv *pSensor6Static = &sensor6Static;
// Dynamic values:
int sensor6Val;
int sensor6LastVal;
int sensor6VectorArray[50];
boolean sensor6VectorEndOn = 0;


//##################### SENSOR 7 VARIABLES: ###########################
ssv sensor7Static = {12, 0, 0, 0, 4095, 10, 1, 50, 0.0, 0, 0, 127, 0.0, 0, 0, 0};
ssv *pSensor7Static = &sensor7Static;
// Dynamic values:
int sensor7Val;
int sensor7LastVal;
int sensor7VectorArray[50];
boolean sensor7VectorEndOn = 0;


//##################### SENSOR 8 VARIABLES: ###########################
ssv sensor8Static = {12, 0, 0, 0, 4095, 10, 1, 50, 0.0, 0, 0, 127, 0.0, 0, 0, 0};
ssv *pSensor8Static = &sensor8Static;
// Dynamic values:
int sensor8Val;
int sensor8LastVal;
int sensor8VectorArray[50];
boolean sensor8VectorEndOn = 0;


//##################### Joystick 1 VARIABLES: ###########################
ssv joystick1Static = {12, 0, 0, 0, 4095, 10, 1, 50, 0.0, 0, 0, 127, 0.0, 0, 0, 0};
ssv *pJoystick1Static = &joystick1Static;
// Dynamic values:
int joystick1Val;
int joystick1LastVal;
int joystick1VectorArray[50];
boolean joystick1VectorEndOn = 0;

//##################### Joystick 2 VARIABLES: ###########################
ssv joystick2Static = {12, 0, 0, 0, 4095, 10, 1, 50, 0.0, 0, 0, 127, 0.0, 0, 0, 0};
ssv *pJoystick2Static = &joystick2Static;
// Dynamic values:
int joystick2Val;
int joystick2LastVal;
int joystick2VectorArray[50];
boolean joystick2VectorEndOn = 0;



//##################### IMU Pitch VARIABLES: ###########################
ssv IMUpitchStatic = {0, 80, 0, 0, 0, 10, 1, 50, 0.0, 0, 0, 127, 0.0, 1, 0, 0}; // IMU is recognized by the "read analog" function, by having "pin" set to "0"
ssv *pIMUpitchStatic = &IMUpitchStatic;
// Dynamic values:
int IMUpitchVal;
int IMUpitchLastVal;
int IMUpitchVectorArray[50];
boolean IMUpitchVectorEndOn = 0;


//##################### IMU Roll VARIABLES: ###########################
ssv IMUrollStatic = {0, 45, 0, 0, -45, 10, 1, 50, 0.0, 0, 0, 127, 0.0, 1, 0, 0};
ssv *pIMUrollStatic = &IMUrollStatic;
// Dynamic values:
int IMUrollVal;
int IMUrollLastVal;
int IMUrollVectorArray[50];
boolean IMUrollVectorEndOn = 0;

//##################### IMU Yaw VARIABLES: ###########################
ssv IMUyawStatic = {0, 0, 0, 0, 4095, 10, 1, 50, 0.0, 0, 0, 127, 0.0, 0, 0, 0};
ssv *pIMUyawStatic = &IMUyawStatic;
// Dynamic values:
int IMUyawVal;
int IMUyawLastVal;
int IMUyawVectorArray[50];
boolean IMUyawVectorEndOn = 0;


//##############SAVED "LAST STATE" FOR "REVERT" FUNCTION: ######################
ssv sensorTempStatic = {12, 0, 0, 0, 4095, 10, 1, 50, 0.0, 0, 0, 127, 0.0, 0, 0, 0};
ssv *pSensorTempStatic = &sensorTempStatic;







