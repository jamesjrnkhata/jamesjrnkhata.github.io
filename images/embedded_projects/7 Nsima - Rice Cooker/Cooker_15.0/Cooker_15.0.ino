
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Servo.h>
#include <Hx711.h>
#include <LiquidCrystal.h>
#include <AnalogKeypad.h>
 
// Data wire is plugged into pin 2 on the Arduino
const int ONE_WIRE_BUS = 2; // Temperature sensor on pin 2
 
// Setup a oneWire instance to communicate with any OneWire devices 
// (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
 
// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

HX711 scale(A2, A3);
Servo servoMain; // Define our Servo

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(13, 11, 10, 6, 5, 3);

// FLAGS AND STATES
byte Heated_flag, Start_Water_Temp_Flag, start_Heating = 0; // Declare all flags to be used 
byte First_Pour_Flag, Second_Pour_Flag, Third_Pour_Flag, Simmer_Flag, Final_Cook_Flag, Completed_Cook_Flag = 0;
byte Low_Heat_Flag, High_Heat_Flag, Low_Stirr_Flag, High_Stirr_Flag = 0;
byte selection_lock, first_selection_flag, rice_selection_flag, water_level_flag, powder_level_flag = 0;
byte powder_drain_flag, pasta_selection_flag , manual_selection_flag, manual_cook;
int cook_selection = 0;
int selected = 0;
byte portion_selection = 0;
int texture_selection = 0;
int water, powder;
int current_water, current_powder; 
int next_water, next_powder; 
unsigned long system_count = 0;
unsigned long cook_count = 0;

byte powder_hatch_state = 1; // variable to hold the state of the powder door
byte water_hatch_state = 1; // variable to hold the state of the water door
byte main_hatch_state = 1; // variable to hold the state of the main hatch

byte powder_hatch = 0; // powder door
byte water_hatch = 0; // water door
byte main_hatch = 0; // main door

byte progress_bar[8] = { 0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111};

DeviceAddress WaterBoilerTemp = {0x28, 0xFF, 0x9F, 0xEA, 0x72, 0x15, 0x02, 0xCD};
DeviceAddress PotTemp = {0x28, 0xFF, 0x95, 0x5A, 0x10, 0x14, 0x00, 0x73};

// OUTPUT PINS
const int HeaterSwitch = 4;
const int waterDrain = 7; 
const int Heat_Low = 14;
const int Heat_High = 15;
const int Stirr_Low = 8;
const int Stirr_High = 12;

// BUTTONS AND SWITCHES
const int Button_analogPin = 19;
//Button 1 = firstchoice_button
//Button 2 = rice_button
//Button 3 = button_portion

//Button 4 = button_porridge,button_soft and button_firm

//Button 5 = drain_button
//Button 6 = start_Cook_button

// LEDS AND INDICATORS
//const int HeatedInd = 3;
//const int firstchoice_Led = A5;
//const int rice_Led = 7;
//const int button_portion_Led = 8;
//const int drain_Led = 6;

// MISCELLANEOUS

// Variables will change :
int ledState = LOW; // ledState used to set the LED

// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0; // will store last time
unsigned long minutes = 0;
byte seconds = 0;
long mod_seconds;
byte two_second_counter;
byte lcd_delay;
byte lcd_toggle = 5; // SET TO 5 AS THE DEFAULT INACTIVE STATE
String how_many;
String texture;

// constants won't change :
const long interval = 1000; // interval at which to blink (milliseconds)

String Key_press; // variable to hold key presses
char BT_press; // variable to hold key presses
String Food_Choice; //Variable used to carry the name of the food being made
String blank = "                ";

int powder_dec1, powder_dec2, powder_dec3;
int water_dec1, water_dec2;

AnalogKeypad AnKeypad(Button_analogPin);
 

