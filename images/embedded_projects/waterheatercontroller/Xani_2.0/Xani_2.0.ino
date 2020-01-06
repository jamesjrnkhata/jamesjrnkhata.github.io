
/////////THOKO HOUSE AREA 6 AUTOMATION SKETCH ///////////////////////////////////////////
#include <DS3231.h>
#include <Wire.h>
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
/*
 * LCD RS pin to D2 digital [pin number 5]
 * LCD Enable pin to D3 digital [pin number 6]
 * LCD D4 pin to D4 digital [pin number 7]
 * LCD D5 pin to D5 digital [pin number 8]
 * LCD D6 pin to D6 digital [pin number 9]
 * LCD D7 pin to D7 digital [pin number 10]
 */

// Init the DS3231 using the hardware interface
DS3231  rtc(SDA, SCL); // pin (A4, A5) [pin number 23 SDA, pin number 24 SCL)]

// Init a Time-data structure
Time  t;

const int water_heater = 12; // [pin number 15]
const int kitchen_lights = 11; // [pin number 14]
const int pantry_lights = 10; // [pin number 13]
const int hallway_lights = 9; // [pin number 12]
// const int downstrshallway_lights = 8; // [pin number 11] will combine upstairs and downstairs
// const int downstairsbathroom_lights = 7; // [pin number 10] will be connected directly to Relay through transistor
 
const int pir_kitchen = 14; // [pin number 19] (A0)
const int pir_pantry = 15; // [pin number 20] (A1)
const int pir_upstairshallway = 16; // [pin number 21] (A2)
const int pir_downstairshallway = 17; // [pin number 22] (A3)
// const int pir_downstairsbathroom= 20; // [pin number 25] (A6)
const int time_button = 8; // [pin number 11]
const int cancel_button = 20; // [pin number 25] (A6)
const int start_button = 13; // [pin number 16]

byte dark_outside; // flag set to off by default   
byte light_outside; // flag set to off by default
byte automatic_heat_flag; // flag for set time heating 
byte manual_heat_flag; // flag for manual heating set by user 


// TIME AND DATE VARIABLES
String month;
byte day;
byte hours;
byte minutes;
byte seconds;
byte second_counter;

int heat_time;


void setup(){
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  // start serial port at baud rate 9600
  Serial.begin(9600);
  // Uncomment the next line if you are using an Arduino Leonardo
  //while (!Serial) {}

  // Initialize the rtc object
  rtc.begin();
  
  // SET TIME AND DATE
  // The following lines can be uncommented to set the date and time (re-comment after set)
  // rtc.setDOW(SUNDAY); // Set Day-of-Week to SUNDAY
  // rtc.setTime(21, 27, 0); // Set the time to 12:00:00 (24hr format)
  // rtc.setDate(7, 8, 2017); // Set the date to 1st January, 2014
  
  time_display(); // PROTOTYPING THE FUNCTION
  Manual_Waterheat(); // PROTOTYPE THE FUNCTION
  
  pinMode(water_heater, OUTPUT); // initialize digital pin 12 as an output.
  pinMode(kitchen_lights, OUTPUT); // initialize digital pin 14 as an output.
  pinMode(pantry_lights, OUTPUT); // initialize digital pin 13 as an output.
  pinMode(hallway_lights, OUTPUT); // initialize digital pin 12 as an output.
 // pinMode(downstrshallway_lights, OUTPUT); // initialize digital pin 11 as an output.
 // pinMode(downstairsbathroom_lights, OUTPUT); // initialize digital pin 10 as an output.
  
  
  pinMode(pir_kitchen, INPUT); // initialize digital pin 19 as an input.
  pinMode(pir_pantry, INPUT); // initialize digital pin 20 as an input.
  pinMode(pir_upstairshallway, INPUT); // initialize digital pin 21 as an input.
  pinMode(pir_downstairshallway, INPUT); // initialize digital pin 22 as an input.
//  pinMode(DownstairsBathroom_PIR, INPUT); // initialize digital pin 25 as an input.

  pinMode(time_button, INPUT); // initialize digital pin 11 as an input.
  pinMode(cancel_button, INPUT); // initialize digital pin 20 as an input.
  pinMode(start_button, INPUT); // initialize digital pin 20 as an input.
   
  
  digitalWrite(water_heater, LOW); // initialize water_heater to "off" (ACTIVE LOW SIGNAL REQUIRED TO SWITCH ON)
  digitalWrite(kitchen_lights, HIGH); // initialize kitchen_lights to "off" (ACTIVE LOW SIGNAL REQUIRED TO SWITCH ON)
  //digitalWrite(pantry_lights, HIGH); // initialize pantry_lights to "off" (ACTIVE LOW SIGNAL REQUIRED TO SWITCH ON)
  digitalWrite(hallway_lights, HIGH); // initialize Upstrs_hallway_lights to "off" (ACTIVE LOW SIGNAL REQUIRED TO SWITCH ON)
 // digitalWrite(downstrshallway_lights, HIGH); // initialize downstrshallway_lights to "off" (ACTIVE LOW SIGNAL REQUIRED TO SWITCH ON)
 // digitalWrite(downstairsbathroom_lights, HIGH); // initialize downstairsbathroom_lights to "off" (ACTIVE LOW SIGNAL REQUIRED TO SWITCH ON)

}

