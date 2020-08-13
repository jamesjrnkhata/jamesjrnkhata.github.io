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
---

<!-- youtube clip "Watering Remotely with Sprinkler Overview" -->
<div class="youtube-player" data-id="4arRe6cnxJQ"></div>

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

<embed src="https://drive.google.com/viewerng/
viewer?embedded=true&url=https://jamesjrnkhata.github.io/images/embedded_projects/beckyallotmentsystem/Plumbing-Layout.pdf" width="1024" height="768">


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
*	Only start 48 hour counter when the soil is dry (by a determined Soil Moisture Threshold).
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

**System Controller Software Flowchart**

<embed src="https://drive.google.com/viewerng/
viewer?embedded=true&url=https://jamesjrnkhata.github.io/images/embedded_projects/beckyallotmentsystem/Software-Requirements.pdf" width="1024" height="768">

<h2 class="text-underline">Implementation</h2>

<!-- youtube clip "Irrigation System Extra Features" -->
<div class="youtube-player" data-id="FQUCazGfT6A"></div>


### Hardware

* Wi-Fi, MQTT, Soil Moisture Sensor, ESP8266, Cayenne, Relay Modules,

### Software

**CAYENNE MQTT**

**Code**

```cpp
////////////////////////// ALLOTMENT WATER SYSTEM CONTROLLER ///////////////////////////////
///////////////////////// FEATHER HUZZAH USING CAYENNE MQTT ////////////////////////////////
/////////////////////////// written by: JAMES JR NKHATA ////////////////////////////////////

//#define CAYENNE_DEBUG
#define CAYENNE_PRINT Serial
#include <CayenneMQTTESP8266.h>

// WiFi network info.
char ssid[] = "Allotment"; //
char wifiPassword[] = "***********"; //

// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
char username[] = "********-****-****-****-************";
char password[] = "****************************************";
char clientID[] = "********-****-****-****-************";

/*************************************************************************************************************************************************************  
 *************************************************** SYSTEM VARIABLES ****************************************************************************************
 *************************************************************************************************************************************************************/

/*
 * Time tracking with millis()
 */
uint8_t seconds = 0;
uint8_t minutes = 0;
uint8_t hours = 0;
uint32_t previousTime = 0;

uint8_t totalSampleHours = 0;
uint16_t totalSampleValues = 0;

 /************************************************************************************************************************************************************/

/*
 * Soil sensor data
 */
uint16_t capSoilSensor1;
uint16_t airDryValue = 380; // dry soil analog reading
uint16_t soilWetValue = 240; // dry soil analog reading
uint16_t soilMoisture;
//soilDryValue = 368 - 372 (363 - 374)(Dry - 0 - 25%)
//soilPartWetValue = 338 - 350 (Low Wetness < 60 %)
//soilWetValue = 310 - 327 (Medium Wetness 61 - 70 %)
//soilWetValue = 254 - 260 (Fully Wet > 85 %)
/************************************************************************************************************************************************************/

/*
 *  Cayenne System Variables
 */
 #define SYSTEM_OFF_BUTTON_CHANNEL                    1  /*!< Switch the system on and off >*/
 #define STATUS_CHECK_SCHED_BUTTON_CHANNEL            2  /*!< Used to start a “Status Check” scheduled routine >*/  
 #define WATER_PROCESS_SCHED_BUTTON_CHANNEL           3  /*!< Used to start a “Watering Process” scheduled routine >*/
 #define MANUAL_WATER_BUTTON_CHANNEL                  4  /*!< Used to start Watering Process Manually >*/
 #define CANCEL_WATER_BUTTON_CHANNEL                  5  /*!< Used to Cancel next scheduling or currently Watering Process >*/

 #define CANCEL_WATERING_BUTTON_FLAG_CHANNEL          6  /*!< Used to reset the state of the Cancel Watering Button Cayenne Button press >*/
 #define STATUS_CHECK_SCHEDULE_BUTTON_FLAG_CHANNEL    7  /*!< Used to reset the state of the Check Schedule Button Cayenne Button press >*/
 #define WATER_PROCESS_SCHEDULE_BUTTON_FLAG_CHANNEL   8  /*!< Used to reset the state of the Water Process Schedule Button Cayenne Button press >*/
 #define MANUAL_WATER_BUTTON_FLAG_CHANNEL             9  /*!< Used to reset the state of the Manual Water Button Cayenne Button press >*/
 #define SOIL_MOISTURE_DATA_CHANNEL                   10 /*!< Used to receive and display feed from the soil moisture sensor >*/
 #define FINISHED_WATERING_CHANNEL                    11 /*!< Used to log Completed Watering Processed (used to indicate the time too) >*/
 #define STARTED_WATERING_CHANNEL                     12 /*!< Used to log when watering was started and when it ended >*/
 #define WATERING_SCHEDULED_TOMORROW_CHANNEL          13 /*!< Used to send a notification to the user informing them of a scheduled watering session >*/

 #define WATERING_STATUS_CHANNEL                      16 /*!< Used to log the watering for activity for the user >*/

 #define TOTAL_SAMPLE_HOURS_CHANNEL                   14 /*!< Used to send a Total Sample Hour data for DEBUGGING >*/
 #define TOTAL_SAMPLE_VALUES_CHANNEL                  15 /*!< Used to send a Total Sample Value data for DEBUGGING >*/

 uint8_t systemOffButton;
 uint8_t statusCheckButton;
 uint8_t waterProcessButton;
 uint8_t manualWaterButton;
 uint8_t cancelWaterButton;

 uint8_t cancelWateringState = 0;
 uint8_t statusCheckSchedState = 0 ;
 uint8_t waterProcessSchedState = 0;
 uint8_t manualWateringState = 0;
 uint8_t finishedWateringState = 0;
 uint8_t startedWateringState = 0;
 uint8_t wateringSchedTomorrowState = 0;

 uint8_t wateringStatus = 0;
/************************************************************************************************************************************************************/
 /*
  * Watering Process variables
  */
 uint8_t autoWateringFlag = 0;
 uint8_t manualWateringFlag = 0;
 uint8_t wateringFlag = 0;
 uint8_t startWateringFlag = 0;
/************************************************************************************************************************************************************/

/*
 * Define the macros to use with the relays
 */
 #define SPRINKLER_VALVE_RELAY                        12 /*!< Used to control Sprinkler Solenoid Valve >*/
 #define PUMP_RELAY                                   13 /*!< Used to control the Pump>*/
/************************************************************************************************************************************************************/

/*
 * prototype the functions used in the system
 */
uint16_t Soil_Moisture_Reading(void);

void Reset_Moist_Sample_Collect(void);

void Time_Counter(void);

void Status_Check_Process(uint8_t setSampleHours);

void Watering_Process(void);

/************************************************************************************************************************************************************/
/************************************************************************************************************************************************************/

void setup() {
	Serial.begin(9600);
	Cayenne.begin(username, password, clientID, ssid, wifiPassword);

  pinMode(SPRINKLER_VALVE_RELAY, OUTPUT); // setup Sprinkler valve relay as output
  digitalWrite(SPRINKLER_VALVE_RELAY, HIGH); // switch off relay (ACTIVE LOW - LOW turns on and HIGH turns off)

  pinMode(PUMP_RELAY, OUTPUT); // setup Pump relay as output
  digitalWrite(PUMP_RELAY, HIGH); // switch off relay (ACTIVE LOW - LOW turns on and HIGH turns off)  

}
/************************************************************************************************************************************************************/
/************************************************************************************************************************************************************/

void loop() {
	Cayenne.loop();  

  Time_Counter(); // call Time_Counter function

  capSoilSensor1 = analogRead(A0); /*!< > */

  soilMoisture = map(capSoilSensor1, airDryValue, soilWetValue, 0, 100);

  if(soilMoisture > 100 || soilMoisture < 0)
  {
    soilMoisture = 0;
    // 1. if the reading is below 0% or above 100% register as sensor error handler
  }

/************************************************************************************************************************************************************/
  // ***** CHECK IF SOIL WAS WATERED / IT RAINED **** //
/************************************************************************************************************************************************************/  
  if(soilMoisture > 85 && !(wateringFlag) )
  {
     uint16_t tempValue = Soil_Moisture_Reading(); // start collecting samples

     if(tempValue >= 85)
     {
      // Check if the average soil moisture reading is greater than the passed threshold in %
      // and the wateringFlag is not SET
      Reset_Moist_Sample_Collect(); // reset the hourly sensor collection    
     }
  }
/************************************************************************************************************************************************************/
  // ***** HOURLY SAMPLE COLLECTION **** //
/************************************************************************************************************************************************************/  
  if( (minutes == 58 && seconds == 1) && !(wateringFlag) )//
  {
    uint16_t value = Soil_Moisture_Reading(); // start collecting samples for the hour

    if(value > 0 && value < 85)
    {
      totalSampleValues += value;
      totalSampleHours += 1;  
    }
    else if (value >= 85 && !(wateringFlag))
    {
      // Check if the average soil moisture reading is greater than the passed threshold in %
      // and the wateringFlag is not SET
      Reset_Moist_Sample_Collect(); // reset the hourly sensor collection
    }
    else
    {
      // 1. sensor error handler
      // 2. try another sample collection ?
    }

  }

/************************************************************************************************************************************************************/
  // ***** STATUS CHECK ON SCHEDULED EVENT **** //
/************************************************************************************************************************************************************/
  // Status check is on and System off is not on
  if( !(systemOffButton) && statusCheckButton)
  {    
    // run Status_check_process
    // call status check function and pass parameter of the minimum hours acceptable between soil watering
    Status_Check_Process(37);

    // send a notifaction to the user if watering is scheduled tomorrow
    Notification_Watering_Tomorrow();

    // reset status check schedule button by sending reset flag back to cayenne system       
    Notification_Reset_Status_Check_Sched();
  }

/************************************************************************************************************************************************************/
  // ***** WATERING PROCESSING **** //
/************************************************************************************************************************************************************/
  Watering_Process();

/************************************************************************************************************************************************************/
  // ***** WATERING CYCLE **** //
/************************************************************************************************************************************************************/
  Watering_Cycle();

/************************************************************************************************************************************************************/
  // ***** MANUAL WATERING **** //
/************************************************************************************************************************************************************/
  // System off is not on
  if(!(systemOffButton))
  {
    ManualWatering();
  }
}

/************************************************************************************************************************************************************/
                                                          // ***** END OF VOID LOOP **** //
/************************************************************************************************************************************************************/


/************************************************************************************************************************************************************
 * @fn                - CAYENNE_OUT_DEFAULT
 *
 * @brief             - Default function for sending sensor data at intervals to Cayenne (See https://cayenne.mydevices.com/cayenne/)
 *                      You can also use functions for specific channels, e.g CAYENNE_OUT(1) for sending channel 1 data.
 * @param[in]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -
 *
 * @Note              -
 */
CAYENNE_OUT_DEFAULT()
{
	// Write Soil Moisture Data to CAYENNE
  Cayenne.virtualWrite(SOIL_MOISTURE_DATA_CHANNEL, soilMoisture, "soil_moist", "p");

  //
  Cayenne.virtualWrite(CANCEL_WATERING_BUTTON_FLAG_CHANNEL, cancelWateringState, "digital_sensor", "d");

  //
  Cayenne.virtualWrite(STATUS_CHECK_SCHEDULE_BUTTON_FLAG_CHANNEL, statusCheckSchedState);

  //
  Cayenne.virtualWrite(WATER_PROCESS_SCHEDULE_BUTTON_FLAG_CHANNEL, waterProcessSchedState);

  //
  Cayenne.virtualWrite(MANUAL_WATER_BUTTON_FLAG_CHANNEL, manualWateringState);          

  //
  Cayenne.virtualWrite(STARTED_WATERING_CHANNEL, startedWateringState, "digital_sensor", "d");   

  //
  Cayenne.virtualWrite(FINISHED_WATERING_CHANNEL, finishedWateringState, "digital_sensor", "d");   

  //
  Cayenne.virtualWrite(WATERING_SCHEDULED_TOMORROW_CHANNEL, wateringSchedTomorrowState, "digital_sensor", "d");

  //
  Cayenne.virtualWrite(TOTAL_SAMPLE_HOURS_CHANNEL, totalSampleHours);

  //
  Cayenne.virtualWrite(TOTAL_SAMPLE_VALUES_CHANNEL, totalSampleValues);

  //
  Cayenne.virtualWrite(WATERING_STATUS_CHANNEL, wateringStatus, "digital_sensor", "d");

}

/************************************************************************************************************************************************************
 * @fn                - CAYENNE_IN
 *
 * @brief             - Used to receive data from the CAYENNE System (See https://cayenne.mydevices.com/cayenne/)
 *
 * @param[in]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -
 *
 * @Note              -
 */
CAYENNE_IN(SYSTEM_OFF_BUTTON_CHANNEL) //System Button
{
  systemOffButton = getValue.asInt();
}

CAYENNE_IN(STATUS_CHECK_SCHED_BUTTON_CHANNEL) //Status Check Scheduled Button
{
  statusCheckButton = getValue.asInt();
}

CAYENNE_IN(WATER_PROCESS_SCHED_BUTTON_CHANNEL) // Water Process Scheduled Button
{
  waterProcessButton = getValue.asInt();
}

CAYENNE_IN(MANUAL_WATER_BUTTON_CHANNEL) // Manual Water Button
{
  manualWaterButton = getValue.asInt();
}

CAYENNE_IN(CANCEL_WATER_BUTTON_CHANNEL) // Cancel Water Button   
{
  cancelWaterButton = getValue.asInt();
}

/************************************************************************************************************************************************************
 * @fn                - Time_Counter
 *
 * @brief             - Used millis() function to count seconds, minutes and hours
 *
 * @param[in]         - "start" is an uint8_t used to start or stop the counter (1 - start, 0 - stop)
 * @param[in]         - "seconds_minutes_hours" uint8_t used to select return type 0 - seconds, 1 - minutes and 2 hours
 * @param[in]         - userPreviousTime used to reset the timer (set to 0)
 *
 * @return            - returns - seconds,minutes or hours based on parameters passed
 *
 * @Note              -
 */
void Time_Counter(void)
{  
  if((millis()- previousTime) > 1000)
  {
      seconds += 1;
      if (seconds > 59)
      {
        seconds = 0;
        minutes += 1;
        if (minutes > 59)
        {
          minutes = 0;
          hours += 1;  
        }
      }
      previousTime = millis();
  }

  // condition to counter the millis function rolling over
  else if(millis() - previousTime < 0)
  {
    previousTime = millis();
  }

}

/************************************************************************************************************************************************************
 * @fn                - Soil_Moisture_Reading
 *
 * @brief             - Used to collect samples every hour (time is determined by user through minutes and seconds)
 *
 * @param[in]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -
 *
 * @Note              -
 */
uint16_t Soil_Moisture_Reading(void)
{
  uint16_t sampleValue = 0;
  uint8_t sampleCount = 0;
  uint8_t samples = 10;

  for(uint8_t x; x<samples; x++ )
  {

    sampleValue += soilMoisture;
    sampleCount += 1;
    delay(1000); // add a 1 second delay between every Soil Moisture reading

  }  

  seconds += samples; // advance the seconds by the amount taken by the sample taking

  uint16_t averageSampleValue = (sampleValue/(uint16_t)sampleCount) ;

  return averageSampleValue;  
}

/************************************************************************************************************************************************************
 * @fn                - Average_Soil_Moisture_Reading
 *
 * @brief             - Used to calculate average Soil Moisture from collected
 *                      samples over a set period
 *
 * @param[in]         - soil wetness threshold in percent 0 - 100 (above 70% is still wet)
 * @param[in]         -
 * @param[in]         -
 *
 * @return            - 1 for above Threshold and 0 for below Threshold (uint8_t)
 *
 * @Note              -
 */
uint8_t Average_Soil_Moisture_Reading(uint8_t wetThreshold)
{     
    if((totalSampleValues/(uint16_t)totalSampleHours) > wetThreshold)
    {
      return 1;
    }
    else
    {
      return 0;
    }
}

/************************************************************************************************************************************************************
 * @fn                - Reset_Moist_Sample_Collect
 *
 * @brief             - Used to reset the parameters used to keep track of the timings
 *                      
 *
 * @param[in]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -
 *
 * @Note              -
 */
void Reset_Moist_Sample_Collect(void)
{
    totalSampleHours = 0; /*<! Reset hours samples collected period>*/
    totalSampleValues = 0; /*<! Reset collect sample values>*/
    seconds = 0;
    minutes = 0;
    hours = 0;
    previousTime = millis();    
}


void Flag_State_Change(uint8_t flag, uint8_t trigger)
{
  uint8_t previousState;
  uint8_t currentState;
  //1. if trigger is high then change flag
  //2. only change if trigger changes state
}

void Sensor_Error_Handler(void)
{

}

/************************************************************************************************************************************************************
 * @fn                - Status_Check_Process
 *
 * @brief             - Used to determine if the user has set the system on (from Cayenne system)
 *                      also used to check for the scheduled check for watering the next day
 *                      and if the hours passed are enough to require watering
 *
 * @param[in]         - setSampleHours used to set the minimum hours of samples collected to start auto watering
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -
 *
 * @Note              -
 */
void Status_Check_Process(uint8_t setSampleHours)
{
  if(totalSampleHours > setSampleHours)
  {
    // Calculate Average Soil Moisture
    if( Average_Soil_Moisture_Reading(70) && !(wateringFlag) )
    {
      // Soil is still wet
      // and the wateringFlag is not SET
      Reset_Moist_Sample_Collect(); // reset the hourly sensor collection

      //*******DEBUG********//
      Serial.println("STATUS CHECK RESET TIMER");
      // ********************* //   
    }
    else
    {
      // Soil is dry
      // START WATERING PROCESS (Set Auto watering flag)
      autoWateringFlag = 1;
    }
  }        
}

/************************************************************************************************************************************************************
 * @fn                - Watering_Process
 *
 * @brief             - Used to initialize the watering when a scheduled signal is received from Cayenne system
 *                      it uses a few parameters to determine if the conditions are appropriate to carryout watering
 * @param[in]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            - none
 *
 * @Note              -
 */
void Watering_Process(void)
{
  if(autoWateringFlag)
  {
    //*******DEBUG********//
    Serial.println("START WATERING PROCESS");
    // ********************* //

    // send a notifaction to the user "watering is scheduled tomorrow"
    // Notification_Watering_Tomorrow();

    // Wait for watering process schedule to start / Cancel button to be received / it rains before the water process schedule signal is received
    if(soilMoisture > 85 && !(waterProcessButton) )
    {
        uint16_t tempValue = Soil_Moisture_Reading(); // start collecting samples        
        // if collected sample average is greater than
        if(tempValue > 85)
        {
          // send notification to user that it rained / soil is wet so watering is cancelled
          Notification_Cancel_Watering();

          // Reset Auto Watering Flag
          autoWateringFlag = 0;
        }    
    }

    // 4. If not cancelled water until completion (1 hour), (reset seconds, minutes, hours, previousTime and pause sample collection - wateringFlag)
    else if(waterProcessButton)
    {
      // check if the user has cancelled the watering      
      // Note: waited until Water Process Scheduled button is activated before cancelling incase the user changes their mind
      if(cancelWaterButton)
      {
        // Reset Auto Watering Flag
        autoWateringFlag = 0;        

        // reset water processs schedule button by sending reset flag back to cayenne system    
        Notification_Reset_Water_Process_Sched();

        // reset cancel water button by sending reset flag back to cayenne system    
        Notification_Cancel_Watering();       
      }
      else
      {
        // set watering flag
        wateringFlag = 1;
      }      
    }     
  }
}

/************************************************************************************************************************************************************
 * @fn                - ManualWatering
 *
 * @brief             - used to water when the manual button is pressed, watering until completion (1 hour) or cancel button is pressed or manual button is off
 *                      
 * @param[in]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            - none
 *
 * @Note              -
 */
void ManualWatering(void)
{
  if(manualWaterButton && !(wateringFlag) )
  {
    manualWateringFlag = 1;
    // set waterirngFlag to initialize watering cycle
    wateringFlag = 1;
    // rest manual button by sending reset flag back to cayenne system    
    Notification_Reset_Manual_Button();       
  }

 // if( manualWaterButton && cancelWaterButton)
 // {
 //   StopWatering();
 // }
}

/************************************************************************************************************************************************************
 * @fn                - Watering_Cycle
 *
 * @brief             -
 *                      
 * @param[in]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            - none
 *
 * @Note              -
 */
void Watering_Cycle(void)
{


  if( (wateringFlag && autoWateringFlag) || (wateringFlag && manualWateringFlag))
  {
    // reset the timing variables once to be used for watering
    seconds = 0;
    minutes = 0;
    hours = 0;
    previousTime = millis();    
    autoWateringFlag = 0; // reset autowateringflag
    manualWateringFlag = 0; // reset manualwateringflag    
    startWateringFlag = 1;

    wateringStatus = 1;
    //Cayenne.virtualWrite(WATERING_STATUS_CHANNEL, wateringStatus);

    // Send started watering notification to user
    Notification_Started_Watering();

    // start opening the solenoid valve first to prevent pump from using its built-in pressure control valve (high amp draw)    
    digitalWrite(SPRINKLER_VALVE_RELAY ,LOW);
    delay(5000); // add a 5 second delay
  }

  // start opening the valve first  
  if( hours < 1 && startWateringFlag)
  {
    digitalWrite(SPRINKLER_VALVE_RELAY ,LOW);
    digitalWrite(PUMP_RELAY ,LOW);
    Serial.println("TURN ON RELAYS");

    if(cancelWaterButton)
    {
      StopWatering();

      // Send cancel notification to user
      // reset cancel water button by sending reset flag back to cayenne system    
      Notification_Cancel_Watering();    
    }
  }
  else if( hours > 0 && startWateringFlag)
  {    
    StopWatering();

    // Send completion notification to user
    Notification_Finished_Watering();
  }
}

/************************************************************************************************************************************************************
 * @fn                - StopWatering
 *
 * @brief             -
 *                      
 * @param[in]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            - none
 *
 * @Note              -
 */
void StopWatering(void)
{
  // switch off Sprinkler Solenoid and Pump
  digitalWrite(SPRINKLER_VALVE_RELAY ,HIGH);
  digitalWrite(PUMP_RELAY ,HIGH);  

  Serial.print("STOP WATERING");

  // reset water processs schedule button by sending reset flag back to cayenne system    
  Notification_Reset_Water_Process_Sched();

  // rest manual button by sending reset flag back to cayenne system    
  Notification_Reset_Manual_Button();

  // reset cancel water button by sending reset flag back to cayenne system    
  Notification_Cancel_Watering();

  // reset watering flags
  autoWateringFlag = 0;
  wateringFlag = 0;
  startWateringFlag = 0;

  wateringStatus = 0;

  minutes = 0;
  hours = 0;
}

/************************************************************************************************************************************************************
 * @fn                - Notification_Cancel_Watering
 *
 * @brief             - Function used to reset cancel water button by sending reset flag back to cayenne system
 *                      
 * @param[in]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            - none
 *
 * @Note              -
 */
void Notification_Cancel_Watering(void)
{
  // reset cancel water button by sending reset flag back to cayenne system
  cancelWateringState = 1; // SET cancelWateringState
  Cayenne.virtualWrite(CANCEL_WATERING_BUTTON_FLAG_CHANNEL , cancelWateringState);
  cancelWateringState = 0; // RESET cancelWateringState
}

/************************************************************************************************************************************************************
 * @fn                - Notification_Reset_Status_Check_Sched
 *
 * @brief             - Function used to reset status check schedule button by sending reset flag back to cayenne system
 *                      
 * @param[in]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            - none
 *
 * @Note              -
 */
void Notification_Reset_Status_Check_Sched(void)
{
  // reset status check schedule button by sending reset flag back to cayenne system       
  statusCheckSchedState = 1; // SET statusCheckSchedFlag  
  Cayenne.virtualWrite(STATUS_CHECK_SCHEDULE_BUTTON_FLAG_CHANNEL, statusCheckSchedState);
  statusCheckSchedState = 0; // RESET statusCheckSchedFlag

}

/************************************************************************************************************************************************************
 * @fn                - Notification_Reset_Water_Process_Sched
 *
 * @brief             - Function used to reset water processs schedule button by sending reset flag back to cayenne system
 *                      
 * @param[in]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            - none
 *
 * @Note              -
 */
void Notification_Reset_Water_Process_Sched(void)
{
  // reset water processs schedule button by sending reset flag back to cayenne system    
  waterProcessSchedState = 1; // SET waterProcessSchedState
  Cayenne.virtualWrite(WATER_PROCESS_SCHEDULE_BUTTON_FLAG_CHANNEL, waterProcessSchedState);
  waterProcessSchedState = 0; // RESET waterProcessSchedState
}

/************************************************************************************************************************************************************
 * @fn                - Notification_Reset_Manual_Button
 *
 * @brief             - Function used to rest manual button by sending reset flag back to cayenne system
 *                      
 * @param[in]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            - none
 *
 * @Note              -
 */
void Notification_Reset_Manual_Button(void)
{
  // rest manual button by sending reset flag back to cayenne system
  manualWateringState = 1; // SET manualWateringState
  Cayenne.virtualWrite(MANUAL_WATER_BUTTON_FLAG_CHANNEL, manualWateringState);
  manualWateringState = 0; // RESET manualWateringState    
}

/************************************************************************************************************************************************************
 * @fn                - Notification_Started_Watering
 *
 * @brief             - Function used to send a flag to cayenne to intialize a customised message to the user that watering has started
 *                      
 * @param[in]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            - none
 *
 * @Note              -
 */
void Notification_Started_Watering(void)
{
  // send a notification to the user that watering has started
  startedWateringState = 1; // SET startedWateringState
  Cayenne.virtualWrite(STARTED_WATERING_CHANNEL, startedWateringState);
  startedWateringState = 0; // RESET startedWateringState
}

/************************************************************************************************************************************************************
 * @fn                - Notification_Stopped_Watering
 *
 * @brief             - Function used to send a flag to cayenne to intialize a customised message to the user that watering has finished
 *                      
 * @param[in]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            - none
 *
 * @Note              -
 */
void Notification_Finished_Watering(void)
{
  // send a notification to the user that watering has finished
  finishedWateringState = 1; // SET finishedWateringState
  Cayenne.virtualWrite(FINISHED_WATERING_CHANNEL, finishedWateringState);
  finishedWateringState = 0; // RESET finishedWateringState
}

/************************************************************************************************************************************************************
 * @fn                - Notification_Watering_Tomorrow
 *
 * @brief             - Function used to send a flag to cayenne to intialize a customised message to the user that watering is scheduled tomorrow
 *                      
 * @param[in]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            - none
 *
 * @Note              -
 */
void Notification_Watering_Tomorrow(void)
{
  // send a notification to the user that watering is scheduled to occur tomorrow
  wateringSchedTomorrowState = 1; // SET wateringSchedTomorrowState
  Cayenne.virtualWrite(WATERING_SCHEDULED_TOMORROW_CHANNEL, wateringSchedTomorrowState);
  wateringSchedTomorrowState = 0; // RESET wateringSchedTomorrowState
}
```

<h2 class="text-underline">Gallery</h2>
