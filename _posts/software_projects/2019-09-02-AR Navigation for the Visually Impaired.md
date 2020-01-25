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

The decision was made to let the user access the application’s functionalities through touch and hearing. Screen swipe gestures (*see Figure 4*) commands implemented in the <a class="custom_link" href="#touchmanagercs-script">‘**TouchManager.cs**’</a> script were used to navigate and access the applications functionalities (*see Figure 5*).
 The touch commands were incorporated with audio notifications that would inform the user of the current process being carried out or the state the application was in. This was achieved by assigning recorded notification to an ‘*AudioClip*’ object type variable and playing it back through an ‘*AudioSource*’ type object in the <a class="custom_link" href="#audiomanagercs-script">‘**AudioManager.cs**’</a> script.

Instead of just simple playback of an AudioClip, some functionalities needed custom methods to play the AudioClip objects with special behaviour. These ranged from having to play the AudioClip object with a delay in seconds (before or after), playing an AudioClip to loop specified number of times, to some that played when the device was in a specific state. ‘*ObjectDistanceAlarm()*’ function was used to give proximity sound based on the reading from the ‘*HitTest*’ distance reading. It worked by using the ‘*physDistance*’ value from the ‘*DistanceFinder()*’ function from the <a class="custom_link" href="#distancedetectionmanagercs-script">‘**DistanceDetectionManager.cs**’</a> script as a parameter and converting the number into a ‘*repeatTime*’ integer. The ‘repeatTime’ would later be used as a parameter to a coroutine that would play a single beep for every 10 units in the ‘*physDistance*’ (example the value 120 will give 12 beeps).

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

To assist with testing, Placenote’s Features Visualizer was modified (in the ‘**PlacenoteARGeneratePlane.cs**’ script) to have User interface text overlays and a ‘RayHit Indicator Quad’ GameObject used to provide visual information about the application running on a device.

#### Initializing ARKit and Placenote in Unity

In order to use Placenote’s cloud based features, an API key had to be obtained from the Placenote developer portal (www.placenote.com). This key was generated by the website once a developer account was created with Placenote’s developer portal. The API key was then placed in the LibPlacenote script element’s ‘API key’ box in the inspector panel of the unity editor.

LibPlacenote script was an element attached to the ‘**PlacenoteCameraManager.cs**’ script which was one of the objects in the ‘AR navigation’ scene (the name of the container for the Augmented Reality Navigation for the visually impaired application) in unity editor’s scene hierarchy.

A session of ARKit had to be created every time the application was run. This was done by creating an ARKit session handler and instantiating it with the ‘*GetARSessionNativeInterface()*’ function from the ‘**UnityARSessionNativeInterface.cs**’ script. This was then followed by configuring the ARKit session (ARKitWorldTrackingSessionConfiguration).

Lastly, a Listener had to be registered to the session for events published (‘*OnPose*’ and ‘*OnStatusChange*’) by the ‘**LibPlacenote.cs**’ script (Placenote) using ‘*Instance.RegisterListener()*’ function.  These settings were done in the custom <a class="custom_link" href="#mapsaveandloadmanagercs-script">‘**MapSaveAndLoadManager.cs**’</a> script.

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

This was achieved by modifying ‘**ARKitHitTesting.cs**’ [63] example code from the Placenote website to produce the ‘*AddMarker()*’ function in the <a class="custom_link" href="#markermanagercs-script">‘**MarkerManager.cs**’</a> script. ‘*AddMarker()*’ passed the camera’s centre point 2D coordinates through the ‘*ScreenToViewportPoint()*’ function to the custom ‘*AddMarkerHitTestWithResultType()*’ function to perform a HitTest. The ‘*EstimatedHorizontalPlane*’ and the ‘*FeaturePoint*’ ARHitTestResultTypes were used for the HitTest because they gave the best results when placing marker GameObjects in the scene (vertically placed ARHitTestResultTypes did not give an ideal orientation for the marker GameObjects). HitTest Pose coordinates (after a few matrix transform processes) were used to instantiate a marker model into the scene as well as add its information to the ‘*ModelObjList*’ and ‘*ModelInfoList*’ (for later reference) using the ‘*AddModel()*’ function.

#### Removing a Marker

‘*RemoveMarker()*’ function in the <a class="custom_link" href="#markermanagercs-script">‘**MarkerManager.cs**’</a> script was used to remove markers placed in the scene. This function worked by looping through the ‘*ModelObjList*’ elements to find the ‘*.name*’ (custom string entry set when instantiating marker GameObjects using the ‘*AddModel*’ function) property value that was equal to the value obtained from the object being ‘hit’ by the ray-cast’s ‘*GetInstanceID()*’ function. The matching ‘*ModelObjList*’ entry’s index was extracted and used to reference the ‘*ModelInfoList*’ to remove the objects entry as well.

#### Detecting Markers

Detecting Markers was done using ‘*MarkerDirectionFinder()*’ function in the custom <a class="custom_link" href="#markermanagercs-script">‘**MarkerManager.cs**’</a> script. This used a Physics ray-cast (unity’s world space object ray-cast) to cast a ray from the camera using the ‘*ViewportPointToRay()*’ function with vector3 coordinates that corresponded to the centre of the screen. The hit (‘*objectHit*’) data returned was checked to see if it had a Tag (word linked to a GameObject) of ‘*destinationMarker*’. If the tag returned true, then further action would be carried out like sounding off a proximity alarm, start vibration, setting a flag to start other processes and returning the distance information of the detected marker GameObject.

#### Marker Occlusion

A custom ‘*markerActivator*’ coroutine was used to only activate marker GameObjects that were within a certain range (between 1 – 5 meters) of the camera’s position using the ‘*Vector3.Distance()*’ function. The markers beyond that range were deactivated. Markers that fell within 0.60 meters of the camera were removed entirely from the current list as they were considered as already visited. A map load would reinstate the markers within the scene after a successful map re-localization.

#### Creating, Extending and Saving a Map

Marker pose data and GPS location data were the elements that made up a map. Creating a map involved starting a mapping session through Placenote’s ‘*LibPlacenote.Instance.StartSession()*’ function. Map saving used the ‘*LibPlacenote.Instance.SaveMap()*’ callback that used ‘*MapMetadataSettable()*’ function to convert marker GameObject and GPS location into a serializable format by using the JSON [64]. To extend the map, ‘*LibPlacenote.Instance.StartSession(true)*’ function with the ‘*true*’ Boolean was used. <a class="custom_link" href="#mapsaveandloadmanagercs-script">‘**MapSaveAndLoadManager.cs**’</a> script managed all the mapping functions.  

#### Map Loading

Map Loading was carried out in a similar manner as Map saving, however a different callback ‘*LibPlacenote.Instance.LoadMap*’ and the map metadata was de-serialized. In its current implementation the application would use its last used Map ID to query for a map load. This meant maps could only be loaded if they were the last one used (‘*/mapIDFile.txt*’).

#### Navigation and Distance Detection

Using the two types of ray-casting methods available (Unity's Physics and ARKit's HitTest), the user was expected to infer a path way to navigate the environment by using the information they provided as guides. **ARKit**’s *HitTest* ray-cast was used to notify the user of the distances of objects around them in the environment, while **Unity**’s *Physics* ray-cast was used to detect previously placed marker GameObjects in the AR scene. If the device was facing the direction where a marker was present, the physics ray-cast would return a ‘hit’ with the marker’s collider, notifying the user with a vibration and audio signal from the device. This gave the user an idea of the way to go. By getting within a certain range of the marker GameObject, the coroutine ‘*RadiusActivator*’ in the <a class="custom_link" href="#markermanagercs-script">‘**MarkerManager.cs**’</a> script would deactivate the current marker and activate the next marker in the scene.

