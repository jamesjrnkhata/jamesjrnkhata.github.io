---
title: "Remote Allotment Irrigation System"
date: 2020-07-17
categories: [embedded-projects]
permalink: /:categories/:title/
feature_img: /images/embedded_projects/beckyallotmentsystem/beckyallotmentsystem_img00.jpg
excerpt: "c++, irrigation, esp8266, iot, cayenne, mqtt, remote-control, renewable-energy"
purpose: "The aim of this project was to provide an automated solution for watering of vegetables in an allotment situated in a remote location with no direct access to water plumbing or electricity."
toc: true
classes: wide
---


<h2 class="text-underline">Challenge</h2>
The system was intended to be used for monitoring the soil moisture and autonomously watering the vegetables planted at an Allotment in a remote location. As the Allotment was in an area that was far from the owner's residence, access to water and electricity was not possible.  However a stream ran through the length of the Allotment which was decided to be used as the source for watering the vegetables using a Water Pump.

The challenges that the project potentially faced were:
* Power Source - Depending on the type of water pump used, a method of powering the pump was required.  
* Watering Control - A way to register when the ground was watered, when it needed watering and a method to start watering without the need for the user to visit the Allotment.
* Security of Equipment - Although the Allotment was in a gated area, further consideration was supposed to be taken for the security and protection of the components (pump, controller etc) as the Allotment was located in a public area surrounded by other Allotment owners. This would leave the components susceptible to theft, vandalism or weather.  

<h2 class="text-underline">Requirements</h2>
The user required the system to be able to water an area of roughly 100 square feet autonomously. They also wanted the system to be able to have capabilities of attaching a hose pipe for hand watering and also filling up Rain Barrels and Water Butts.

<h2 class="text-underline">Design</h2>

### Security
The user had a shed built on the location which was 16 meters from the stream (water source). It was decided that shed would be used to house and protect the components (solar panels etc) from theft, vandalism and weather elements.  

### Power Source

In-order to power the system the decision of an off-grid solution seemed the more feasible option. This would comprise of solar panel(s), charge controller, Inverter (for a 240 volt Pump if needed) and Deep Cycle Battery (for deep discharges). Through analysing the user's needs and the distance from the water stream to the shed (16 meters),  it was determined that a 12 Volt (12V) DC Pump would be more than adequate for the job. 12V was also ideal as it would make it easier and efficient to power more devices without the need for extra components such as step-down transformers such as a 240 volt system.

Sizing of the Battery Bank and Solar panels was calculated and determined by the number of components being powered and the length of use required by the user.

### Water Controller
* Wi-Fi, MQTT, Soil Moisture Sensor, ESP8266, Cayenne, Relay Modules,  



<h2 class="text-underline">Implementation</h2>

<!-- youtube clip " " -->
<div class="youtube-player" data-id="e3Qg-X7DNN8"></div>

* Wi-Fi, MQTT, Soil Moisture Sensor, ESP8266, Cayenne, Relay Modules,

### Hardware

### Software

<h2 class="text-underline">Gallery</h2>