void setup(void)
{
  // start serial port
  Serial.begin(9600);
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print(" Casa-Juegos Inc");
  delay(2000);
  lcd.setCursor(0,0);
  lcd.print(blank);
  lcd.setCursor(0,0);
  lcd.createChar(0, progress_bar);
        
  servoMain.attach(9); // servo on digital pin 9
  servoMain.write(0);  // Turn Servo Left to 0 degrees

  // Start up the library
  sensors.begin();
  
  // Set Output Pins
  pinMode(HeaterSwitch, OUTPUT);
  pinMode(waterDrain, OUTPUT);
  
  pinMode(Heat_Low, OUTPUT);
  pinMode(Heat_High, OUTPUT);

  pinMode(Stirr_Low, OUTPUT);
  pinMode(Stirr_High, OUTPUT);

 
  digitalWrite(HeaterSwitch, HIGH); // switch off Element on start up
  digitalWrite(waterDrain, HIGH); // switch off Drain on start up
  
  digitalWrite(Heat_Low, HIGH); // switch off Cooker Low on start up
  digitalWrite(Heat_High, HIGH); // switch off Cooker Low on start up

  digitalWrite(Stirr_Low, HIGH); // switch off Stirring Low on start up
  digitalWrite(Stirr_High, HIGH); // switch off Stirring High on start up  
}
 
 
void loop(void)
{ 
  sensors.requestTemperatures(); // Send the command to get temperatures
//  Serial.print("Temperature from Water Dispenser is: ");
//  Serial.print(sensors.getTempC(WaterBoilerTemp));
//  Serial.println();
 // delay(1000);
 // Serial.print("Temperature from Pot is: ");
 // Serial.print(sensors.getTempC(PotTemp));
//  Serial.println();

  timer(); // START TIMER TO USE FOR COOKING
  opened_hatches(); // BLOCK USED TO HANDLE HATCHES OPENING
  manual_drain(); // MANUAL DRAIN FUNCTION
  Cook_Progress(); // DISPLAY FUNCTION USED FOR AUTOMATIC COOK PROGRESS 
  Start_Cook(); // START COOKING ROUTINE 
  heat(); // "LOW" & "HIGH" COOKING
  stirr(); // "LOW" & "HIGH" STIRRING
  Cook_complete(); // RUN FINALIZING FUNCTION    
    
  system_count ++; // Counter to use for timing the temperature reading (false reading)

 if(Serial.available()){
    BT_press = Serial.read();       
 }
 
  if(BT_press == 'Z'){
    main_hatch_state = 0;
     Serial.println(main_hatch_state);
  }

  if(BT_press == 'Y'){
    main_hatch_state = 1;
     Serial.println(main_hatch_state);
  }       
  


  // BUTTON CONTROL FOR WHEN A COOK IS NOT IN PROGRESS
  if(selection_lock == 0){  
     Key_press = AnKeypad.readKey();
     if(Serial.available()){
      BT_press = Serial.read();       
     }
          
     
     // CLEAR BUTTON FOR MOST SELECTION FLAGS BUT NOT WHEN THE AUTO COOKS ARE ON
     if(Key_press == "STOP" || BT_press == 'S'){
      
      manual_selection_flag = 0;
      rice_selection_flag = 0;
      first_selection_flag = 0;
      pasta_selection_flag = 0;

      texture_selection = 0;
      portion_selection = 0;
      BT_press = ' ';      
     }
    }


  // CONTROLS FOR MANUAL MODE ONLY  
  if(selection_lock == 1 && manual_cook == 1){  
     Key_press = AnKeypad.readKey();
     if(Serial.available()){
      BT_press = Serial.read();       
     }
     
     if(Key_press == "STOP" || BT_press == 'S'){
      
      Completed_Cook_Flag = 1; 
      lcd_toggle = 4;
      Low_Heat_Flag = 0;
      High_Heat_Flag = 0; 
      Low_Stirr_Flag = 0; 
      High_Stirr_Flag = 0;
      BT_press = ' ';
      // WORK OUT A WAY TO HAVE DIFFERENT ALORITHMS FOR THE STOP / CLEAR FOR MANUAL C
     }
    }
    

  // CHECK IF MAIN HATCH ONLY IS CLOSED, THE REST CAN BE OPEN
    if(main_hatch_state == 1){ 
      if(Key_press == "MANUAL" && selection_lock == 0 || BT_press == 'M' && selection_lock == 0 ){ // "MANUAL"
        water_level_flag = 0; // reset water_level_flag to accommodate for last minute changes
        powder_level_flag = 0; // reset powder_level_flag to accommodate for last minute changes 
        manual_selection_flag = 1;
        rice_selection_flag = 0;
        first_selection_flag = 0;
        pasta_selection_flag = 0;
        lcd_toggle = 7;
        BT_press = ' ';
     }
   }

   if(manual_selection_flag == 1){

    if (Key_press == "START_COOK" || BT_press == 'G' ){
      Food_Choice = "FOOD"; 
      lcd_toggle = 1;
      manual_cook = 1;
      selection_lock = 1;
      main_hatch = 1; // lock main hatch until after cook
      water_hatch = 1; // lock water door until after cook
      BT_press = ' '; 
    }
    
    if (manual_cook == 1){
       servoMain.write(125);     
       if(lcd_toggle == 1){
        switch(two_second_counter){
           case 0:  
             lcd.setCursor(0,0);lcd.print(blank);lcd.setCursor(0,1);lcd.print(blank);lcd.setCursor(0,0);
             lcd.print("USE STIRRING");
             lcd.setCursor(0,1);
             lcd.print("LOW or HIGH"); 
           break;
           case 1:  
             lcd.setCursor(0,0);lcd.print(blank);lcd.setCursor(0,1);lcd.print(blank);lcd.setCursor(0,0);
             lcd.print("TURN HEATING");
             lcd.setCursor(0,1);
             lcd.print("LOW or HIGH");      
           break;           
        break;
       }
      }

       if(lcd_toggle == 2){
         lcd.setCursor(0,0);lcd.print(blank);lcd.setCursor(0,1);lcd.print(blank);lcd.setCursor(0,0);  
         
         if (Low_Stirr_Flag == 0 && High_Stirr_Flag == 0){
           lcd.setCursor(0,0);
           lcd.print("STIRRING is OFF ");
          }
         else if (Low_Stirr_Flag == 1){
           lcd.setCursor(0,0);
           lcd.print("STIRRING is LOW ");
          }
         else if (High_Stirr_Flag == 1){
           lcd.setCursor(0,0);
           lcd.print("STIRRING is HIGH");
          }
         
         
         if (Low_Heat_Flag == 0){
           lcd.setCursor(0,1);
           lcd.print("HEATING is OFF  ");
          }
         else if (Low_Heat_Flag == 1 && High_Heat_Flag == 0){
           lcd.setCursor(0,1);
           lcd.print("HEATING is LOW  ");
          }
         else if (Low_Heat_Flag == 1 && High_Heat_Flag == 1){
           lcd.setCursor(0,1);
           lcd.print("HEATING is HIGH ");
          }

      }

      if(Key_press == "LOW_HEAT" || BT_press == 'L'){
         lcd_toggle = 2; 
         if(High_Heat_Flag == 1){
          Low_Heat_Flag = 1;
          High_Heat_Flag = 0;
          BT_press = ' ';          
         }
         else if(Low_Heat_Flag == 1){
          Low_Heat_Flag = 0;
          High_Heat_Flag = 0;
          BT_press = ' ';           
         }
         else if(Low_Heat_Flag == 0){
          Low_Heat_Flag = 1;
          High_Heat_Flag = 0;
          BT_press = ' ';           
         }
       }

      if(Key_press == "HIGH_HEAT" || BT_press == 'H'){
         Low_Heat_Flag = 1;
         High_Heat_Flag = 1;
         BT_press = ' ';
         lcd_toggle = 2; 
       }


      if(Key_press == "LOW_STIRRING" || BT_press == 'O'){
         lcd_toggle = 2; 
         if(High_Stirr_Flag == 1){
          High_Stirr_Flag = 0; 
          delay(1000);
          Low_Stirr_Flag = 1;                   
          BT_press = ' ';          
         }
         else if(Low_Stirr_Flag == 1){
          Low_Stirr_Flag = 0;
          //High_Stirr_Flag = 0;
          BT_press = ' ';           
         }
         else if(Low_Stirr_Flag == 0){
          Low_Stirr_Flag = 1;
          //High_Stirr_Flag = 0;
          BT_press = ' ';           
         }
       }       

      if(Key_press == "HIGH__STIRRING" || BT_press == 'I'){
         Low_Stirr_Flag = 0;
         delay(1000);
         High_Stirr_Flag = 1;
         BT_press = ' ';
         lcd_toggle = 2; 
       }                  
    }    
   }


  // CONDITION TO CHECK IF THE DEVICE IS OPEN, IF IT IS ONLY SECONDARY FUNCTIONS CAN BE CARRIED OUT
  if(main_hatch_state == 1 && water_hatch_state == 1 && powder_hatch_state == 1){  
          
        
    // START FIRST CHOICE SELECTION 
    if(Key_press == "FIRSTCHOICE" && selection_lock == 0 || BT_press == 'N' && selection_lock == 0){
     Food_Choice = "FIRST";     
     lcd_toggle = 0;
     water_level_flag = 0; // reset water_level_flag to accommodate for last minute changes
     powder_level_flag = 0; // reset powder_level_flag to accommodate for last minute changes
     first_selection_flag = 1;
     rice_selection_flag = 0;
     pasta_selection_flag = 0;
     manual_selection_flag = 0;
     BT_press = ' ';
    }
    
    // START RICE SELECTION
    if(Key_press == "RICE" && selection_lock == 0 || BT_press == 'R' && selection_lock == 0){
     Food_Choice = "RICE"; 
     lcd_toggle = 0;          
     water_level_flag = 0; // reset water_level_flag to accommodate for last minute changes
     powder_level_flag = 0; // reset powder_level_flag to accommodate for last minute changes 
     rice_selection_flag = 1;
     first_selection_flag = 0;      
     pasta_selection_flag = 0;
     manual_selection_flag = 0;
     BT_press = ' ';
   }
   
    // START PASTA SELECTION    
    if(Key_press == "PASTA" && selection_lock == 0 || BT_press == 'P' && selection_lock == 0){
     Food_Choice = "PASTA";
     lcd_toggle = 0;  
     water_level_flag = 0; // reset water_level_flag to accommodate for last minute changes
     powder_level_flag = 0; // reset powder_level_flag to accommodate for last minute changes 
     pasta_selection_flag = 1;
     rice_selection_flag = 0;
     first_selection_flag = 0;
     manual_selection_flag = 0;
     BT_press = ' ';
   }   
      
    
  // FIRST CHOICE SELECTION BLOCK 
   if(first_selection_flag == 1){  

      Auto_Cook_Selection();
      
      //WAIT FOR START COOK BUTTON PRESS 
      if(Key_press == "START_COOK" || BT_press == 'G'){
        
        lcd_toggle = 3;
        lcd_delay = 0;
                
        water_read();
        powder_read();
                   
        level_check(); // FUNCTION TO RUN A WATER LEVEL AND POWDER LEVEL CHECK
        water_temp_check(); // RUN TEMPERATURE CHECK SUB ROUTINE 
        BT_press = ' ';
        
        //  POT IS EMPTY... CONDITION TO CHECK BEFORE START COOKING
         
        if(water_level_flag == 1 && powder_level_flag == 1 && start_Heating == 1){ //THREE CONDITIONS TO CHECK BEFORE START COOKING
          selection_lock = 1;        
          lcd_toggle = 4;
          powder_hatch = 1; // lock powder door until after cook
          water_hatch = 1; // lock water door until after cook
          main_hatch = 1; // lock main hatch until after cook
          BT_press = ' ';
          lcd.setCursor(0,0);lcd.print(blank);lcd.setCursor(0,1);lcd.print(blank);lcd.setCursor(0,0);            
         }
      }              
    }

  // RICE SELECTION BLOCK 
   if(rice_selection_flag == 1){   
     
      Auto_Cook_Selection();
      
      //WAIT FOR START COOK BUTTON PRESS 
      if(Key_press == "START_COOK" || BT_press == 'G'){
        
        lcd_toggle = 3;
        lcd_delay = 0;
                
        water_read();
        powder_read();
                   
        level_check(); // FUNCTION TO RUN A WATER LEVEL AND POWDER LEVEL CHECK
        start_Heating = 1; // SET FLAG TO START WATER BOILING ROUTINE  ; // RUN TEMPERATURE CHECK SUB ROUTINE 
        BT_press = ' ';
        
        //  POT IS EMPTY... CONDITION TO CHECK BEFORE START COOKING
         
        if(water_level_flag == 1 && powder_level_flag == 1 && start_Heating == 1){ //THREE CONDITIONS TO CHECK BEFORE START COOKING
          selection_lock = 1;          
          lcd_toggle = 4;
          powder_hatch = 1; // lock powder door until after cook
          water_hatch = 1; // lock water door until after cook
          main_hatch = 1; // lock main hatch until after cook
          BT_press = ' ';
          lcd.setCursor(0,0);lcd.print(blank);lcd.setCursor(0,1);lcd.print(blank);lcd.setCursor(0,0);            
         }
      }      
   }
       
  }    
}