### Hardware

Due to **Placenote**'s limited support at the time of the writing the thesis (03 September 2019), only *iOS* devices compatible with **ARKit** could be used. An iPhone 6s and iPad (6th Generation) were used for this project.

### Software

Code (C#) for the application is available in the <a href="#audiomanagercs-script">Appendix</a> section of this post.

The full project code with all assets for Unity, ARkit and Placenote for the <a class="custom_link" href="https://github.com/jamesjrnkhata/AR-Navigation-for-the-Visually-Impaired">*AR-Navigation-for-the-Visually-Impaired*</a> are available on <a class="custom_link" href="https://github.com/jamesjrnkhata/AR-Navigation-for-the-Visually-Impaired">GitHub</a> page.

<h2 class="text-underline">Results and Evaluation</h2>

This section discusses how **ARKit**’s distance estimation method was evaluated. When a camera image was processed by **ARKit**, a 2D point corresponded to multiple points on a 3D line and returned all the objects detected along that line depending on the ARHitTestResultType specified.

When a ‘*hit*’ occurred, **ARKit**’s HitTest returned an array that contained the intersection information for all the objects detected sorted from the closest to the camera to the furthest [44]. By using the ‘*hitResult.distance*’ property, the distance to the first point of intersection could be found which was used to determine how far the nearest obstacle in the real-space was to the camera.

The approach involved using a tape measure to establish a ground truth (exact value) for measurements between the device (running the augmented reality navigation for the visually impaired application) and an object in the real-space environment. Another measurement was then carried out simultaneously using **ARKit**’s HitTest ‘*hitResult.distance*’ property between the object and the device.  This was to be done at varied distances (0.5, 1, 1.5 and 2 meters), while using the different ARHitTestResultTypes. This expected to have two outcomes, the first was to determine the best suited ARHitTestResultType’s for each tested object type in the real-space, and the second was to determine the accuracy of the combined efforts of the ARHitTestResultTypes compared to the tape measure’s readings.

The obtained results were then later processed and the *Data Analyse* was carried out using calculations such as *Absolute Error*, *Percentage Error*, *Mean Absolute Percentage Error (MAPE)* and *Mean Absolute Deviation (MAD)*.

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

### "DistanceDetectionManager.cs" Script

```c#
using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.XR.iOS;

namespace MapSaveAndLoadManager
{
    public class DistanceDetectionManager : MonoBehaviour
    {            

        public Text physDistanceReading; // display on screen for Debugging and testing
        public double physDistance = 0;

        public GameObject rayHitIndicator; // GameObject used to indicator a HitTest intersection point
        private Pose rayHitPose; // pose type variable         
        private bool rayHitPoseIsValid = false; // flag used to indicate if a pose detected by a HitTest exists

        // Handle for enum HitTestResultTypeChoice in TouchManager
        private TouchManager _hitTest;
        void Start()
        {
            _hitTest = GetComponent<TouchManager>(); // assign the handle to the TouchManager component
        }

        // Function used to start the first part of finding the distance between the centre coordinates of the phone screen to the physical objects in the real space
        public void DistanceFinder()
            {
            float width = Screen.width / 2; // calculate the midpoint of the screen's resolution width (x coordinates)
            float height = Screen.height / 2; // calculate the midpoint of the screen's resolution height (y coordinates)

            // run ScreenToViewportPoint() function on main camera using the center of the mobile device's width and height as its parameters
            var screenPosition = Camera.main.ScreenToViewportPoint(new Vector2(width, height));
            ARPoint point = new ARPoint
            {
                x = screenPosition.x,
                y = screenPosition.y
            };
            // condition to check if the enumerator ARHitTestResultTypeChoice state is set to ExistingPlaneUsingExtent
            if (_hitTest.desiredResultType == TouchManager.ARHitTestResultTypeChoice.ExistingPlaneUsingExtent)
            {
                ARHitTestResultType resultType = ARHitTestResultType.ARHitTestResultTypeExistingPlaneUsingExtent;
                if (DistanceFinderHitTestWithResultType(point, resultType))
                {                 
                    return;
                }
            }

            // condition to check if the enumerator ARHitTestResultTypeChoice state is set to ExistingPlaneUsingGeometry
            else if (_hitTest.desiredResultType == TouchManager.ARHitTestResultTypeChoice.ExistingPlaneUsingGeometry)
            {
                ARHitTestResultType resultType = ARHitTestResultType.ARHitTestResultTypeExistingPlaneUsingGeometry;
                if (DistanceFinderHitTestWithResultType(point, resultType))
                {
                    return;
                }
            }

            // condition to check if the enumerator ARHitTestResultTypeChoice state is set to ExistingPlane
            else if (_hitTest.desiredResultType == TouchManager.ARHitTestResultTypeChoice.ExistingPlane)
            {
                ARHitTestResultType resultType = ARHitTestResultType.ARHitTestResultTypeExistingPlane;
                if (DistanceFinderHitTestWithResultType(point, resultType))
                {
                    return;
                }
            }

            // condition to check if the enumerator ARHitTestResultTypeChoice state is set to EstimatedHorizontalPlane
            else if (_hitTest.desiredResultType == TouchManager.ARHitTestResultTypeChoice.EstimatedHorizontalPlane)
            {
                ARHitTestResultType resultType = ARHitTestResultType.ARHitTestResultTypeEstimatedHorizontalPlane;
                if (DistanceFinderHitTestWithResultType(point, resultType))
                {
                    return;
                }
            }

            // condition to check if the enumerator ARHitTestResultTypeChoice state is set to EstimatedVerticalPlane
            else if (_hitTest.desiredResultType == TouchManager.ARHitTestResultTypeChoice.EstimatedVerticalPlane)
            {
                ARHitTestResultType resultType = ARHitTestResultType.ARHitTestResultTypeEstimatedVerticalPlane;
                if (DistanceFinderHitTestWithResultType(point, resultType))
                {
                    return;
                }
            }

            // condition to check if the enumerator ARHitTestResultTypeChoice state is set to FeaturePoint
            else if (_hitTest.desiredResultType == TouchManager.ARHitTestResultTypeChoice.FeaturePoint)
            {
                ARHitTestResultType resultType = ARHitTestResultType.ARHitTestResultTypeFeaturePoint;
                if (DistanceFinderHitTestWithResultType(point, resultType))
                {
                    return;
                }
            }
            // condition to check if the enumerator ARHitTestResultTypeChoice state is set to AllResultTypes
            else if (_hitTest.desiredResultType == TouchManager.ARHitTestResultTypeChoice.AllResultTypes)
            {
                // prioritize results types
                ARHitTestResultType[] resultTypes = {
                        ARHitTestResultType.ARHitTestResultTypeExistingPlaneUsingExtent,                        
                        ARHitTestResultType.ARHitTestResultTypeExistingPlaneUsingGeometry,
                        ARHitTestResultType.ARHitTestResultTypeExistingPlane,
                        ARHitTestResultType.ARHitTestResultTypeEstimatedVerticalPlane,
                        ARHitTestResultType.ARHitTestResultTypeEstimatedHorizontalPlane,
                        ARHitTestResultType.ARHitTestResultTypeFeaturePoint
                    };

                foreach (ARHitTestResultType resultType in resultTypes)
                {
                    if (DistanceFinderHitTestWithResultType(point, resultType))
                    {
                        Debug.Log("Found a hit test result");
                        return;
                    }
                }
            }

        }

        // Adapted from: "https://www.youtube.com/watch?v=Ml2UakwRxjk&t=908s" - Getting Started With ARFoundation in Unity (ARKit, ARCore)
        // Function used to complete the  DistanceFinder() functions distance detection
        bool DistanceFinderHitTestWithResultType(ARPoint point, ARHitTestResultType resultTypes)
        {
            // Perform a HitTest on the parameters of the specified screen position (point) and ARHitTestResultType (resultTypes)
            List<ARHitTestResult> hitResults = UnityARSessionNativeInterface.GetARSessionNativeInterface().HitTest(point, resultTypes); // Save the HitTest result in an ARHitTestResult List hitResults

            if (hitResults.Count > 0)
            {
                rayHitPoseIsValid = hitResults.Count > 0; // rayHitPoseIsValid if the HitTest has more than 0 hits

                foreach (var hitResult in hitResults)
                {

                    Debug.Log("Got hit!");

                    if (rayHitPoseIsValid)
                    {
                        //Transform from ARKit frame of reference to Unity World frame of reference  
                        rayHitPose.position = UnityARMatrixOps.GetPosition(hitResult.worldTransform); // HitTest results worldTransform postion coordinates
                        rayHitPose.rotation = UnityARMatrixOps.GetRotation(hitResult.worldTransform); // HitTest results worldTransform rotation coordinates

                        // the rayHitIndicator will not turn on device rotation, because the orientation is set to the direction the device was facing when ARKit started up
                        // the following three lines help to fix the rotation issue and make the rayHitIndicator turn as the device turns
                        var cameraForward = Camera.main.transform.forward;
                        var cameraBearing = new Vector3(cameraForward.x, 0, cameraForward.z).normalized;
                        rayHitPose.rotation = Quaternion.LookRotation(cameraBearing);

                        rayHitIndicator.transform.SetPositionAndRotation(rayHitPose.position, rayHitPose.rotation); // function used to simulatenously set the Position and Rotation
                        rayHitIndicator.SetActive(true); // show rayHitIndicator
                    }
                    else
                    {
                        rayHitIndicator.SetActive(false); // hide rayHitIndicator
                    }

                    physDistance = (Math.Round(hitResult.distance * 100)) / 100; // set the physDistance from hitResult.distance and round it to two decimal places
                    physDistanceReading.text = "Phys Dist: " + physDistance.ToString(); // use the physDistanceReading User Interface text object to display the distance

                    // Give an audio indicator for distance readings
                    GetComponent<AudioManager>().ObjectDistanceAlarm(physDistance); // AudioManager function ObjectDistanceAlarm() used to play distance notification sound

                    return true;
                }
            }
            else
            {
                physDistanceReading.text = " "; // Clear the "Phys Distance" reading if there is no hit
                rayHitIndicator.SetActive(false); // hide rayHitIndicator if there is no hit
            }
            return false;
        }
    }
}
```

### "MapSaveAndLoadManager.cs" Script

```c#

using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;
using UnityEngine.UI;
using UnityEngine.XR.iOS;
using System.Runtime.InteropServices;
using System.IO;
using Newtonsoft.Json.Linq;
using Newtonsoft.Json;

namespace MapSaveAndLoadManager
{
    public class MapSaveAndLoadManager : MonoBehaviour, PlacenoteListener
    {

        [SerializeField] Text mLabelText; // display on screen for Debugging and testing
        [SerializeField] PlacenoteARGeneratePlane mPlaneGenerator; // used to visual planes for debugging and testing


        // Unity ARKit Session handler
        private UnityARSessionNativeInterface mSession;

        // Handle for enum AppState in TouchManager
        private TouchManager _appState;

        private LibPlacenote.MapInfo mCurrMapInfo;   // variable used for current map info

        private string mCurrMapId; // string used to hold the last saved MapID
        private LibPlacenote.MapMetadata downloadedMetaData; // variable used for map metadata info


        private bool mARKitInit = false; // Boolean for Intializing ARKit
        private bool localizedFirstTime = false; // Boolean used to manipulate map loading behaviour

        // Use this for initialization
        void Start()
        {
            _appState = GetComponent<TouchManager>(); // assign the handle to the TouchManager component

            _appState.currentState = TouchManager.AppState.Home; // change state to AppState.Home         

            downloadedMetaData = new LibPlacenote.MapMetadata(); // assign a varaible for the MapMetadata
            Input.location.Start(); // property for accessing mobile device GPS location information

            // assign an Session instance for ARKit
            mSession = UnityARSessionNativeInterface.GetARSessionNativeInterface();
            StartARKit(); // Start ARKit using the Unity ARKit Plugin
            FeaturesVisualizer.EnablePointcloud();
            LibPlacenote.Instance.RegisterListener(this);

            // start to generate and display planes with PlacenoteARGeneratePlane's StartPlaneDetection()
            mPlaneGenerator.StartPlaneDetection();
            // check if LibPlacnote has been initialized
            if (LibPlacenote.Instance.Initialized())
            {

                GetComponent<AudioManager>().PlayAfterDelay(AudioManager.initializedAudio, 1f);
            }

        }

        // Function used to Exit the current state the application is in.
        public void OnExitClick()
        {
            if (_appState.currentState != TouchManager.AppState.MapExtend)
            {
                LibPlacenote.Instance.StopSession(); // Stop Session
            //    if(_appState.currentState != TouchManager.AppState.MapLoad)
            //    {
                    AudioManager.audioSource.PlayOneShot(AudioManager.exitAudio); // PLAY exit notification sound
            //    }
                _appState.currentState = TouchManager.AppState.Home; // change state to AppState.Home


                GetComponent<AudioManager>().AppStateNotification(); // run Audio Manager AppStateNotification() function

                FeaturesVisualizer.DisablePointcloud(); // Disable FeaturesVisualizer
                FeaturesVisualizer.clearPointcloud(); // Clear PointCloud Data
                GetComponent<MarkerManager>().ClearModels(); // Clear ModelInfoList and ModelObjList on Exit (OnExitClick)
                GetComponent<MarkerManager>().DestroyMarkers("destinationMarker"); // Clear all Marker GameObjects in the scene that have the string tag "destinationMarker"

                ConfigureSession(true, true); // continue plane detection and delete existing planes                              

            }
            else if (_appState.currentState == TouchManager.AppState.MapExtend)
            {
                _appState.currentState = TouchManager.AppState.Navigate; // change state to AppState.Navigate
                GetComponent<AudioManager>().AppStateNotification(); // run Audio Manager AppStateNotification() function

                GetComponent<MarkerManager>().InitNavigation(); // INTIALIZE MARKER ACTIVATOR OCCLUSION COROUTINE AND FUNCTIONS                            

                LibPlacenote.Instance.StartSession();
                FeaturesVisualizer.EnablePointcloud(); // re-enable pointcloud Feature Visualizer

                ConfigureSession(true, false); // Start Plane Detection, dont delete existing planes

            }
        }


        // Load map and relocalize. Check OnStatusChange function for behaviour upon relocalization
        public void OnLoadMapClicked()
        {
            _appState.currentState = TouchManager.AppState.MapLoad; // change state to AppState.MapLoad
            GetComponent<AudioManager>().AppStateNotification(); // run Audio Manager AppStateNotification() function

            LibPlacenote.Instance.StopSession();
            ConfigureSession(false, true); // Stop Plane Detection, delete existing planes
            FeaturesVisualizer.DisablePointcloud(); // disable FeaturesVisualizer

            if (!LibPlacenote.Instance.Initialized())
            {
                mLabelText.text = "SDK not yet initialized";
                return;
            }

            // Reading the last saved MapID from file
            mCurrMapId = LoadMapIDFromFile();

            LibPlacenote.Instance.LoadMap(mCurrMapId,
            (completed, faulted, percentage) =>
            {
                if (completed)
                {
                    // Get the meta data as soon as the map is downloaded
                    LibPlacenote.Instance.GetMetadata(mCurrMapId, (LibPlacenote.MapMetadata obj) =>
                    {
                        if (obj != null)
                        {
                            downloadedMetaData = obj;

                            FeaturesVisualizer.clearPointcloud(); //  clear PointCloud Data

                            // Now trying to localize the map
                            mLabelText.text = "Trying to Localize Map: " + mCurrMapId;
                            AudioManager.audioSource.PlayOneShot(AudioManager.searchingAreaAudio); // PLAY searchingAreaAudio for trying to localize notification sound
                            LibPlacenote.Instance.StartSession(); // Start the session
                        }
                        else
                        {
                            mLabelText.text = "Failed to download meta data";

                            AudioManager.audioSource.PlayOneShot(AudioManager.noMapFoundAudio); // PLAY no map information found notification sound

                            return;
                        }
                    });

                }
                else if (faulted)
                {
                    mLabelText.text = "Failed to load ID: " + mCurrMapId;

                    AudioManager.audioSource.PlayOneShot(AudioManager.loadingFailedAudio); // PLAY loading map failed notification sound

                    // Exit and go to AppState.Home
                    _appState.currentState = TouchManager.AppState.Home;
                    OnExitClick(); // Exit
                }
                else
                {
                    mLabelText.text = "Download Progress: " + percentage.ToString("F2") + "/1.0)"; // for debugging and testing
                }
            }

            );
        }

        /* COMMENTED OUT MAP DELETING AS THERE IS NO NEED FOR IT CURRENTLY. KEPT FOR FUTURE WORK
        public void OnDeleteMapClicked()
        {
            if (!LibPlacenote.Instance.Initialized())
            {
                Debug.Log("SDK not yet initialized");
                return;
            }

            mLabelText.text = "Deleting Map ID: " + mCurrMapId;
            LibPlacenote.Instance.DeleteMap(mCurrMapId, (deleted, errMsg) =>
            {
                if (deleted)
                {
                    mLabelText.text = "Deleted ID: " + mCurrMapId;
                }
                else
                {
                    mLabelText.text = "Failed to delete ID: " + mCurrMapId;
                }
            });
        }
        */

        public void OnNewMapClick()
        {
            if (!LibPlacenote.Instance.Initialized())
            {
                AudioManager.audioSource.PlayOneShot(AudioManager.notIntializedAudio); // PLAY not intialized notification sound
                Debug.Log("SDK not yet initialized");
                return;
            }

            _appState.currentState = TouchManager.AppState.MapCreate; // change state to AppState.MapCreate

            GetComponent<AudioManager>().AppStateNotification(); // run Audio Manager AppStateNotification() function

            GetComponent<MarkerManager>().ClearModels(); // Clear ModelInfoList and ModelObjList

            // start plane detection
            ConfigureSession(true, true); // Start Plane Detection, delete existing planes

            // start to generate and display planes with PlacenoteARGeneratePlane's StartPlaneDetection()
            mPlaneGenerator.StartPlaneDetection();

            FeaturesVisualizer.EnablePointcloud(); // enable FeaturesVisualizer
            LibPlacenote.Instance.StartSession(); // start session

        }

        // Initialize ARKit.
        private void StartARKit()
        {
            mLabelText.text = "Initializing ARKit"; // for debugging and testing
            Application.targetFrameRate = 60; // set framerate
            ConfigureSession(true, false); // start Start Plane Detection, do not delete existing planes
        }

        // Function used to configure the ARKit session and toggle PlaneDetection and Plane Clearing
        private void ConfigureSession(bool togglePlaneDetection, bool clearOldPlanes)
        {

            ARKitWorldTrackingSessionConfiguration config = new ARKitWorldTrackingSessionConfiguration();

            if (togglePlaneDetection)
            {
                if (UnityARSessionNativeInterface.IsARKit_1_5_Supported())
                {
                    config.planeDetection = UnityARPlaneDetection.HorizontalAndVertical;
                }
                else
                {
                    config.planeDetection = UnityARPlaneDetection.Horizontal;
                }

            }
            else
            {
                config.planeDetection = UnityARPlaneDetection.None;
            }

            if (clearOldPlanes)
            {
                mPlaneGenerator.ClearPlanes();
            }

            config.alignment = UnityARAlignment.UnityARAlignmentGravity;
            config.getPointCloudData = true;
            config.enableLightEstimation = true;
            UnityARSessionRunOption options = new UnityARSessionRunOption();
            /* DESCRIPTION OF THE CONFIG OPTIONS AVAILABLE FOR RESETTING TRACKING AND REMOVING EXISTING ANCHORS
            ARSessionRunOptionResetTracking - The session does not continue device position/ motion tracking from the previous configuration.            
            ARSessionRunOptionRemoveExistingAnchors - Any anchor objects associated with the session in its previous configuration are removed.*/

            //options = UnityARSessionRunOption.ARSessionRunOptionRemoveExistingAnchors | UnityARSessionRunOption.ARSessionRunOptionResetTracking;
            options = UnityARSessionRunOption.ARSessionRunOptionRemoveExistingAnchors;
            mSession.RunWithConfigAndOptions(config, options);

        }

        public void OnSaveMapClick()
        {
            if (!LibPlacenote.Instance.Initialized())
            {
                AudioManager.audioSource.PlayOneShot(AudioManager.notIntializedAudio); // PLAY not intialized notification sound
                Debug.Log("SDK not yet initialized");

                return;
            }

            bool useLocation = Input.location.status == LocationServiceStatus.Running;
            LocationInfo locationInfo = Input.location.lastData;

            mLabelText.text = "Saving...";
            AudioManager.audioSource.PlayOneShot(AudioManager.savingAudio); // PLAY map saving notification sound
            LibPlacenote.Instance.SaveMap(
                (mapId) =>
                {
                    LibPlacenote.Instance.StopSession();
                    FeaturesVisualizer.DisablePointcloud(); // Disable pointcloud Featture Visualizer


                    mLabelText.text = "Saved Map ID: " + mapId;

                    LibPlacenote.MapMetadataSettable metadata = CreateMetaDataObject();

                    LibPlacenote.Instance.SetMetadata(mapId, metadata, (success) =>
                    {
                        if (success)
                        {
                            mLabelText.text = "Meta data successfully saved";
                        }
                        else
                        {
                            mLabelText.text = "Meta data failed to save";
                            AudioManager.audioSource.PlayOneShot(AudioManager.errorAudio); // PLAY error notification sound
                        }
                    });

                    SaveMapIDToFile(mapId);

                },
                (completed, faulted, percentage) =>
                {

                    if (completed)
                    {
                        mLabelText.text = "Upload Complete:";
                        _appState.currentState = TouchManager.AppState.Navigate; // put app in AppState.Navigate for map following
                        GetComponent<AudioManager>().AppStateNotification(); // run Audio Manager AppStateNotification() function
                        FeaturesVisualizer.EnablePointcloud(); // re-enable pointcloud Feature Visualizer                        

                        GetComponent<MarkerManager>().InitNavigation(); // INTIALIZE MARKER ACTIVATOR OCCLUSION COROUTINE AND FUNCTIONS

                        ConfigureSession(true, false); // Start Plane Detection, dont delete existing planes

                    }
                    else if (faulted)
                    {
                        mLabelText.text = "Upload of Map failed";
                        AudioManager.audioSource.PlayOneShot(AudioManager.savingFailedAudio); // PLAY saving failed notification sound
                    }
                    else
                    {
                        mLabelText.text = "Upload Progress: " + percentage.ToString("F2") + "/1.0)";

                    }

                }
            );
        }


        public void OnExtendMapClick()
        {
            LibPlacenote.Instance.StartSession(true); // true flag is used to  extend a previously created map, after a successful localization
            _appState.currentState = TouchManager.AppState.MapExtend; // set to AppState.MapExtend
            GetComponent<AudioManager>().AppStateNotification(); // run Audio Manager AppStateNotification() function

        }


        // Function used to create Map MetaData that contains GameObject and location data
        public LibPlacenote.MapMetadataSettable CreateMetaDataObject()
        {
            LibPlacenote.MapMetadataSettable metadata = new LibPlacenote.MapMetadataSettable();

            metadata.name = "AR Nav Map";

            // get GPS location of device to save with map
            bool useLocation = Input.location.status == LocationServiceStatus.Running;
            LocationInfo locationInfo = Input.location.lastData;
            if (useLocation)
            {
                metadata.location = new LibPlacenote.MapLocation();
                metadata.location.latitude = locationInfo.latitude;
                metadata.location.longitude = locationInfo.longitude;
                metadata.location.altitude = locationInfo.altitude;
            }

            JObject userdata = new JObject(); // create JObject varaible

            // Get JSON Model data created from MarkerManager.cs
            JObject modelList = GetComponent<MarkerManager>().Models2JSON();
            userdata["modelList"] = modelList; // add to an entry field in the userdata referenced by the "modelist" string


            metadata.userdata = userdata; // assign userdata to metadata.userdata
            return metadata;
        }

        // Function used to mapid
        public void SaveMapIDToFile(string mapid)
        {
            string filePath = Application.persistentDataPath + "/mapIDFile.txt";
            StreamWriter sr = File.CreateText(filePath);
            sr.WriteLine(mapid);
            sr.Close();
        }

        // Function used to load from mapid
        public string LoadMapIDFromFile()
        {
            string savedMapID;
            // read history file
            FileInfo historyFile = new FileInfo(Application.persistentDataPath + "/mapIDFile.txt");
            StreamReader sr = historyFile.OpenText();
            string text;
            do
            {
                text = sr.ReadLine();
                if (text != null)
                {
                    // Create drawing command structure from string.
                    savedMapID = text;
                    return savedMapID;

                }
            } while (text != null);
            return null;
        }

        // Callback used to publish the computed poses along with its corresponding ARKit pose to listeners
        public void OnPose(Matrix4x4 outputPose, Matrix4x4 arkitPose) { }

        // Function used to handle status changes
        public void OnStatusChange(LibPlacenote.MappingStatus prevStatus, LibPlacenote.MappingStatus currStatus)
        {
            Debug.Log("prevStatus: " + prevStatus.ToString() + " currStatus: " + currStatus.ToString());
            if (currStatus == LibPlacenote.MappingStatus.RUNNING && prevStatus == LibPlacenote.MappingStatus.LOST)
            {

                // Placenote has successfully localized your map

                mLabelText.text = "Localized State!";

                if (!localizedFirstTime)
                {
                    //localizedFirstTime = true;

                    mLabelText.text = "Localized: loaded shapes";

                    JToken modelData = downloadedMetaData.userdata; // retrieve metadata
                    GetComponent<MarkerManager>().LoadModelsFromJSON(modelData); // load models from the JSON

                    _appState.currentState = TouchManager.AppState.Navigate; // put app in AppState.Navigate for map following
                    GetComponent<AudioManager>().AppStateNotification(); // run Audio Manager AppStateNotification() function

                    ConfigureSession(true, false); // Start Plane Detection, dont delete existing planes
                    FeaturesVisualizer.EnablePointcloud(); // enable FeatureVisualizer

                    GetComponent<MarkerManager>().InitNavigation(); // INTIALIZE MARKER ACTIVATOR OCCLUSION COROUTINE AND FUNCTIONS

                    // stops the Placenote loading session
                    LibPlacenote.Instance.StopSession();

                }
            }
            else if (currStatus == LibPlacenote.MappingStatus.RUNNING && prevStatus == LibPlacenote.MappingStatus.WAITING)
            {
                // Started a new mapping Session

                mLabelText.text = "Mapping";

            }
            else if (currStatus == LibPlacenote.MappingStatus.LOST)
            {
                // Lost map, trying to localize again

                mLabelText.text = "Searching for position lock";


            }
            else if (currStatus == LibPlacenote.MappingStatus.WAITING)
            {
                // After stop session is called.
            }
        }
    }
}
```

### "MarkerManager.cs" Script

```c#
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.EventSystems;
using UnityEngine.XR.iOS;
using Newtonsoft.Json.Linq;
using Newtonsoft.Json;
using UnityEngine.UI;

namespace MapSaveAndLoadManager
{

    // Classes to hold model information

    [System.Serializable]
    public class ModelInfo
    {
        public float px; //position.x
        public float py; //position.y
        public float pz; //position.z
        public float qx; //rotation.x
        public float qy; //rotation.y
        public float qz; //rotation.z
        public float qw; //rotation.w
        public bool visited; // flag for visited status
    }

    [System.Serializable]
    public class ModelList
    {
        public ModelInfo[] models;
    }

     // Main Class for Managing Models
    public class MarkerManager : MonoBehaviour
    {

        public GameObject modelPrefab; // 1 prefab ("marker") attached in the inspector

        public static List<ModelInfo> ModelInfoList = new List<ModelInfo>();
        public static List<GameObject> ModelObjList = new List<GameObject>();


        // UI Debugging and Testing GameObjects         
        public Text objDistanceReading;        
        public Text tagReading;        
        public float objDistance = 0;

        public static bool isMarkerFlag = false; // Flag used to toggle between detecting a marker for adding and removing
        public RaycastHit objectHit; // a public variable used to hold Physics Raycast (Unity world space) returned data

        // Handle for enum AppState in TouchManager
        private TouchManager _appState;

        Vector3 cameraPos; // User postion Vector3 (x, y and z)
        float distanceRadius = 1f; // start the distance radius to search for markers at 1 meter
        float maxDistanceRadius = 5f; // maximum distance radius set to 5 meters

        float distanceCameraToMarker = 0f; // set variable used to hold result between object to camera distance "distanceCameraToMarker" variable to 0.


        void Start()
        {
            _appState = GetComponent<TouchManager>(); // assign the handle to the TouchManager component            
        }


        void Update()
        {
            MarkerDirectionFinder(); // run the MarkerDirectionFinder() function on every update
            UserPosition(); // run the Update UserPosition() function on every update
        }

        //Function used to retrieve the position coordinates of the user in the world space
        void UserPosition()
        {
            cameraPos = Camera.main.transform.position; // current position of the camera
        }

        // Function used to check for a gameObject marker (destinationMarker) in the scene
            public void MarkerDirectionFinder()
        {      
            var screenCenter = Camera.main.ViewportPointToRay(new Vector3(0.5f, 0.5f));

            if (Physics.Raycast(screenCenter, out objectHit, maxDistanceRadius*2))
            {

                if (objectHit.transform.tag == "destinationMarker") // marker tag is set to the "marker" prefab through the inspector of Unity
                {
                    // vibrate the iPhone if a destination marker is hit by the physics raycast
                    Handheld.Vibrate();

                    // ipad DOESNT VIBRATE so if a destination marker is hit by the physics raycast play sound too.
                    GetComponent<AudioManager>().MarkerDetectionAlarm();

                    isMarkerFlag = true; // set markerFlag to true to indicate a marker has been hit by the raycast

                    objDistance = (Mathf.Round(objectHit.distance * 100)) / 100;  // set the objDistance from objectHit.distance and round it to two decimal places
                    objDistanceReading.text = "Object Dist: " + objDistance.ToString(); // display on screen for Debugging and testing
                }

            }
            else
            {
                objDistanceReading.text = " "; // clear display on screen for Debugging and testing
                //tagReading.text = " ";
                isMarkerFlag = false; // set isMarkerFlag to false when it is not hit by the raycast
            }
        }

        // The HitTest to Add a Marker
        public void AddMarker()
        {           

                Debug.Log("Not touching a UI button. Moving on.");

            // add marker object
            float width = Screen.width / 2; // calculate the midpoint of the screen's resolution width (x coordinates)
            float height = Screen.height / 2; // calculate the midpoint of the screen's resolution height (y coordinates)

            // run ScreenToViewportPoint() function on main camera using the center of the mobile device's width and height as its parameters
            var screenPosition = Camera.main.ScreenToViewportPoint(new Vector2(width, height));
            ARPoint point = new ARPoint
                {                     
                    x = screenPosition.x,
                    y = screenPosition.y
                };

                // Place Object Markers on Horizontal planes (floor placement) or FeaturePoints
                // prioritize results types
                ARHitTestResultType[] resultTypes = {
                        //ARHitTestResultType.ARHitTestResultTypeExistingPlaneUsingExtent,
                        //ARHitTestResultType.ARHitTestResultTypeExistingPlane,
                        ARHitTestResultType.ARHitTestResultTypeEstimatedHorizontalPlane,

                        //ARHitTestResultType.ARHitTestResultTypeEstimatedVerticalPlane,
                        ARHitTestResultType.ARHitTestResultTypeFeaturePoint
                    };

                foreach (ARHitTestResultType resultType in resultTypes)
                {
                    if (AddMarkerHitTestWithResultType(point, resultType))
                    {
                        Debug.Log("Found a hit test result");
                        return;
                    }
                }

        }

        // Boolean function used to carryout a ARKit hitTest and convert the Pose to Unity and Placenote's frame of reference
        bool AddMarkerHitTestWithResultType(ARPoint point, ARHitTestResultType resultTypes)
        {
            // Perform a HitTest on the parameters of the specified screen position (point) and ARHitTestResultType (resultTypes)
            List<ARHitTestResult> hitResults = UnityARSessionNativeInterface.GetARSessionNativeInterface().HitTest(point, resultTypes); // Save the HitTest result in an ARHitTestResult List hitResults

            if (hitResults.Count > 0)
            {
                foreach (var hitResult in hitResults)
                {

                    Debug.Log("Got hit!");

                    //Transform from ARKit frame of reference to Unity World frame of reference (ARKit uses right hand coordinates and Unity uses left hand coordinates)
                    Vector3 position = UnityARMatrixOps.GetPosition(hitResult.worldTransform); // HitTest results worldTransform postion coordinates
                    Quaternion rotation = UnityARMatrixOps.GetRotation(hitResult.worldTransform); // HitTest results worldTransform rotation coordinates

                    //Transform to placenote frame of reference (planes are detected in ARKit frame of reference)
                    Matrix4x4 worldTransform = Matrix4x4.TRS(position, rotation, Vector3.one); // create a translation, rotation and scale matrix (4 x 4 Matrix) using the converted unity world coordinates and Vector3(1, 1, 1)
                    Matrix4x4? placenoteTransform = LibPlacenote.Instance.ProcessPose(worldTransform); // Return a transform in the current ARKit frame transformed into the inertial frame w.r.t the current Placenote Map

                    Vector3 hitPosition = PNUtility.MatrixOps.GetPosition(placenoteTransform.Value); // Get Position coordinates from the ARKit frame coordinates
                    Quaternion hitRotation = PNUtility.MatrixOps.GetRotation(placenoteTransform.Value);  // Get Rotation coordinates from the ARKit frame coordinates

                    // create model info object
                    ModelInfo modelInfo = new ModelInfo();
                    modelInfo.px = hitPosition.x;
                    modelInfo.py = hitPosition.y;
                    modelInfo.pz = hitPosition.z;
                    modelInfo.qx = hitRotation.x;
                    modelInfo.qy = hitRotation.y;
                    modelInfo.qz = hitRotation.z;
                    modelInfo.qw = hitRotation.w;
                    modelInfo.visited = false; // set the visited object boolean to false

                    AddModel(modelInfo);

                    return true;
                }
            }
            return false;
        }

        // Function used to remove marker GameObject hit by a raycast
        public void RemoveMarker()
        {
            if (objectHit.collider != null)
            {
                if (ModelObjList != null)
                {
                    foreach (var obj in ModelObjList)
                    {
                        if (obj.name == objectHit.collider.gameObject.GetInstanceID().ToString())
                        {
                            var indexValue = ModelObjList.IndexOf(obj);
                            ModelObjList.Remove(obj);
                            Destroy(objectHit.collider.gameObject);
                            if(ModelInfoList != null)
                            {
                                ModelInfoList.RemoveAt(indexValue);
                            }
                        }
                    }
                }
            }
        }


        // Function used to initialise the InitNavigation used to control marker activation and deactivation instantiated in the map
        public void InitNavigation()
        {

            if (ModelInfoList != null)
            {
                StartCoroutine("HideAllModels"); // run coroutine (IEnumerator HideAllModels)
            }
        }

        // Function used to start ShowAllModels Coroutine
        public void ShowModelsMapExtend()
        {
            StartCoroutine("ShowAllModels");
        }

        // coroutine used to  hide all the marker GameObjects within the environment
        IEnumerator HideAllModels()
        {
            distanceRadius = 1f; // start the distance at 1 meter
            foreach (GameObject item in ModelObjList)
            {
                item.SetActive(false); // deactivate all the loaded marker gameObjects
            }            
            yield return new WaitForSeconds(0.5f);

            StartCoroutine("RadiusActivatior"); // run coroutine (IEnumerator RadiusActivatior)
        }

        // coroutine used to show all the marker GameObjects hidden within the environment
        IEnumerator ShowAllModels()
        {

            foreach (GameObject item in ModelObjList)
            {
                item.SetActive(true); // activate all the loaded marker gameObjects
            }            
            yield return new WaitForSeconds(0.5f);

        }

        // coroutine used to handle marker GameObject Occlusion and navigation session Visted markers
        // Adapted from: "https://www.youtube.com/watch?v=kvI2NmlkRUo" Unity Tutorial - Deactivate objects when far from player.
        IEnumerator RadiusActivatior()
        {

            tagReading.text = ModelInfoList.Count.ToString();
            int markersInRadiusCount = 0;
            for(int x = 0; x < ModelInfoList.Count ; x++)
            {
                // float
                distanceCameraToMarker = Vector3.Distance(cameraPos, ModelObjList[x].transform.position);
                tagReading.text = "diff: " + distanceCameraToMarker.ToString() + " visited " + ModelInfoList[x].visited;
                yield return new WaitForSeconds(2f);
                // check if any marker gameObjects are within the current distanceRadius of the camera
                if (distanceCameraToMarker < distanceRadius)
                {
                    // check if the current marker gameObject's ModelInfoList visited flag is false (I.e. that user has not navigated through it yet)
                    if (ModelInfoList[x].visited == false)
                    {
                        ModelObjList[x].SetActive(true); // activate the current marker
                        markersInRadiusCount++; // increment markersInRadiusCount whenever a marker is within distanceRadius and ModelInfoList[x].visited is false (if true it does not count)    
                    }

                }
                // if previously in range marker gameObjects are out of range of the distanceRadius
                else
                {
                    // check if the current marker gameObject's ModelInfoList visited flag is false (I.e. that user has not navigated through it yet)
                    if (ModelInfoList[x].visited == false)
                    {
                        ModelObjList[x].SetActive(false); // deactivate the current marker as it is far away to be used
                    }
                }

                // if the distance between the current gameObject marker and the user (CameraPos) is less than or equal to 60 cm
                if (distanceCameraToMarker <= 0.60f)
                {
                    ModelObjList[x].SetActive(false); // Deactivate the gameObject if its within 20 cm of the camera's position
                    ModelInfoList[x].visited = true; // Set visited flag to true
                }

            }
            // check if no gameObject markers in ModelInfoList and ModelObjList where detected in the current distanceRadius
            if (markersInRadiusCount == 0)
            {
                // if distanceRadius is less than maxDistanceRadius                
                if (distanceRadius < maxDistanceRadius)
                {
                    distanceRadius += 1f; // extend the range by 1 meter
                }
                // if distance radius is equal to maxDistanceRadius
                else if (distanceRadius == maxDistanceRadius)
                {
                    // reset distance radius to 1 meter
                    distanceRadius = 1f;
                }
            }
            tagReading.text = "Distance Radius " + distanceRadius.ToString();

            yield return new WaitForSeconds(0.5f);

            // condition to check if the currentState is still in "Navigate"
            if (_appState.currentState == TouchManager.AppState.Navigate)
            {
                StartCoroutine("RadiusActivatior"); // re-run coroutine (IEnumerator RadiusActivation)
            }

        }        

        // ADDING, DESTROYING AND JSON CONVERSION OF MARKER MODELS
        #region Create, Delete convert and Models with JSON
        // Function used to instantiate gameObjects from modelInfo as well add the information and object to the "ModelInfoList" and "ModelObjList"
        public void AddModel(ModelInfo modelInfo)
        {

            GameObject newModel = Instantiate(modelPrefab); // instantiate from [System.Serializable] prefab

            newModel.transform.position = new Vector3(modelInfo.px, modelInfo.py, modelInfo.pz); // set the position of the newModel object
            newModel.transform.rotation = new Quaternion(modelInfo.qx, modelInfo.qy, modelInfo.qz, modelInfo.qw); // set the rotation of the newModel object

            newModel.name = newModel.GetInstanceID().ToString(); // use the GetInstance() to add the unique object identifier as name property for ModelObjList important to add and remove markers without looping through            

            ModelObjList.Add(newModel); // add current model to ModelObjList            
            ModelInfoList.Add(modelInfo); // add current modelInfo to ModelInfoList
        }

        public void ClearModels()
        {
            foreach (var obj in ModelObjList)
            {
                Destroy(obj);
            }
            ModelObjList.Clear();
            ModelInfoList.Clear();
        }

        // Function used to destroy all the GameObjects in the scene that have the passed string tag name
        public void DestroyMarkers(string tag)
        {
            GameObject[] markergameObjects = GameObject.FindGameObjectsWithTag(tag);
            if(markergameObjects != null)
            {
                foreach (GameObject marker in markergameObjects)
                {
                    GameObject.Destroy(marker);
                }
            }
        }


        // Helper Functions to convert (Serialize and Deserialize) models to and from JSON objects
        // Create JSON file from "ModelInfoList"
        public JObject Models2JSON()
        {
            ModelList modelList = new ModelList();
            modelList.models = new ModelInfo[ModelInfoList.Count];
            for (int i = 0; i < ModelInfoList.Count; i++)
            {
                modelList.models[i] = ModelInfoList[i];
            }

            return JObject.FromObject(modelList);
        }

        // Load and deserialize GameObjects from mapMetadata
        public void LoadModelsFromJSON(JToken mapMetadata)
        {
            ClearModels();

            if (mapMetadata is JObject && mapMetadata["modelList"] is JObject)
            {
                ModelList modelList = mapMetadata["modelList"].ToObject<ModelList>();
                if (modelList.models == null)
                {
                    Debug.Log("no models added");
                    return;
                }

                // foreach loop used to load models from JSON back to "ModelObjList" and the scene as GameObjects
                foreach (var modelInfo in modelList.models)
                {
                    AddModel(modelInfo);
                }
            }

        }
    #endregion
    }

}
```

### "TouchManager.cs" Script

```c#
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.EventSystems;
using UnityEngine.XR.iOS;
using UnityEngine.UI;

namespace MapSaveAndLoadManager
{

    public class TouchManager : MonoBehaviour
    {
        // Create enum for the different states of the app
        public enum AppState
        {
            Home,
            MapLoad,
            MapCreate,
            Navigate,
            MapExtend
        }

        public AppState currentState; // create a variable "currentState" for the app states

        // Create enum for the different states between ARHitTestResultType Result Types for "DistanceDetectionManager.cs" Physical Distance
        public enum ARHitTestResultTypeChoice
        {
            AllResultTypes = 0,
            ExistingPlaneUsingExtent = 1,
            ExistingPlaneUsingGeometry = 2,
            ExistingPlane = 3,
            EstimatedHorizontalPlane = 4,
            EstimatedVerticalPlane = 5,
            FeaturePoint = 6
        }

        public ARHitTestResultTypeChoice desiredResultType = 0; // create a variable "desiredResultType" for the HitTestResultTypeChoice

        // Touch and Swipe
        public float maxTime = 1f; // 1 second
        public float minSwipeDist = 100; // 100 pixels
        public bool screenSwiped = false;

        float swipeDistance;
        float touchTime;

        float startTime;
        float endTime;

        Vector3 startPos;
        Vector3 endPos;

        public Text displayAppState;
        public Text displayHitTestResultTypeChoice;


        void Update()
        {
            DisplaySystemState(); // Run the DisplaySystemState() function


            // Check if the screen is touched

            // ONE FINGER TOUCH COMMANDS
            #region ONE FINGER TOUCH
            // check if only one finger is detected on the screen
            if (Input.touchCount == 1)
            {
                Touch touch = Input.GetTouch(0);
                if (touch.phase == TouchPhase.Moved)
                {
                    screenSwiped = true;
                }
                if (touch.phase == TouchPhase.Began)
                {
                    startTime = Time.time;
                    startPos = touch.position;

                }
                else if (touch.phase == TouchPhase.Ended)
                {
                    endTime = Time.time;
                    endPos = touch.position;

                    swipeDistance = (endPos - startPos).magnitude;
                    touchTime = endTime - startTime;

                    if (touchTime < maxTime && swipeDistance > minSwipeDist && screenSwiped == true)
                    {
                        Swipe();
                        screenSwiped = false;
                    }
                    else if (touchTime > 0 && touchTime < 2 && screenSwiped == false)
                    {
                           GetComponent<DistanceDetectionManager>().DistanceFinder();                        
                    }

                    else
                    {
                        screenSwiped = false;
                    }

                }
                // Screen held down with one touch
                else if (touch.phase == TouchPhase.Stationary)
                {
                    if ((Time.time - startTime) > 2)
                    {
                        GetComponent<DistanceDetectionManager>().DistanceFinder();
                    }

                }
            }
            #endregion

            // TWO FINGER TOUCH COMMANDS
            #region TWO FINGER TOUCH
            // two finger touch on the phone/tablet screen should place a marker on the EstimatedHorizontalPlane
            else if (Input.touchCount == 2)
            {
                Touch touch0 = Input.GetTouch(0);
                Touch touch1 = Input.GetTouch(1);
                if (touch0.phase == TouchPhase.Began && touch1.phase == TouchPhase.Began)
                {
                    startTime = Time.time;
                }
                else if (touch0.phase == TouchPhase.Ended || touch1.phase == TouchPhase.Ended)
                {
                    endTime = Time.time;
                    touchTime = endTime - startTime;

                    // check if the touchTime is greater than 0 , less than 2 seconds and currentState is on AppState.MapCreate or AppState.MapExtend
                    if (((touchTime > 0 && touchTime < 2) && (currentState == AppState.MapCreate || currentState == AppState.MapExtend)))
                    {
                        // Add a marker to a HitTest Result if isMarkerFlag is false
                        if (MarkerManager.isMarkerFlag == false)
                        {
                            GetComponent<MarkerManager>().AddMarker();
                        }
                        // Destroy a HitTest Result detected marker if isMarkerFlag is set to true
                        if (MarkerManager.isMarkerFlag == true)
                        {
                            GetComponent<MarkerManager>().RemoveMarker();
                        }
                    }

                    // check if the two finger touchTime is greater than 2 seconds
                    if (touchTime > 2)
                    {
                        GetComponent<AudioManager>().AppStateHelpNotifications(); // run AppStateHelpNotification() function

                    }

                }

            }
            #endregion
            // THREE FINGER TOUCH COMMANDS
            #region THREE FINGER TOUCH
            // three finger touch on the phone/tablet screen should Save the map
            else if (Input.touchCount == 3)
            {
                Touch touch0 = Input.GetTouch(0);
                Touch touch1 = Input.GetTouch(1);
                Touch touch2 = Input.GetTouch(2);
                if (touch0.phase == TouchPhase.Began && touch1.phase == TouchPhase.Began && touch2.phase == TouchPhase.Began)
                {
                    startTime = Time.time;
                }
                else if (touch0.phase == TouchPhase.Ended || touch1.phase == TouchPhase.Ended || touch2.phase == TouchPhase.Ended)
                {
                    endTime = Time.time;
                    touchTime = endTime - startTime;

                    // check if the touchTime is less than the maxTime
                    if (touchTime > 0 && touchTime < 2)
                    {
                        // Run SwitchDesiredResultType() function used to toggle between "DistanceDetectionManager.cs" HitTestResultTypeChoice for Physical Distance ARHitTestResultType Result Types:
                        // AllResultTypes = 0, ExistingPlaneUsingExtent = 1, ExistingPlane = 2, EstimatedHorizontalPlane = 3, EstimatedVerticalPlane = 4, FeaturePoint = 5

                        SwitchDesiredResultType();

                    }

                }

            }
            #endregion    
        }

        private void Swipe()
        {
            Vector2 touchDistance = endPos - startPos;

            // Horizontal Swipe
            if (Mathf.Abs(touchDistance.x) > Mathf.Abs(touchDistance.y))
            {

                // Right Swipe to create a new map (if the currentState is AppState.Home Only)
                if (touchDistance.x > 0 && currentState == AppState.Home)
                {                    
                    GetComponent<MapSaveAndLoadManager>().OnNewMapClick(); // run the OnNewMapClick() function
                    if (MarkerManager.ModelInfoList != null && MarkerManager.ModelObjList != null)
                    {
                        GetComponent<MarkerManager>().ClearModels();
                    }

                }
                // Right Swipe to extend the current map (if the currentState is AppState.Navigate)
                if (touchDistance.x > 0 && currentState == AppState.Navigate)
                {
                    // START UP CREATE MAPPING WITHOUT THE MODEL CLEARING
                    GetComponent<MapSaveAndLoadManager>().OnExtendMapClick(); // run the OnExtendMapClick() function
                    if (MarkerManager.ModelInfoList != null && MarkerManager.ModelObjList != null)
                    {
                        // REACTIVATE ALL MODELS WITHIN THE SCENE
                        GetComponent<MarkerManager>().ShowModelsMapExtend();
                    }

                }
                // Left Swipe (if the currentState is Not AppState.Home)
                if (touchDistance.x < 0 && currentState != AppState.Home)
                {                    
                     GetComponent<MapSaveAndLoadManager>().OnExitClick(); // swipe left to exit from current task
                }
            }

            // Vertical Swipe
            else if (Mathf.Abs(touchDistance.x) < Mathf.Abs(touchDistance.y))
            {

                // Up Swipe (if the currentState is AppState.MapCreate or AppState.MapExtend)
                if (touchDistance.y > 0 &&(currentState == AppState.MapCreate || currentState == AppState.MapExtend))
                {                    
                    GetComponent<MapSaveAndLoadManager>().OnSaveMapClick(); // swipe up to save map
                }
                // Down Swipe (if the currentState is AppState.Home or AppState.Navigate to prevent the user from accidentally load map during map creation or map extending )
                if (touchDistance.y < 0 && (currentState == AppState.Home || currentState == AppState.Navigate))
                {                 
                    GetComponent<MapSaveAndLoadManager>().OnLoadMapClicked(); // swipe down to load map                    
                }
            }
        }
        // Function used to toggle between HitTestResultTypeChoice Options
        public void SwitchDesiredResultType()
        {
            switch (desiredResultType)
            {
                case ARHitTestResultTypeChoice.AllResultTypes:
                    desiredResultType = ARHitTestResultTypeChoice.EstimatedHorizontalPlane;
                    break;
                case ARHitTestResultTypeChoice.EstimatedHorizontalPlane:
                    desiredResultType = ARHitTestResultTypeChoice.EstimatedVerticalPlane;
                    break;
                case ARHitTestResultTypeChoice.EstimatedVerticalPlane:
                    desiredResultType = ARHitTestResultTypeChoice.ExistingPlane;
                    break;
                case ARHitTestResultTypeChoice.ExistingPlane:
                    desiredResultType = ARHitTestResultTypeChoice.ExistingPlaneUsingExtent;
                    break;

                case ARHitTestResultTypeChoice.ExistingPlaneUsingExtent:
                    desiredResultType = ARHitTestResultTypeChoice.ExistingPlaneUsingGeometry;
                    break;

                case ARHitTestResultTypeChoice.ExistingPlaneUsingGeometry:
                    desiredResultType = ARHitTestResultTypeChoice.FeaturePoint;
                    break;
                case ARHitTestResultTypeChoice.FeaturePoint:
                    desiredResultType = ARHitTestResultTypeChoice.AllResultTypes;
                    break;
                default:
                    desiredResultType = ARHitTestResultTypeChoice.AllResultTypes;
                    break;
            }
        }
        public void DisplaySystemState()
        {
            // Condtional statements to display AppState
            if (currentState == AppState.Home)
            {
                displayAppState.text = "Mode: " + "Home";
            }
            else if (currentState == AppState.MapCreate)
            {
                displayAppState.text = "Mode: " + "Map Creation";
            }
            else if (currentState == AppState.Navigate)
            {
                displayAppState.text = "Mode: " + "Navigation";
            }
            else if (currentState == AppState.MapExtend)
            {
                displayAppState.text = "Mode: " + "Extending Map";
            }

            // Condtional statements to display selected HitTestResultTypeChoice
            if (desiredResultType == ARHitTestResultTypeChoice.AllResultTypes)
            {
                displayHitTestResultTypeChoice.text = "AllResultTypes";
            }
            else if (desiredResultType == ARHitTestResultTypeChoice.EstimatedHorizontalPlane)
            {
                displayHitTestResultTypeChoice.text = "EstimatedHorizontalPlane";
            }
            else if (desiredResultType == ARHitTestResultTypeChoice.EstimatedVerticalPlane)
            {
                displayHitTestResultTypeChoice.text = "EstimatedVerticalPlane";
            }
            else if (desiredResultType == ARHitTestResultTypeChoice.ExistingPlane)
            {
                displayHitTestResultTypeChoice.text = "ExistingPlane";
            }
            else if (desiredResultType == ARHitTestResultTypeChoice.ExistingPlaneUsingExtent)
            {
                displayHitTestResultTypeChoice.text = "ExistingPlaneUsingExtent";
            }

            else if (desiredResultType == ARHitTestResultTypeChoice.ExistingPlaneUsingGeometry)
            {
                displayHitTestResultTypeChoice.text = "ExistingPlaneUsingGeometry";
            }

            else if (desiredResultType == ARHitTestResultTypeChoice.FeaturePoint)
            {
                displayHitTestResultTypeChoice.text = "FeaturePoint";
            }

        }

    }

}
```
