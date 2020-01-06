
/////////THOKO HOUSE AREA 6 AUTOMATION SCRIPT ///////////////////////////////////////////
#include <DS3231.h>
#include <Wire.h>
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

// Init the DS3231 using the hardware interface
DS3231  rtc(SDA, SCL); // pin (A4, A5) (SDA, SCL)

// Init a Time-data structure
Time  t;

const int Water_Heater = 12; // pin 15
const int Kitchen_Lights = 11; // pin 14
const int Pantry_Lights = 10; // pin 13
const int Hallway_Lights = 9; // pin 12
// const int DownstrsHallway_Lights = 8; // pin 11 will combine upstairs and downstairs
// const int DownstairsBathroom_Lights = 7; // pin 10 will be connected directly to Relay through transistor

/*
 * LCD RS pin to D2 digital pin 5
 * LCD Enable pin to D3 digital pin 6
 * LCD D4 pin to D4 digital pin 7
 * LCD D5 pin to D5 digital pin 8
 * LCD D6 pin to D6 digital pin 9
 * LCD D7 pin to D7 digital pin 10
 */
 
const int Kitchen_PIR = 14; // pin 19 (A0)
const int Pantry_PIR = 15; // pin 20 (A1)
const int UpstrsHallway_PIR = 16; // pin 21 (A2)
const int DownstrsHallway_PIR = 17; // pin 22 (A3)
// const int DownstairsBathroom_PIR = 20; // pin 25 (A6)
const int time_Button = 8; // pin 11
const int reset_Button = 20; // pin 25 (A6)
const int start_Button = 13; // pin 25 (A6)

byte dark_out_on;   
byte light_out_on;
byte automatic_heat_flag;
byte manual_heat_flag;
byte second_counter;

String month;
byte day;
byte hours;
byte minutes;
byte seconds;

int heat_time;


