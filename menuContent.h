static const unsigned char PROGMEM SomeBitmap[] =
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
  B00000000, B00110000 
};




struct MENU_PAGE{
const char title[22];              // 21 letters max
const char subTitle[13][10];        // 13 lines of 9 letters max
const char leftMenuBar[2][4];  // 2 lines of 3 letters max
const char leftMenu[6][10];         // 6 lines of 9 letters max
const char rightMenu[6][7][13];    // 6 pages of 7 lines of 12 letters max
};

typedef struct MENU_PAGE menuPage;

int titleSize = 21;
int subTitleSize = 13;
int leftMenuBarSize = 2;
int leftMenuSize = 6;
int rightMenuSize = 7;

// MENU ITEM STRINGS:


menuPage mainMenu = {
  "   OHMs  MAIN MENU", 
  {
  // no "subtitle
  },
  {
  // no leftMenuBar
  },
  {    // start of "leftMenu[6][10]"
    "Exit",      
    "Sensors",   
    "Outputs",    
    "Keys",    
    "Presets",
    "Info"     
  },
  {  // start of "rightMenu[6][7][13]"
    {
      "Keep changes",       
      "Save changes",          
      "Del. Changes"
    },
    { 
      "Settings",  
      "Calibration",
      "Live cal.",    
      "Show"  
    },
    { 
      "USB MIDI",     
      "OSC",     
      "Analog",  
      "Wifi" 
    },
    { 
      "Find keys",     
      "Fingerings",     
      "Octaves",
      "Biphonic"   
    },
    { 
      "Load presets",
      "Save presets",
      "Set defaults",
      "Fact. reset"     
    },
    { 
      "Credits",     
      "License",     
      "More info"     
    }
  }
};

//static const char mainMenu[7][7][21] = {
//  {
//    {"OHMs  MAIN MENU"}, //[0][0]
//    {"Exit"},            //[0][1]
//    {"Sensors"},         //[0][2]
//    {"Output"},          //[0][3]
//    {"Keys"},            //[0][4]
//    {"Presets"},         //[0][5]
//    {"Info"}             //[0][6]
//  },
//  {
//    {"Keep changes"},  //[1][0]
//    {"Save changes"},  //[1][1]
//    {"Del. changes"}   //[1][2]
//  },
//  { 
//    {"Settings"},      //[2][0]
//    {"Calibrate"},     //[2][1]
//  },
//  {
//    {"USBMIDI"},       //[3][0]
//    {"OSC"},           //[3][1]
//    {"Analog"},        //[3][2]
//    {"Wifi"}           //[3][3]
//  },
//  { 
//    {"Find keys"},     //[4][0]
//    {"Fingerings"},    //[4][1]
//    {"Octaves"},       //[4][2]
//    {"Biphonic"}       //[4][3]
//  },
//   { 
//    {"Load presets"},  //[5][0]
//    {"Save presets"},  //[5][1]
//    {"Set defaults"},  //[5][2]
//    {"Fact. reset"}    //[5][3]
//  },
//   { 
//    {"Credits"},       //[6][0]
//    {"License"},       //[6][1]
//    {"More info"},     //[6][2]
//  }
// };


//static const char sensorsMenu[6][11][12] = {
//  {
//    {" Sensor  "},       //[0][0]
//    {"settings "}       //[0][1]
//  },    
//  {
//    {"Sensor1"},       //[1][0]
//    {"Sensor2"},       //[1][1]
//    {"Sensor3"},       //[1][2]
//    {"Sensor4"},       //[1][3]
//    {"Sensor5"},       //[1][4]
//    {"Sensor6"},       //[1][5]
//    {"Sensor7"},       //[1][6]
//    {"Sensor8"},       //[1][7]
//    {"IMU pitch"},     //[1][8]
//    {"IMU roll"},      //[1][9]
//    {"IMU yaw"}        //[1][10]
//  },
//  {
//    {" Input   "},      //[2][0]
//    {" Output  "},      //[2][1]
//    {" Mode    "}       //[2][2]
//  },
//  {
//    {"    Live"},      //[3][0]
//    {"M. Filter"},     //[3][1]
//    {"Minimum"},       //[3][2]
//    {"Middle"},        //[3][3]
//    {"Buffer"},        //[3][4]
//    {"Maximum"},       //[3][5]
//    {"Slope"}          //[3][6]
//  },
//  { 
//    {"   Live"},       //[4][0]
//    {"Minimum"},       //[4][1]
//    {"Middle"},        //[4][2]
//    {"Maximum"},       //[4][3]
//    {"Slope"},         //[4][4]
//    {"Vec.Filt."},     //[4][5]
//    {"Smoother"}       //[4][6]
//  },
//  {
//    {"On/Off"},        //[5][0]
//    {"Multiplier"},    //[5][1]
//    {"+ - * /"},       //[5][2]
//    {"Other 1/2"}      //[5][3]
//  }
// };
//
//static const char calibrationMenu[5][12][21] = {
//
//  {
//    {"Calibration"},       //[0][0] 
//    {"Cal. menu"},       //[0][1]
//    {"Live cal."},       //[0][2]
//    {"Auto cal."}        //[0][3]
//  },
//  {
//    {"Sensor1"},       //[1][0]
//    {"Sensor2"},       //[1][1]
//    {"Sensor3"},       //[1][2]
//    {"Sensor4"},       //[1][3]
//    {"Sensor5"},       //[1][4]
//    {"Sensor6"},       //[1][5]
//    {"Sensor7"},       //[1][6]
//    {"Sensor8"},       //[1][7]
//    {"IMU"},           //[1][8]
//    {"pitch"},         //[1][9]
//    {"roll"},          //[1][10]
//    {"yaw"}            //[1][11]
//  },
//  {
//    {"Go!"},             //[2][0]
//    {"Press 'GO!'"},      //[2][1]
//    {"when ready"},      //[2][2]
//  },
//  {
//    {"On"},      //[3][0]
//    {"Off"},      //[3][1]
//    {"Btn1"},      //[3][2]
//    {"Btn2"},      //[3][3]
//  },
//  {
//    {"On"},      //[4][0]
//    {"Off"},      //[4][1]
//    {"Mid"},      //[4][2]
//    {"Min"},      //[4][3]
//  },
// };

//menuPage USBMIDIMenu[7][6][21] = {
//
//menuPage OSCMenu[7][6][21] = {
//
//menuPage AnalogOutMenu[7][6][21] = {
//
//menuPage WifiMenu[7][6][21] = {
//
//menuPage FindKeysMenu[7][6][21] = {
//
//menuPage FingeringsMenu[7][6][21] = {
//
//menuPage OctavesMenu[7][6][21] = {
//
//menuPage BiphonicMenu[7][6][21] = {
//
//menuPage LoadPresetsMenu[7][6][21] = {
//
//menuPage SavePresetsMenu[7][6][21] = {
//
//menuPage SetDefaultsMenu[7][6][21] = {
//
//menuPage FactResetMenu[7][6][21] = {



