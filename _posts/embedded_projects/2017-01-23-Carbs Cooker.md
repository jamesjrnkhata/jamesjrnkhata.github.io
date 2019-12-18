---
title: "Carbs Cooker"
date: 2017-01-23
categories: [embedded-projects]
permalink: /:categories/:title/
feature_img: "http://img.youtube.com/vi/e3Qg-X7DNN8/0.jpg"
excerpt: "auto-cooker, food, embedded, c++, arduino, rice, pasta, nsima, food"
purpose: "The project aimed at developing a proof of concept (POC) for an all-in-one automatic cooker for three popular forms of carbs: Rice, Pasta and Nsima (Southern-African dish)."
toc: true
classes: wide 
---
The project aimed at developing a proof of concept (POC) for an all-in-one automatic cooker for three popular forms of carbs: Rice, Pasta and Nsima (Southern-African dish).

<h2 class="text-underline">Motivation</h2>

The incentive behind designing the Carb Cooker was to:
1.	Simplify the process of determining the measurements required (Uncooked rice, pasta, maize flour and water) to cook for a specific amount of people.
2.	Automate the process of cooking each carb food type from adding the ingredients, heating and the timings required.
3.	Automate the process of stirring the Nsima (which requires a lot of energy and skill to prevent the maize flour from forming lumps).

<h2 class="text-underline">Concept</h2>

