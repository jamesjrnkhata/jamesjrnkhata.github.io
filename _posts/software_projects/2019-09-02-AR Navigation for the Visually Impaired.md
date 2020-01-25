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
    weight: 2     
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


The full Thesis (and citations) on <a class="custom_link" href="https://github.com/jamesjrnkhata/AR-Navigation-for-the-Visually-Impaired">*Augmented Reality Navigation for the Visually Impaired (Thesis)*</a> can be found on <a class="custom_link" href="https://github.com/jamesjrnkhata/AR-Navigation-for-the-Visually-Impaired">GitHub</a> page. This details the Literature Review, Methodology, Background Work, Implementation, Evaluation and Results Obtained by the auhtor (James Junior Nkhata).  
<h2 class="text-underline">Implementation</h2>

**Unity** is a real-time development platform [30]. Unity is capable of providing a developer with cross-platform features necessary to produce 3D (3 dimensional), 2D, VR (virtual reality) and Augmented Reality (AR) applications for devices running on different operating systems (Windows, iOS and Android). Unity uses hierarchy component–based design structure that can help speed up development [31]. It supports C# (C sharp) scripting API (application programming interface) natively.

**ARKit** is Apple’s proprietary SDK used to produce Augmented Reality (AR) experience by integrating iOS device camera and motion features [39].

**Placenote** is a Cloud-based mapping engine that extends ARKit functionality while providing a way to save AR content in physical locations, indoors and outdoors [49]. Placenote uses ARKit’s tracking functionality and a custom implementation of point cloud mapping and localization that provides enhanced persistence (removing reliance for ARKit’s persistence functionality) and simple to use cloud backend (manageable online as well as through Unity scripts).

The application was built using **Unity** *editor 2019.1.8f1* to manage the user interface, custom Marker *GameObject* manipulation (creation and deletion) as well as integration with the **ARKit** and **Placenote** *SDKs*. *ARKit 2.0* was used to add AR functionality to the application through *Unity-ARKit-Plugin* (only one compatible with Placenote as of the writing of this thesis). *Placenote 1.6.12* was used to add Cloud-based mapping engine to the application. *Apple’s* voice-controlled voice assistant *Siri* feature included with most post 12 October 2011 iOS devices was also an attractive feature to utilise for launching the augmented reality navigation for visually impaired application.

### System Overview

<ul class="photo-gallery-3col">
  {% for image in page.images %}
    {% if image.weight == 3 %}
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

#### Initializing ARKit and Placenote in Unity

In order to use Placenote’s cloud based features, an API key had to be obtained from the Placenote developer portal (www.placenote.com). This key was generated by the website once a developer account was created with Placenote’s developer portal. The API key was then placed in the LibPlacenote script element’s ‘API key’ box in the inspector panel of the unity editor. LibPlacenote script was an element attached to the ‘PlacenoteCameraManager.cs’ script which was one of the objects in the ‘AR navigation’ scene (the name of the container for the Augmented Reality Navigation for the visually impaired application) in unity editor’s scene hierarchy.  A session of ARKit had to be created every time the application was run. This was done by creating an ARKit session handler and instantiating it with the ‘GetARSessionNativeInterface()’ function from the ‘UnityARSessionNativeInterface.cs’ script. This was then followed by configuring the ARKit session (ARKitWorldTrackingSessionConfiguration). Plane Detection (both horizontal and vertical) through the ‘UnityARPlaneDetection.cs’ script, ‘UnityARAlignmentGravity’ (aligning the session with device’s gravity sensor data for use with plane detection) through the ‘UnityARAlignment’ enumeration (y-axis matches the direction of gravity as detected by the device’s motion sensing hardware) [54], ‘getPointCloudData’ and ‘enableLightEstimation’ were set to true and ‘targetFrameRate’ set to 60 frames per second. Lastly, a Listener had to be registered to the session for events published (‘OnPose’ and ‘OnStatusChange’) by the ‘LibPlacenote.cs’ script (Placenote) using ‘Instance.RegisterListener()’ function.  These settings were done in the custom ‘MapSaveAndLoadManager.cs’ script.

#### Marker GameObjects

#### Adding a Marker

#### Detecting Markers

#### Marker Occlusion

#### Creating, Extending and Saving a Map

#### Navigation and Distance Detection 

### User interface

As the application was intended for individuals that are blind, a suitable interface had to be designed to make it accessible.

The application was given a short product name of ‘AR Nav App’ through unity’s ‘Project Settings – Player – Product Name’ entry field. This allowed the user to launch the deployed application on an AR supported iOS device by using a short voice command (‘launch AR Nav’) through Apple’s Siri assistant.

