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
images:
  - image_path: /images/embedded_projects/beckyallotmentsystem/beckyallotmentsystem_img02.jpg
    title: "Water stream running along the length of the Allotment"
    weight: 1
  - image_path: /images/embedded_projects/beckyallotmentsystem/beckyallotmentsystem_img13.jpg
    title: "Figure 2 - "
    weight: 2
  - image_path: /images/embedded_projects/beckyallotmentsystem/beckyallotmentsystem_img16.jpg
    title: "Figure 3 - "
    weight: 3       
  - image_path: /images/embedded_projects/beckyallotmentsystem/beckyallotmentsystem_img18.jpg
    title: "Figure 4 - "
    weight: 4    
  - image_path: /images/embedded_projects/beckyallotmentsystem/beckyallotmentsystem_img19.jpg
    title: "System Controller Software Flowchart"
    weight: 5  
---

<!-- youtube clip " " -->
<div class="youtube-player" data-id="lPfLFi2TlY0"></div>

<h2 class="text-underline">Challenges</h2>
The system was intended to be used for monitoring the soil moisture and autonomously watering the vegetables planted at an Allotment in a remote location. As the Allotment was in an area that was far from the owner's residence, access to water and electricity was not possible.  However a stream ran through the length of the Allotment which was decided to be used as the source for watering the vegetables using a Water Pump.

The challenges that the project potentially faced were:
* Power Source - Depending on the type of water pump used, a method of powering the pump was required.  
* Watering Control - A way to register when the ground was watered, when it needed watering and a method to start watering without the need for the user to visit the Allotment.
* Security of Equipment - Although the Allotment was in a gated area, further consideration was supposed to be taken for the security and protection of the components (pump, controller etc) as the Allotment was located in a public area surrounded by other Allotment owners. This would leave the components susceptible to theft, vandalism or weather.

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

<h2 class="text-underline">Requirements</h2>
The user required the system to be able to water an area of roughly 100 square feet autonomously. They also wanted the system to be able to have capabilities of attaching a hose pipe for hand watering and also filling up Rain Barrels / Water Butts.

<h2 class="text-underline">Design</h2>

### Hardware

**Security**

The user had a shed built on the location which was 16 meters from the stream (water source). It was decided that the shed would be used to house and protect the components (Controller, Pump, Solar Panel, Battery etc) from theft, vandalism and weather elements.  

**Power Source**

In-order to power the system the decision of an off-grid solution seemed the more feasible option. This would comprise of solar panel(s), charge controller, Inverter (for a 240 volt Pump if needed) and Deep Cycle Battery (for deep discharges). Through analysing the user's needs and the distance from the water stream to the shed (16 meters),  it was determined that a 12 Volt (12V) DC Centrifugal Pump running on a 12v Deep Cycle Battery (Wet Cell) would be more than adequate for the job. 12V was also ideal as it would make it easier and efficient to power more devices without the need for extra components such as step-down transformers such as a 240 volt system.

Sizing of the Battery Bank and Solar panels was calculated and determined by the number of components being powered and the length of use required by the user.

A 12V Centrifugal Pump with an Automatic Pressure Control Switch was also preferred as it would allow the user to be able to control the water flow by simply opening valves (or tap) without fusing with the pump.  

**System Controller**

The Scheduling and Remote switching Controller solution was going to be achieved by integration of components such as: Feather Huzzah (ESP8266) MCU, Wi-Fi Modem (Hotpsot), MQTT through Cayenne Iot platform, Soil Moisture Sensor and Relay Modules.

<ul class="photo-gallery-2col">
  {% for image in page.images %}
    {% if image.weight >= 2 and image.weight <= 3 %}
      <li>
        <figure class="custom-figure">
          <img class="galley_img" src="{{ image.image_path }}" alt="{{ image.title }}">
          <figcaption class="custom-figcaption">
            {{ image.title }}
          </figcaption>
        </figure>  
      </li>
    {% endif %}  
  {% endfor %}  
</ul>

**System Plumbing Layout**

<ul class="photo-gallery">
  {% for image in page.images %}
    {% if image.weight == 4 %}
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

The system's plumbing was design to serve 5 functions:
1. Draw water from the *Stream (Inline Valve - Inlet 1 Opened)* to the *Sprinkler* Manually *(Inline Valve - Outlet 1 Opened)* or Automatically *(Solenoid Valve)* by User Remote / Schedule (through System Controller MCU).
2. Draw water from the *Stream (Inline Valve - Inlet 1 Opened)* to the *Garden Tap* for hand watering / hose attachment.
3. Draw water from the *Stream (Inline Valve - Inlet 1 Opened)* to fill up the *Water Drum (Inline Valve - Outlet 2)*.
4. Draw water from the *Drum (Inline Valve - Inlet 2 Opened)* to the Sprinkler Manually or Automatically.
5. Draw water from the *Drum (Inline Valve - Inlet 2 Opened)* to the Garden Tap.  

### Software

**System Requirements**

Through Analysis of the User's requirements, the following specifications were determined for the *System Controller*:

*	Have a Main Shut off Button for the system.
*	Use Soil Moisture Sensor to determine when to water automatically.
*	Have a minimum of two days in between watering sessions for scheduled watering.
*	Give the user information on Soil Moisture Sensor readings.
*	Prompt the user to Cancel a Scheduled watering session if it may rain.
*	Allow the user to Cancel watering sessions.
*	Allow the user to Manually start a watering session.
*	Only start 48 hr counter when the soil is dry (by a determined soil moisture threshold).
*	Collect a few samples of Soil Moisture Sensor readings and calculate the average value every hour.

<ul class="photo-gallery">
  {% for image in page.images %}
    {% if image.weight == 5 %}
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

<object data="https://jamesjrnkhata.github.io/embedded-projects/beckyallotmentsystem/Software-Requirements.pdf" type="application/pdf" width="700px" height="700px">
    <embed src="https://jamesjrnkhata.github.io/embedded-projects/beckyallotmentsystem/Software-Requirements.pdf">
        <p>This browser does not support PDFs. Please download the PDF to view it: <a href="https://jamesjrnkhata.github.io/embedded-projects/beckyallotmentsystem/Software-Requirements.pdf">Download PDF</a>.</p>
    </embed>
</object>

<embed src="https://drive.google.com/viewerng/
viewer?embedded=true&url=https://jamesjrnkhata.github.io/embedded-projects/beckyallotmentsystem/Software-Requirements.pdf" width="500" height="375">

<h2 class="text-underline">Implementation</h2>

<!-- youtube clip " " -->
<div class="youtube-player" data-id="lPfLFi2TlY0"></div>

* Wi-Fi, MQTT, Soil Moisture Sensor, ESP8266, Cayenne, Relay Modules,

### Hardware

### Software

<h2 class="text-underline">Gallery</h2>
