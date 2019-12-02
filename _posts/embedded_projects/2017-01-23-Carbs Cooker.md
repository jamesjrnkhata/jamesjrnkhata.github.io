---
title: "Carbs Cooker"
date: 2017-01-23
categories: [embedded-projects]
permalink: /:categories/:title/
feature_img: "http://img.youtube.com/vi/e3Qg-X7DNN8/0.jpg"
excerpt: "embedded, auto-cooker, C++, Arduino rice, pasta, nsima, food"
purpose: "This project aimed at developing a proof of concept (POC) for an all-in-one automatic cooker for three popular forms of carbs: Rice, Pasta and Nsima (Southern-African dish)."
---
This project aimed at developing a proof of concept (POC) for an all-in-one automatic cooker for three popular forms of carbs: Rice, Pasta and Nsima (Southern-African dish).

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
*	Non-stick cooking pot
*	Microcontroller (MCU) that fulfilled the requirements (General I/O pins, Flash Memory etc.).
*	LCD Display, Button Matrix PCB and Buzzer
*	Load cells, High torque Servo motors, Relays, Temperature Probes (Sensors)
*	Temperature Sensor for Electric Rice Cooker
*	Electric Hot Plate Cooking Coil
*	Hot water pump
*	Water holder, heating and feeding unit
*	Rice, Pasta, maize flour feeding units
*	High torque DC Motor for stirring
*	Stirring spatula

<h2 class="text-underline">Implementation</h2>

### Hardware
**User Interface** – This was made up of an *LCD Display* and the *Button Matrix PCB* (with button labels). The buttons were used to make selections. The *LCD Display* was used to give the user prompts, get information on the minimum requirements needed to cook a particular carb and progress of the cooking process. The *Buzzer* was used to notify the user when a cooking process was completed.

**Water Heater / Feeder Unit** – This was achieved with a *Boiling Kettle* modified to receive on and off signals from the *Controller unit* through a *Relay*. This was also fitted with a *Hot Water Pump* to feed the water to the *Non-Stick Cooking Pot*.

**Maize Flour Feeder Unit** – This was made up of 3D printed *Screw Feeding Auger* combined with *Load Sensors* and a *High Torque Servo Motor* connected to the *Controller Unit*. This unit fed into the *Non-Stick Cooking Pot*. The *Load Sensors* were tested and calibrated to give the amount of maize flour available for cooking.

**Rice / Pasta Feeder Unit** – This was another 3D printed feeder with a different design from the *Maize Flour Feeder Unit*. This was also fitted with the *Load Sensors* and a *High Torque Servo Motor* for precision control when feeding into the *Non-Stick Cooking Pot*. Similar calibration to the *Maize Flour Unit* were made.  

**Stirring Unit** – This was made up of a *High Torque DC Motor*, *Stirring Spatula* (designed for the project) and a 3D printed *Motor Bracket*. The *Stirring Spatula* was designed to fit the *High Torque DC Motor’s* shaft that ran through a small opening in the lid of the *Non-Stick Cooking Pot*. The *Stirring Spatula* design also allowed decoupling from the motor shaft for easy cleaning. The *High Torque DC Motor* was connected to the *Controller Unit* through a *Relay*.

**Pot Heater Unit** – This unit consisted of the *Temperature Probe (Sensor)*, *Temperature Sensor for Electric Rice Cooker* and the *Electric Hot Plate Cooking Coil*. Both *Temperature Sensors* were connected to the *Controller Unit* while the *Electric Hot Plate Cooking Coil* was connected through a *Relay*.

**Controller Unit** – This was made up of the *Microcontroller (MCU)*. It received and sent control signals to all the *Units*, *Sensors* and *Relays* of the Cooker.

**Cooker Housing** – A prototype case was built for the Cooker using local hardware (B&Q) material to hold its units and components together.   

### Software
The portions were estimated for each carb type by cooking the dishes conventionally (pot and stove), while recording how much ingredients were used in weight. This data was then used as a standard in *Load Sensor* readings (weight) to determine how much ingredients were required for extra portions of each carb type. All the steps carried out in cooking rice; Pasta and Nsima were then implemented into Arduino Sketch.   
