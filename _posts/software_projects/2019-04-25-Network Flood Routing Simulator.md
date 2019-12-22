---
title: "Network Flood Routing Simulator (18 Nodes)"
date: 2019-04-25
categories: [software-projects]
permalink: /:categories/:title/
feature_img: "/images/software_projects/networkfloodrouting/networkfloodrouting_img00.jpg"
excerpt: "python, networking, flooding, packets, software, tkinter, threading"
purpose: "The assignment aimed at writing a programme in Python to simulate Flood Routing in a network with a minimum of 15 nodes and investigate the congestion caused by duplication of packets."
toc: true
classes: wide
images:
  - image_path: /images/software_projects/networkfloodrouting/networkfloodrouting_img01.jpg
    title: "Figure 1 - Proposed Network Topology of the Flood Routing Simulation"
    weight: 1
  - image_path: /images/software_projects/networkfloodrouting/networkfloodrouting_img02.jpg
    title: "Figure 2 - State Chart Diagram Depicting Concurrent Processes in Nodes 1 to 18 (Per Time Interval)"
    weight: 2
  - image_path: /images/software_projects/networkfloodrouting/networkfloodrouting_img03.jpg
    title: "Figure 3 - Choice of Main storage structures used to implement the Flood Routing Simulation Network"
    weight: 3   
  - image_path: /images/software_projects/networkfloodrouting/networkfloodrouting_img04.jpg
    title: "Figure 4 - Node objects created by passing neighbour node numbers to the Node Class __init__ function"
    weight: 4
  - image_path: /images/software_projects/networkfloodrouting/networkfloodrouting_img00.jpg
    title: "Figure 5 - Screenshot of Python’s User interface for Flood Routing Simulator using TkInter"
    weight: 5
---
<h2 class="text-underline">Purpose</h2>
The assignment aimed at writing a programme in Python to simulate Flood Routing in a network with a minimum of 15 nodes and investigate the congestion caused by duplication of packets. The results obtained at each node were to be represented graphically, analysed, discussed and a proposal for a solution to reduce the duplication causing the congestion made.

The flood routing simulation was to work using discrete time intervals, where transmissions to a neighbour node were done on each time increment.

The nodes needed a buffer that could queue additional packets generated. The nodes were to be connected to each other through links and although the links were bi-directional, only one-way transmission could be made by each link during any time interval.

Each packet was to have a counter that represented its hop-count (the amount of times the packet could be copied over before being terminated). The counter was initialised at 10 (n = 10) and decremented by ‘1’ on each hop the packet made from one node to another. If the counter reached ‘0’, the packet was to be discarded.
