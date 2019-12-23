---
title: "Home Lighting Control System"
date: 2017-06-04
categories: [embedded-projects]
permalink: /:categories/:title/
feature_img: /images/embedded_projects/homelightingcontrol/homelc_img00.jpg
excerpt: "c++, security, automation, lighting, embedded, control, arduino"
purpose: "The project was one of the embedded control solutions offered to customers in domestic and industrial environments in Malawi. This particular system provided an energy saving and security lighting control system."
toc: true
classes: wide
---
The project was one of the embedded control solutions offered to customers in domestic and industrial environments in Malawi. This particular system provided an energy saving and security lighting control system.

<h2 class="text-underline">Background / Challenge</h2>

It is common practice in Malawi (Africa) for residents to turn their security lights on in the evenings and switch them off early in the mornings. Besides illumination, it is necessary (as it is believed) to put off burglars and thieves as it gives the impression of the residents being at home.  This is somewhat effective towards the intruders but not so cost effective on the electric bill.

The security lights on method becomes a problem when there is no one home. This lives many people left with two options: Either asking a neighbour or relative to house sit for them or more commonly leaving their security lights on throughout the day when they are out short term or even long term (holidays).

<h2 class="text-underline">Requirements</h2>

Eliminate the need to manually switch the lights on and off (wake up early to switch them off). Use a cheaper solution compared to dedicated 240 Volt PIR Sensors devices.  Save on the electric bill.

<h2 class="text-underline">Design</h2>

The system consisted of DC powered components set to control AC powered lighting. The solution applied was designed to:
1.	Control the lights switching on / off autonomously through a *Microcontroller (MCU)* and *Relays*. This was done using information from a *Real-Time Clock Module* (with the option of *Photoresistors* for accurate information on sunrise and sunset).
2.	Extend the switching functionality of the security lights using inexpensive DC Passive Infrared Sensors (PIR Sensors) motion detectors. This was to allow the lights to go off at a set point during the evening and come back on after detecting motion (around the perimeter of the house).
3.	Implement a similar motion detection lighting process for common areas inside the house to maximize on energy saving such as corridors, bathrooms, toilets, kitchens, front door (external) etc.
4.	Have the customer switch to *Low Consumption LED Light Bulbs* to lessen consumption as well as the load requirement for the *Relays*.

The house security lights would come on at sunset and then go off around a set time during the evening (e.g. 10 pm). From this point onwards, the PIR Sensors would determine when the lights turned on after motion detection until sunrise (The lights would come on for a user specified amount of seconds / minutes). Further motion signal detections would prolong the period the lights stayed on.

The internal lights integrated with motion sensing could also work similar to the security lights, where they start to work at sunset and stop at sunrise. Internal PIR lighting was set to turn on for varied time intervals depending on the area used and customer’s request (normally 30 seconds for corridors and 3 – 7 minutes for kitchens, bathrooms etc.).

<h2 class="text-underline">Implementation</h2>

### Hardware
This section lists the hardware used and some decisions that were made in installation.

*	Microcontroller (Arduino Uno)
*	10A Relay Modules (5v to 240v / 10A)
*	Photoresistors (if necessary)
*	Real-Time Clock Module (DS32231)
*	Passive Infrared Sensors (HC SR501 PIR Sensors)
*	Low Consumption LED Light Bulbs

**PIR Sensors** – were placed strategically around the external ceiling structure of the house to pick up motion (especially near windows and doors). Overlapping the detection arcs between the *PIR Sensors* was necessary to eliminate blind spots and utilise the least amount of sensors. Internally, *PIR sensors* were installed on the ceiling of the areas where motion detection lighting was required. The sensors were then interfaced to the *Microcontroller (MCU)*.

**Photoresistors** – were grouped and positioned in an area were the light intensity from outside would be properly detected. These were used when accurate detection of sunrise and sunset was required due to variations that occur throughout the year. These resistors were interfaced to the *Microcontroller (MCU)*.