void water_read()
{
  scale.set_gain(128);
  long value = scale.read_average(5);
  water_level(value);
  Serial.print("water: ");    
  Serial.println(water);
}

void powder_read()
{
  scale.set_gain(32);
  long value2 = scale.read_average(5);
  powder_level(value2);
  Serial.print("powder: ");    
  Serial.println(powder);
}

void heat()
{
 if(Low_Heat_Flag == 1){
    digitalWrite(Heat_Low, LOW);
  }

 if(High_Heat_Flag == 1){
    digitalWrite(Heat_High, LOW);
  }

 if(Low_Heat_Flag == 0){
    digitalWrite(Heat_Low, HIGH);      
  } 
    
 if(High_Heat_Flag == 0){
    digitalWrite(Heat_High, HIGH);
  }
}

void stirr()
{
 if(Low_Stirr_Flag == 1){    
    digitalWrite(Stirr_High, HIGH);
    delay(1000);
    digitalWrite(Stirr_Low, LOW);  
  }  
 if(High_Stirr_Flag == 1){
    digitalWrite(Stirr_Low, HIGH);
    delay(1000);
    digitalWrite(Stirr_High, LOW);   
  }
 if(Low_Stirr_Flag == 0 && High_Stirr_Flag == 0){
   digitalWrite(Stirr_Low, HIGH);
   digitalWrite(Stirr_High, HIGH);
  }
  if(Low_Stirr_Flag == 1 && High_Stirr_Flag == 1){
   digitalWrite(Stirr_Low, HIGH);
   digitalWrite(Stirr_High, HIGH);
  } 
}

void water_temp_check()
{
//CHECK IF ITS THE FIRST TIME THE ROUTINE HAS BEEN CALLED
 if(start_Heating == 0){
    if(sensors.getTempCByIndex(0) > 32 && system_count > 5 && water > 0){
       switch(two_second_counter){
           case 0:  
             lcd.setCursor(0,0);lcd.print(blank);lcd.setCursor(0,1);lcd.print(blank);lcd.setCursor(0,0);
             lcd.print("WATER IS TOO");
             lcd.setCursor(0,1);
             lcd.print("  WARM TO COOK !"); 
           break;
           case 1:  
             lcd.setCursor(0,0);lcd.print(blank);lcd.setCursor(0,1);lcd.print(blank);lcd.setCursor(0,0);
             lcd.print("DRAIN THE WATER");       
           break;
           case 2:  
             lcd.setCursor(0,0);lcd.print(blank);lcd.setCursor(0,1);lcd.print(blank);lcd.setCursor(0,0);
             lcd.print("OR SELECT RICE");
             lcd.setCursor(0,1);
             lcd.print("  / PASTA ");         
           break;
        break;
       } 
    }
    if(sensors.getTempCByIndex(0) < 32 && water > 0){   
      start_Heating = 1; // SET FLAG TO START WATER POUR & BOILING ROUTINE  
    }   
 }  
}

void Water_Heater()
{
   if (sensors.getTempCByIndex(0) < 90){    
    digitalWrite(HeaterSwitch, LOW);   
   }
   if (sensors.getTempCByIndex(0) >= 90 && Heated_flag == 0){
    digitalWrite(HeaterSwitch, HIGH); // switch off Element
    Heated_flag = 1; // set water is heated flag on because boiling should only happen once // FLAG INITIALIZES THE NEXT ROUTINE
   }  
}

void timer()
{
  unsigned long currentMillis = millis();

   if (currentMillis - previousMillis >= interval) {
     // save the last time
     previousMillis = currentMillis;
     seconds ++;
     if(seconds >= 60){      
      minutes ++;
      seconds = 0;
     }
     if(seconds > 0 && seconds < 60){      
      mod_seconds = seconds % 2;
     }
     else
     {
      mod_seconds = 0;      
     }
     
     if(mod_seconds == 1){      
      two_second_counter ++;
     }
     if(two_second_counter > 2){
      two_second_counter = 0;
     }

      if(two_second_counter == 2){
       lcd_delay ++;
      }     
   }
}


void opened_hatches()
{    
// MAIN HATCH IS OPEN NOTHING WORKS 
 
  if(main_hatch_state == 0){
     lcd_toggle = 6;  
  }

// REFILL WATER ONLY ALLOWED WHEN COOK HAS NOT STARTED 
    
    if(water_hatch_state == 0){
      scale.set_gain(128);
      long value = scale.read_average(5);
      water_level(value);
      // mod_seconds used to display water level on every odd second
      if (mod_seconds == 1){
        lcd.setCursor(0,0);lcd.print(blank);lcd.setCursor(0,1);lcd.print(blank);lcd.setCursor(0,0);
        lcd.print("Water Level : ");        
        int w = water/100;
        for(int x = 0; x < w ; x++){
          lcd.setCursor(x,1);
          lcd.write(byte(0));
        }         
      }
      
      if (water > 1500){
        lcd.setCursor(0,0);lcd.print(blank);lcd.setCursor(0,1);lcd.print(blank);lcd.setCursor(0,0);
        lcd.print("Water Level : ");
        lcd.setCursor(0,1);
        lcd.print(" FULL CAPACITY !");
      }
      if(Key_press == "FIRSTCHOICE" || BT_press == 'N'){
        // CHECK WATER LEVEL RELATIVE TO FIRSTCHOICE
      }
      if(Key_press == "RICE" || BT_press == 'R'){
        // CHECK WATER LEVEL RELATIVE TO RICE
      }
      if(Key_press == "PASTA" || BT_press == 'P'){
        // CHECK WATER LEVEL RELATIVE TO PASTA
      }
    }  

  // REFILL POWDER ONLY ALLOWED WHEN COOK HAS NOT STARTED 
 
  if(powder_hatch_state == 0){
    scale.set_gain(32);
    long value2 = scale.read_average(5);
    powder_level(value2);
    // mod_seconds used to display powder level on every even second
    if (mod_seconds == 0){
      lcd.setCursor(0,0);lcd.print(blank);lcd.setCursor(0,1);lcd.print(blank);lcd.setCursor(0,0);
      lcd.print("Powder Level : "); 
      int y = powder/90;
      for(int z = 0; z < y ; z++){
        lcd.setCursor(z,1);
        lcd.write(byte(0));
      }
    }
    if (powder > 1350){
      lcd.setCursor(0,0);lcd.print(blank);lcd.setCursor(0,1);lcd.print(blank);lcd.setCursor(0,0);
      lcd.print("Powder Level : ");
      lcd.setCursor(0,1);
      lcd.print(" FULL CAPACITY !");
    }
    if(Key_press == "FIRSTCHOICE" || BT_press == 'N'){
      // CHECK HOLDER LEVEL RELATIVE TO FIRSTCHOICE
    }
    if(Key_press == "RICE" || BT_press == 'R'){
      // CHECK HOLDER LEVEL RELATIVE TO RICE
    }
    if(Key_press == "PASTA" || BT_press == 'P'){
      // CHECK HOLDER LEVEL RELATIVE TO PASTA
    }
  } 
   //   Serial.println(water);
  //    Serial.println();
 //     Serial.println(powder);
 //     Serial.println();
}

