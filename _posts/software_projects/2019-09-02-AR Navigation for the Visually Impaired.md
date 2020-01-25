---
title: "Augmented Reality Navigation for the Blind"
date: 2019-09-02
categories: [software-projects]
permalink: /:categories/:title/
feature_img: /images/software_projects/arnavigationfortheblind/arnavigationfortheblind_img00.jpg
excerpt: "c#, arkit, unity, assistive technology, ar, xcode, blind, navigation, cloud, placenote, travelling aid"
purpose: "The purpose of this study was to develop a Mobile device Augmented Reality based Assistive Technology (AT) for indoor navigation by blind users. Augmented Reality ARKit Ray-Casting is used to detect real-world objects and place virtual Marker GameObjects as way points for navigation in an AR scene."
toc: true
classes: wide
images:
  - image_path: /images/software_projects/arnavigationfortheblind/arnavigationfortheblind_img01.jpg
    title: "Figure 1 - 2D representation of an object’s projection on to a view plane viewed from a viewpoint"
    weight: 1   
  - image_path: /images/software_projects/arnavigationfortheblind/arnavigationfortheblind_img02.jpg
    title: "Figure 2 - In gravity-only alignment, X and Z directions are relative to the device's initial orientation"
    weight: 2  
  - image_path: /images/software_projects/arnavigationfortheblind/arnavigationfortheblind_img03.jpg
    title: "Figure 3 - AR Navigation for the Viusally Impaired Overview"
    weight: 3   
  - image_path: /images/software_projects/arnavigationfortheblind/arnavigationfortheblind_img04.jpg
    title: "Figure 4 - Touch Commands and their corresponding actions (for each mode)"
    weight: 4
  - image_path: /images/software_projects/arnavigationfortheblind/arnavigationfortheblind_img05.jpg
    title: "Figure 5 - AR Navigation User Interface state changes using touch screen swipes"
    weight: 5    
  - image_path: /images/software_projects/arnavigationfortheblind/arnavigationfortheblind_img06.jpg
    title: "Figure 6 - Marker GameObject used as a waypoint"
    weight: 6
  - image_path: /images/software_projects/arnavigationfortheblind/arnavigationfortheblind_img07.jpg
    title: "Figure 7 - Distance Detection to Object 1 (Canvas on Wall)"
    weight: 7
  - image_path: /images/software_projects/arnavigationfortheblind/arnavigationfortheblind_img08.jpg
    title: "Figure 8 - Distance Detection to Object 2 (Sofa)"
    weight: 8  
  - image_path: /images/software_projects/arnavigationfortheblind/arnavigationfortheblind_img00.jpg
    title: "Figure 9 - Distance Detection to Object 3 (Ride on Toy Car)"
    weight: 9
  - image_path: /images/software_projects/arnavigationfortheblind/arnavigationfortheblind_img09.jpg
    title: "Figure 10 - Distance Detection to Object 4 (Backpack) "
    weight: 10                            
---
The purpose of the study was to evaluate the accuracy of Augmented Reality Software Development Kit (SDK), **ARKit’s** *Ray-casting* as an approach to detect how far real-world objects are in an indoor environment.  The aim was to explore the feasibility of combining *Cloud Computing* with **ARKit's** *SDK* for the purpose of obstacle avoidance and navigation for the blind using an **iOS** (*Apple* mobile operating system) mobile device.   

<h2 class="text-underline">Methodology</h2>

Augmented Reality **ARKit** *Ray-Casting* was used to detect real-world objects and place *virtual Marker GameObjects* as way points for navigation in an *AR scene*. **Unity** *Physics Ray-Casting* was used to detect the user’s previously placed Markers while audio and vibration cues give information to the user to aid in navigating the environment. **Placenote’s** *Cloud-based mapping engine* was used to provide a consistent method to store the positions of Marker objects in the *AR rendered environment*.

