

void getEEPROMaddresses(){

  EEPROM.setMemPool(0, 2048);
  int address = 0;
    // Set up EEPROM:
    // Always get the adresses first and in the same order

  int addressDefaults     = EEPROM.getAddress(1);
    
  int addressSensor1_A    = EEPROM.getAddress(30);
  int addressSensor2_A    = EEPROM.getAddress(30);
  int addressSensor3_A    = EEPROM.getAddress(30);
  int addressSensor4_A    = EEPROM.getAddress(30);
  int addressSensor5_A    = EEPROM.getAddress(30);    
  int addressSensor6_A    = EEPROM.getAddress(30);  
  int addressSensor7_A    = EEPROM.getAddress(30);
  int addressSensor8_A    = EEPROM.getAddress(30);
  int addressIMU_A        = EEPROM.getAddress(30);
  int addressCalib_A      = EEPROM.getAddress(6);  // + 276 bytes
  
  int addressSensor1_B    = EEPROM.getAddress(30);
  int addressSensor2_B    = EEPROM.getAddress(30);
  int addressSensor3_B    = EEPROM.getAddress(30);
  int addressSensor4_B    = EEPROM.getAddress(30);
  int addressSensor5_B    = EEPROM.getAddress(30);    
  int addressSensor6_B    = EEPROM.getAddress(30);  
  int addressSensor7_B    = EEPROM.getAddress(30);
  int addressSensor8_B    = EEPROM.getAddress(30);
  int addressIMU_B        = EEPROM.getAddress(30);
  int addressCalib_B      = EEPROM.getAddress(6);
  
  int addressSensor1_C    = EEPROM.getAddress(30);
  int addressSensor2_C    = EEPROM.getAddress(30);
  int addressSensor3_C    = EEPROM.getAddress(30);
  int addressSensor4_C    = EEPROM.getAddress(30);
  int addressSensor5_C    = EEPROM.getAddress(30);    
  int addressSensor6_C    = EEPROM.getAddress(30);  
  int addressSensor7_C    = EEPROM.getAddress(30);
  int addressSensor8_C    = EEPROM.getAddress(30);
  int addressIMU_C        = EEPROM.getAddress(30);
  int addressCalib_C      = EEPROM.getAddress(6);    // 276 * 3 = 833 bytes

  int addressKeys_A       = EEPROM.getAddress(20);
  int addressKeys_B       = EEPROM.getAddress(20);   // + 40 = 873 bytes

  int addressFingerings_A = EEPROM.getAddress(325); // (13 noteKeys * 20 available fingerings)
  int addressFingerings_B = EEPROM.getAddress(325);  // + 975 = 1523 bytes
  int addressFingerings_C = EEPROM.getAddress(325);
 
  int addressOctaves_A    = EEPROM.getAddress(36); // 4 octave keys * 9 octaves
  int addressOctaves_B    = EEPROM.getAddress(36);  // + 72 = 1595

  int addressOutput_A     = EEPROM.getAddress(66);   // 11 possible outputs * 6 bytes each. ??
  int addressOutput_B     = EEPROM.getAddress(66);  // + 198 = 1793 bytes
            // 1793 bytes up to here
}

void loadAllDefaults(){
  
}

void setDefaults(){
  
}

void loadSensorsPreset(){
  
}

void loadKeysPreset(){
  
}

void loadFingeringsPreset(){
  
}

void loadOctavesPreset(){
  
}

void loadOutputPreset(){
  
}



////################### set up EEPROM: ########################



//       For reading:
//  uint8_t read(int address);
//  uint8_t readByte(int address);
//  uint16_t readInt(int address);
//  uint32_t readLong(int address);
//  float readFloat(int address);
//  double readDouble(int address);
//  Where address is the starting position in EEPROM, and the return value the value read from EEPROM. 

//        For writing:
//  bool write(int address, uint8_t value);
//  bool writeByte(int address, uint8_t value);
//  bool writeInt(int address, uint16_t value);
//  bool writeLong(int address, uint32_t value);
//  bool writeFloat(int address, float value);
//  bool writeDouble(int address, double value);
