---
title: "Carbs Cooker"
date: 2017-01-23
categories: [embedded-projects]
permalink: /:categories/:title/
feature_img: "http://img.youtube.com/vi/e3Qg-X7DNN8/0.jpg"
excerpt: "embedded, auto-cooker, c++, arduino, microcontroller, rice, pasta, nsima, food"
purpose: "The project aimed at developing a proof of concept (POC) for an all-in-one automatic cooker for three popular forms of carbs: Rice, Pasta and Nsima (Southern-African dish)."
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

**Declaration Snippet (Nsima and Rice Only)**

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
String blank = "                ";

int powder_dec1, powder_dec2, powder_dec3;
int water_dec1, water_dec2;

AnalogKeypad AnKeypad(Button_analogPin);
```  
