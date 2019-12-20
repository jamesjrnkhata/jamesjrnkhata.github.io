---
title: "Water Heater Controller"
date: 2017-07-09
categories: [embedded-projects]
permalink: /:categories/:title/
feature_img: /images/embedded_projects/waterheatercontroller/waterheatercontroller_img00.jpg
excerpt: "boiler, automation, embedded, control, domestic, c++, arduino"
purpose: "This project was an embedded controller offered to customers with Water Heaters (Geysers) with in-efficient thermostats or built-in temperature regulators. Its purpose was to elevate the need for the customer to manually switch the Water Heater on and off. "
toc: true
classes: wide
---
This project was an embedded controller offered to customers with Water Heaters (Geysers) with in-efficient thermostats or built-in temperature regulators. Its purpose was to elevate the need for the customer to manually switch the Water Heater on and off.

<h2 class="text-underline">Background / Challenge</h2>

As there are no services in Malawi (Africa) that offer Gas directly into homes (likely due to the country’s economic state and limited infrastructure), residents do not own Gas Water Heaters. The only options available for house water heating are Electric and Vacuum Tube Solar Water Heaters.

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

**Arduino Nano** – was used to determine the actions of the controller. The *Real-Time Clock module* and *Push Buttons* were interfaced as input signals to the *Arduino Nano*. The *30A Relay Module* and the *16x2 LCD Display* were used as output.

**Push Buttons** – were used to give commands to the *Arduino Nano*. The three buttons were; *TIME TI* button (cycle between 30 minute increments to turn on the Water Heater), *START* button (to start the selected interval to turn the Water Heater) and the *CANCEL* button (to cancel the current heating process or return to the main menu).

**Real-Time Clock module** – was used to help the system maintain the clock and timing. It was used to turn the Water Heater on or off depending on the times it was coded to come on through software.

**16x2 LCD Display** – Was used to give information to the user to do with current activities of the controller. It was also used to show the current time and how long a pre-heat operation had left to complete.  

**30A Relay Module** – was used to switch the Water Heater. The high rating (30Amps) was used due to the Water Heaters high power draw.

**2-Gang Surface Pattress Box** – Was used to hold the components of the controller.

### Software


**Declaration Code Snippet**

<h2 class="text-underline">Gallery</h2>

<h2 class="text-underline">Future Upgrades</h2>
