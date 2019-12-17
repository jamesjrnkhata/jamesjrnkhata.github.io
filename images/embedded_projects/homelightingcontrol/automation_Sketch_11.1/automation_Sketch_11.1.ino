//////////////////GUOJI HOUSE 37 AUTOMATION SKETCH ///////////////////////////////////////////
#include <DS3231.h>

// Init the DS3231 using the hardware interface
DS3231  rtc(SDA, SCL);

// Init a Time-data structure
Time  t;

// OUTPUT PIN DECLARATION
const int security_lights = 2; // security lights [on pin 02]
const int kitchen_lights = 3; // kitchen lights [on pin 03]
const int front_lights = 4; // front porch lights [on pin 04]
const int back_lights = 5; // back porch lights [on pin 05]
const int shower_lights = 6; // shower lights [on pin 06]
const int hallway_lights = 7; // hallway lights [on pin 07]

// INPUT PIN DECLARATION
const int pir_extfront_right = 8; // external front right PIR [on pin 08]
const int pir_extback_right = 9; // external back right PIR [on pin 09]
const int pir_extfront_left = 10; // external front left PIR [on pin 10]
const int pir_extback_left = 11; // external back left PIR [on pin 11]

const int pir_shower = 12; // internal shower PIR [on pin 12]
const int pir_hallway = 13; // internal hallway PIR[on pin 13]

const int pir_front = 14; // external front porch PIR [on pin 14 (A0)]
const int pir_back = 15; // external back porch PIR [on pin 15 (A1)]

const int pir_kitchen = 21; // internal kitchen PIR [on Pin 16 (A2)]

//const int photoresistors02 = 22; // external photoresistors 2 [on Pin 17 (A3)]

// FLAG VARIABLES
byte full_on_flag; // flag for full mode (keeps security lights on all night, turns off during the day)
byte echo_on_flag = 1; // flag for echo mode set to default (security lights on at sunset, go off at 10pm and turns on from PIR motion until sunrise)
byte yard_motion_flag; // flag to indicate any external PIR motion detected
byte ext_pir_group; // flag for collection of external PIR sensor detection (exclduing pir_front and pir_back)

byte security_light_flag = 0; // flag set to off by default
byte kitchen_led_flag = 0; // flag set to off by default
byte front_light_flag = 0; // flag set to off by default
byte back_light_flag = 0; // flag set to off by default
byte dark_outside; // flag set to off by default
byte echo_hours_on; // flag set to off by default
byte light_outside; // flag set to off by default

// TIME AND DATE VARIABLES
String month; 
byte day;
byte hours;
byte minutes;

// SETUP FUNCTION
void setup(){

  // start serial port at baud rate 115200
  Serial.begin(115200);
  // Uncomment the next line if you are using an Arduino Leonardo
  //while (!Serial) {}

  // Initialize the rtc object
  rtc.begin();
  
  // SET TIME AND DATE
  // The following lines can be uncommented to set the date and time (re-comment after set)
  // rtc.setDOW(SUNDAY); // Set Day-of-Week to SUNDAY
  // rtc.setTime(21, 27, 0); // Set the time to 12:00:00 (24hr format)
  // rtc.setDate(7, 8, 2017); // Set the date to 1st January, 2014
  
  void On_Status(); //Prototype the On_Status function  
  pinMode(security_lights, OUTPUT); // initialize digital pin 02 as an output.
  pinMode(kitchen_lights, OUTPUT); // initialize digital pin 03 as an output.
  pinMode(front_lights, OUTPUT); // initialize digital pin 04 as an output.
  pinMode(back_lights, OUTPUT); // initialize digital pin 05 as an output.
  
  pinMode(pir_front, INPUT); // initialize digital pin 06 as an input.
  pinMode(pir_back, INPUT); // initialize digital pin 07 as an input.
  
  pinMode(pir_hallway, INPUT); // initialize digital pin 08 as an input.
  pinMode(pir_shower, INPUT); // initialize digital pin 09 as an input.
  
  pinMode(pir_extfront_right, INPUT); // initialize digital pin 12 as an input.
  pinMode(pir_extback_right, INPUT); // initialize digital pin 13 as an input.
  pinMode(pir_extfront_left, INPUT); // initialize digital pin 18 as an input.
  pinMode(pir_extback_left, INPUT); // initialize digital pin 19 as an input.
  
  pinMode(pir_kitchen, INPUT); // initialize digital pin 21 as an input.
  
  pinMode(hallway_lights, OUTPUT); // initialize digital pin 07 as an output.
  pinMode(shower_lights, OUTPUT); // initialize digital pin 06 as an output.
  
  digitalWrite(hallway_lights, HIGH); // initialize hallway_lights to "off" (ACTIVE LOW SIGNAL REQUIRED TO SWITCH ON)
  digitalWrite(shower_lights, HIGH); // initialize shower_lights to "off" (ACTIVE LOW SIGNAL REQUIRED TO SWITCH ON)
  digitalWrite(security_lights, HIGH); // initialize security_lights to "off" (ACTIVE LOW SIGNAL REQUIRED TO SWITCH ON)
  digitalWrite(kitchen_lights, HIGH); // initialize kitchen_lights to "off" (ACTIVE LOW SIGNAL REQUIRED TO SWITCH ON)
  digitalWrite(front_lights, HIGH); // initialize front_lights to "off" (ACTIVE LOW SIGNAL REQUIRED TO SWITCH ON)
  digitalWrite(back_lights, HIGH); // initialize back_lights to "off" (ACTIVE LOW SIGNAL REQUIRED TO SWITCH ON)

}

