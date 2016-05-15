



boolean firstTime = 1;
boolean menuOn = 0;

int currentMenu;
int currentMenuItem;
int currentMenuSize;

int currentSubTitle;

int currentSubMenu;
int currentSubMenuItem;
int currentSubMenuSize;

int lastMenu = 0;
int lastMenuItem = 0;

boolean subMenuActive = 0;


//########################################################
//###########    MAIN MENU FUNCTION:   ###################
void updateMenu(){
  while(1){
    if(firstTime == 1){    // Entering menu for the first time
      currentMenu = 0;
      currentMenuItem = 1;
      currentSubTitle = 0;
      currentSubMenu = 1;
      currentSubMenuItem = 0;
      displayMainMenu(currentMenuItem, currentSubMenuItem);
    }
    // First time end.
    
    // Read input:
    else{
      rotEncRead();
      rotEncButtonRead();
    }
//    else{
//      joystickMenuRead();
//      joystickBtnMenuRead();
//    }
    firstTime = 0;
    // Read encoder input end. Turn "firstTime" off
    
    
    
    

    //////////////////
    // ON NEW ENCODER INPUT:
    if(newValueBool == 1 && firstTime == 0){
      if(subMenuActive == 0){
        currentMenuItem = currentMenuItem + rotEncDir;
        if(currentMenuItem >= leftMenuSize){
          currentMenuItem = leftMenuSize - 1;
        }
        else if(currentMenuItem < 0){
          currentMenuItem = 0;
        }
        else{
          currentSubMenuItem = 0;
        }
      }
      else{
        currentSubMenuItem = currentSubMenuItem + rotEncDir;
        if(currentSubMenuItem >= rightMenuSize){
          currentSubMenuItem = rightMenuSize - 1;
        }
        else if(currentSubMenuItem <= 0){
          currentSubMenuItem = 0;
        }
      }        
      displayMainMenu(currentMenuItem, currentSubMenuItem);
    }
//      if(activeMenu == 0){
//        menuItem += rotEncDir; //
//        if(menuItem < 1){
//          menuItem = mainMenuSize - 1;
//        }
//        else if(menuItem > mainMenuSize - 1){
//          menuItem = 1;
//        }
//        lcdTextLine1(mainMenu[menuItem]);
//      }
    newValueBool = 0;
    firstTime = 0;
    
    
    
    ////////////////////
    // ON BUTTON PRESS:
    if(rotEncButtonPressed == 1){
      if(subMenuActive == 0){
        subMenuActive = 1;
        currentSubMenuItem = 0;
      }
      else{
        subMenuActive = 0;
      }
      
      //#############################################################
      //#### MAIN MENU BUTTON SECTION:
//      if(activeMenu == 0){
//        if(menuItem == 1){
//          activeMenu = menuItem;
//          lcdTextLine0(breathMenu[0]);
//          lcdTextLine1(breathMenu[1]);
//        }
//        else if(menuItem == 2){
//          activeMenu = menuItem;
//          menuItem = 1;
//          lcdTextLine0(bendMenu[0]);
//          lcdTextLine1(bendMenu[1]);
//        }
//        else if(menuItem == 3){
//          activeMenu = menuItem;
//          menuItem = 1;
//          lcdTextLine0(modeMenu[0]);
//          lcdTextLine1(modeMenu[1]);
//        }
//        else if(menuItem == 4){
//          activeMenu = menuItem;
//          menuItem = 1;
//          lcdTextLine0(instrumentMenu[0]);
//          lcdTextLine1(instrumentMenu[1]);
//        }
//        else if(menuItem == 5){
//          lcdOff();
//          menuOn = 0;
//          firstTime = 1;
//          return;
//        }
//      }
    }
 // if(buttonPressed == 1) end




    //#############################################################
    // ON BUTTON RELEASE: 
    if(rotEncButtonReleased == 1){
      if(currentMenuItem == 0){
        //#############################################################
        //#### MODE MENU BUTTON release SECTION:
        menuOn = 0;
        firstTime = 1;
        display.clearDisplay();
        display.display();
        rotEncButtonReleased = 0;
        subMenuActive = 0;
        return;
      }
    }

    
    rotEncButtonPressed = 0;
    rotEncButtonReleased = 0;
  } //while(1) end
} //updateMenu() end)
