---
title: "Network Flood Routing Simulator (18 Nodes)"
date: 2019-04-25
categories: [software-projects]
permalink: /:categories/:title/
feature_img: /images/software_projects/networkfloodrouting/networkfloodrouting_img00.jpg
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

<h2 class="text-underline">Procedure</h2>

## Flooding

Flooding worked by having a node forward its incoming packets to all its communication ports except for the one it arrived from. To have it redistributed, the packet had to be multiplied at the node and then forwarded to its next nodes. The exponential growth of these packets as they travelled from node to node and the restrictions of each node’s packet forwarding ability led to duplication and congestion of the network. If left uncontrolled the packets would multiply continuously and render the network unusable.

Controls could be applied to the network to minimise the effect of packet exponential growth by giving each packet a time-to-live (TTL) or hop count. Another method to make sure the packets did not multiply indefinitely was for the packet to keep track of the nodes it had visited as stated by Leon-Garcia and Widjaja (2003).

## Specifications

*	Transmissions between nodes were to be done during time intervals and each link could only be used one way.
*	The nodes were to copy the packets to their neighbour nodes except the one they received the packet from.
*	The nodes were to have buffers to store any additional packets. The buffers were to work on a first in first out queue basis (FIFO queue).
*	Each packet needed a counter for its time-to-live (n = 10), and this number had to be related to the network diameter. Network diameter was the minimum hop number between two furthest nodes according to Leon-Garcia and Widjaja (2003).
*	Packets were to be discarded once the counter reached zero.
*	A packet was to be initialised from a node (inserted) to start the flooding algorithm.

## Flood Routing Simulation Algorithm

The network topology had to take the initial hop count of 10 into consideration to fulfil the network diameter needed (minimum hop number between two furthest nodes). This meant the furthest nodes had to be about 10 connections away. To fulfil this requirement, 18 nodes were used and connected as shown in Figure 1.

    <ul class="photo-gallery">
      <li>
        <figure class="custom-figure">
          <img class="galley_img" src="{{ /images/software_projects/networkfloodrouting/networkfloodrouting_img01.jpg }}" alt="{{ Figure 1 }}">
          <figcaption class="custom-figcaption">
            Figure 1 - Proposed Network Topology of the Flood Routing Simulation
          </figcaption>
        </figure>
      </li>
    </ul>
