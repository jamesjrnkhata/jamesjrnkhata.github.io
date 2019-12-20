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
---
<h2 class="text-underline">Purpose</h2>
The assignment aimed at writing a programme in Python to simulate Flood Routing in a network with a minimum of 15 nodes and investigate the congestion caused by duplication of packets. The results obtained at each node were to be represented graphically, analysed, discussed and a proposal for a solution to reduce the duplication causing the congestion made.

The flood routing simulation was to work using discrete time intervals, where transmissions to a neighbour node were done on each time increment.

The nodes needed a buffer that could queue additional packets generated. The nodes were to be connected to each other through links and although the links were bi-directional, only one-way transmission could be made by each link during any time interval.

Each packet was to have a counter that represented its hop-count (the amount of times the packet could be copied over before being terminated). The counter was initialised at 10 (n = 10) and decremented by ‘1’ on each hop the packet made from one node to another. If the counter reached ‘0’, the packet was to be discarded.

<h2 class="text-underline">Procedure</h2>


<h2 class="text-underline">Implementation</h2>

<h2 class="text-underline">Conclusion</h2>