The decision was made to let the user access the application’s functionalities through touch and hearing. Screen swipe gestures (**see FIGURE** ) commands implemented in the ‘TouchManager.cs’ script were used to navigate and access the applications functionalities as illustrated in **Fig 7**. The touch commands were incorporated with audio notifications that would inform the user of the current process being carried out or the state the application was in. This was achieved by assigning recorded notification to an ‘AudioClip’ object type variable and playing it back through an ‘AudioSource’ type object in the ‘AudioManager.cs’ script. Instead of just simple playback of an AudioClip, some functionalities needed custom methods to play the AudioClip objects with special behaviour. These ranged from having to play the AudioClip object with a delay in seconds (before or after), playing an AudioClip to loop specified number of times, to some that played when the device was in a specific state. ‘ObjectDistanceAlarm()’ function was used to give proximity sound based on the reading from the ‘HitTest’ distance reading. It worked by using the ‘physDistance’ value from the ‘DistanceFinder()’ function from the ‘DistanceDetectionManager.cs’ script as a parameter and converting the number into a ‘repeatTime’ integer. The ‘repeatTime’ would later be used as a parameter to a coroutine that would play a single beep for every 10 units in the ‘physDistance’ (example the value 120 will give 12 beeps).

<ul class="photo-gallery-3col">
  {% for image in page.images %}
    {% if image.weight == 4 %}
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

#### Debugging and Testing Interface

To assist with testing, Placenote’s Features Visualizer, modified ‘PlacenoteARGeneratePlane.cs’ script (that does not save planes), User interface text overlays and a ‘RayHit Indicator Quad’ GameObject were used to provide visual information about the deployed application running on a device.


### Hardware



### Software


Full code available from <a class="custom_link" href="https://github.com/jamesjrnkhata/AR-Navigation-for-the-Visually-Impaired">GitHub</a> page (<a class="custom_link" href="https://github.com/jamesjrnkhata/AR-Navigation-for-the-Visually-Impaired">AR-Navigation-for-the-Visually-Impaired</a>).

<h2 class="text-underline">Results and Evaluation</h2>

In this section, the author discussed how ARKit’s distance estimation method was evaluated. When a camera image was processed by ARKit, a 2D point corresponded to multiple points on a 3D line and returned all the objects detected along that line depending on the ARHitTestResultType specified.

When a ‘hit’ occurred, ARKit’s HitTest returned an array that contained the intersection information for all the objects detected sorted from the closest to the camera to the furthest [44]. By using the ‘hitResult.distance’ property, the distance to the first point of intersection could be found which was used to determine how far the nearest obstacle in the real-space was to the camera.

The approach involved using a tape measure to establish a ground truth (exact value) for measurements between the device (running the augmented reality navigation for the visually impaired application) and an object in the real-space environment. Another measurement was then carried out simultaneously using ARKit’s HitTest ‘hitResult.distance’ property between the object and the device.  This was to be done at varied distances (0.5, 1, 1.5 and 2 meters), while using the different ARHitTestResultTypes. This expected to have two outcomes, the first was to determine the best suited ARHitTestResultType’s for each tested object type in the real-space, and the second was to determine the accuracy of the combined efforts of the ARHitTestResultTypes compared to the tape measure’s readings.

The obtained results were then later processed and the *Data Analysed* using calculations such as **Absolute Error**, **Percentage Error**, **Mean Absolute Percentage Error (MAPE)** and **Mean Absolute Deviation (MAD)**.

<ul class="photo-gallery-3col">
  {% for image in page.images %}
    {% if image.weight >= 1 and image.weight <= 3 %}
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

The full set of results obtained can be found on <a class="custom_link" href="https://github.com/jamesjrnkhata/AR-Navigation-for-the-Visually-Impaired">*Augmented Reality Navigation for the Visually Impaired (Thesis)*</a> can be found on <a class="custom_link" href="https://github.com/jamesjrnkhata/AR-Navigation-for-the-Visually-Impaired">GitHub</a> page.

<h2 class="text-underline">Discussion</h2>

*Tape Measure Method*

 From the calculations carried out from the recorded results, the author suspected there were inaccuracies experienced because of the method of manually holding the tape measure with the device running the application. This led to slight hand movements that altered the readings. Another error in our readings came from the inconsistencies in the area where the RayHit Indicator Quad was placed and a reading was taken. They were instances were different areas had to be used for similar pairs because a reading could not be obtained depending on the type of ARHitTestType that was being used.

 The in-depth discussion of the project can be found on <a class="custom_link" href="https://github.com/jamesjrnkhata/AR-Navigation-for-the-Visually-Impaired">*Augmented Reality Navigation for the Visually Impaired (Thesis)*</a> can be found on <a class="custom_link" href="https://github.com/jamesjrnkhata/AR-Navigation-for-the-Visually-Impaired">GitHub</a> page.

 <h2 class="text-underline">Conclusion</h2>

The study investigated the feasibility of a mobile device application for iOS devices to assist visually impaired individuals navigate through indoor environment using audio and vibration feedback. The usability and limitations of the interface was determined, and future work recommended to be carried out. The research findings suggest that it is possible to accurately measure the distance between a mobile device’s monocular camera and the physical objects in the real-world environment using Augmented Reality (AR) ARKit SDK’s Ray-casting, hence, the more studies required to address the gaps in existing knowledge.