void manual_drain(){
  
  // MANUAL DRAIN BLOCK
  if(selection_lock == 0 && Key_press == "DRAIN_WATER" || selection_lock == 0 && BT_press == 'D'){
          
    water_read();
    if (water > 0){
      Start_Water_Temp_Flag = 1;
      BT_press = ' '; 
    }
    else
    {
      lcd.setCursor(0,0);lcd.print(blank);lcd.setCursor(0,1);lcd.print(blank);lcd.setCursor(0,0);
      lcd.print("Water is Empty"); 
      BT_press = ' ';
      delay(1000); 
    }
  }

  if (Start_Water_Temp_Flag == 1){
    digitalWrite(waterDrain, LOW);
    water_read();
          
    lcd.setCursor(0,0);lcd.print(blank);lcd.setCursor(0,1);lcd.print(blank);lcd.setCursor(0,0);
    lcd.print("Draining Water !");
    int w = water/100;
    for(int x = 0; x < w ; x++){
      lcd.setCursor(x,1);
      lcd.write(byte(0));
    }            
    
    if(water == 0){
      digitalWrite(waterDrain, HIGH);
      Start_Water_Temp_Flag = 0;
      start_Heating = 0; // RESET TO START PREREQUISITES CHECK AGAIN    
    }
  }

 if(selection_lock == 0 && Key_press == "DUMP_POWDER" || selection_lock == 0 && BT_press == 'E'){            
    powder_read();
    if (powder > 0){
      powder_drain_flag = 1;
      BT_press = ' '; 
    }
    else
    {
      lcd.setCursor(0,0);lcd.print(blank);lcd.setCursor(0,1);lcd.print(blank);lcd.setCursor(0,0);
      lcd.print("Holder is Empty"); 
      BT_press = ' ';
      delay(1000); 
    }
  }

  if (powder_drain_flag == 1){
    powder_read();
    if(powder > next_powder){
      servoMain.write(105);
      delay(300);  //                 
      servoMain.write(0);  // Turn Servo Left to 0 degrees
                  
      lcd.setCursor(0,0);lcd.print(blank);lcd.setCursor(0,1);lcd.print(blank);lcd.setCursor(0,0);
      lcd.print("Holder Draining!");
      int y = powder/90;
      for(int z = 0; z < y ; z++){
        lcd.setCursor(z,1);
        lcd.write(byte(0));
      }           
    }
    if(powder == 0){       
      powder_drain_flag = 0;        
    }
  }  
}


void Cook_Progress()
{
  if(manual_cook == 0){ 
    
   if(lcd_toggle == 0 && Start_Water_Temp_Flag != 1 && powder_drain_flag != 1){
     if(mod_seconds == 0){
       lcd.setCursor(0,0);lcd.print(blank);lcd.setCursor(0,1);lcd.print(blank);lcd.setCursor(0,0);
       lcd.print("Feed How Many ?");
       lcd.setCursor(0,1);
      // lcd.print("'ADD PORTIONS'");
     }
     if(mod_seconds == 1){
       lcd.setCursor(0,0);lcd.print(blank);lcd.setCursor(0,1);lcd.print(blank);lcd.setCursor(0,0);
       lcd.print("Press: ");
       lcd.setCursor(0,1);
       lcd.print("* ADD PORTIONS *");
     }               
  }

  if(lcd_toggle == 1 && Start_Water_Temp_Flag != 1 && powder_drain_flag != 1){
    if(lcd_delay < 2){
         if(portion_selection == 1){
           how_many = " Person";
           lcd.setCursor(0,0);lcd.print(blank);lcd.setCursor(0,1);lcd.print(blank);lcd.setCursor(0,0);
           lcd.print("Cook for  ");
           lcd.setCursor(0,1);
           lcd.print(portion_selection);lcd.print(how_many);
         }
         else
         {
           how_many = " People";
           lcd.setCursor(0,0);lcd.print(blank);lcd.setCursor(0,1);lcd.print(blank);lcd.setCursor(0,0);
           lcd.print("Cook for  ");
           lcd.setCursor(0,1);
           lcd.print(portion_selection);lcd.print(how_many);            
         }           
       }
       else
       {
           if(mod_seconds == 0){
           lcd.setCursor(0,0);lcd.print(blank);lcd.setCursor(0,1);lcd.print(blank);lcd.setCursor(0,0);
           lcd.print("How do you");
           lcd.setCursor(0,1);
           lcd.print("want it cooked ?");
         }
         if(mod_seconds == 1){
           lcd.setCursor(0,0);lcd.print(blank);lcd.setCursor(0,1);lcd.print(blank);lcd.setCursor(0,0);
           lcd.print("Press: PORRIDGE");
           lcd.setCursor(0,1);
           if(first_selection_flag == 1){
            lcd.print("SOFT OR FIRM");
           }
           else
           {
            lcd.print("       OR SOFT");
           }
         }
       }             
    }

    if(lcd_toggle == 2 && Start_Water_Temp_Flag != 1 && powder_drain_flag != 1){         
       if(mod_seconds == 0){
         lcd.setCursor(0,0);lcd.print(blank);lcd.setCursor(0,1);lcd.print(blank);lcd.setCursor(0,0);
         lcd.print("Cook ");lcd.print(texture);
         lcd.setCursor(0,1);
         lcd.print(Food_Choice);lcd.print(" for ");lcd.print(portion_selection);
       }
       if(mod_seconds == 1){
         lcd.setCursor(0,0);lcd.print(blank);lcd.setCursor(0,1);lcd.print(blank);lcd.setCursor(0,0);
         lcd.print("To Begin Press: ");
         lcd.setCursor(0,1);
         lcd.print(" * START COOK *");
       }       
     }

     if(lcd_toggle == 3 && Start_Water_Temp_Flag != 1 && powder_drain_flag != 1){
         if(lcd_delay < 1){
          if(water_level_flag == 0 && mod_seconds == 0){
             lcd.setCursor(0,0);lcd.print(blank);lcd.setCursor(0,1);lcd.print(blank);lcd.setCursor(0,0);
             lcd.print("Water is Low");
             lcd.setCursor(0,1);
             lcd.print("Add More Water");
            // delay(2000);
            // lcd_toggle = 2;   
           }
  
           if(powder_level_flag == 0 && mod_seconds == 1){
             lcd.setCursor(0,0);lcd.print(blank);lcd.setCursor(0,1);lcd.print(blank);lcd.setCursor(0,0);
             lcd.print("Powder is Low");
             lcd.setCursor(0,1);
             lcd.print("Add More Powder");
         //    delay(2000);
           //  lcd_toggle = 2;   
           }          
         }
     else
     {
        lcd_toggle = 2;
     }             
    }    
  }

  if(selection_lock == 1 && lcd_toggle == 4){
    int w, x1;
    if (Completed_Cook_Flag == 0){
      if(First_Pour_Flag == 0 && Heated_flag == 0){
        w = 9;
       }
      if(Heated_flag == 1 && Second_Pour_Flag == 0){
        w = 10;
       }
      if(Second_Pour_Flag == 1 && Simmer_Flag == 0){
        w = 11;
       } 
      if(Simmer_Flag == 1 && Third_Pour_Flag == 0){
        w = 12;
       }
      if(Third_Pour_Flag == 1 && Final_Cook_Flag == 0){
        w = 13;
       }
      if(Final_Cook_Flag == 1){
        w = 14;
       }  
                           
      lcd.setCursor(0,0);lcd.print(blank);lcd.setCursor(0,1);lcd.print(blank);lcd.setCursor(0,0);
      lcd.print("Cooking "); lcd.print(Food_Choice);       
      for(int x = 0; x < w ; x++){
        lcd.setCursor(x,1);
        lcd.write(byte(0));
        x1 = x + 1;
      }
      if(seconds % 2 == 1){
       lcd.setCursor(x1,1);
       lcd.write(" ");
      }
      else
      {
        lcd.setCursor(x1,1);
        lcd.write(byte(0));          
      }           
    }
    else
    {
     switch(mod_seconds){
         case 0:  
           lcd.setCursor(0,0);lcd.print(blank);lcd.setCursor(0,1);lcd.print(blank);lcd.setCursor(0,0);
           lcd.print(Food_Choice);lcd.print(" is Ready");
         break;
         case 1:  
           lcd.setCursor(0,0);lcd.print(blank);lcd.setCursor(0,1);lcd.print(blank);lcd.setCursor(0,0);
           lcd.print("OPEN COOKER DOOR");
           lcd.setCursor(0,1);
           lcd.print("ENJOY YOUR MEAL!");       
         break;           
      break;
     }  
    }     
  }

  if(Start_Water_Temp_Flag == 0 &&  first_selection_flag == 0 && powder_drain_flag == 0 && rice_selection_flag == 0 && pasta_selection_flag == 0 && manual_selection_flag == 0){
    
     // MAIN HATCH IS CLOSED EVERYTHING GOES BACK TO NORMAL 
      if(main_hatch_state == 1){
         lcd_toggle = 5;  
      }   
      
     if(lcd_toggle == 5){
       switch(mod_seconds){
           case 0:  
             lcd.setCursor(0,0);lcd.print(blank);lcd.setCursor(0,1);lcd.print(blank);lcd.setCursor(0,0);
             lcd.print("READY TO COOK !");
             lcd.setCursor(0,1);
             lcd.print(blank); 
           break;
           case 1:  
             lcd.setCursor(0,0);lcd.print(blank);lcd.setCursor(0,1);lcd.print(blank);lcd.setCursor(0,0);
             lcd.print("Select: FIRST");
             lcd.setCursor(0,1);
             lcd.print(" RICE OR PASTA");       
           break;           
        break;
       }
     } 
   }

   if(lcd_toggle == 6){
    switch(mod_seconds){
         case 0:  
           lcd.setCursor(0,0);lcd.print(blank);lcd.setCursor(0,1);lcd.print(blank);lcd.setCursor(0,0);
           lcd.print("MAIN DOOR");
           lcd.setCursor(0,1);
           lcd.print("IS OPENED"); 
         break;
         case 1:  
           lcd.setCursor(0,0);lcd.print(blank);lcd.setCursor(0,1);lcd.print(blank);lcd.setCursor(0,0);
           lcd.print("MAKE SURE IT IS");
           lcd.setCursor(0,1);
           lcd.print("PROPERLY CLOSED");       
         break;           
      break;
     }    
   }

   if(lcd_toggle == 7){
     switch(mod_seconds){
       case 0:  
         lcd.setCursor(0,0);lcd.print(blank);lcd.setCursor(0,1);lcd.print(blank);lcd.setCursor(0,0);
         lcd.print("COOK IT YOUR WAY");
         lcd.setCursor(0,1);
         lcd.print("MANAUL MODE !"); 
       break;
       case 1:  
         lcd.setCursor(0,0);lcd.print(blank);lcd.setCursor(0,1);lcd.print(blank);lcd.setCursor(0,0);
         lcd.print("To Begin Press: ");
         lcd.setCursor(0,1);
         lcd.print(" * START COOK *");      
       break;           
    break;
   }
  }   
} 


