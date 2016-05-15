
// Output arrays:
                 //  {ch,b1,b2,b3,b4, 
byte outPutSens1[6] = {3, 0, 0, 0, 0, 0};




const uint8_t RPN_MSB = 101;
const uint8_t RPN_LSB = 100;
const uint8_t RPN_DataMSB = 6;
const uint8_t RPN_DataLSB = 38;

const uint8_t RPN_MSB_STD = 0;
const uint8_t RPN_LSB_BendSens = 0;
const uint8_t RPN_LSB_FineTune = 1;
const uint8_t RPN_LSB_CoarseTune = 2;
const uint8_t RPN_LSB_TuningPgm = 3;
const uint8_t RPN_LSB_TuningBank = 4;

const uint8_t RPN_MSB_CANCEL_NUM = 127;
const uint8_t RPN_LSB_CANCEL_NUM = 127;


const uint8_t NRPN_MSB = 99;
const uint8_t NRPN_LSB = 98;
const uint8_t NRPN_DataMSB = 6;
const uint8_t NRPN_DataLSB = 38;






void sendUSB_STD(byte msgArray[6], byte arrayLength){
  if(msgArray[0] == 1 || msgArray[0] == 3){
    usbMIDI.sendControlChange(msgArray[1], msgArray[0], 1);
  }
  if(msgArray[0] == 2 || msgArray[0] == 3){
    usbMIDI.sendControlChange(msgArray[1], msgArray[0], 2);
  }
}


void sendUSB_RPN_NRPN(byte msgArray[6], byte arrayLength){
  if(msgArray[0] == 1 || msgArray[0] == 3){
    usbMIDI.sendControlChange(RPN_MSB, msgArray[1], 1);
    usbMIDI.sendControlChange(RPN_LSB, msgArray[2], 1);
    usbMIDI.sendControlChange(RPN_DataMSB, msgArray[3], 1);
    usbMIDI.sendControlChange(RPN_DataLSB, msgArray[4], 1);
    
    usbMIDI.sendControlChange(RPN_MSB, 127, 1);
    usbMIDI.sendControlChange(RPN_LSB, 127, 1);
  }
  if(msgArray[0] == 2 || msgArray[0] == 3){
    usbMIDI.sendControlChange(RPN_MSB, msgArray[1], 2);
    usbMIDI.sendControlChange(RPN_LSB, msgArray[2], 2);
    usbMIDI.sendControlChange(RPN_DataMSB, msgArray[3], 2);
    usbMIDI.sendControlChange(RPN_DataLSB, msgArray[4], 2);
    
    usbMIDI.sendControlChange(RPN_MSB, 127, 2);
    usbMIDI.sendControlChange(RPN_LSB, 127, 2);
  }
}