In similar, Monocular camera Depth estimation projects, methods have been used that involved image size ratio comparison upon movement, predictions based on semantic information and image to keyframe matching. Most related projects of mobile device navigation solutions have required external sensors, embedded beacon placement, pre-exiting building plans to familiarise the device to the environment.

<h2 class="text-underline">Background Work</h2>

### Augmented Reality
Spatial computing is a way a human can interact with a device that stores and manipulates references to real objects [15]. Augmented reality is a form of Spatial computing that works on two fundamental concepts, identifying features [16] and being able to track and recognize the environment from camera frames. In AR, devices use a process called Simultaneous Localization and Mapping (SLAM) to know more about its position in the world.

SLAM is a popular model used in robotics for autonomy. Landmarks are detected using sensors and these are compared with a map to localize the robot while trying to add other detected landmarks to the map according to Shelley [17].  

### AR Cloud Computing
Cloud AR is the latest trend in AR computing as it provides a solution to multi user AR experience and can be attested by the many start-up companies working on AR Cloud solutions of their own [21].

### Ray-casting
Ray-casting is a useful way of detecting objects within the scene based on its onscreen image [35].

<ul class="photo-gallery-2col">
  {% for image in page.images %}
    {% if image.weight >= 1 and image.weight <= 2 %}
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


The full Thesis (and citations) on <a class="custom_link" href="https://github.com/jamesjrnkhata/AR-Navigation-for-the-Visually-Impaired">*Augmented Reality Navigation for the Visually Impaired (Thesis)*</a> can be found on <a class="custom_link" href="https://github.com/jamesjrnkhata/AR-Navigation-for-the-Visually-Impaired">GitHub</a> page. This details the Literature Review, Methodology, Background Work, Implementation, Evaluation and Results Obtained by the author (James Junior Nkhata).  
<h2 class="text-underline">Implementation</h2>

**Unity** is a real-time development platform [30]. Unity is capable of providing a developer with cross-platform features necessary to produce 3D (3 dimensional), 2D, VR (virtual reality) and Augmented Reality (AR) applications for devices running on different operating systems (Windows, iOS and Android). Unity uses hierarchy component–based design structure that can help speed up development [31]. It supports C# (C sharp) scripting API (application programming interface) natively.

**ARKit** is Apple’s proprietary SDK used to produce Augmented Reality (AR) experience by integrating iOS device camera and motion features [39].

**Placenote** is a Cloud-based mapping engine that extends ARKit functionality while providing a way to save AR content in physical locations, indoors and outdoors [49]. Placenote uses ARKit’s tracking functionality and a custom implementation of point cloud mapping and localization that provides enhanced persistence (removing reliance for ARKit’s persistence functionality) and simple to use cloud backend (manageable online as well as through Unity scripts).

The application was built using **Unity** *editor 2019.1.8f1* to manage the user interface, custom Marker *GameObject* manipulation (creation and deletion) as well as integration with the **ARKit** and **Placenote** *SDKs*. *ARKit 2.0* was used to add AR functionality to the application through *Unity-ARKit-Plugin* (only one compatible with Placenote as of the writing of this thesis). *Placenote 1.6.12* was used to add Cloud-based mapping engine to the application. *Apple’s* voice-controlled voice assistant *Siri* feature included with most post 12 October 2011 iOS devices was also an attractive feature to utilise for launching the augmented reality navigation for visually impaired application.

### System Overview

<ul class="photo-gallery">
  {% for image in page.images %}
    {% if image.weight == 3 %}
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

#### User interface

As the application was intended for individuals that are blind, a suitable interface had to be designed to make it accessible.

The application was given a short product name of ‘AR Nav App’ through unity’s ‘Project Settings – Player – Product Name’ entry field. This allowed the user to launch the deployed application on an AR supported iOS device by using a short voice command (‘launch AR Nav’) through Apple’s Siri assistant.

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