// LOOP FUNCTION
void loop() {
 
  // Get data from the DS3231
  t = rtc.getTime(); // get time data
  month = rtc.getMonthStr(); // get month data
  day = t.dow; // retrieved day as a integer.
  hours = t.hour; // get hour data from time
  minutes = t.min; // get minute data from time
  
  On_Status(); // initialize function

  // CONDITIONS USED TO READ COMMANDS FROM DS3231 SERIAL INPUT AND SET LIGHT AND DAY CYCLE DEPENDING ON TIME
  
  // condtion to start dark_outside flag
  if(hours == 17  && minutes >= 40){
    dark_outside = 1; // set flag to on
    echo_hours_on = 0; // set flag to off    
    light_outside = 0; // set flag to off     
  } 
  // condtion used incase of power outage to re-set the dark_outside flag 
  if(hours >= 18  && hours < 22){
    dark_outside = 1; // set flag to on
    echo_hours_on = 0; // set flag to off        
    light_outside = 0; // set flag to off    
  }
  // condition used to start echo_hours flag
  if(hours >= 22  && hours <= 23){
    dark_outside = 0; // set flag to off    
    echo_hours_on = 1; // set flag to on
    light_outside = 0; // set flag to off 
  }
  // condition to maintain echo_hours for AM hours
  if(hours >= 0 && hours < 5){
    dark_outside = 0; // set flag to off
    echo_hours_on = 1; // set flag to on
    light_outside = 0; // set flag to off
  }
  // condition to start light_outside flag  
  if(hours >= 5 && hours < 17){
    dark_outside = 0; // set flag to off
    echo_hours_on = 0; // set flag to off
    light_outside = 1;  // set flag to on
  }

   // CONDITIONS USED TO CONTROL INTERAL AND EXTERNAL LIGHTS BASED ON TIME AND PIR INPUT
   
   if(digitalRead(pir_front) == HIGH && (dark_outside == 1 || echo_hours_on == 1)){digitalWrite(front_lights, LOW); // turn on}
   else{digitalWrite(front_lights, HIGH); turn off}
 
   if(digitalRead(pir_back) == HIGH && (dark_outside == 1 || echo_hours_on == 1)){digitalWrite(back_lights, LOW); // turn on}
   else{digitalWrite(back_lights, HIGH); turn off}
   
   if(digitalRead(pir_shower) == HIGH && (dark_outside == 1 || echo_hours_on == 1)){digitalWrite(shower_lights, LOW); // turn on}
   else{digitalWrite(shower_lights, HIGH); turn off}
   
   if(digitalRead(pir_hallway) == HIGH && (dark_outside == 1 || echo_hours_on == 1)){digitalWrite(hallway_lights, LOW); // turn on}
   else{digitalWrite(hallway_lights, HIGH); turn off}

   if(digitalRead(pir_kitchen) == HIGH && (dark_outside == 1 || echo_hours_on == 1)){digitalWrite(kitchen_lights, LOW); // turn on}
   else{digitalWrite(kitchen_lights, HIGH); turn off}

   // condition to set ext_pir_group flag (set by any external PIRs excluding pir_front and pir_back)
   if (digitalRead(pir_extfront_right) == HIGH || digitalRead(pir_extback_right) == HIGH || digitalRead(pir_extfront_left) == HIGH || digitalRead(pir_extback_left) == HIGH){
     ext_pir_group = 1;  // set flag to on
   }
   else{ext_pir_group = 0;  // set flag to off}

   // condition to set yard_motion_flag by all external PIRs
   if((digitalRead(pir_back) == HIGH || digitalRead(pir_front) == HIGH || ext_pir_group == 1) && echo_hours_on == 1){
    yard_motion_flag = 1; // set flag to on}
   }
   else{yard_motion_flag = 0; // set flag to off}
  
   if(dark_outside == 0 && yard_motion_flag == 1){digitalWrite(security_lights, LOW); // turn on}
   else{digitalWrite(security_lights, HIGH); turn off} 
   
   if(dark_outside == 1){digitalWrite(security_lights, LOW); // turn on} 
   if(light_outside == 1){digitalWrite(security_lights, HIGH); turn off}
}

 // OTHER FUNCTIONS 
    
 // Function used to toggle between ECHO MODE and FULL MODE
 void Mode_Switch
 {
   // ECHO MODE - TIME AND PIR CONTROLLED    
   //if (digitalRead(State_Button) == LOW){ 
      // full_on_flag = 0;
      // echo_on_flag = 1;
   // }
    
   // FULL MODE - SECURITY LIGHTS THROUGHOUT THE EVENING
   //else if (digitalRead(State_Button) == HIGH){
      // full_on_flag = 1;
      // echo_on_flag = 0;   
   // }   
 }
 

 // Function to indicate the system is active
  void On_Status()
 {
  // digitalWrite(On_Led, HIGH); // turn the LED on (HIGH is the voltage level)
  // delay(100); // wait for a second
  // digitalWrite(On_Led, LOW); // turn the LED off by making the voltage LOW
  // delay(100); // wait for a second
 }
    

 
