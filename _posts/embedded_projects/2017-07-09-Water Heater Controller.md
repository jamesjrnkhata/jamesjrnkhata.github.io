---
title: "Water Heater Controller"
date: 2017-07-09
categories: [embedded-projects]
permalink: /:categories/:title/
feature_img: /images/embedded_projects/waterheatercontroller/waterheatercontroller_img00.jpg
excerpt: "c++, boiler, automation, embedded, control, domestic, arduino"
purpose: "This project was an embedded controller offered to customers with Water Heaters (Geysers) with in-efficient thermostats or built-in temperature regulators. Its purpose was to elevate the need for the customer to manually switch the Water Heater on and off. "
toc: true
classes: wide
images:
  - image_path: /images/embedded_projects/waterheatercontroller/waterheatercontroller_img00.jpg
    title: "Figure 1 - Water Heater"
    weight: 1
  - image_path: /images/embedded_projects/waterheatercontroller/waterheatercontroller_img02.jpg
    title: "Figure 2 - Hardware Components"
    weight: 2
  - image_path: /images/embedded_projects/waterheatercontroller/waterheatercontroller_img03.jpg
    title: "Figure 3 - Software and Hardware Implemented"
    weight: 3
  - image_path: /images/embedded_projects/waterheatercontroller/waterheatercontroller_img04.jpg
    title: "Figure 4"
    weight: 4   
  - image_path: /images/embedded_projects/waterheatercontroller/waterheatercontroller_img05.jpg
    title: "Figure 5"
    weight: 5  
  - image_path: /images/embedded_projects/waterheatercontroller/waterheatercontroller_img06.jpg
    title: "Figure 6"
    weight: 6   
  - image_path: /images/embedded_projects/waterheatercontroller/waterheatercontroller_img07.jpg
    title: "Figure 7"
    weight: 7  
  - image_path: /images/embedded_projects/waterheatercontroller/waterheatercontroller_img08.jpg
    title: "Figure 8"
    weight: 8   
  - image_path: /images/embedded_projects/waterheatercontroller/waterheatercontroller_img09.jpg
    title: "Figure 9"
    weight: 9
  - image_path: /images/embedded_projects/waterheatercontroller/waterheatercontroller_img10.jpg
    title: "Figure 10"
    weight: 10   
  - image_path: /images/embedded_projects/waterheatercontroller/waterheatercontroller_img11.jpg
    title: "Figure 11"
    weight: 11  
  - image_path: /images/embedded_projects/waterheatercontroller/waterheatercontroller_img12.jpg
    title: "Figure 12"
    weight: 12   
  - image_path: /images/embedded_projects/waterheatercontroller/waterheatercontroller_img13.jpg
    title: "Figure 13"
    weight: 13  
  - image_path: /images/embedded_projects/waterheatercontroller/waterheatercontroller_img14.jpg
    title: "Figure 14"
    weight: 14   
  - image_path: /images/embedded_projects/waterheatercontroller/waterheatercontroller_img15.jpg
    title: "Figure 15"
    weight: 15
  - image_path: /images/embedded_projects/waterheatercontroller/waterheatercontroller_img16.jpg
    title: "Figure 16"
    weight: 16   
  - image_path: /images/embedded_projects/waterheatercontroller/waterheatercontroller_img17.jpg
    title: "Figure 17"
    weight: 17  
  - image_path: /images/embedded_projects/waterheatercontroller/waterheatercontroller_img18.jpg
    title: "Figure 18"
    weight: 18                
---
This project was an embedded controller offered to customers with Water Heaters (Geysers) with in-efficient thermostats or built-in temperature regulators. Its purpose was to elevate the need for the customer to manually switch the Water Heater on and off.

<h2 class="text-underline">Background / Challenge</h2>

As there are no services in Malawi (Africa) that offer Gas directly into homes (likely due to the country’s economic state and limited infrastructure), residents do not own Gas Water Heaters. The only options available for house water heating are Electric and Vacuum Tube Solar Water Heaters.