void Auto_Cook_Selection()
{
   if(Key_press == "ADD_PORTIONS" || BT_press == 'A'){
    lcd_delay = 0;
    lcd_toggle = 1;
    if(portion_selection < 5){
      delay(100); // To slow down the transition between button presses
      portion_selection ++;
      water_level_flag = 0; // reset water_level_flag to accommodate for last minute changes
      powder_level_flag = 0; // reset powder_level_flag to accommodate for last minute changes
      BT_press = ' ';
     }
    else
     {
      delay(100); // To slow down the transition between button presses
      portion_selection = 1;
      water_level_flag = 0; // reset water_level_flag to accommodate for last minute changes
      powder_level_flag = 0; // reset powder_level_flag to accommodate for last minute changesBT_press = ' ';
     }
     
   if(BT_press == '1'){
    lcd_delay = 0;
    lcd_toggle = 1;
    portion_selection = 1;
    BT_press = ' ';
    water_level_flag = 0; // reset water_level_flag to accommodate for last minute changes
    powder_level_flag = 0; // reset powder_level_flag to accommodate for last minute changes      
   }

   if(BT_press == '2'){
    lcd_delay = 0;
    lcd_toggle = 1;
    portion_selection = 2;
    BT_press = ' ';
    water_level_flag = 0; // reset water_level_flag to accommodate for last minute changes
    powder_level_flag = 0; // reset powder_level_flag to accommodate for last minute changes      
   }
      
   if(BT_press == '3'){
    lcd_delay = 0;
    lcd_toggle = 1;
    portion_selection = 3;
    BT_press = ' ';
    water_level_flag = 0; // reset water_level_flag to accommodate for last minute changes
    powder_level_flag = 0; // reset powder_level_flag to accommodate for last minute changes      
   } 

   if(BT_press == '4'){
    lcd_delay = 0;
    lcd_toggle = 1;
    portion_selection = 4;
    BT_press = ' ';
    water_level_flag = 0; // reset water_level_flag to accommodate for last minute changes
    powder_level_flag = 0; // reset powder_level_flag to accommodate for last minute changes      
   }

   if(BT_press == '5'){
    lcd_delay = 0;
    lcd_toggle = 1;
    portion_selection = 5;
    BT_press = ' ';
    water_level_flag = 0; // reset water_level_flag to accommodate for last minute changes
    powder_level_flag = 0; // reset powder_level_flag to accommodate for last minute changes      
   }           
       
    }
    // INDICATE BUTTON_PORTION SELECTION LED
    //  digitalWrite(button_portion_Led, HIGH);
      
      if(Key_press == "PORRIDGE" || BT_press == 'T'){
        lcd_toggle = 2;
        texture = "PORRIDGE";
        if(first_selection_flag == 1){texture_selection = 100;}
        else if(rice_selection_flag == 1){texture_selection = 400;}
        water_level_flag = 0; // reset water_level_flag to accommodate for last minute changes
        powder_level_flag = 0; // reset powder_level_flag to accommodate for last minute changes
        BT_press = ' ';
       }
      if(Key_press == "SOFT" || BT_press == 'U'){
        lcd_toggle = 2;
        texture = "SOFT";            
        if(first_selection_flag == 1){texture_selection = 200;}
        else if(rice_selection_flag == 1){texture_selection = 500;}
        water_level_flag = 0; // reset water_level_flag to accommodate for last minute changes
        powder_level_flag = 0; // reset powder_level_flag to accommodate for last minute changes  
        BT_press = ' ';        
       }
      if(Key_press == "FIRM" || BT_press == 'V'){
        lcd_toggle = 2;
        texture = "FIRM";            
        if(first_selection_flag == 1){texture_selection = 300;}
        else if(rice_selection_flag == 1){texture_selection = 500;}
        water_level_flag = 0; // reset water_level_flag to accommodate for last minute changes
        powder_level_flag = 0; // reset powder_level_flag to accommodate for last minute changes
        BT_press = ' ';
       }
         
      selected = texture_selection + portion_selection;  
}

void Start_Cook()
{
  switch (cook_selection) {
      case 101: // THE BUTTON HAS BEEN PRESSED FOR FIRSTCHOICE PORRIDGE     
       if(selection_lock == 1){
       //  Cook_Progress(); // FUNCTION TO INDICATE FOOD COOKING PROGRESS          
         first_porridge(); // RUN FIRST PORRIDGE COOK
         first_porridge_complete(); // FINALIZE COOK AS PORRIDGE         
    //     Cook_complete(); // RUN FINALIZING FUNCTION    
       }   
      break;
      
      case 102: // THE BUTTON HAS BEEN PRESSED FOR FIRSTCHOICE SOFT / FIRM     
       if(selection_lock == 1){  
       //  Cook_Progress(); // FUNCTION TO INDICATE FOOD COOKING PROGRESS                              
         first_porridge(); // RUN FIRST PORRIDGE COOK
         first_soft_firm(); // RUN FIRST SOFT / FIRM TO COMPLETE COOK
       //  Cook_complete(); // RUN FINALIZING FUNCTION          
       }   
      break;


      case 201: // THE BUTTON HAS BEEN PRESSED FOR RICE PORRIDGE     
       if(selection_lock == 1){
      //   Cook_Progress(); // FUNCTION TO INDICATE FOOD COOKING PROGRESS          
 
       }   
      break;
      
      case 202: // THE BUTTON HAS BEEN PRESSED FOR RICE SOFT / FIRM    
       if(selection_lock == 1){
      //   Cook_Progress(); // FUNCTION TO INDICATE FOOD COOKING PROGRESS   
                       
       }   
      break; 
                 
    break;
  }  
}