void setup(){
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  Serial.begin(9600);
  // Uncomment the next line if you are using an Arduino Leonardo
  //while (!Serial) {}

  // Initialize the rtc object
  rtc.begin();
  
  // The following lines can be uncommented to set the date and time
//  rtc.setDOW(SUNDAY);     // Set Day-of-Week to SUNDAY
 // rtc.setTime(16, 47, 0);     // Set the time to 12:00:00 (24hr format)
 // rtc.setDate(3, 9, 2017);   // Set the date to 1st January, 2014
  
  time_display(); // PROTOTYPING THE FUNCTION
  Manual_Waterheat(); // PROTOTYPE THE FUNCTION
  
  pinMode(Water_Heater, OUTPUT); // initialize digital pin 12 as an output.
  pinMode(Kitchen_Lights, OUTPUT); // initialize digital pin 14 as an output.
  pinMode(Pantry_Lights, OUTPUT); // initialize digital pin 13 as an output.
  pinMode(Hallway_Lights, OUTPUT); // initialize digital pin 12 as an output.
 // pinMode(DownstrsHallway_Lights, OUTPUT); // initialize digital pin 11 as an output.
 // pinMode(DownstairsBathroom_Lights, OUTPUT); // initialize digital pin 10 as an output.
  
  
  pinMode(Kitchen_PIR, INPUT); // initialize digital pin 19 as an input.
  pinMode(Pantry_PIR, INPUT); // initialize digital pin 20 as an input.
  pinMode(UpstrsHallway_PIR, INPUT); // initialize digital pin 21 as an input.
  pinMode(DownstrsHallway_PIR, INPUT); // initialize digital pin 22 as an input.
//  pinMode(DownstairsBathroom_PIR, INPUT); // initialize digital pin 25 as an input.

  pinMode(time_Button, INPUT); // initialize digital pin 11 as an input.
  pinMode(reset_Button, INPUT); // initialize digital pin 20 as an input.
  pinMode(start_Button, INPUT); // initialize digital pin 20 as an input.
   
  
  digitalWrite(Water_Heater, LOW); // initialize Water_Heater to "off" (ACTIVE LOW SIGNAL REQUIRED TO SWITCH ON)
  digitalWrite(Kitchen_Lights, HIGH); // initialize Kitchen_Lights to "off" (ACTIVE LOW SIGNAL REQUIRED TO SWITCH ON)
  //digitalWrite(Pantry_Lights, HIGH); // initialize Pantry_Lights to "off" (ACTIVE LOW SIGNAL REQUIRED TO SWITCH ON)
  digitalWrite(Hallway_Lights, HIGH); // initialize Upstrs_Hallway_Lights to "off" (ACTIVE LOW SIGNAL REQUIRED TO SWITCH ON)
 // digitalWrite(DownstrsHallway_Lights, HIGH); // initialize DownstrsHallway_Lights to "off" (ACTIVE LOW SIGNAL REQUIRED TO SWITCH ON)
 // digitalWrite(DownstairsBathroom_Lights, HIGH); // initialize DownstairsBathroom_Lights to "off" (ACTIVE LOW SIGNAL REQUIRED TO SWITCH ON)

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
  
 if(manual_heat_flag == 1){digitalWrite(Water_Heater, HIGH);}
 else if(automatic_heat_flag == 1){digitalWrite(Water_Heater, HIGH);}
 else
 {
   digitalWrite(Water_Heater, HIGH);
 }
 
  
  
  // FUNCTION USED TO READ COMMANDS FROM DS3231 SERIAL INPUT AND SET LIGHT AND DAY CYCLE
  if(hours == 17  && minutes >= 40){
    dark_out_on = 1;
  //  echo_hours_on = 0;    
    light_out_on = 0;
  } 
  if(hours >= 18  && hours < 22){
    dark_out_on = 1;
  //  echo_hours_on = 0;    
    light_out_on = 0;
  }
  
  if(hours >= 22  && hours <= 23){
    dark_out_on = 1;
 //   echo_hours_on = 1;
    light_out_on = 0;
  }
  // compensate for AM hours
  if(hours >= 0 && hours < 5){
    dark_out_on = 1;
 //   echo_hours_on = 1;
    light_out_on = 0;
  }  
  if(hours >= 5 && hours < 17){
    dark_out_on = 0;
  //  echo_hours_on = 0;
    light_out_on = 1;
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
  // if(digitalRead(pir_Front) == HIGH && (dark_out_on == 1 || echo_hours_on == 1)){digitalWrite(Front_Lights, LOW);}
 //  else{digitalWrite(Front_Lights, HIGH);}
 
  // if(digitalRead(pir_Back) == HIGH && (dark_out_on == 1 || echo_hours_on == 1)){digitalWrite(Back_Lights, LOW);}
  // else{digitalWrite(Back_Lights, HIGH);}
   
  // if(echo_hours_on == 0 && dark_out_on == 1){digitalWrite(Kitchen_Leds, LOW);}
  // else{digitalWrite(Kitchen_Leds, HIGH);}
   
  // if((digitalRead(pir_Back) == HIGH || digitalRead(pir_Front) == HIGH || digitalRead(Ext_pir_Group) == HIGH) && echo_hours_on == 1){yard_motion_flag = 1;}
//   else{yard_motion_flag = 0;}
  
 //  if(dark_out_on == 0 && yard_motion_flag == 1){digitalWrite(Security_Lights, LOW);}
 //  else{digitalWrite(Security_Lights, HIGH);} 
 //  if(dark_out_on == 1){digitalWrite(Security_Lights, LOW);} 
 //  if(light_out_on == 1){digitalWrite(Security_Lights, HIGH);}
 

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

   if (digitalRead(time_Button) == HIGH){
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
  
  if(digitalRead(reset_Button) == HIGH){
   heat_time = 0;
   lcd.setCursor(0,1);
   lcd.print("                ");
  // lcd.print(heat_time);  
  }
  
  if(digitalRead(start_Button) == HIGH && heat_time > 0){
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
    digitalWrite(Water_Heater, LOW);
    manual_heat_flag = 0;
    lcd.setCursor(0,1);
    lcd.print("                ");
   }
  }
 
   
}

