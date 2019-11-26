---
title: "CasaJuegos Cafe"
date: 2011-10-31
categories: [software-projects]
permalink: /:categories/:title/
feature_img: /images/software_projects/casajuegoscafe/casajuegos_img00.jpg
excerpt: "software, media entertainment, networking, gaming"
purpose: "The purpose of the project was to establish a start-up that could offer services as a modern video game arcade and an offline media-streaming hub at a location in Lilongwe, Malawi, South-East Africa."
images:
  - image_path: /images/software_projects/casajuegoscafe/casajuegos_img00.jpg
    title: XBOX 360 room
    weight: 7   
  - image_path: /images/software_projects/casajuegoscafe/casajuegos_img01.jpg
    title: First Customers
    weight: 6    
  - image_path: /images/software_projects/casajuegoscafe/casajuegos_img02.jpg
    title: Lobby pic 1
    weight: 4   
  - image_path: /images/software_projects/casajuegoscafe/casajuegos_img03.jpg
    title: Lobby pic 2
    weight: 5
  - image_path: /images/software_projects/casajuegoscafe/casajuegos_img04.jpg
    title: PS3 room
    weight: 1    
  - image_path: /images/software_projects/casajuegoscafe/casajuegos_img05.jpg
    title: Customer in the XBOX 360 room
    weight:    
  - image_path: /images/software_projects/casajuegoscafe/casajuegos_img06.jpg
    title: Customers in the Private Gaming room
    weight: 8   
  - image_path: /images/software_projects/casajuegoscafe/casajuegos_img07.jpg
    title: Private Gaming room
    weight: 2
  - image_path: /images/software_projects/casajuegoscafe/casajuegos_img08.jpg
    title: Cinema
    weight: 3    
  - image_path: /images/software_projects/casajuegoscafe/casajuegos_img09.jpg
    title:  Customers in the Cinema room 1
    weight: 9    
  - image_path: /images/software_projects/casajuegoscafe/casajuegos_img10.jpg
    title: Customers in the Cinema room 2
    weight: 10   
  - image_path: /images/software_projects/casajuegoscafe/casajuegos_img11.jpg
    title: Customers in the Cinema room 3
    weight: 11
  - image_path: /images/software_projects/casajuegoscafe/casajuegos_img12.jpg
    title: Customers in the Cinema room 4
    weight: 12   
  - image_path: /images/software_projects/casajuegoscafe/casajuegos_img13.jpg
    title: Customers in the Cinema room 5
    weight: 13   
  - image_path: /images/software_projects/casajuegoscafe/casajuegos_img14.jpg
    title: Entrance to Cafe
    weight: 14   
  - image_path: /images/software_projects/casajuegoscafe/casajuegos_img15.jpg
    title: College Tournament Trials 1
    weight: 15
  - image_path: /images/software_projects/casajuegoscafe/casajuegos_img16.jpg
    title: College Tournament Lecture Hall Presentation
    weight: 16
  - image_path: /images/software_projects/casajuegoscafe/casajuegos_img17.jpg
    title: College Tournament Trials 2
    weight: 17
  - image_path: /images/software_projects/casajuegoscafe/casajuegos_img18.jpg
    title: College Outdoor Screening Demo 1
    weight: 18
  - image_path: /images/software_projects/casajuegoscafe/casajuegos_img19.jpg
    title: College Outdoor Screening Demo 2
    weight: 19    
---
The purpose of the project was to establish a start-up that could offer services as a modern video game arcade and an offline media-streaming hub at a location in Lilongwe, Malawi, South-East Africa.

<h2 class="text-underline">Structure of the Café</h2>

<ul class="photo-gallery-2col">
  {% for image in page.images %}
    {% if image.weight >= 4 and image.weight <= 5 %}  
      <li>
        <img src="{{ image.image_path }}" alt="{{ image.title }}">
      </li>
    {% endif %}  
  {% endfor %}  
</ul>

The location was partitioned into four groups:
*	PlayStation 3 room
*	XBOX 360 room
*	Private Gaming rooms  
*	Cinema room

PlayStation 3 as well as the XBOX 360 room accommodated up to 2 users per console / screen, Private Gaming rooms accommodated up to 6 users and Cinema room up to 20 users. Private Gaming rooms offered a Gaming PC and a Nintendo Wii on a 32” inch monitor.  The Cinema room offered a PlayStation 3, XBOX 360 and Nintendo Wii on a 150” inch projected screen. All devices with the exception of the Nintendo Wii’s could access and playback the media files stored on a central media-hosting computer (Media Server PC).

<h2 class="text-underline">How it worked</h2>

