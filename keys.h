
/*
notekeys: 
   6
  7
   8
  9
  
  10
   11
   12

 14
   15
   
   16
   
   17
  18
  19
*/

//"Must be pressed", "0", "Must be open", "0", "Special funct"([< 12]), "Note"([12]) 
// byte note1[] = {6, 14, 0, 7, 9, 10, 0, 0, 0, 0, 0, 0, 63};

byte ActiveFingSet[20][13];

// Factory Fingering Set:
byte factFingSet[20][13] = {
{6, 14, 0, 7, 9, 10, 0, 0, 0, 0, 0, 0, 63},
{6, 0, 7, 10, 14, 0, 0, 0, 0, 0, 0, 0, 62},
{0, 6, 7, 9, 10, 0, 0, 0, 0, 0, 0, 0, 61},
{9, 0, 6, 7, 10, 0, 0, 0, 0, 0, 0, 0, 60},
{7, 0, 8, 9, 10, 14, 15, 16, 0, 0, 0, 0, 59},
{7, 8, 0, 9, 10, 14, 15, 16, 0, 0, 0, 0, 58},
{7, 9, 14, 0, 10, 0, 0, 0, 0, 0, 0, 0, 58},
{7, 9, 0, 10, 14, 0, 0, 0, 0, 0, 0, 0, 57},
{7, 9, 10, 11, 0, 15, 16, 0, 0, 0, 0, 0, 56},
{7, 9, 10, 0, 11, 15, 16, 0, 0, 0, 0, 0, 55},
{7, 9, 10, 16, 0, 15, 0, 0, 0, 0, 0, 0, 54},
{7, 9, 10, 15, 0, 16, 0, 0, 0, 0, 0, 0, 53},
{7, 9, 10, 15, 16, 0, 17, 0, 0, 0, 0, 0, 52},
{7, 9, 10, 15, 16, 17, 18, 0, 19, 0, 0, 0, 51},
{7, 9, 10, 15, 16, 17, 0, 12, 18, 19, 0, 0, 50},
{7, 9, 10, 11, 15, 16, 17, 19, 0, 12, 0, 0, 49},
{7, 9, 10, 15, 16, 17, 19, 0, 11, 12, 18, 0, 48},
{7, 9, 10, 12, 15, 16, 17, 0, 18, 19, 0, 0, 47},
{7, 9, 10, 12, 15, 16, 17, 19, 0, 18, 0, 0, 46},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

byte activeKeyPins[20];                                                  
byte factKeyPins[20] = {2, 30, 29, 27, 28, 9, 11, 4, 6, 7, 8, 5, 12, 23, 25, 21, 3, 26, 22, 24};
#define NUMKEYS 20


//Main array which stores the current state of each key pin:
byte keysPressed[NUMKEYS];
// Another array which stores the previous state for comparison:
byte lastPressed[NUMKEYS];
// Where each key is in the keysPressedArray
//byte noteKeys[13] = {6, 7, 8, 9, 10, 11, 12, 14, 15, 16, 17, 18, 19};
//                     0, 1, 2, 3,  4,  5,  6,  7,  8,  9, 10, 11, 12
//                     D  B  Bb A   G   Ab lBb sBb  F   E  D   Eb  C
byte octaveKeys[4] = {1, 2, 3, 4};
byte biphonicModeKeys[2] = {5, 13};




unsigned long checkTimer = 0;
unsigned long lastCheckTime = 0;

boolean newNote;
boolean correct;

byte baseNote;       
byte currentNote;    
byte lastNote;       
int octave = 0;      
int lastOctave = 0;

byte splitLowPressed; //"bitwrite" variable
byte splitHighPressed; //"bitwrite" variable


byte currentSplitHighNote;
byte duplicateSplitHighNote;
byte currentSplitLowNote;
byte lastSplitHighNote;
byte lastSplitLowNote;
byte currentSplitNote;
byte lastSplitNote;

boolean splitActive = 0;
boolean lastSplitActive = 0;


byte currentSustainNote;
byte lastSustainNote;
boolean sustainActive = 0;
boolean lastSustainActive = 0;

byte sustainInterval;

byte currentIntervalNote;
boolean intervalActive = 0;
boolean lastIntervalActive = 0;




//#################################################################
//#################################################################
// READ THE TOUCH KEYS:



//#################################################################
//##################    PICK INTERVAL:    #########################

void pickSplit(){
  lastSplitHighNote = currentSplitHighNote;
  lastSplitLowNote = currentSplitLowNote;
  
  bitWrite(splitHighPressed, 0, keysPressed[11]);
  bitWrite(splitHighPressed, 1, keysPressed[10]);
  bitWrite(splitHighPressed, 2, keysPressed[9]);
  bitWrite(splitHighPressed, 3, keysPressed[7]);
  byte n = 0;
  byte i;
  for(i = 18; i > 14; i--){
    bitWrite(splitLowPressed, n, keysPressed[i]);
    n++;
  }
  
  if(splitHighPressed != 0){
    correct = 1;
    currentSplitHighNote = splitHighPressed + octave + 47;
    if(splitLowPressed != 0){
      currentSplitLowNote = splitLowPressed + octave + 47; //(+ splitOctaveDistance)
    }
    else{
      currentSplitLowNote = currentSplitHighNote;
    }
//  
//    if(correct == 1){
//      if(currentSplitHighNote != lastSplitHighNote || currentSplitLowNote != lastSplitLowNote){
//        newNote = 1;
//      }
//    }
  }
}


//#################################################################
//#################    Octave Update Function:    #################
void setOctave(){
  if     (keysPressed[octaveKeys[0]] == 0 && keysPressed[octaveKeys[1]] == 1 && keysPressed[octaveKeys[2]] == 1 && keysPressed[octaveKeys[3]] == 1){
    octave = 48;
  }
  else if(keysPressed[octaveKeys[0]] == 0 && keysPressed[octaveKeys[1]] == 0 && keysPressed[octaveKeys[2]] == 0 && keysPressed[octaveKeys[3]] == 1){
    octave = 36;
  }
  else if(keysPressed[octaveKeys[0]] == 0 && keysPressed[octaveKeys[1]] == 0 && keysPressed[octaveKeys[2]] == 1 && keysPressed[octaveKeys[3]] == 1){
    octave = 24;
  }
  else if(keysPressed[octaveKeys[0]] == 0 && keysPressed[octaveKeys[1]] == 0 && keysPressed[octaveKeys[2]] == 1 && keysPressed[octaveKeys[3]] == 0){
    octave = 12;
  }
  else if(keysPressed[octaveKeys[0]] == 0 && keysPressed[octaveKeys[1]] == 1 && keysPressed[octaveKeys[2]] == 1 && keysPressed[octaveKeys[3]] == 0){
    octave = 0;
  }
  else if(keysPressed[octaveKeys[0]] == 0 && keysPressed[octaveKeys[1]] == 1 && keysPressed[octaveKeys[2]] == 0 && keysPressed[octaveKeys[3]] == 0){
    octave = -12;
  }
  else if(keysPressed[octaveKeys[0]] == 1 && keysPressed[octaveKeys[1]] == 1 && keysPressed[octaveKeys[2]] == 0 && keysPressed[octaveKeys[3]] == 0){
    octave = -24;
  }
  else if(keysPressed[octaveKeys[0]] == 1 && keysPressed[octaveKeys[1]] == 0 && keysPressed[octaveKeys[2]] == 0 && keysPressed[octaveKeys[3]] == 0){
    octave = -36;
  }
  else if(keysPressed[octaveKeys[0]] == 1 && keysPressed[octaveKeys[1]] == 1 && keysPressed[octaveKeys[2]] == 1 && keysPressed[octaveKeys[3]] == 0){
    octave = -48;
  }
//  else if(keysPressed[1] == 0 && keysPressed[2] == 0 && keysPressed[3] == 0 && keysPressed[4] == 0){
//    octave = 48;
//  }
//  octave = octave + transposeValue; // Transpose operation from menu settings
}


void newKeyLogic(){
  int i;
  int keyPhase = 0;
  int j;
  int n = 0;
  
  lastNote = currentNote;
  setOctave();
    
  lastSustainActive = sustainActive;
  lastIntervalActive = intervalActive;  
  if(keysPressed[biphonicModeKeys[1]] == 1){
    sustainActive = 1;
    if(keysPressed[biphonicModeKeys[0]] == 0){
      intervalActive = 0;
    }
    else if(keysPressed[biphonicModeKeys[0]] == 1){
      intervalActive = 1;
    }
  }
  else{
    sustainActive = 0;
    intervalActive = 0;
  }
 
 
  lastSplitActive = splitActive; 
  if(keysPressed[biphonicModeKeys[0]] == 1 && keysPressed [biphonicModeKeys[1]] == 0){
    splitActive = 1;
    pickSplit();
  }
  else{
    splitActive = 0;
      
      
    //New keylogic starts here:
    
    
    for(n = 0; n < 20; n++){
      keyPhase = 0;
//      Serial.println(n);
      for(i = 0; i < 12; i++){
//        Serial.print(i);
        if(factFingSet[n][i] != 0){
          if(keyPhase == 0){  // Check "closed" keys
            if(keysPressed[factFingSet[n][i]] == 1){
              correct = 1;
            }
            else{
              correct = 0;
              break;
            }
          }
          else if(keyPhase == 1){ // Check "closed" keys
            if(keysPressed[factFingSet[n][i]] == 0){
              correct = 1;
            }
            else{
              correct = 0;
              break;
            }
          }
          else if(keyPhase == 2){ // Check "special function" keys
            if(keysPressed[factFingSet[n][i]] != 0){
              int fxOn = factFingSet[n][i];
            }
            else{
              break;
            }
          }
        }
        else if(factFingSet[n][i] == 0){
          keyPhase ++;
        }
      }
//      Serial.println(" ");
      if(correct == 1){
        currentNote = factFingSet[n][12];
//        Serial.print("done. Note:");              
//        Serial.println(currentNote);
        break;
      }
    }

    if(correct == 1){
      currentNote = currentNote + octave;
      if(currentNote != lastNote){
        newNote = 1;
      }
    }
  } 
}



void readKeyPins(){
  byte j;
  for (j = 0; j < NUMKEYS; j++){
    lastPressed[j] = keysPressed[j];
  }
  for (j = 0; j < NUMKEYS; j++){ // Call debounce for touch keys
    keysPressed[j] = digitalRead(factKeyPins[j]); // Original debounceTime = 8
  }
}




void readKeys(){
  correct = 0;
  newNote = 0;
    
  readKeyPins();
  byte i;  
  if(keysPressed[0] == 0){
    checkTimer = millis();
    lastCheckTime = checkTimer;
  }
  else if(keysPressed[0] == 1){
    checkTimer = millis();
  }

  if(checkTimer - lastCheckTime > 10){
    newKeyLogic();
  }

  for(int i = 0; i < 20; i++){
    Serial.print(keysPressed[i]);
  }
  Serial.print(" ");
  Serial.println(currentNote);
//  
  if(velocity != 0){
    if(splitActive == 0){
      if(lastSplitActive == 1){
        usbMIDI.sendNoteOn(currentSplitLowNote, 0, 1);
        usbMIDI.sendNoteOn(currentSplitHighNote, 0, 2);
      }
      if(sustainActive == 1 && intervalActive == 0){
        if(lastSustainActive == 0){
          currentSustainNote = currentNote;
          usbMIDI.sendNoteOn(currentNote, velocity, 2);
        }
      }
      else if(sustainActive == 1 && intervalActive == 1){
        if(lastIntervalActive == 0){
          sustainInterval = currentSustainNote - currentNote;
        }
        lastSustainNote = currentSustainNote;
        currentSustainNote = currentNote + sustainInterval;
      }
      else if(lastSustainActive == 1){
        usbMIDI.sendNoteOn(currentSustainNote, 0, 1);
        usbMIDI.sendNoteOn(currentNote, 0, 2);
        usbMIDI.sendNoteOn(currentNote, velocity, 1);
      }
      
      if(newNote == 1){
        if(sustainActive == 1){
          usbMIDI.sendNoteOn(lastNote, 0, 2);
          usbMIDI.sendNoteOn(currentNote, velocity, 2);
          if(intervalActive == 1){
            usbMIDI.sendNoteOn(lastSustainNote, 0, 1);
            usbMIDI.sendNoteOn(currentSustainNote, velocity, 1);
          }         
        }
        else{
          usbMIDI.sendNoteOn(lastNote, 0, 1);
          usbMIDI.sendNoteOn(currentNote, velocity, 1);
        }
      }
    }
    else if(splitActive == 1){
      if(lastSplitActive == 0){
        if(sustainActive == 1){
          usbMIDI.sendNoteOn(currentNote, 0, 2);
          usbMIDI.sendNoteOn(currentSustainNote, 0, 1);
        }
        else{
          usbMIDI.sendNoteOn(currentNote, 0, 1);
        }
        usbMIDI.sendNoteOn(currentSplitLowNote, velocity, 1);
        usbMIDI.sendNoteOn(currentSplitHighNote, velocity, 2);
      }
      else{
        if(currentSplitLowNote != lastSplitLowNote){
  //          xBeeMIDI(noteONCh1,lastNote, 0);
  //          xBeeMIDI(noteONCh1, currentNote, velocity);
          usbMIDI.sendNoteOn(lastSplitLowNote, 0, 1);
          usbMIDI.sendNoteOn(currentSplitLowNote, velocity, 1);
        }
        if(currentSplitHighNote != lastSplitHighNote){
  //          xBeeMIDI(noteONCh2,lastSplitNote, 0);
  //          xBeeMIDI(noteONCh2,currentSplitNote, velocity);
          usbMIDI.sendNoteOn(lastSplitHighNote, 0, 2);
          usbMIDI.sendNoteOn(currentSplitHighNote, velocity, 2);
        }
      }
    }
  }
  else{
    if(sustainActive == 1 && intervalActive == 0){
      if(lastSustainActive == 0){
        currentSustainNote = currentNote;
//        usbMIDI.sendNoteOn(currentNote, velocity, 2);
      }
    }
    else if(sustainActive == 1 && intervalActive == 1){
      if(lastIntervalActive == 0){
        sustainInterval = currentSustainNote - currentNote;
      }
      lastSustainNote = currentSustainNote;
      currentSustainNote = currentNote + sustainInterval;
    }
  }
}