The decision was made to let the user access the application’s functionalities through touch and hearing. Screen swipe gestures (*see Figure 4*) commands implemented in the ‘TouchManager.cs’ script were used to navigate and access the applications functionalities (*see Figure 5*).
 The touch commands were incorporated with audio notifications that would inform the user of the current process being carried out or the state the application was in. This was achieved by assigning recorded notification to an ‘AudioClip’ object type variable and playing it back through an ‘AudioSource’ type object in the ‘AudioManager.cs’ script.

Instead of just simple playback of an AudioClip, some functionalities needed custom methods to play the AudioClip objects with special behaviour. These ranged from having to play the AudioClip object with a delay in seconds (before or after), playing an AudioClip to loop specified number of times, to some that played when the device was in a specific state. ‘ObjectDistanceAlarm()’ function was used to give proximity sound based on the reading from the ‘HitTest’ distance reading. It worked by using the ‘physDistance’ value from the ‘DistanceFinder()’ function from the ‘DistanceDetectionManager.cs’ script as a parameter and converting the number into a ‘repeatTime’ integer. The ‘repeatTime’ would later be used as a parameter to a coroutine that would play a single beep for every 10 units in the ‘physDistance’ (example the value 120 will give 12 beeps).

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

#### Debugging and Testing Interface

To assist with testing, Placenote’s Features Visualizer was modified (in the ‘PlacenoteARGeneratePlane.cs’ script) to have User interface text overlays and a ‘RayHit Indicator Quad’ GameObject used to provide visual information about the application running on a device.

#### Initializing ARKit and Placenote in Unity

In order to use Placenote’s cloud based features, an API key had to be obtained from the Placenote developer portal (www.placenote.com). This key was generated by the website once a developer account was created with Placenote’s developer portal. The API key was then placed in the LibPlacenote script element’s ‘API key’ box in the inspector panel of the unity editor.

LibPlacenote script was an element attached to the ‘PlacenoteCameraManager.cs’ script which was one of the objects in the ‘AR navigation’ scene (the name of the container for the Augmented Reality Navigation for the visually impaired application) in unity editor’s scene hierarchy.

A session of ARKit had to be created every time the application was run. This was done by creating an ARKit session handler and instantiating it with the ‘GetARSessionNativeInterface()’ function from the ‘UnityARSessionNativeInterface.cs’ script. This was then followed by configuring the ARKit session (ARKitWorldTrackingSessionConfiguration).

Lastly, a Listener had to be registered to the session for events published (‘OnPose’ and ‘OnStatusChange’) by the ‘LibPlacenote.cs’ script (Placenote) using ‘Instance.RegisterListener()’ function.  These settings were done in the custom ‘MapSaveAndLoadManager.cs’ script.

#### Marker GameObjects

One of the fundamental elements required to enable the visually impaired individual to navigate an area was the ability to add, remove and detect Marker GameObjects in the environment without using their sight. The GameObject used as the marker was a custom created 3D object of x, y and z dimensions (1, 0.6, and 0.6) in meters with position coordinates of (0, 1, 0 in x, y and z). The y-axis position value of 1 made sure that the marker was placed at least a meter above the y-axis of the unity world coordinates. The marker template was saved in the "*Assets/Scene/ARNavigation/Models/Marker*" folder as a *prefab* (prefabricated object) which could later be placed within an AR scene through screen touch commands.

To allow the user to interact with the marker beyond placing it in an AR environment, a box collider was added to the centre coordinate (0, 0, 0) of the marker GameObject of size 0.8 x 2.34 x 1.6 (x, y and z) (*demonstrated in Figure 6*). This allowed the object to respond to physics ray-cast (Unity) collisions as the box collider would be identified as an extension of the geometry of the marker GameObject.

<ul class="photo-gallery">
  {% for image in page.images %}
    {% if image.weight == 6 %}
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

#### Adding a Marker