<ul class="photo-gallery">
  {% for image in page.images %}
    {% if image.weight == 1 %}
      <li>
        <figure class="custom-figure">
          <img src="{{ image.image_path }}" alt="{{ image.title }}">
          <figcaption class="custom-figcaption">
            {{ image.title }}
          </figcaption>
        </figure>  
      </li>
    {% endif %}  
  {% endfor %}  
</ul>

It was observed that most homeowners with Electric Water Heaters had older (or used) models that did not come with efficient enough thermostats capable of regulating power consumption of the unit. Therefore,  to always have hot water the homeowners can leave their water heaters on constantly or they can keep it off and only switch it on when they need hot water (wait at least an hour). It is left to the homeowner’s discretion to turn their Water Heater on and off to moderate the power consumption as well as the temperature of their water.

In the event that these water heaters are not regulated, two concerns would be:
1.	The water’s temperature could heat up to scolding levels.
2.	The power consumption of the Electric Water Heater could be extremely high especially if left on for long periods.      

<h2 class="text-underline">Requirements</h2>

The user should have warm water for normal use and pre-heated (for at least an hour) for showers.

<h2 class="text-underline">Design</h2>

The solution applied was designed to:
1.	Have user set times for the water to be heated (shower)
2.	The ability to pre-heat the water manually

The user would determine the times they wanted their water to be hot and the controller would be set through software to turn the Water Heater on for an hour prior to that time. The user would also be able to manual pre-heat the water for a number of minutes (incremented by 30 minutes); the controller would then switch the Water Heater off after.

<h2 class="text-underline">Implementation</h2>

### Hardware
*	Push Buttons (Tactile Switches)
*	30A Relay Module (AC 250V / 30A)
*	16x2 LCD Display
*	Arduino Nano (Atmega328p)
*	Real-Time Clock Module (DS32231)
*	2-Gang Surface Pattress Box (Housing for the components)

<ul class="photo-gallery-2col">
  {% for image in page.images %}
    {% if image.weight == 2 and image.weight == 3 %}
      <li>
        <figure class="custom-figure">
          <img src="{{ image.image_path }}" alt="{{ image.title }}">
          <figcaption class="custom-figcaption">
            {{ image.title }}
          </figcaption>
        </figure>  
      </li>
    {% endif %}  
  {% endfor %}  
</ul>

**Arduino Nano** – was used to determine the actions of the controller. The *Real-Time Clock module* and *Push Buttons* were interfaced as input signals to the *Arduino Nano*. The *30A Relay Module* and the *16x2 LCD Display* were used as output.

**Push Buttons** – were used to give commands to the *Arduino Nano*. The three buttons were; *TIME TI* button (cycle between 30 minute increments to turn on the Water Heater), *START* button (to start the selected interval to turn the Water Heater) and the *CANCEL* button (to cancel the current heating process or return to the main menu).

**Real-Time Clock module** – was used to help the system maintain the clock and timing. It was used to turn the Water Heater on or off depending on the times it was coded to come on through software.

**16x2 LCD Display** – Was used to give information to the user to do with current activities of the controller. It was also used to show the current time and how long a pre-heat operation had left to complete.  

**30A Relay Module** – was used to switch the Water Heater. The high rating (30Amps) was used due to the Water Heaters high power draw.

**2-Gang Surface Pattress Box** – Was used to hold the components of the controller.

### Software

**Declaration Code Snippet**
```cpp
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

```
**Manual Heat Function Code Snippet**

```cpp
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

```

<h2 class="text-underline">Gallery</h2>

<ul class="photo-gallery-3col">
  {% for image in page.images %}
    {% if image.weight >= 4 and image.weight <= 18 %}  
      <li>
        <img class="galley_img" src="{{ image.image_path }}" alt="{{ image.title }}">
      </li>
    {% endif %}  
  {% endfor %}  
</ul>

Full code available from <a class="custom_link" href="https://github.com/jamesjrnkhata/Water-Heater-Controller">GitHub</a> page (<a class="custom_link" href="https://github.com/jamesjrnkhata/Water-Heater-Controller">water-heater-controller</a>).
