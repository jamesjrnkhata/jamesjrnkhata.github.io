// This example shows how to connect to Cayenne using an ESP8266 and send/receive sample data.
// Make sure you install the ESP8266 Board Package via the Arduino IDE Board Manager and select the correct ESP8266 board before compiling. 

//#define CAYENNE_DEBUG
#define CAYENNE_PRINT Serial
#include <CayenneMQTTESP8266.h>

// WiFi network info.
char ssid[] = "Allotment"; // "VM2536773"
char wifiPassword[] = "chunchine17"; // "z3sqXyvGsrwj"

// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
char username[] = "0fff8c00-b6d0-11ea-93bf-d33a96695544";
char password[] = "a0618bb99df4f82c76eb5f45e0fd60bf4f2cbbd3";
char clientID[] = "3ae1a820-ba3d-11ea-883c-638d8ce4c23d";//"96ea3650-b6e1-11ea-883c-638d8ce4c23d";

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

/*************************************************************************************************************************************************************/
 
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

 //#define USER_SCHED_WATER_BUTTON_CHANNEL              17  /*!< Used to manually schedule Watering the next day >*/
 
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
      // Start wait_five_minutes()
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
    Status_Check_Process(24);
    
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

  // Write Data to CAYENNE
  Cayenne.virtualWrite(CANCEL_WATERING_BUTTON_FLAG_CHANNEL, cancelWateringState, "digital_sensor", "d");

  // Write Data to CAYENNE
  Cayenne.virtualWrite(STATUS_CHECK_SCHEDULE_BUTTON_FLAG_CHANNEL, statusCheckSchedState); 

  // Write Data to CAYENNE
  Cayenne.virtualWrite(WATER_PROCESS_SCHEDULE_BUTTON_FLAG_CHANNEL, waterProcessSchedState);

  // Write Data to CAYENNE
  Cayenne.virtualWrite(MANUAL_WATER_BUTTON_FLAG_CHANNEL, manualWateringState);          
   
  // Write Data to CAYENNE
  Cayenne.virtualWrite(STARTED_WATERING_CHANNEL, startedWateringState, "digital_sensor", "d");   

  // Write Data to CAYENNE
  Cayenne.virtualWrite(FINISHED_WATERING_CHANNEL, finishedWateringState, "digital_sensor", "d");   
           
  // Write Data to CAYENNE
  Cayenne.virtualWrite(WATERING_SCHEDULED_TOMORROW_CHANNEL, wateringSchedTomorrowState, "digital_sensor", "d");
             
  // Write Data to CAYENNE
  Cayenne.virtualWrite(TOTAL_SAMPLE_HOURS_CHANNEL, totalSampleHours);
             
  // Write Data to CAYENNE
  Cayenne.virtualWrite(TOTAL_SAMPLE_VALUES_CHANNEL, totalSampleValues);

  // Write Data to CAYENNE
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
      
    //**DEBUG
    Serial.print("sampleValues ");
    Serial.println(sampleValue);

    Serial.print("sampleCount ");
    Serial.println(sampleCount);
    //**    
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

/*
void Flag_State_Change(uint8_t flag, uint8_t trigger)
{
  uint8_t previousState;
  uint8_t currentState;
  //1. if trigger is high then change flag
  //2. only change if trigger changes state
}

void Wait_Minutes(uint8_t waitTime)
{
  
}

void Sensor_Error_Handler(void)
{

}
*/

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
    if( Average_Soil_Moisture_Reading(75) && !(wateringFlag) )
    {
      // Soil is still wet
      // and the wateringFlag is not SET
      Reset_Moist_Sample_Collect(); // reset the hourly sensor collection  
    }
    else
    {
      // Soil is dry
      // START WATERING PROCESS (Set Auto watering flag)
      autoWateringFlag = 1;
      
      // send a notifaction to the user if watering is scheduled tomorrow
      Notification_Watering_Tomorrow();
    }
  }
  
  /*
  // USER HAS MANUALLY SCHEDULED WATERING  
  else if()
  {
      // START WATERING PROCESS (Set Auto watering flag)
      autoWateringFlag = 1;         
  }
  */
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
        Serial.println("autoWateringFlag is reset");

        // reset water processs schedule button by sending reset flag back to cayenne system    
        Notification_Reset_Water_Process_Sched();
  
        // reset cancel water button by sending reset flag back to cayenne system    
        Notification_Cancel_Watering();       
      }
      else
      {
        // set watering flag
        wateringFlag = 1;
        Serial.println("wateringFlag is set");
        Serial.println("");
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
  // delay for 5 seconds to let the pressure switch kick in and build the pressure in the pipes

  delay(5000);
  digitalWrite(PUMP_RELAY ,HIGH);  

  Serial.print("STOP WATERING");

  seconds += 5; // increment seconds by 5 to make up for the delay 

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