This was achieved by modifying ‘**ARKitHitTesting.cs**’ [63] example code from the Placenote website to produce the ‘*AddMarker()*’ function in the ‘**MarkerManager.cs**’ script. ‘*AddMarker()*’ passed the camera’s centre point 2D coordinates through the ‘*ScreenToViewportPoint()*’ function to the custom ‘*AddMarkerHitTestWithResultType()*’ function to perform a HitTest. The ‘*EstimatedHorizontalPlane*’ and the ‘*FeaturePoint*’ ARHitTestResultTypes were used for the HitTest because they gave the best results when placing marker GameObjects in the scene (vertically placed ARHitTestResultTypes did not give an ideal orientation for the marker GameObjects). HitTest Pose coordinates (after a few matrix transform processes) were used to instantiate a marker model into the scene as well as add its information to the ‘*ModelObjList*’ and ‘*ModelInfoList*’ (for later reference) using the ‘*AddModel()*’ function.

#### Removing a Marker

‘*RemoveMarker()*’ function in the ‘**MarkerManager.cs**’ script was used to remove markers placed in the scene. This function worked by looping through the ‘*ModelObjList*’ elements to find the ‘*.name*’ (custom string entry set when instantiating marker GameObjects using the ‘*AddModel*’ function) property value that was equal to the value obtained from the object being ‘hit’ by the ray-cast’s ‘*GetInstanceID()*’ function. The matching ‘*ModelObjList*’ entry’s index was extracted and used to reference the ‘*ModelInfoList*’ to remove the objects entry as well.

#### Detecting Markers

Detecting Markers was done using ‘*MarkerDirectionFinder()*’ function in the custom ‘**MarkerManager.cs**’ class. This used a Physics ray-cast (unity’s world space object ray-cast) to cast a ray from the camera using the ‘*ViewportPointToRay()*’ function with vector3 coordinates that corresponded to the centre of the screen. The hit (‘*objectHit*’) data returned was checked to see if it had a Tag (word linked to a GameObject) of ‘*destinationMarker*’. If the tag returned true, then further action would be carried out like sounding off a proximity alarm, start vibration, setting a flag to start other processes and returning the distance information of the detected marker GameObject.

#### Marker Occlusion

A custom ‘*markerActivator*’ coroutine was used to only activate marker GameObjects that were within a certain range (between 1 – 5 meters) of the camera’s position using the ‘*Vector3.Distance()*’ function. The markers beyond that range were deactivated. Markers that fell within 0.60 meters of the camera were removed entirely from the current list as they were considered as already visited. A map load would reinstate the markers within the scene after a successful map re-localization.

#### Creating, Extending and Saving a Map

Marker pose data and GPS location data were the elements that made up a map. Creating a map involved starting a mapping session through Placenote’s ‘*LibPlacenote.Instance.StartSession()*’ function. Map saving used the ‘*LibPlacenote.Instance.SaveMap()*’ callback that used ‘*MapMetadataSettable()*’ function to convert marker GameObject and GPS location into a serializable format by using the JSON [64]. To extend the map, ‘*LibPlacenote.Instance.StartSession(true)*’ function with the ‘*true*’ Boolean was used. ‘**MapSaveAndLoadManager.cs**’ script managed all the mapping functions.  

#### Map Loading

Map Loading was carried out in a similar manner as Map saving, however a different callback ‘*LibPlacenote.Instance.LoadMap*’ and the map metadata was de-serialized. In its current implementation the application would use its last used Map ID to query for a map load. This meant maps could only be loaded if they were the last one used (‘*/mapIDFile.txt*’).

#### Navigation and Distance Detection

Using the two types of ray-casting methods available (Unity's Physics and ARKit's HitTest), the user was expected to infer a path way to navigate the environment by using the information they provided as guides. **ARKit**’s *HitTest* ray-cast was used to notify the user of the distances of objects around them in the environment, while **Unity**’s *Physics* ray-cast was used to detect previously placed marker GameObjects in the AR scene. If the device was facing the direction where a marker was present, the physics ray-cast would return a ‘hit’ with the marker’s collider, notifying the user with a vibration and audio signal from the device. This gave the user an idea of the way to go. By getting within a certain range of the marker GameObject, the coroutine ‘*RadiusActivator*’ in the ‘**MarkerManager.cs**’ script would deactivate the current marker and activate the next marker in the scene.

