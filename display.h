
//############ OLED DEFINES: ####################

#define OLED_RESET 33

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2
Adafruit_SSD1306 display(OLED_RESET);


static const unsigned char PROGMEM logo16_glcd_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000 };

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif



int linePosArray[6] = {11, 20, 29, 38, 46, 55};


void displayMainMenu(byte menuItem, byte subMenuItem){ // Menu 0
  display.clearDisplay();

  // Text:
  display.setTextSize(1);
  display.setTextColor(WHITE, BLACK);
  display.setCursor(0, 0);
  display.print(mainMenu.title);

  // LEFT MENU:
  for(int i = 0; i < leftMenuSize; i++){
    if(i != menuItem){
      display.setCursor(0, linePosArray[i]);
      display.print(mainMenu.leftMenu[i]);
    }
    else{
      display.setCursor(0, linePosArray[i]);
      display.setTextColor(BLACK, WHITE);
      display.print(mainMenu.leftMenu[i]);
      display.setTextColor(WHITE, BLACK);
    }
  }
  
  // RIGHT MENU: 
  for(int j = 0; j < rightMenuSize; j++){  
    if(j != subMenuItem){
      display.setCursor(46, linePosArray[j]);
      display.print(mainMenu.rightMenu[menuItem][j]);
    }
    else{
      display.setCursor(46, linePosArray[j]);
      display.setTextColor(BLACK, WHITE);
      display.print(mainMenu.rightMenu[menuItem][j]);
      display.setTextColor(WHITE, BLACK);
    }
  }  
   display.drawLine(0, 8, 127, 8, WHITE);
   display.drawLine(44, 9, 44, 64, WHITE);
    
   
   display.display();

}


void debugMPU9250(){
  if(debugIMU == 1){
    displayTimer = millis();
    if(displayTimer - lastDisplay > 30){
//      Serial.println("                 Display");
//      Serial.print("mx: ");
//      Serial.println(mx); 
//      Serial.print("my: ");
//      Serial.println(my);  
//      Serial.print("mz: ");
//      Serial.println(mz);   
      
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(WHITE);
      
      display.setCursor(0,0);
      
      display.print(" YAW:   ");
      display.println(yaw);
      display.println("");
      
      display.print(" PITCH: ");
      display.println(pitch);
      display.println("");
    
      display.print(" ROLL:  ");
      display.println(roll);  
      display.println("");
      
      display.display();
      lastDisplay = millis();
    }
  }
  
   else if(debugIMU == 2){
    displayTimer = millis();
    Serial.print("DisplayTimer: ");
    Serial.println(displayTimer);
    if(displayTimer - lastDisplay > 30){
//      Serial.println("                 Display");
//      Serial.print("mx: ");
//      Serial.println(mx); 
//      Serial.print("my: ");
//      Serial.println(my);  
//      Serial.print("mz: ");
//      Serial.println(mz);   
      
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(WHITE);
      
      display.setCursor(0,0);
      
      display.print(" YAW:   ");
      display.println(yawMIDI);
      display.println("");
      
      display.print(" PITCH: ");
      display.println(pitchMIDI);
      display.println("");
    
      display.print(" ROLL:  ");
      display.println(rollMIDI);  
      display.println("");
      
      display.display();
      lastDisplay = millis();
    }
  }
}