void level_check()
{
 switch(selected){

    // PORRIDGE FIRST_SELECTION
     
     case 101:  
      // minimum required levels are checked for cook
      if(water >= 1){water_level_flag = 1;}
      if(powder >= 1){powder_level_flag = 1;}      
      // variables to be used for porridge portion 1
      powder_dec1 = 0; powder_dec2 = 0; powder_dec3 = 0;
      water_dec1 = 0;  water_dec2 = 0;
      cook_selection = 101; 
     break;
     
     case 102:  
      // minimum required levels are checked for cook
      if(water >= 1){water_level_flag = 1;}
      if(powder >= 1){powder_level_flag = 1;}      
      // variables to be used for porridge portion 2
      powder_dec1 = 0; powder_dec2 = 0; powder_dec3 = 0;
      water_dec1 = 0;  water_dec2 = 0;
      cook_selection = 101;    
     break;
     
     case 103:  
      // minimum required levels are checked for cook
      if(water >= 1){water_level_flag = 1;}
      if(powder >= 1){powder_level_flag = 1;}      
      // variables to be used for porridge portion 3
      powder_dec1 = 0; powder_dec2 = 0; powder_dec3 = 0;
      water_dec1 = 0;  water_dec2 = 0;
      cook_selection = 101; 
     break;
     
     case 104:  
      // minimum required levels are checked for cook
      if(water >= 1){water_level_flag = 1;}
      if(powder >= 1){powder_level_flag = 1;}      
      // variables to be used for porridge portion 4
      powder_dec1 = 0; powder_dec2 = 0; powder_dec3 = 0;
      water_dec1 = 0;  water_dec2 = 0;
      cook_selection = 101; 
     break;
     
     case 105:  
      // minimum required levels are checked for cook
      if(water >= 1){water_level_flag = 1;}
      if(powder >= 1){powder_level_flag = 1;}      
      // variables to be used for porridge portion 5
      powder_dec1 = 0; powder_dec2 = 0; powder_dec3 = 0;
      water_dec1 = 0;  water_dec2 = 0;
      cook_selection = 101;   
     break;

   // SOFT FIRST_SELECTION

     case 201:  
      // minimum required levels are checked for cook
      if(water >= 1){water_level_flag = 1;}
      if(powder >= 1){powder_level_flag = 1;}      
      // variables to be used for soft portion 1
      powder_dec1 = 0; powder_dec2 = 0; powder_dec3 = 0;
      water_dec1 = 0;  water_dec2 = 0;
      cook_selection = 102; 
     break;
     
     case 202:  
      // minimum required levels are checked for cook
      if(water >= 1){water_level_flag = 1;}
      if(powder >= 1){powder_level_flag = 1;}      
      // variables to be used for soft portion 2
      powder_dec1 = 0; powder_dec2 = 0; powder_dec3 = 0;
      water_dec1 = 0;  water_dec2 = 0;
      cook_selection = 102;  
     break;
     
     case 203:  
      // minimum required levels are checked for cook
      if(water >= 1){water_level_flag = 1;}
      if(powder >= 1){powder_level_flag = 1;}      
      // variables to be used for soft portion 3
      powder_dec1 = 0; powder_dec2 = 0; powder_dec3 = 0;
      water_dec1 = 0;  water_dec2 = 0;
      cook_selection = 102;       
     break;
     
     case 204:  
      // minimum required levels are checked for cook
      if(water >= 1){water_level_flag = 1;}
      if(powder >= 1){powder_level_flag = 1;}      
      // variables to be used for soft portion 4
      powder_dec1 = 0; powder_dec2 = 0; powder_dec3 = 0;
      water_dec1 = 0;  water_dec2 = 0;
      cook_selection = 102; 
     break;
     
     case 205:  
      // minimum required levels are checked for cook
      if(water >= 1500){water_level_flag = 1;}
      if(powder >= 660){powder_level_flag = 1;}      
      // variables to be used for soft portion 5
      powder_dec1 = 120; powder_dec2 = 180; powder_dec3 = 360;
      water_dec1 = 500;  water_dec2 = 1000;
      cook_selection = 102;         
     break;

   // FIRM FIRST_SELECTION   

     case 301:  
      // minimum required levels are checked for cook
      if(water >= 1){water_level_flag = 1;}
      if(powder >= 1){powder_level_flag = 1;}      
      // variables to be used for firm portion 1
      powder_dec1 = 0; powder_dec2 = 0; powder_dec3 = 0;
      water_dec1 = 0;  water_dec2 = 0;
      cook_selection = 102;
     break;
     
     case 302:  
      // minimum required levels are checked for cook
      if(water >= 1){water_level_flag = 1;}
      if(powder >= 1){powder_level_flag = 1;}      
      // variables to be used for firm portion 2
      powder_dec1 = 0; powder_dec2 = 0; powder_dec3 = 0;
      water_dec1 = 0;  water_dec2 = 0;
      cook_selection = 102;  
     break;
     
     case 303:  
      // minimum required levels are checked for cook
      if(water >= 1){water_level_flag = 1;}
      if(powder >= 1){powder_level_flag = 1;}      
      // variables to be used for firm portion 3
      powder_dec1 = 0; powder_dec2 = 0; powder_dec3 = 0;
      water_dec1 = 0;  water_dec2 = 0;
      cook_selection = 102;    
     break;
     
     case 304:  
      // minimum required levels are checked for cook
      if(water >= 1){water_level_flag = 1;}
      if(powder >= 1){powder_level_flag = 1;}      
      // variables to be used for firm portion 4
      powder_dec1 = 0; powder_dec2 = 0; powder_dec3 = 0;
      water_dec1 = 0;  water_dec2 = 0;
      cook_selection = 102;
     break;
     
     case 305:  
      // minimum required levels are checked for cook
      if(water >= 1){water_level_flag = 1;}
      if(powder >= 1){powder_level_flag = 1;}      
      // variables to be used for firm portion 5
      powder_dec1 = 0; powder_dec2 = 0; powder_dec3 = 0;
      water_dec1 = 0;  water_dec2 = 0;
      cook_selection = 102;   
     break;

   // PORRIDGE RICE SELECTION    

     case 401:  
      // minimum required levels are checked for cook
      if(water >= 1){water_level_flag = 1;}
      if(powder >= 1){powder_level_flag = 1;}      
      // variables to be used for rice portion 1
      powder_dec1 = 0; powder_dec2 = 0; powder_dec3 = 0;
      water_dec1 = 0;  water_dec2 = 0;
      cook_selection = 201;
     break;
     
     case 402:  
      // minimum required levels are checked for cook
      if(water >= 1){water_level_flag = 1;}
      if(powder >= 1){powder_level_flag = 1;}      
      // variables to be used for firm portion 2
      powder_dec1 = 0; powder_dec2 = 0; powder_dec3 = 0;
      water_dec1 = 0;  water_dec2 = 0;
      cook_selection = 201;  
     break;
     
     case 403:  
      // minimum required levels are checked for cook
      if(water >= 1){water_level_flag = 1;}
      if(powder >= 1){powder_level_flag = 1;}      
      // variables to be used for firm portion 3
      powder_dec1 = 0; powder_dec2 = 0; powder_dec3 = 0;
      water_dec1 = 0;  water_dec2 = 0;
      cook_selection = 201;    
     break;
     
     case 404:  
      // minimum required levels are checked for cook
      if(water >= 1){water_level_flag = 1;}
      if(powder >= 1){powder_level_flag = 1;}      
      // variables to be used for firm portion 4
      powder_dec1 = 0; powder_dec2 = 0; powder_dec3 = 0;
      water_dec1 = 0;  water_dec2 = 0;
      cook_selection = 201;
     break;
     
     case 405:  
      // minimum required levels are checked for cook
      if(water >= 1){water_level_flag = 1;}
      if(powder >= 1){powder_level_flag = 1;}      
      // variables to be used for firm portion 5
      powder_dec1 = 0; powder_dec2 = 0; powder_dec3 = 0;
      water_dec1 = 0;  water_dec2 = 0;
      cook_selection = 201;   
     break;

   // SOFT AND FIRM RICE SELECTION        

     case 501:  
      // minimum required levels are checked for cook
      if(water >= 400){water_level_flag = 1;}
      if(powder >= 60){powder_level_flag = 1;}      
      // variables to be used for rice portion 1
      powder_dec1 = 60; powder_dec2 = 0; powder_dec3 = 0;
      water_dec1 = 400;  water_dec2 = 0;
      cook_selection = 202;
     break;
     
     case 502:  
      // minimum required levels are checked for cook
      if(water >= 1){water_level_flag = 1;}
      if(powder >= 1){powder_level_flag = 1;}      
      // variables to be used for firm portion 2
      powder_dec1 = 0; powder_dec2 = 0; powder_dec3 = 0;
      water_dec1 = 0;  water_dec2 = 0;
      cook_selection = 202;  
     break;
     
     case 503:  
      // minimum required levels are checked for cook
      if(water >= 1){water_level_flag = 1;}
      if(powder >= 1){powder_level_flag = 1;}      
      // variables to be used for firm portion 3
      powder_dec1 = 0; powder_dec2 = 0; powder_dec3 = 0;
      water_dec1 = 0;  water_dec2 = 0;
      cook_selection = 202;    
     break;
     
     case 504:  
      // minimum required levels are checked for cook
      if(water >= 1){water_level_flag = 1;}
      if(powder >= 1){powder_level_flag = 1;}      
      // variables to be used for firm portion 4
      powder_dec1 = 0; powder_dec2 = 0; powder_dec3 = 0;
      water_dec1 = 0;  water_dec2 = 0;
      cook_selection = 202;
     break;
     
     case 505:  
      // minimum required levels are checked for cook
      if(water >= 1){water_level_flag = 1;}
      if(powder >= 1){powder_level_flag = 1;}      
      // variables to be used for firm portion 5
      powder_dec1 = 0; powder_dec2 = 0; powder_dec3 = 0;
      water_dec1 = 0;  water_dec2 = 0;
      cook_selection = 202;   
     break;           
    
  break;
 }
}