### Hardware

Due to **Placenote**'s limited support at the time of the writing the thesis (03 September 2019), only *iOS* devices compatible with **ARKit** could be used. An iPhone 6s and iPad (6th Generation) were used for this project.

### Software

Full code available from <a class="custom_link" href="https://github.com/jamesjrnkhata/AR-Navigation-for-the-Visually-Impaired">GitHub</a> page (<a class="custom_link" href="https://github.com/jamesjrnkhata/AR-Navigation-for-the-Visually-Impaired">AR-Navigation-for-the-Visually-Impaired</a>).

<h2 class="text-underline">Results and Evaluation</h2>

This section discusses how **ARKit**’s distance estimation method was evaluated. When a camera image was processed by **ARKit**, a 2D point corresponded to multiple points on a 3D line and returned all the objects detected along that line depending on the ARHitTestResultType specified.

When a ‘*hit*’ occurred, **ARKit**’s HitTest returned an array that contained the intersection information for all the objects detected sorted from the closest to the camera to the furthest [44]. By using the ‘*hitResult.distance*’ property, the distance to the first point of intersection could be found which was used to determine how far the nearest obstacle in the real-space was to the camera.

The approach involved using a tape measure to establish a ground truth (exact value) for measurements between the device (running the augmented reality navigation for the visually impaired application) and an object in the real-space environment. Another measurement was then carried out simultaneously using **ARKit**’s HitTest ‘*hitResult.distance*’ property between the object and the device.  This was to be done at varied distances (0.5, 1, 1.5 and 2 meters), while using the different ARHitTestResultTypes. This expected to have two outcomes, the first was to determine the best suited ARHitTestResultType’s for each tested object type in the real-space, and the second was to determine the accuracy of the combined efforts of the ARHitTestResultTypes compared to the tape measure’s readings.

The obtained results were then later processed and the *Data Analysed* using calculations such as **Absolute Error**, **Percentage Error**, **Mean Absolute Percentage Error (MAPE)** and **Mean Absolute Deviation (MAD)**.

<ul class="photo-gallery-2col">
  {% for image in page.images %}
    {% if image.weight >= 7 and image.weight <= 8 %}
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

<ul class="photo-gallery-2col">
  {% for image in page.images %}
    {% if image.weight >= 9 and image.weight <= 10 %}
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

The full set of results obtained from <a class="custom_link" href="https://github.com/jamesjrnkhata/AR-Navigation-for-the-Visually-Impaired">*Augmented Reality Navigation for the Visually Impaired (Thesis)*</a> can be found on <a class="custom_link" href="https://github.com/jamesjrnkhata/AR-Navigation-for-the-Visually-Impaired">GitHub</a> page.

<h2 class="text-underline">Discussion</h2>

*Tape Measure Method*

 From the calculations carried out from the recorded results, the author suspected there were inaccuracies experienced because of the method of manually holding the tape measure with the device running the application. This led to slight hand movements that altered the readings. Another error in our readings came from the inconsistencies in the area where the RayHit Indicator Quad was placed and a reading was taken. They were instances were different areas had to be used for similar pairs because a reading could not be obtained depending on the type of ARHitTestType that was being used.

 The in-depth discussion of the <a class="custom_link" href="https://github.com/jamesjrnkhata/AR-Navigation-for-the-Visually-Impaired">*Augmented Reality Navigation for the Visually Impaired (Thesis)*</a> can be found on <a class="custom_link" href="https://github.com/jamesjrnkhata/AR-Navigation-for-the-Visually-Impaired">GitHub</a> page.

 <h2 class="text-underline">Conclusion</h2>

