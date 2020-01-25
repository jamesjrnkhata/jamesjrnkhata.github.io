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

The full Thesis on <a class="custom_link" href="https://github.com/jamesjrnkhata/AR-Navigation-for-the-Visually-Impaired">*Augmented Reality Navigation for the Visually Impaired*</a> can be found on <a class="custom_link" href="https://github.com/jamesjrnkhata/AR-Navigation-for-the-Visually-Impaired">GitHub</a>. This details the Literature Review, Methodology, Background Work, Implementation, Evaluation and Results Obtained by the auhtor (James Junior Nkhata).  
<h2 class="text-underline">Implementation</h2>

**Unity** is a real-time development platform [30]. Unity is capable of providing a developer with cross-platform features necessary to produce 3D (3 dimensional), 2D, VR (virtual reality) and Augmented Reality (AR) applications for devices running on different operating systems (Windows, iOS and Android). Unity uses hierarchy component–based design structure that can help speed up development [31]. It supports C# (C sharp) scripting API (application programming interface) natively.

**ARKit** is Apple’s proprietary SDK used to produce Augmented Reality (AR) experience by integrating iOS device camera and motion features [39].

**Placenote** is a Cloud-based mapping engine that extends ARKit functionality while providing a way to save AR content in physical locations, indoors and outdoors [49]. Placenote uses ARKit’s tracking functionality and a custom implementation of point cloud mapping and localization that provides enhanced persistence (removing reliance for ARKit’s persistence functionality) and simple to use cloud backend (manageable online as well as through Unity scripts).

The application was built using **Unity** *editor 2019.1.8f1* to manage the user interface, custom Marker *GameObject* manipulation (creation and deletion) as well as integration with the **ARKit** and **Placenote** *SDKs*. *ARKit 2.0* was used to add AR functionality to the application through *Unity-ARKit-Plugin* (only one compatible with Placenote as of the writing of this thesis). *Placenote 1.6.12* was used to add Cloud-based mapping engine to the application. *Apple’s* voice-controlled voice assistant *Siri* feature included with most post 12 October 2011 iOS devices was also an attractive feature to utilise for launching the augmented reality navigation for visually impaired application.

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

### System Overview

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
