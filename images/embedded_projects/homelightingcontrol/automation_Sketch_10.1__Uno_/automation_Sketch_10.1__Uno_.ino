/////////GUOJI HOUSE 37 AUTOMATION SCRIPT ///////////////////////////////////////////
#include <DS3231.h>

// Init the DS3231 using the hardware interface
DS3231  rtc(SDA, SCL);

// Init a Time-data structure
Time  t;

const int Security_Lights = 2; // pin 02
const int Kitchen_Leds = 3; // pin 03
const int Front_Lights = 4; // pin 04
const int Back_Lights = 5; // pin 05
const int Shower_Lights = 6; // pin 06
const int Hallway_Lights = 7; // pin 07

const int pir_ExtFront_Right = 8; // pin 08
const int pir_ExtBack_Right = 9; // pin 09
const int pir_ExtFront_Left = 10; // pin 10
const int pir_ExtBack_Left = 11; // pin 11

const int pir_Shower = 12; // pin 12
const int pir_Hallway = 13; // pin 13

const int pir_Front = 14; // pin 14 (A0)
const int pir_Back = 15; // pin 15 (A1)

//const int PhotoSensorO1 = 21; // Pin 16 (A2)
//const int PhotoSensorO2 = 22; // Pin 17 (A3)

byte full_on_flag;
byte echo_on_flag = 1;
byte yard_motion_flag;
byte Ext_pir_Group;

byte security_light_flag = 0;
byte kitchen_led_flag = 0;
byte front_light_flag = 0;
byte back_light_flag = 0;
byte dark_out_on;
byte echo_hours_on;
byte light_out_on;

String month;
byte day;
byte hours;
byte minutes;

void setup(){
  Serial.begin(115200);
  // Uncomment the next line if you are using an Arduino Leonardo
  //while (!Serial) {}

  // Initialize the rtc object
  rtc.begin();
  
  // The following lines can be uncommented to set the date and time
 // rtc.setDOW(SUNDAY);     // Set Day-of-Week to SUNDAY
//  rtc.setTime(21, 27, 0);     // Set the time to 12:00:00 (24hr format)
 // rtc.setDate(7, 8, 2017);   // Set the date to 1st January, 2014
  
  void On_Status(); //Prototype the function  
  pinMode(Security_Lights, OUTPUT); // initialize digital pin 02 as an output.
  pinMode(Kitchen_Leds, OUTPUT); // initialize digital pin 03 as an output.
  pinMode(Front_Lights, OUTPUT); // initialize digital pin 04 as an output.
  pinMode(Back_Lights, OUTPUT); // initialize digital pin 05 as an output.
  
  pinMode(pir_Front, INPUT); // initialize digital pin 06 as an input.
  pinMode(pir_Back, INPUT); // initialize digital pin 07 as an input.
  
  pinMode(pir_Hallway, INPUT); // initialize digital pin 08 as an input.
  pinMode(pir_Shower, INPUT); // initialize digital pin 09 as an input.
  
  pinMode(pir_ExtFront_Right, INPUT); // initialize digital pin 12 as an input.
  pinMode(pir_ExtBack_Right, INPUT); // initialize digital pin 13 as an input.
  pinMode(pir_ExtFront_Left, INPUT); // initialize digital pin 18 as an input.
  pinMode(pir_ExtBack_Left, INPUT); // initialize digital pin 19 as an input.
  
  pinMode(Hallway_Lights, OUTPUT); // initialize digital pin 05 as an output.
  pinMode(Shower_Lights, OUTPUT); // initialize digital pin 05 as an output.
  
  digitalWrite(Hallway_Lights, LOW); // initialize Hallway_Lights to "off"
  digitalWrite(Shower_Lights, HIGH); // initialize Shower_Lights to "off" (ACTIVE LOW SIGNAL REQUIRED TO SWITCH ON)
  digitalWrite(Security_Lights, HIGH); // initialize Security_Lights to "off" (ACTIVE LOW SIGNAL REQUIRED TO SWITCH ON)
  digitalWrite(Kitchen_Leds, HIGH); // initialize Kitchen_Leds to "off" (ACTIVE LOW SIGNAL REQUIRED TO SWITCH ON)
  digitalWrite(Front_Lights, HIGH); // initialize Front_Lights to "off" (ACTIVE LOW SIGNAL REQUIRED TO SWITCH ON)
  digitalWrite(Back_Lights, HIGH); // initialize Back_Lights to "off" (ACTIVE LOW SIGNAL REQUIRED TO SWITCH ON)

}