The customer(s) would choose the room they desired and a game to play from the titles displayed in the lobby (with the freedom to change at any time). They would then proceed to pay for the hours and room size they required. Prices were fixed for each room size regardless of the number of users.

<ul class="photo-gallery-3col">
  {% for image in page.images %}
    {% if image.weight >= 1 and image.weight <= 3 %}  
      <li>
        <img src="{{ image.image_path }}" alt="{{ image.title }}">
      </li>
    {% endif %}  
  {% endfor %}  
</ul>

<h2 class="text-underline">Technical Requirements</h2>

**Hardware** required for the project were: *PC’s*, *Consoles*, *Wireless Controllers*, *Wireless Mice*, *Wireless Keyboards*, *24” Monitors*, *32” HDTV’s*, *HD Projectors*, *5.1 Surround Sound Speakers*, *Router*, *Switches*, *RJ45 (Ethernet) Cables*, *PC Headphones*, *Media BLU-RAYs & DVDs*, *Digital Games*, *Game Discs*, *HDMI cables* (20 metres), *VGA cables* (20 metres), *XBOX VGA adapter*, *3.5 mm to RCA cables* (20 metres), *PlayStation 3 component cable*, *wall mounts* and *ceiling mounts*.

**Software** required was *Windows 7 OS license* for each PC, *Windows Media Center* (included with Windows 7 OS), *Media Browser Server license*, *PS3 Media Server*, *Time Tracking Software*, *BLU-RAY & DVD Ripping Software* and *MetaBrowser* (Media Metadata Software).

**Decorations** used was *Wallpaper*, *Posters*, *Light Fittings* and *Promotional Material*.

The hardware, software and decorations were appropriated ahead of travel from the UK and sent to Lilongwe, Malawi through Air Freight for the project.

<h2 class="text-underline">Implementation</h2>
### Decoration
The *wallpaper* was put up, *light fittings* were installed and the wiring was routed through the ceiling to prevent trip hazards once the cargo was cleared from customs.

### Hardware
The devices (*consoles and PCs*) were centralised in one well-ventilated room (Control room) for security, networking and ease of access (change gaming media). Because *monitors* were used, the audio and video signals had to be separated from the consoles to the room were the users would sit. For the XBOX 360 room, the *XBOX VGA adapter* combined with *VGA* and *3.5 mm to RCA cables* were used to carry the signals from the Control room. In the case of the PlayStation 3 room, the *PlayStation 3 component cable* combined with the *HDMI* and the *3.5 mm to RCA cables* were used to carry the signals from the Control room. The Private Gaming rooms and the Cinema room used *HDMI cables* to the *HDTV’s* and *Projector* and then those were used to connect to *5.1 Surround Sound Speakers*.

The PCs had two user profiles each, one for the Customer and the other for Administrative duties (to prevent the customers from making modifications to the *PCs*). One PC (Media Server PC) was used as the Media Server and hosted all the Media for the Café (only accessible through administrative rights to prevent media deletion). All devices were connected through the *Router* and *Switches* to create a Local Area Network used for Media Viewing and Multiplayer Gaming.

### Software
The *ripping software* was used to extract the content from the owned *BLU-RAYs* and *DVD*. These were then stored on the *Media Server PC* separated by the content type: Movies, TV Shows and Animated Shows. The *MetaBrowser software* was used to collect media information for the content such as Poster, backdrops and actor information. *Media Browser Server* and *PS3 Media Server* were used to organize and stream to the devices on the Local Area Network. *XBOX 360* and *PCs* used Windows Media Center to interface with the media library.

*Time tracking software* was used to track the customers remaining time for each session.

<h2 class="text-underline">Gallery</h2>

<ul class="photo-gallery-2col">
  {% for image in page.images %}
    {% if image.weight >= 6 and image.weight <= 13 %}  
      <li>
        <img src="{{ image.image_path }}" alt="{{ image.title }}">
      </li>
    {% endif %}  
  {% endfor %}  
</ul>

<h2 class="text-underline">Exhibits and Road Shows</h2>

On occasion, the Café would go on the road and provide the services available to Colleges and Universities during weekends. These ranged from Movie Screenings to Video Game Tournaments with prizes.

<ul class="photo-gallery-2col">
  {% for image in page.images %}
    {% if image.weight >= 15 and image.weight <= 19 %}  
      <li>
        <img src="{{ image.image_path }}" alt="{{ image.title }}">
      </li>
    {% endif %}  
  {% endfor %}  
</ul>

facebook page link for the CasaJuegos [link](https://www.facebook.com/casajuegos/)
