////////////////////////// WATER HEATER CONTROLLER ///////////////////////////////////////// 
//////////////////// THOKO HOUSE AREA 6 AUTOMATION SKETCH //////////////////////////////////
////////////////////////////// CASA-JUEGOS INC /////////////////////////////////////////////
/////////////////////////// written by: JAMES JR NKHATA ////////////////////////////////////

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

const int time_button = 8; // [pin number 11]
const int cancel_button = 20; // [pin number 25] (A6)
const int start_button = 13; // [pin number 16]

byte automatic_heat_flag; // flag for pre-set time heating 
byte manual_heat_flag; // flag for manual heating set by user 

// TIME AND DATE VARIABLES
String month;
byte day;
byte hours;
byte minutes;
byte seconds;
byte second_counter; // used for displaying seconds count on the LCD Display

int heat_time; // variable to hold the 30 minute heating durations 

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
  
  Time_Display(); // prototyping the Time_Display function
  Manual_Waterheat(); // prototyping the Manual_Waterheat function
  
  pinMode(water_heater, OUTPUT); // initialize digital pin 12 as an Output.

  pinMode(time_button, INPUT); // initialize digital pin 08 as an Input.
  pinMode(cancel_button, INPUT); // initialize digital pin 20 as an Input.
  pinMode(start_button, INPUT); // initialize digital pin 13 as an Input.
   
  digitalWrite(water_heater, LOW); // initialize water_heater to "off" (ACTIVE LOW SIGNAL REQUIRED TO SWITCH ON)
}

void loop() {
  // Get data from the DS3231
  t = rtc.getTime();
  month = rtc.getMonthStr();
  day = t.dow; // retrieved as an integer.
  hours = t.hour;
  minutes = t.min;
  seconds = t.sec;
  
  Time_Display(); // execute Time_Display function 
  Manual_Waterheat(); //execute Manual_Waterheat function
  
 // condition to check if manual_heat_flag is active or automatic_heat_flag is active else switch the water_heater off
 if(manual_heat_flag == 1){
  digitalWrite(water_heater, HIGH);
  }
 else if(automatic_heat_flag == 1){
  digitalWrite(water_heater, HIGH);
  }
 else
 {
   digitalWrite(water_heater, HIGH);
 } 
   
  // CONDITIONS USED TO SET DAILY AUTOMATIC HEATING TIMES 
  // switch on at 18:00
  if(hours == 18 && minutes >= 0){
    automatic_heat_flag == 1;
  }
  // switch off at 19:00
  if(hours == 19 && minutes >= 0){
    automatic_heat_flag == 0;
  }
}

// FUNCTION USED TO DISPLAY TIME TO LCD DISPLAY
// Display adjustments made to propely display on the LCD Display
void Time_Display()
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

//FUNCTION USED TO MANUAL SWITCH THE WATER HEATER ON FOR AN INCREMENT OF 30 MINUTES (MAXIMUM 120 MINUTES)
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