**Relay Modules** – were used to interface the 240 volt light switches to the DC powered *Microcontroller (MCU)*, bypassing the manual light switches. The eliminated manual light switches were replaced with blanking plates for safety and clean aesthetics.

**Real-Time Clock Module** – was used to provide real-time clock information to the *Microcontroller (MCU)*. This module was set and used to provide the time information needed to tell the system when to alter its behaviour depending on the time of the day.

**Microcontroller (MCU)** – was responsible for interpreting sensor information and giving commands to the *Relay Modules* connected to the light switches.

### Software


**Declaration Code Snippet**
```cpp
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
```


**Main Code Snippet**

```cpp

// Get data from the DS3231
t = rtc.getTime(); // get time data
month = rtc.getMonthStr(); // get month data
day = t.dow; // retrieved day as a integer.
hours = t.hour; // get hour data from time
minutes = t.min; // get minute data from time

// On_Status(); // initialize function

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
  light_outside = 1; // set flag to on
}

 // CONDITIONS USED TO CONTROL INTERAL AND EXTERNAL LIGHTS BASED ON TIME AND PIR INPUT

 if(digitalRead(pir_front) == HIGH && (dark_outside == 1 || echo_hours_on == 1)){
   digitalWrite(front_lights, LOW); // turn on
 }
 else
 {
   digitalWrite(front_lights, HIGH);
 }

 if(digitalRead(pir_back) == HIGH && (dark_outside == 1 || echo_hours_on == 1)){
  digitalWrite(back_lights, LOW); // turn on
 }
 else
 {
  digitalWrite(back_lights, HIGH); // turn off
 }

 if(digitalRead(pir_shower) == HIGH && (dark_outside == 1 || echo_hours_on == 1)){
  digitalWrite(shower_lights, LOW); // turn on
 }
 else
 {
  digitalWrite(shower_lights, HIGH); // turn off
 }

 if(digitalRead(pir_hallway) == HIGH && (dark_outside == 1 || echo_hours_on == 1)){
  digitalWrite(hallway_lights, LOW); // turn on
 }
 else
 {
  digitalWrite(hallway_lights, HIGH); // turn off
 }

 if(digitalRead(pir_kitchen) == HIGH && (dark_outside == 1 || echo_hours_on == 1)){
  digitalWrite(kitchen_lights, LOW); // turn on
 }
 else
 {
  digitalWrite(kitchen_lights, HIGH); // turn off
 }

 // condition to set ext_pir_group flag (set by any external PIRs excluding pir_front and pir_back)
 if (digitalRead(pir_extfront_right) == HIGH || digitalRead(pir_extback_right) == HIGH || digitalRead(pir_extfront_left) == HIGH || digitalRead(pir_extback_left) == HIGH){
   ext_pir_group = 1;  // set flag to on
 }
 else
 {
  ext_pir_group = 0;  // set flag to off
 }

 // condition to set yard_motion_flag by all external PIRs
 if((digitalRead(pir_back) == HIGH || digitalRead(pir_front) == HIGH || ext_pir_group == 1) && echo_hours_on == 1){
  yard_motion_flag = 1; // set flag to on
 }
 else
 {
  yard_motion_flag = 0; // set flag to off
 }

 if(dark_outside == 0 && yard_motion_flag == 1){
  digitalWrite(security_lights, LOW); // turn on
 }
 else
 {
  digitalWrite(security_lights, HIGH); // turn off
 }

 if(dark_outside == 1){
  digitalWrite(security_lights, LOW); // turn on
 }
 if(light_outside == 1){
  digitalWrite(security_lights, HIGH); // turn off
 }
}
```

<h2 class="text-underline">Future Upgrades</h2>

* Alarm system was an option that could be added with the controller.
* Closed Circuit Television (CCTV) Surveillance system could be integrated with the system
*	Mobile phone GSM notifications could be integrated to alert the residents of Sensor detections.