// the loop function runs over and over again forever
void loop() {
 //CODE STARTS FROM HERE
  // Get data from the DS3231
  t = rtc.getTime();
  month = rtc.getMonthStr();
  day = t.dow; // retrieved as a integer.
  hours = t.hour;
  minutes = t.min;
  seconds = t.sec;
  
  time_display();
  Manual_Waterheat();
  
 if(manual_heat_flag == 1){digitalWrite(water_heater, HIGH);}
 else if(automatic_heat_flag == 1){digitalWrite(water_heater, HIGH);}
 else
 {
   digitalWrite(water_heater, HIGH);
 }
 
  
  
  // FUNCTION USED TO READ COMMANDS FROM DS3231 SERIAL INPUT AND SET LIGHT AND DAY CYCLE
  if(hours == 17  && minutes >= 40){
    dark_outside = 1;
  //  echo_hours_on = 0;    
    light_outside = 0;
  } 
  if(hours >= 18  && hours < 22){
    dark_outside = 1;
  //  echo_hours_on = 0;    
    light_outside = 0;
  }
  
  if(hours >= 22  && hours <= 23){
    dark_outside = 1;
 //   echo_hours_on = 1;
    light_outside = 0;
  }
  // compensate for AM hours
  if(hours >= 0 && hours < 5){
    dark_outside = 1;
 //   echo_hours_on = 1;
    light_outside = 0;
  }  
  if(hours >= 5 && hours < 17){
    dark_outside = 0;
  //  echo_hours_on = 0;
    light_outside = 1;
  }
  
  // ACTIVATE DAILY TIMER
  if(hours == 18 && hours == 00){
    automatic_heat_flag == 1;
  }

  if(hours == 19 && hours == 00){
    automatic_heat_flag == 0;
  }
 
 //digitalWrite(Kitchen_Leds, LOW);
//  digitalWrite(Security_Lights, LOW);
   // FUNCTION USED TO CONTROL UTILITY LIGHTS BASED ON PIR INPUT
  // if(digitalRead(pir_Front) == HIGH && (dark_outside == 1 || echo_hours_on == 1)){digitalWrite(Front_Lights, LOW);}
 //  else{digitalWrite(Front_Lights, HIGH);}
 
  // if(digitalRead(pir_Back) == HIGH && (dark_outside == 1 || echo_hours_on == 1)){digitalWrite(Back_Lights, LOW);}
  // else{digitalWrite(Back_Lights, HIGH);}
   
  // if(echo_hours_on == 0 && dark_outside == 1){digitalWrite(Kitchen_Leds, LOW);}
  // else{digitalWrite(Kitchen_Leds, HIGH);}
   
  // if((digitalRead(pir_Back) == HIGH || digitalRead(pir_Front) == HIGH || digitalRead(Ext_pir_Group) == HIGH) && echo_hours_on == 1){yard_motion_flag = 1;}
//   else{yard_motion_flag = 0;}
  
 //  if(dark_outside == 0 && yard_motion_flag == 1){digitalWrite(Security_Lights, LOW);}
 //  else{digitalWrite(Security_Lights, HIGH);} 
 //  if(dark_outside == 1){digitalWrite(Security_Lights, LOW);} 
 //  if(light_outside == 1){digitalWrite(Security_Lights, HIGH);}
 

}

// FUNCTION USED TO DISPLAY TIME TO LCD DISPLAY
void time_display()
{
lcd.setCursor(0,0);
  if (hours < 10){
    lcd.setCursor(0,0);
    lcd.print('0');
    lcd.print(hours);
  }
  else
  {
    lcd.print(hours);  
  }

  lcd.print(":");  
    if (minutes < 10){
    lcd.setCursor(3,0);
    lcd.print('0');
    lcd.print(minutes);
  }
  else
  {
    lcd.print(minutes);  
  }

  lcd.print(":");
  if (seconds < 10){
    lcd.setCursor(6,0);
    lcd.print('0');
    lcd.print(seconds);
  }
  else
  {
    lcd.print(seconds);  
  }
}

void Manual_Waterheat(){

   if (digitalRead(time_button) == HIGH){
    lcd.print("                ");
    heat_time += 30;
    delay(1000);
   if(heat_time > 120){
     heat_time = 30;
     lcd.print("                ");
     delay(1000);
   }
   lcd.setCursor(0,1);
   lcd.print("HEAT ");
   lcd.print(heat_time);
   lcd.print(" mins");   
  }
  
  if(digitalRead(cancel_button) == HIGH){
   heat_time = 0;
   lcd.setCursor(0,1);
   lcd.print("                ");
  // lcd.print(heat_time);  
  }
  
  if(digitalRead(start_button) == HIGH && heat_time > 0){
    manual_heat_flag = 1;
    second_counter = seconds - 1;
    lcd.print("                ");
  }  
  if(manual_heat_flag == 1){

   lcd.setCursor(0,1);
   lcd.print("LEFT ");
   lcd.print(heat_time);
   lcd.print(" mins"); 
   if(seconds == second_counter){
    heat_time = heat_time - 1;
    delay(1000); 
   }
   if (heat_time == 0){
    digitalWrite(water_heater, LOW);
    manual_heat_flag = 0;
    lcd.setCursor(0,1);
    lcd.print("                ");
   }
  }
 
   
}