// the loop function runs over and over again forever
void loop() {
 //CODE STARTS FROM HERE
  // Get data from the DS3231
  t = rtc.getTime(); // get time data
  month = rtc.getMonthStr(); // get month data
  day = t.dow; // retrieved day as a integer.
  hours = t.hour; // get hour data from time
  minutes = t.min; // get minute data from time
  
  On_Status(); // initialize function

  // FUNCTION USED TO READ COMMANDS FROM DS3231 SERIAL INPUT AND SET LIGHT AND DAY CYCLE
  if(hours == 17  && minutes >= 40){
    dark_out_on = 1;
    echo_hours_on = 0;    
    light_out_on = 0;
  } 
  if(hours >= 18  && hours < 22){
    dark_out_on = 1;
    echo_hours_on = 0;    
    light_out_on = 0;
  }
  
  if(hours >= 22  && hours <= 23){
    dark_out_on = 0;
    echo_hours_on = 1;
    light_out_on = 0;
  }
  // compensate for AM hours
  if(hours >= 0 && hours < 5){
    dark_out_on = 0;
    echo_hours_on = 1;
    light_out_on = 0;
  }  
  if(hours >= 5 && hours < 17){
    dark_out_on = 0;
    echo_hours_on = 0;
    light_out_on = 1;
  }
  
  if (digitalRead(pir_ExtFront_Right) == HIGH || digitalRead(pir_ExtBack_Right) == HIGH || digitalRead(pir_ExtFront_Left) == HIGH || digitalRead(pir_ExtBack_Left) == HIGH){
    Ext_pir_Group = 1;
  }
  else
  {
    Ext_pir_Group = 0;
  }
 
 //digitalWrite(Kitchen_Leds, LOW);
//  digitalWrite(Security_Lights, LOW);
   // FUNCTION USED TO CONTROL UTILITY LIGHTS BASED ON PIR INPUT
   if(digitalRead(pir_Front) == HIGH && (dark_out_on == 1 || echo_hours_on == 1)){digitalWrite(Front_Lights, LOW);}
   else{digitalWrite(Front_Lights, HIGH);}
 
   if(digitalRead(pir_Back) == HIGH && (dark_out_on == 1 || echo_hours_on == 1)){digitalWrite(Back_Lights, LOW);}
   else{digitalWrite(Back_Lights, HIGH);}
   
   if(digitalRead(pir_Shower) == HIGH && (dark_out_on == 1 || echo_hours_on == 1)){digitalWrite(Shower_Lights, LOW);}
   else{digitalWrite(Shower_Lights, HIGH);}
   
   if(digitalRead(pir_Hallway) == HIGH && (dark_out_on == 1 || echo_hours_on == 1)){digitalWrite(Hallway_Lights, HIGH);}
   else{digitalWrite(Hallway_Lights, LOW);}
   
   if(echo_hours_on == 0 && dark_out_on == 1){digitalWrite(Kitchen_Leds, LOW);}
   else{digitalWrite(Kitchen_Leds, HIGH);}
   
   if((digitalRead(pir_Back) == HIGH || digitalRead(pir_Front) == HIGH || Ext_pir_Group == 1) && echo_hours_on == 1){yard_motion_flag = 1;}
   else{yard_motion_flag = 0;}
  
   if(dark_out_on == 0 && yard_motion_flag == 1){digitalWrite(Security_Lights, LOW);}
   else{digitalWrite(Security_Lights, HIGH);} 
   
   if(dark_out_on == 1){digitalWrite(Security_Lights, LOW);} 
   if(light_out_on == 1){digitalWrite(Security_Lights, HIGH);}
 

 //  if(dark_out_on == 1 || echo_hours_on == 1){digitalWrite(Outside_State, HIGH);}
  // else {digitalWrite(Outside_State, LOW);}
  
  // if(digitalRead(Hallway_Lights_Signal) == HIGH){digitalWrite(Hallway_Lights, LOW);}
 //  else{digitalWrite(Hallway_Lights, HIGH);} 
   
  
  // ECHO MODE - ENVIRONMENT FRIENDLY MODE
   
//    if (digitalRead(State_Button) == LOW){ 
//    full_on_flag = 0;
 //   echo_on_flag = 1;
//   }
  
 // FULL MODE - RUNS HOUSE AT MAXIMUM 
//  if (digitalRead(State_Button) == HIGH){
//    full_on_flag = 1;
//    echo_on_flag = 0;   
 //  }
}

 // function to indicate the system is active
  void On_Status()
 {
//    digitalWrite(On_Led, HIGH);   // turn the LED on (HIGH is the voltage level)
  //  delay(100);              // wait for a second
 //   digitalWrite(On_Led, LOW);    // turn the LED off by making the voltage LOW
 //   delay(100);              // wait for a second
 }
    

 
