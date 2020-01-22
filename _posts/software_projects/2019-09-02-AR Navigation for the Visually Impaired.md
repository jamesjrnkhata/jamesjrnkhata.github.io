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
---
The purpose of the study was to evaluate the accuracy of Augmented Reality Software Development Kit (SDK), **ARKit’s** *Ray-casting* as an approach to evaluate how far real-world objects are detected in an indoor environment.  The aim was to explore the feasibility of combining *Cloud computing* with **ARKit's** *SDK* for the purpose of obstacle avoidance and navigation for the blind using an **iOS** (*Apple* mobile operating system) mobile device.   

<h2 class="text-underline">Methodology</h2>

Augmented Reality **ARKit** *Ray-Casting* was used to detect real-world objects and place *virtual Marker GameObjects* as way points for navigation in an **AR scene**. **Unity** *Physics Ray-Casting* was used to detect the user’s previously placed Markers while audio and vibration cues give information to the user to aid in navigating the environment. **Placenote’s** *Cloud-based mapping engine* was used to provide a consistent method to store the positions of Marker objects in the *AR rendered environment*.

In similar, Monocular camera Depth estimation projects, methods have been used that involved image size ratio comparison upon movement, predictions based on semantic information and image to keyframe matching. Most related projects of mobile device navigation solutions have required external sensors, embedded beacon placement, pre-exiting building plans to familiarise the device to the environment.

<h2 class="text-underline">Background Work</h2>

### Augmented reality

### AR Cloud computing

### Raycasting

<h2 class="text-underline">Implementation</h2>

The application was built using **Unity** *editor 2019.1.8f1* to manage the user interface, custom *Marker GameObject* manipulation (creation and deletion) as well as integration with the **ARKit** and **Placenote** *SDKs*. *ARKit 2.0* was used to add AR functionality to the application through *Unity-ARKit-Plugin* (only one compatible with Placenote as of the writing of this thesis). *Placenote 1.6.12* was used to add Cloud-based mapping engine to the application. *Apple’s* voice-controlled voice assistant *Siri* [53] feature included with most post 12 October 2011 iOS devices was also an attractive feature to utilise for launching the augmented reality navigation for visually impaired application.