int water_level(long value){
  
  if(value < 8830000){water = 0;} // 0 ml average value between water low and water high

  else if(value >= 8830001 && value <= 8872388){water = 50;}
  else if(value >= 8872389 && value <= 8876731){water = 100;}
  else if(value >= 8876732 && value <= 8919463){water = 150;}
  else if(value >= 8919464 && value <= 8941506){water = 200;}
  else if(value >= 8941507 && value <= 8985593){water = 250;}
  else if(value >= 8985594 && value <= 8998323){water = 300;}
  else if(value >= 8998324 && value <= 9037148){water = 350;}
  else if(value >= 9037149 && value <= 9050584){water = 400;}
  else if(value >= 9050585 && value <= 9091748){water = 450;}
  else if(value >= 9091749 && value <= 9107267){water = 500;}
  else if(value >= 9107268 && value <= 9148683){water = 550;}
  else if(value >= 9148684 && value <= 9166293){water = 600;}
  else if(value >= 9166294 && value <= 9193847){water = 650;}
  else if(value >= 9193848 && value <= 9220366){water = 700;}
  else if(value >= 9220367 && value <= 9252769){water = 750;}
  else if(value >= 9252770 && value <= 9283569){water = 800;}
  else if(value >= 9283570 && value <= 9303586){water = 850;}
  else if(value >= 9303587 && value <= 9346342){water = 900;}
  else if(value >= 9346343 && value <= 9363870){water = 950;}
  else if(value >= 9363871 && value <= 9364987){water = 1000;}
  else if(value >= 9364988 && value <= 9366102){water = 1050;}
  else if(value >= 9366103 && value <= 9418666){water = 1100;}
  else if(value >= 9418667 && value <= 9428327){water = 1150;}
  else if(value >= 9428328 && value <= 9463373){water = 1200;}
  else if(value >= 9463374 && value <= 9479489){water = 1250;}
  else if(value >= 9479490 && value <= 9521370){water = 1300;}
  else if(value >= 9521371 && value <= 9551178){water = 1350;}
  else if(value >= 9551179 && value <= 9560781){water = 1400;}
  else if(value >= 9560782 && value <= 9570381){water = 1450;}
  else if(value >= 9570382 && value <= 9634268){water = 1500;} // 1500 ml Max capacity of water holder, over flow may occur
    
  else if(value > 9634268){water = 1600;} 
  
  return water;
 }

int powder_level(long value2){
  
  if(value2 < 8520782){powder = 0;} // 0 ml average value2 between powder low and water high
  
  else if(value2 >= 8520783 && value2 <= 8521402){powder = 30;}
  else if(value2 >= 8521403 && value2 <= 8526664){powder = 60;}
  else if(value2 >= 8526665 && value2 <= 8527272){powder = 90;}
  else if(value2 >= 8527273 && value2 <= 8532933){powder = 120;}
  else if(value2 >= 8532934 && value2 <= 8533332){powder = 150;}
  else if(value2 >= 8533333 && value2 <= 8538719){powder = 180;}
  else if(value2 >= 8538720 && value2 <= 8544103){powder = 210;}
  else if(value2 >= 8544104 && value2 <= 8544393){powder = 240;}
  else if(value2 >= 8544394 && value2 <= 8550235){powder = 270;}
  else if(value2 >= 8550236 && value2 <= 8550568){powder = 300;}
  else if(value2 >= 8550569 && value2 <= 8555989){powder = 330;}
  else if(value2 >= 8555990 && value2 <= 8556161){powder = 360;}
  else if(value2 >= 8556162 && value2 <= 8561031){powder = 390;}
  else if(value2 >= 8561032 && value2 <= 8562933){powder = 420;}
  else if(value2 >= 8562934 && value2 <= 8568262){powder = 450;}
  else if(value2 >= 8568263 && value2 <= 8569285){powder = 480;}
  else if(value2 >= 8569286 && value2 <= 8574592){powder = 510;}
  else if(value2 >= 8574593 && value2 <= 8575976){powder = 540;}
  else if(value2 >= 8575977 && value2 <= 8581698){powder = 570;}
  else if(value2 >= 8581699 && value2 <= 8582393){powder = 600;}
  else if(value2 >= 8582394 && value2 <= 8588855){powder = 630;}
  else if(value2 >= 8588856 && value2 <= 8589392){powder = 660;}
  else if(value2 >= 8589393 && value2 <= 8595511){powder = 690;}
  else if(value2 >= 8595512 && value2 <= 8595827){powder = 720;}
  else if(value2 >= 8595828 && value2 <= 8601946){powder = 750;}
  else if(value2 >= 8601947 && value2 <= 8602312){powder = 780;}
  else if(value2 >= 8602313 && value2 <= 8608561){powder = 810;}
  else if(value2 >= 8608562 && value2 <= 8608914){powder = 840;}
  else if(value2 >= 8608915 && value2 <= 8612452){powder = 870;}
  else if(value2 >= 8612453 && value2 <= 8614715){powder = 900;}
  else if(value2 >= 8614716 && value2 <= 8614968){powder = 930;}
  else if(value2 >= 8614969 && value2 <= 8621238){powder = 960;}
  else if(value2 >= 8621239 && value2 <= 8622134){powder = 990;}
  else if(value2 >= 8622135 && value2 <= 8625943){powder = 1020;}
  else if(value2 >= 8625944 && value2 <= 8630232){powder = 1050;}
  else if(value2 >= 8630233 && value2 <= 8632033){powder = 1080;}
  else if(value2 >= 8632034 && value2 <= 8637815){powder = 1110;}
  else if(value2 >= 8637816 && value2 <= 8640187){powder = 1140;}
  else if(value2 >= 8640188 && value2 <= 8644145){powder = 1170;}
  else if(value2 >= 8644146 && value2 <= 8646509){powder = 1200;}
  else if(value2 >= 8646510 && value2 <= 8648196){powder = 1230;}
  else if(value2 >= 8648197 && value2 <= 8651908){powder = 1260;} // 1260 ml ideal max capacity of powder holder
  else if(value2 >= 8651909 && value2 <= 8655826){powder = 1290;}
  else if(value2 >= 8655827 && value2 <= 8660056){powder = 1320;}
  else if(value2 >= 8660057 && value2 <= 8660757){powder = 1350;} // 1350 ml Revised ideal max capacity of powder holder
  else if(value2 >= 8660758 && value2 <= 8661613){powder = 1380;}
  else if(value2 >= 8661614 && value2 <= 8665562){powder = 1410;}
  else if(value2 >= 8665563 && value2 <= 8666411){powder = 1440;}
  else if(value2 >= 8666412 && value2 <= 8666774){powder = 1470;}
  else if(value2 >= 8666775 && value2 <= 8672165){powder = 1500;}
  else if(value2 >= 8672166 && value2 <= 8675031){powder = 1530;}
  else if(value2 >= 8675032 && value2 <= 8677524){powder = 1560;}
  else if(value2 >= 8677525 && value2 <= 8682871){powder = 1590;}
  else if(value2 >= 8682872 && value2 <= 8689570){powder = 1620;}
  else if(value2 >= 8689571 && value2 <= 8693683){powder = 1650;}
  else if(value2 >= 8693684 && value2 <= 8696156){powder = 1680;}
  else if(value2 >= 8696157 && value2 <= 8699879){powder = 1710;}
  else if(value2 >= 8699880 && value2 <= 8701590){powder = 1740;}
  else if(value2 >= 8701591 && value2 <= 8704000){powder = 1770;}
  else if(value2 >= 8704001 && value2 <= 8708286){powder = 1800;}
  else if(value2 >= 8708287 && value2 <= 8710433){powder = 1830;}
  else if(value2 >= 8710434 && value2 <= 8715555){powder = 1860;}
  else if(value2 >= 8715556 && value2 <= 8717804){powder = 1890;}
  else if(value2 >= 8717805 && value2 <= 8718611){powder = 1920;}
  else if(value2 >= 8718612 && value2 <= 8722876){powder = 1950;}
  else if(value2 >= 8722877 && value2 <= 8725520){powder = 1980;}
  else if(value2 >= 8725521 && value2 <= 8727198){powder = 2010;}   
  else if(value2 >= 8727199 && value2 <= 8732738){powder = 2040;}// 2040 ml absolute Max capacity of powder holder, over flow may occur   
  
  else if(value2 > 8732738){powder = 2100;} 
  
  return powder;
 }

 void first_porridge()
{   
      
   // STEP 1 POUR COLD WATER AND POUR INITIAL POWDER
   if(First_Pour_Flag == 0){
    
    water_read();
    powder_read();
    
    if(cook_count == 0){
      current_powder = powder;               
      current_water = water;
      next_powder = current_powder - powder_dec1;
      next_water = current_water - water_dec1;
      cook_count ++;
      Low_Stirr_Flag = 1; // Start Low_stirring
      High_Stirr_Flag = 0; // Disable High_stirring
     }
     
     if(water > next_water){digitalWrite(waterDrain, LOW);}
     else{digitalWrite(waterDrain, HIGH);}

     if(powder > next_powder){
       servoMain.write(105);
       delay(300);  //                 
       servoMain.write(0);  // Turn Servo Left to 0 degrees
     }               
     
    if(water <= next_water && powder <= next_powder){
      First_Pour_Flag = 1;               
      current_powder = powder;               
      current_water = water;
      next_powder = current_powder - powder_dec2;
      next_water = current_water - water_dec2;
      Low_Heat_Flag = 1; // start Low_heating 
      High_Heat_Flag = 1;// and High_heating
    }
   }
   
  // STEP 2 START BOILING WATER
   if (Heated_flag == 0 && First_Pour_Flag == 1){    
    Water_Heater(); // Call Water Heating function
   }

        
  // STEP 3 POUR REQUIRED BOILING WATER
   if (Heated_flag == 1 && Second_Pour_Flag == 0){  
          
    water_read();

    if(water > next_water && water != 0){
      digitalWrite(waterDrain, LOW);
     }
    else
    {
      digitalWrite(waterDrain, HIGH);
      Second_Pour_Flag = 1;                  
     }
    }
    
  // STEP 4 POUR SECOND POWDER BATCH  
    if(Second_Pour_Flag == 1 && Simmer_Flag == 0){
    
     powder_read();
     
     if(powder > next_powder){
       servoMain.write(105);
       delay(300);  //                 
       servoMain.write(0);  // Turn Servo Left to 0 degrees
     }               
     
     if(powder <= next_powder){                
      Simmer_Flag = 1;
      minutes = 0; // Reset minutes for next STEP                          
      current_powder = powder;
      next_powder = current_powder - powder_dec3;
     }
    }          


  // STEP 5 LET IT SIMMER
  if(Simmer_Flag == 1 && Final_Cook_Flag == 0){ //AND SIMMER HAS BEEN COMPLETED
     
   // MAINTAIN LOW STIRRING FOR SPECIFIED
   if(minutes < 1){
    Low_Stirr_Flag = 1; // Maintain Low_stirring
    High_Stirr_Flag = 0; // Stop High_stirring
   }

   // MAINTAIN SIMMER FOR SPECIFIED
   if(minutes > 1 && minutes < 3){
    Low_Stirr_Flag = 0; // Stop Low_stirring
    High_Stirr_Flag = 0; // Stop High_stirring
   }
   
   if(minutes > 3){             
    Third_Pour_Flag = 1;
    minutes = 0; // Reset minutes for next STEP 
   }
  }   
}