The study investigated the feasibility of a mobile device application for iOS devices to assist visually impaired individuals navigate through indoor environment using audio and vibration feedback. The usability and limitations of the interface was determined, and future work recommended to be carried out. The research findings suggest that it is possible to accurately measure the distance between a mobile device’s monocular camera and the physical objects in the real-world environment using Augmented Reality (AR) ARKit SDK’s Ray-casting, hence, the more studies required to address the gaps in existing knowledge.

<h2 class="text-underline">Appendix</h2>

### "AudioManager.cs" Script

```c#
using UnityEngine;
using System.Collections;

namespace MapSaveAndLoadManager
{
    public class AudioManager : MonoBehaviour
    {

        // handle for AppState
        private TouchManager _appState;         


        public static AudioClip areaIdentifiedAudio; // Area Identified Audio

        public static AudioClip beepAudio; // Beep Audio

        public static AudioClip buzzAudio; // Buzz Audio

        public static AudioClip createMapAudio; // Create Map Audio

        public static AudioClip errorAudio; // Error Audio

        public static AudioClip exitAudio; // Exit Audio             

        public static AudioClip extendingMapAudio; // Extending Map Audio

        public static AudioClip helpAudio; // Help Audio

        public static AudioClip helpMapCreationAudio; // Help Map Creation Audio

        public static AudioClip helpExtendingMapAudio; // Help Extending Map Audio

        public static AudioClip helpMainMenuAudio; // Help Main Menu Audio

        public static AudioClip helpNavigationModeAudio; // Help Navigation Mode Audio

        public static AudioClip initializedAudio; // Intialized Audio

        public static AudioClip initializingAudio; // Intializing Audio

        public static AudioClip loadingFailedAudio; // Loading Failed Audio

        public static AudioClip loadingMapAudio; // Loading Map Audio

        public static AudioClip mainMenuAudio; // Main Menu Audio

        public static AudioClip navigationMarkersLoadedAudio; // Navigation Markers Loaded Audio

        public static AudioClip navigationScreenAudio; // Navigation Screen Audio

        public static AudioClip noMapFoundAudio; // No Map Found Audio

        public static AudioClip notIntializedAudio; // Not Initialized Audio

        public static AudioClip poorLightingAudio; // Poor Lighting Audio

        public static AudioClip savingAudio; // Saving Audio

        public static AudioClip savingFailedAudio; // Saving Failed Audio

        public static AudioClip searchingAreaAudio; // Searching Area Audio

        // create an AudioSource Handler
        public static AudioSource audioSource;

        private bool isAudioPlayed = false;


        void Awake()
        {
            areaIdentifiedAudio = Resources.Load<AudioClip>("Audio/AreaIdentified"); // Area Identified Audio (Assets/Resources/Audio/AreaIdentified.mp3)
            beepAudio = Resources.Load<AudioClip>("Audio/beep_default"); // Beep Audio (Assets/Resources/Audio/beep_default.mp3)
            buzzAudio = Resources.Load<AudioClip>("Audio/buzz"); // Buzz Audio (Assets/Resources/Audio/buzz.mp3)
            createMapAudio = Resources.Load<AudioClip>("Audio/CreateMap"); // Create Map Audio (Assets/Resources/Audio/CreateMap.mp3)
            errorAudio = Resources.Load<AudioClip>("Audio/Error"); // Error Audio (Assets/Resources/Audio/Error.mp3)
            exitAudio = Resources.Load<AudioClip>("Audio/Exit"); // Exit Audio (Assets/Resources/Audio/Exit.mp3)
            extendingMapAudio = Resources.Load<AudioClip>("Audio/ExtendingMap"); // Extending Map Audio (Assets/Resources/Audio/ExtendingMap.mp3)
            helpAudio = Resources.Load<AudioClip>("Audio/Help"); // Help Audio (Assets/Resources/Audio/Help.mp3)
            helpMapCreationAudio = Resources.Load<AudioClip>("Audio/Help_MapCreation"); // Help Map Creation Audio (Assets/Resources/Audio/Help_ MapCreation.mp3)
            helpExtendingMapAudio = Resources.Load<AudioClip>("Audio/Help_ExtendingMap"); // Help Extending Map Audio (Assets/Resources/Audio/Help_ExtendingMap.mp3)
            helpMainMenuAudio = Resources.Load<AudioClip>("Audio/Help_MainMenu"); // Help Main Menu Audio (Assets/Resources/Audio/Help_MainMenu.mp3)
            helpNavigationModeAudio = Resources.Load<AudioClip>("Audio/Help_NavigationMode2"); // Help Navigation Mode Audio (Assets/Resources/Audio/Help_NavigationMode2.mp3)
            initializedAudio = Resources.Load<AudioClip>("Audio/Initialized"); // Intialized Audio (Assets/Resources/Audio/Initialized.mp3)
            initializingAudio = Resources.Load<AudioClip>("Audio/Initializing"); // Intializing Audio (Assets/Resources/Audio/Initializing.mp3)
            loadingFailedAudio = Resources.Load<AudioClip>("Audio/LoadingFailed"); // Loading Failed Audio (Assets/Resources/Audio/LoadingFailed.mp3)
            loadingMapAudio = Resources.Load<AudioClip>("Audio/LoadingMap"); // Loading Map Audio (Assets/Resources/Audio/LoadingMap.mp3)
            mainMenuAudio = Resources.Load<AudioClip>("Audio/MainMenu"); // Main Menu Audio (Assets/Resources/Audio/MainMenu.mp3)
            navigationMarkersLoadedAudio = Resources.Load<AudioClip>("Audio/NavigationMarkersLoaded"); // Navigation Markers Loaded Audio (Assets/Resources/Audio/NavigationMarkersLoaded.mp3)
            navigationScreenAudio = Resources.Load<AudioClip>("Audio/NavigationScreen"); // Navigation Screen Audio (Assets/Resources/Audio/NavigationScreen.mp3)
            noMapFoundAudio = Resources.Load<AudioClip>("Audio/NoMapFound"); // No Map Found Audio (Assets/Resources/Audio/NoMapFound.mp3)
            notIntializedAudio = Resources.Load<AudioClip>("Audio/NotIntialized"); // Not Initialized Audio (Assets/Resources/Audio/NotIntialized.mp3)
            poorLightingAudio = Resources.Load<AudioClip>("Audio/PoorLighting"); // Poor Lighting Audio (Assets/Resources/Audio/PoorLighting.mp3)
            savingAudio = Resources.Load<AudioClip>("Audio/Saving"); // Saving Audio (Assets/Resources/Audio/Saving.mp3)
            savingFailedAudio = Resources.Load<AudioClip>("Audio/SavingFailed"); // Saving Failed Audio (Assets/Resources/Audio/SavingFailed.mp3)
            searchingAreaAudio = Resources.Load<AudioClip>("Audio/SearchingArea"); // Searching Area Audio (Assets/Resources/Audio/SearchingArea.mp3)

            audioSource = GetComponent<AudioSource>(); // assign the handle to the AudioSource component   

            audioSource.PlayOneShot(initializingAudio); // play initializingAudio
            PlayAfterDelay(helpAudio, 6f); // PLAY prompt on how to acess help information after 6 second delay from app start
        }
        void Start()
        {


            _appState = GetComponent<TouchManager>(); // assign the handle to the _appState    

            PlayAfterDelay(mainMenuAudio, 2f); // PLAY main menu notification sound after 2 second delay
        }


        public void AppStateNotification()
        {
            if (_appState.currentState == TouchManager.AppState.Home)
            {
                PlayAfterDelay(mainMenuAudio, 1f); // PLAY main menu notification sound after 1 second delay
            }

            if (_appState.currentState == TouchManager.AppState.MapLoad)
            {
                PlayAfterDelay(loadingMapAudio, 1f); // PLAY map load notification sound after 1 second delay
            }

            if (_appState.currentState == TouchManager.AppState.MapCreate)
            {
                PlayAfterDelay(createMapAudio, 1f); // PLAY map create notification sound after 1 second delay
            }

            if (_appState.currentState == TouchManager.AppState.Navigate)
            {
                PlayAfterDelay(navigationScreenAudio, 1f); // PLAY navigation mode notification sound after 1 second delay
            }

            if (_appState.currentState == TouchManager.AppState.MapExtend)
            {
                PlayAfterDelay(extendingMapAudio, 1f); // PLAY map extending notification sound after 1 second delay
            }
        }

        public void AppStateHelpNotifications()
        {           
            if (_appState.currentState == TouchManager.AppState.Home)
            {
                // PLAY Main Menu Help Audio
                audioSource.PlayOneShot(helpMainMenuAudio);                
            }

            if (_appState.currentState == TouchManager.AppState.MapCreate)
            {
                // PLAY Map Creation Help
                audioSource.PlayOneShot(helpMapCreationAudio);
            }

            if (_appState.currentState == TouchManager.AppState.Navigate)
            {
                // PLAY Navigation Mode Help
                audioSource.PlayOneShot(helpNavigationModeAudio);
            }

            if (_appState.currentState == TouchManager.AppState.MapExtend)
            {
                // PLAY Extending Map Help
                audioSource.PlayOneShot(helpExtendingMapAudio);
            }            
        }

        // Function used to take physDistance and play proximity sound based on distance
        public void ObjectDistanceAlarm(double physDistance)
        {
            // check if the distance reading is greater than 0
            if (physDistance > 0)
            {
                float metersToCm = (float)physDistance * 100f; // convert decimal value in meters to float value in centimeters
                float CmtoTime = Mathf.Round(metersToCm / 20f); // divide by 10f to get a single beep for every 10cm
                                                                //or divide by 20f to get a single beep for every 20 cm
                int repeatTime = Mathf.FloorToInt(CmtoTime); // convert the results into an integer

                if (!isAudioPlayed)
                {
                    StartCoroutine(PlaySoundWithLoopValue(beepAudio, repeatTime)); // start the PlaySoundWithLoopValue coroutine with repeatTime
                }                
            }
        }

        // Function used to notify when a marker has been detected by the Physics raycast
        public void MarkerDetectionAlarm()
        {
            audioSource.PlayOneShot(buzzAudio, .1f); // Play buzzAudio at Volume 10

        }

        // Function used to start the Coroutine "PlaySoundWithDelay" with a delay before the clip
        public void PlayAfterDelay(AudioClip clip, float delay)
        {
            StartCoroutine(PlaySoundWithDelay(clip, delay, false));
        }

        // Coroutine used to play a passed audio clip with a float delay value and a boolean "false" to play the clip after the delay and "true" to play the clip before the delay.
        public IEnumerator PlaySoundWithDelay(AudioClip clip, float delay, bool isPlayBeforeDelay)
        {
            if (isPlayBeforeDelay)
            {
                audioSource.PlayOneShot(clip);
                yield return new WaitForSeconds(delay);                
            }
            else
            {
                yield return new WaitForSeconds(delay);
                audioSource.PlayOneShot(clip);
            }            
        }
        // coroutine used to loop through a clip with a second pause in between
        public IEnumerator PlaySoundWithLoop(AudioClip clip)
        {                           
            audioSource.PlayOneShot(clip);
            yield return new WaitForSeconds(1f);
            StartCoroutine(PlaySoundWithLoop(clip));                        
        }

        //coroutine used to repeat a clip while disabling any further play back until it completes
        public IEnumerator PlaySoundWithLoopValue(AudioClip clip, int repeatTime)
        {
            for (int x = 0; x < repeatTime; x++)
            {
                isAudioPlayed = true;
                audioSource.PlayOneShot(clip);
                yield return new WaitForSeconds(0.3f);               
            }
            yield return new WaitForSeconds(1f);
            isAudioPlayed = false;            
        }
    }
}
```