<a class="custom_link" target="" href="https://en.wikipedia.org/wiki/Ugali">Nsima </a>is a type of maize flour porridge made in Africa. It is also known as **Ugali pap**, **Ngima**, **Obusuma**, **Kimnyet**, **Mieliepap**, **Nshima**, **Phutu**, **Sadza**, **Kwon**, and other names in different African countries. Process of cooking it may differ with individuals form different countries. However, it is mainly cooked in boiling water or milk until it reaches a stiff or firm dough-like consistency.

 [![Nsima Cooking](http://img.youtube.com/vi/e3Qg-X7DNN8/0.jpg)](https://www.youtube.com/watch?v=e3Qg-X7DNN8 "Nsima Cooking")

 Rice, Pasta and Nsima all require adding different amount of water and heating at various temperatures each with its own timings. Changes on the amount of water or timing can alter the resulting cooked product, either making it too soft, soggy or slightly hard. Nsima requires cold water initially and then hot water later through the cooking stages. Pasta requires hot water while rice can be cooked with either cold or hot depending on how well cooked it is desired. The designing of the auto-cooker had to consider these requirements.

 The solution required a modular design and control over each stage of the cooking process. This was achieved by breaking the cooker down into units responsible for feeding water, feeding raw rice / pasta, feeding maize flour, heating, user interface and stirring the contents of the non-stick cooking pot. The decision was made to use a microcontroller to integrate the units and control the cooking processes. The design used a combination of AC and DC (with a step-down transformer) powered components.

<h2 class="text-underline">Requirements</h2>

The components researched and used were chosen to minimize the cost of the overall design.
*	Cooker Housing (to hold all the components together)
*	Non-Stick Cooking Pot
*	Microcontroller (MCU) that fulfilled the requirements (General I/O pins, Flash Memory etc.).
*	LCD Display, Button Matrix PCB, Bluetooth Module and Buzzer
*	Load Cells, High Torque Servo Motors, Relays, Temperature Probes (Sensors)
*	Temperature Sensor for Electric Rice Cooker
*	Electric Hot Plate Cooking Coil
*	Hot Water Pump
*	Water Holder, Heater and Feeder unit
*	Rice, Pasta, Maize flour Feeder units
*	High torque DC Motor for stirring
*	Stirring Spatula

<h2 class="text-underline">Implementation</h2>

### Hardware
**User Interface** – This was made up of an *LCD Display*, *Bluetooth Module* and the *Button Matrix PCB* (with button labels). The *Button Matrix PCB* and a Mobile Device App that sent serial commands to the *Microcontroller* through the *Bluetooth Module* were used to make selections on the Cooker. The *LCD Display* was used to give the user prompts, get information on the minimum requirements needed to cook a particular carb (with the amount of portions) and progress of the cooking process. The *Buzzer* was used to notify the user when a cooking process was completed.

**Water Heater / Feeder Unit** – This was achieved with a *Boiling Kettle* modified to receive on and off signals from the *Controller unit* through a *Relay*. This was also fitted with a *Hot Water Pump* to feed the water to the *Non-Stick Cooking Pot*.

**Maize Flour Feeder Unit** – This was made up of 3D printed *Screw Feeding Auger* combined with *Load Sensors* and a *High Torque Servo Motor* connected to the *Controller Unit*. This unit fed into the *Non-Stick Cooking Pot*. The *Load Sensors* were tested and calibrated to give the amount of maize flour available for cooking.

**Rice / Pasta Feeder Unit** – This was another 3D printed feeder with a different design from the *Maize Flour Feeder Unit*. This was also fitted with the *Load Sensors* and a *High Torque Servo Motor* for precision control when feeding into the *Non-Stick Cooking Pot*. Similar calibration to the *Maize Flour Unit* were made.  

**Stirring Unit** – This was made up of a *High Torque DC Motor*, *Stirring Spatula* (designed for the project) and a 3D printed *Motor Bracket*. The *Stirring Spatula* was designed to fit the *High Torque DC Motor’s* shaft that ran through a small opening in the lid of the *Non-Stick Cooking Pot*. The *Stirring Spatula* design also allowed decoupling from the motor shaft for easy cleaning. The *High Torque DC Motor* was connected to the *Controller Unit* through a *Relay*.

**Pot Heater Unit** – This unit consisted of the *Temperature Probe (Sensor)*, *Temperature Sensor for Electric Rice Cooker* and the *Electric Hot Plate Cooking Coil*. Both *Temperature Sensors* were connected to the *Controller Unit* while the *Electric Hot Plate Cooking Coil* was connected through a *Relay*.

**Controller Unit** – This was made up of the *Microcontroller (MCU)*. It received and sent control signals to all the *Units*, *Sensors* and *Relays* of the Cooker.

**Cooker Housing** – A prototype case was built for the Cooker using local hardware (B&Q) material to hold its units and components together.   

### Software
The portions were estimated for each carb type by cooking the dishes conventionally (pot and stove), while recording how much ingredients were used in weight. This data was then used as a standard in *Load Sensor* readings (weight) to determine how much ingredients were required for extra portions of each carb type. All the steps carried out in cooking rice; Pasta and Nsima were then implemented into Arduino Sketch.


**Declaration Code Snippet (Nsima and Rice Only)**
```cpp
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
byte selection_lock, nsima_selection_flag, rice_selection_flag, water_level_flag, powder_level_flag = 0;
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
//Button 1 = nsima_button
//Button 2 = rice_button
//Button 3 = button_portion

//Button 4 = button_porridge,button_soft and button_firm

//Button 5 = drain_button
//Button 6 = start_Cook_button

// LEDS AND INDICATORS
//const int HeatedInd = 3;
//const int nsima_Led = A5;
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
String blank = "                "; // white space used to clear the LCD Display

int powder_dec1, powder_dec2, powder_dec3;
int water_dec1, water_dec2;

AnalogKeypad AnKeypad(Button_analogPin);
```


**Cook Selection Code Snippet**
```cpp
// CONDITION TO CHECK IF THE DEVICE IS OPEN, IF IT IS ONLY SECONDARY FUNCTIONS CAN BE CARRIED OUT
  if(main_hatch_state == 1 && water_hatch_state == 1 && powder_hatch_state == 1){


    // START NSIMA SELECTION
    if(Key_press == "NSIMA" && selection_lock == 0 || BT_press == 'N' && selection_lock == 0){
     Food_Choice = "NSIMA";     
     lcd_toggle = 0;
     water_level_flag = 0; // reset water_level_flag to accommodate for last minute changes
     powder_level_flag = 0; // reset powder_level_flag to accommodate for last minute changes
     nsima_selection_flag = 1;
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
     nsima_selection_flag = 0;      
     pasta_selection_flag = 0;
     manual_selection_flag = 0;
     BT_press = ' ';
   }

  // NSIMA SELECTION BLOCK
   if(nsima_selection_flag == 1){  

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
```


**Nsima Cook State-Transition Code Snippet**

```cpp

void nsima_soft_firm()
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


void nsima_porridge_complete(){
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
     selection_lock = 0; nsima_selection_flag = 0; rice_selection_flag = 0; water_level_flag = 0; powder_level_flag = 0;               
     Heated_flag = 0; Start_Water_Temp_Flag = 0; powder_drain_flag = 0; start_Heating = 0;
     First_Pour_Flag = 0; Second_Pour_Flag = 0; Third_Pour_Flag = 0; Simmer_Flag = 0; Final_Cook_Flag = 0;
     Low_Heat_Flag = 0; High_Heat_Flag = 0; Low_Stirr_Flag = 0; High_Stirr_Flag = 0;               
     selected = 0; cook_selection = 0; portion_selection = 0; texture_selection = 0; minutes = 0;
     current_water = 0; current_powder = 0; next_water = 0; next_powder = 0; cook_count = 0;
     servoMain.write(0); manual_cook = 0; // Used for manaul mode

     manual_selection_flag = 0; rice_selection_flag = 0; nsima_selection_flag = 0; pasta_selection_flag = 0;

     Completed_Cook_Flag = 0;

  //   lcd_toggle = 6; // SET TO 6 the state when the Main Hatch is opened
  }
 }
}

```