void first_soft_firm()
{
    if(Simmer_Flag == 1 && Final_Cook_Flag == 0){ 
     if(Third_Pour_Flag == 1 && Final_Cook_Flag == 0){
  
       powder_read();                  
       
       High_Stirr_Flag = 1; // Start High_stirring        
       Low_Stirr_Flag = 0; // Stop Low_stirring               
       
       if(powder > next_powder){             
         if(seconds == 0 || seconds == 10 || seconds == 20 || seconds == 30 || seconds == 40 || seconds == 50){
          servoMain.write(105);
          delay(300);  //                 
          servoMain.write(0);  // Turn Servo Left to 0 degrees                 
         }
       }
       
       if(powder <= next_powder){                
      Final_Cook_Flag = 1;
      minutes = 0; // Reset minutes for next STEP                 
       }               
     }  
  }   
   // STEP 8 TURN STIRRING OFF
   // STEP 9 TURN HEATING PLATE "LOW"
   if(Final_Cook_Flag == 1){
         
     //MAINTAIN THE HIGH STIRR FOR SPECIFIED TIME
     if(minutes < 1){
       
    //   High_Stirr_Flag = 1; // Start High_stirring        
    //   Low_Stirr_Flag = 0; // Stop Low_stirring
     }
     
     //STOP THE HIGH STIRR, TURN LOW HEAT ON
     if(minutes > 0 && minutes < 2){
     
       Low_Stirr_Flag = 0; // Stop Low_stirring 
       High_Stirr_Flag = 0; // Stop High_stirring
    //   digitalWrite(Stirr_High, HIGH);
  
       Low_Heat_Flag = 1; // start Low_heating 
       High_Heat_Flag = 0;// turn off High_heating
     //  digitalWrite(Heat_High, HIGH);
     }
     
     // STEP 10 CLEAR ALL FLAGS, STATES AND VARIABLES
     //TURN LOW HEAT OFF SOUND OFF COOK COMPLETE
     if(minutes > 2){
      
       Low_Heat_Flag = 0; // turn off Low_heating 
       High_Heat_Flag = 0;// turn off High_heating
     //  digitalWrite(Heat_Low, HIGH);
       Completed_Cook_Flag = 1; // Final flag activated        
     }                         
   }  
}


void first_porridge_complete(){
  if(Third_Pour_Flag == 1){
    Completed_Cook_Flag = 1; // Final flag activated
   }
}
void Cook_complete(){
  if(Completed_Cook_Flag == 1){
 
   // OPEN UP ALL THE LOCKS 
   powder_hatch = 0; // unlock powder door
   water_hatch = 0; // unlock water door 
   main_hatch = 0; // unlock main hatch   

   if(main_hatch_state == 0){ 
     selection_lock = 0; first_selection_flag = 0; rice_selection_flag = 0; water_level_flag = 0; powder_level_flag = 0;               
     Heated_flag = 0; Start_Water_Temp_Flag = 0; powder_drain_flag = 0; start_Heating = 0; 
     First_Pour_Flag = 0; Second_Pour_Flag = 0; Third_Pour_Flag = 0; Simmer_Flag = 0; Final_Cook_Flag = 0;
     Low_Heat_Flag = 0; High_Heat_Flag = 0; Low_Stirr_Flag = 0; High_Stirr_Flag = 0;               
     selected = 0; cook_selection = 0; portion_selection = 0; texture_selection = 0; minutes = 0;
     current_water = 0; current_powder = 0; next_water = 0; next_powder = 0; cook_count = 0; 
     servoMain.write(0); manual_cook = 0; // Used for manaul mode
      
     manual_selection_flag = 0; rice_selection_flag = 0; first_selection_flag = 0; pasta_selection_flag = 0;
     
     Completed_Cook_Flag = 0; 
  
  //   lcd_toggle = 6; // SET TO 6 the state when the Main Hatch is opened
  } 
 }
}


