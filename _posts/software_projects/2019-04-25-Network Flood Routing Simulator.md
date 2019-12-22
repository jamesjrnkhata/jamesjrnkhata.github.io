---
title: "Network Flood Routing Simulator (18 Nodes)"
date: 2019-04-25
categories: [software-projects]
permalink: /:categories/:title/
feature_img: /images/software_projects/networkfloodrouting/networkfloodrouting_img00.jpg
excerpt: "python, networking, flooding, packets, software, tkinter, threading"
purpose: "The assignment aimed at writing code in Python to simulate Flood Routing in a network with a minimum of 15 nodes and investigate the congestion caused by duplication of packets. The results obtained at each node were to be represented graphically, analysed, discussed and a proposal for a solution to reduce the duplication causing the congestion made."
toc: true
classes: wide
images:
  - image_path: /images/software_projects/networkfloodrouting/networkfloodrouting_img01.jpg
    title: "Figure 1 - Proposed Network Topology of the Flood Routing Simulation"
    weight: 1
  - image_path: /images/software_projects/networkfloodrouting/networkfloodrouting_img02.png
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
The assignment aimed at writing code in Python to simulate Flood Routing in a network with a minimum of 15 nodes and investigate the congestion caused by duplication of packets. The results obtained at each node were to be represented graphically, analysed, discussed and a proposal for a solution to reduce the duplication causing the congestion made.

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
  {% for image in page.images %}
    {% if image.weight == 1 %}
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

The nodes were represented by numbered circles and the links connecting them by the lines with characters “a” to “z” as depicted in Figure 1. To keep the network neat and uniformly structured a decision was made to have a maximum of 3-links per node.

Upon initializing the first packet within any node in Figure 1, its neighbours had to be identified to determine where the packet was to be copied to. Once this copy list was established, the packet was duplicated to be transmitted to the nodes in its copy list. The link connecting the current node to the next node was examined to see if it was being used by other nodes (since a link could be used for one-way transfer only during any time interval). If the link was in use, the copy process to that next node was suspended and that packet was modified (removed that copy list element from the current packet) and appended to the end of the current node’s buffer as a new packet until the next time interval.

When a packet was successfully transferred to the next node it was deleted from its current node and the hop count was decremented by 1 in the next node. The process was then repeated to copy the packet from its subsequent node, to its neighbour nodes (except for the node it came from) during the next time interval.

### Implementation of Flood Routing Simulator in Python

#### *State Chart for Flood Routing Simulation*

<ul class="photo-gallery">
  {% for image in page.images %}
    {% if image.weight == 2 %}
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

#### *Main storage structures used*
Decisions had to be made for the storage structures to be used for the system. The requirements were defined as follows:
*	A storage structure had to hold information for node connections and the links between them.
*	A storage structure had to hold packet information on a first in first out queue basis (FIFO queue) for the node buffers.

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

To fulfil the requirements for buffer storage two structures were used; “N_Buffer” and “N_Buffer_OrderList”. They were both made into class variables, so each Node class object could access them and change their entries.

“N_Buffer” was a nested dictionary that used a packet’s name string as its key and stored keys; “packet_status_flag”, “hop_count”, “copy_list” and “packet_history” as its entries. “packet_status_flag” was a key with the value that was used as a flag to indicate if a packet was processed to be copied to the next node or just newly copied to a node. “packet_history” held the list of nodes a packet had already visited and was used to prevent a packet from being copied back to a node it had already come from (by using the “remove_similar_nodes” static function). “copy_list” was used to hold the node numbers that a packet was to be copied to, this was determined by a function that extracted the information from the node objects (“node_process”).

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

“N_Buffer_OrderList” was a list containing 18 lists (multidimensional). Each internal list belonged to node 1 to 18 (indexed 0 to 17). The “N_Buffer_OrderList” was used to store the packet name strings and the order they were added to the node’s buffer (list).

Put together “N_Buffer” held the packet name string key with its entries (more keys and their corresponding values), while the “N_Buffer_OrderList” held the same packet name string in the order it was added to a node’s buffer. This gave a solution to storing packet information, the order it was added to node’s buffer and a way to access the information by way of packet name string. Python’s OrderedDict module could have been used to store dictionary entries in the order of being added but it was going to complicate intermediate node processes.

The packet name string adopted a naming convention that used the string prefix “pkt” concatenated to the “initiated node number” followed by “the nodes the packet had visited”. This  guaranteed that packet name strings were unique and did not overwrite entries in the “N_Buffer” nested dictionary.

The “routing_table” and “link_status” was also made into dictionaries. Nested dictionary “routing_table” held the node numbering as its keys (1 - 18), and its internal keys as references to the next node. This gave a method to map node numbers to their corresponding next nodes and their values as the name of the links between them (current node and next node). The “routing_table” map was as depicted by Figure 3.

Dictionary “link_status” held the links between the nodes as its keys and their status as its values in the network (“False” to indicate the link not in use and “True” to indicate that link was in use).

#### *User Interface to represent node buffer information*
Python’s TkInter package was used to develop the user interface for the Flood Routing Simulation program.

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

When the “Main.py” script was running, the interface shown in Figure 5 was displayed to the user.

The nodes were represented by the circles with the numbers in the middle on the canvas (the rectangle with the white background). The lines connecting the circles represented the links between the nodes. The nodes could only copy to and receive packets from the nodes they were immediately connected with.

Below the canvas (bottom rectangle) showed the “Enter Start Node” entry field, “Start” button, “Next Increment (Time + 1)” button, “Reset” button, Node 1 to Node 18 headers with label fields directly below (“Buffer Packet Count:” row label) and a “Buffer Contents:” label with a field label below it that span the page.

<div class="custom-figcaption">Table 1: Items found on the Flood Routing Simulator User Interface and their purpose</div>
| Item | Purpose |
| :-- | :------------------------------|
| “Enter Start Node” entry field | The field was used to select the node to insert the initial packet by specifying it with an integer value (1-18) |
| “Start” button | The button used to start the flood routing process once a start node was entered |
| “Next Increment (Time + 1)” button | The button used to increment time by the value of 1 |
| “Reset” button | The button used to restart the program to insert a new packet in a different start node |
| “Buffer Packet Count:” labels below Node 1 to Node 18 headers | Displayed the number of packets contained within the node’s buffer at that time |
| “Buffer Contents:” (bottom label field) | Displayed the packet name strings of the packets contained within the node that had been highlighted (by moving the mouse cursor over its corresponding node on the canvas) |


<h2 class="text-underline">Implementation</h2>

### Software
This section shows snippets from the two files (main.py and classes.py) that were used to implement the simulator in Python. Full code and full report available from <a class="custom_link" href="https://github.com/jamesjrnkhata/Network-Flood-Routing-Simulator">GitHub</a>  

**"Main.py" Code Snippet**
```python
# ----------------------------------------- START OF MAIN FUNCTION --------------------------------------------------- #

# FUNCTION USED TO LAUNCH THE USERINTERFACE
def flood_start_gui():
    # declare root as global variable to access it beyond the scope of the flood_start_gui
    global root
    # Create a tkinter object and call it root
    root = Tk()
    # -------------------------------- START OF USERINTERFACE FUNCTIONS ---------------------------------------------- #

    # -------------------------------- UserInterface General Functions ----------------------------------------------- #
    # FUNCTION USED TO DRAW CIRCLES ON THE CANVAS
    # ref: https://stackoverflow.com/questions/17985216/draw-circle-in-tkinter-python
    def create_circle(x, y, r):  # center coordinates, radius
        x0 = x - r
        y0 = y - r
        x1 = x + r
        y1 = y + r
        return canvas.create_oval(x0, y0, x1, y1, outline="black", width=2)

    # FUNCTION USED TO DRAW LINES THAT REPRESENT LINKS BETWEEN NODES ON THE CANVAS
    def create_link(x0, y0, x1, y1, orient):  # start node (x,y) to end node (x,y) coordinates and orientation
        # check to see what orientation the coordinates passed are in to adjust the line accordingly
        # when the orientation is "horizontal"
        if orient == "horizontal":
            x_start = x0 + 25  # - to adjust link to the edge of the circle and not the center
            y_start = y0
            x_finish = x1 - 25  # - to adjust link to the edge of the circle and not the center
            y_finish = y1
            return canvas.create_line(x_start, y_start, x_finish, y_finish, width=2, fill="black", dash=(2, 4))
        # when the orientation is "vertical"
        elif orient == "vertical":
            x_start = x0
            y_start = y0 + 25  # - to adjust link to the edge of the circle and not the center
            x_finish = x1
            y_finish = y1 - 25  # - to adjust link to the edge of the circle and not the center
            return canvas.create_line(x_start, y_start, x_finish, y_finish, width=2, fill="black", dash=(2, 4))
        # when the orientation is "diagonal_left" (moving from a node above to a node below on its left)
        elif orient == "diagonal-left":
            x_start = x0 - 18  # - to adjust link to the edge of the circle and not the center
            y_start = y0 + 18  # - to adjust link to the edge of the circle and not the center
            x_finish = x1 + 18  # - to adjust link to the edge of the circle and not the center
            y_finish = y1 - 18  # - to adjust link to the edge of the circle and not the center
            return canvas.create_line(x_start, y_start, x_finish, y_finish, width=2, fill="black", dash=(2, 4))
        # when the orientation is "diagonal_right" (moving from a node above to a node below on its right)
        elif orient == "diagonal-right":
            x_start = x0 + 18  # - to adjust link to the edge of the circle and not the center
            y_start = y0 + 18  # - to adjust link to the edge of the circle and not the center
            x_finish = x1 - 18  # - to adjust link to the edge of the circle and not the center
            y_finish = y1 - 18  # - to adjust link to the edge of the circle and not the center
            return canvas.create_line(x_start, y_start, x_finish, y_finish, width=2, fill="black", dash=(2, 4))

    # FUNCTION USED TO RESTRICT FUNCTIONALITY OF THE USERINTERFACE TO PREVENT ABNORMAL OPERATIONS
    def start_button_press():
        buttonmanual.config(state="normal")
        buttonreset.config(state="normal")
        buttonstart.config(state="disabled")
        entry_init.config(state="disabled")
        label_entry.config(fg="blue")

    # FUNCTION USED TO INITIALISE THE FIRST PACKET THROUGH THE USERINTERFACE AND INIT_ROUTING() NODE FUNCTION
    def gui_init_routing():
        #  use an exception handler for when non-integer or 1 - 18 range values are used
        try:
            start_node = int(entry_init.get())  # get the entry_init value and assign it to start_node
            Classes.Node.time_counter = 1  # set time_counter to 1
            # check if the value entered by the user is 1
            if start_node == 1:
                Node_1.init_routing()  # run the init_routing() function
                start_button_press()  # run the start_button_press()
            # check if the value entered by the user is 2
            elif start_node == 2:
                Node_2.init_routing()  # run the init_routing() function
                start_button_press()  # run the start_button_press()
            # check if the value entered by the user is 3
            elif start_node == 3:
                Node_3.init_routing()  # run the init_routing() function
                start_button_press()  # run the start_button_press()
            # check if the value entered by the user is 4
            elif start_node == 4:
                Node_4.init_routing()  # run the init_routing() function
                start_button_press()  # run the start_button_press()
            # check if the value entered by the user is 5
            elif start_node == 5:
                Node_5.init_routing()  # run the init_routing() function
                start_button_press()  # run the start_button_press()
            # check if the value entered by the user is 6
            elif start_node == 6:
                Node_6.init_routing()  # run the init_routing() function
                start_button_press()  # run the start_button_press()
            # check if the value entered by the user is 7
            elif start_node == 7:
                Node_7.init_routing()  # run the init_routing() function
                start_button_press()  # run the start_button_press()
            # check if the value entered by the user is 8
            elif start_node == 8:
                Node_8.init_routing()  # run the init_routing() function
                start_button_press()  # run the start_button_press()
            # check if the value entered by the user is 9
            elif start_node == 9:
                Node_9.init_routing()  # run the init_routing() function
                start_button_press()  # run the start_button_press()
            # check if the value entered by the user is 10
            elif start_node == 10:
                Node_10.init_routing()  # run the init_routing() function
                start_button_press()  # run the start_button_press()
            # check if the value entered by the user is 11
            elif start_node == 11:
                Node_11.init_routing()  # run the init_routing() function
                start_button_press()  # run the start_button_press()
            # check if the value entered by the user is 12
            elif start_node == 12:
                Node_12.init_routing()  # run the init_routing() function
                start_button_press()  # run the start_button_press()
            # check if the value entered by the user is 13
            elif start_node == 13:
                Node_13.init_routing()  # run the init_routing() function
                start_button_press()  # run the start_button_press()
            # check if the value entered by the user is 14
            elif start_node == 14:
                Node_14.init_routing()  # run the init_routing() function
                start_button_press()  # run the start_button_press()
            # check if the value entered by the user is 15
            elif start_node == 15:
                Node_15.init_routing()  # run the init_routing() function
                start_button_press()  # run the start_button_press()
            # check if the value entered by the user is 16
            elif start_node == 16:
                Node_16.init_routing()  # run the init_routing() function
                start_button_press()  # run the start_button_press()
            # check if the value entered by the user is 17
            elif start_node == 17:
                Node_17.init_routing()  # run the init_routing() function
                start_button_press()  # run the start_button_press()
            # check if the value entered by the user is 18
            elif start_node == 18:
                Node_18.init_routing()  # run the init_routing() function
                start_button_press()  # run the start_button_press()

            # if non of the values between 1 - 18 are entered
            else:
                messagebox.showinfo("Error", "An Integer between 1 - 18 must be Entered ")
            # use the display_buff_count to display the Node entries in the GUI
            display_buff_count()
        # when a wrong data type is inputted display a warning messagebox
        except ValueError:
            messagebox.showwarning("Value Error", "Only Integers between 1 - 18 can be Entered ")
```

**"Classes.py" Code Snippet**

```python
# -------------------------------- START OF NODE CLASS FUNCTIONS ------------------------------------------------- #

# FUNCTION USED TO INITIALISE VARIABLES IN THE CLASS
def __init__(self, *args):
    self.neighbor_nodes = list(args)  # variable used to unpack the tuple values passed when creating Node objects
    self.node_buff = []  # list used to temporarily hold N_Buffer information
    self.packet_data = []  # list used to work on N_Buffer information
    self.current_node = 0  # variable used to hold current node value
    self.first_buff_element = ''  # variable used to hold first buffer string name

# FUNCTION USED TO INITIALISE THE FIRST PACKET INTO THE NETWORK
def init_routing(self):
    new_packet_name = 'pkt_' + str(self.neighbor_nodes[0])  # - create initial packet name and parse it to string

    # - add initial packet to N_Buffer_OrderList
    self.N_Buffer_OrderList[self.neighbor_nodes[0] - 1] = [new_packet_name]

    # set first packet entries, packet_status_flag = False, hop_count = 10, empty copy_list and empty packet_history
    buffer_value = {
        new_packet_name: {
            "packet_status_flag": False,
            "hop_count": 10,
            "copy_list": [],
            "packet_history": []
        }
    }
    self.N_Buffer.update(buffer_value)  # update the N_Buffer with the new packet

# FUNCTION USED TO START THE SEQUENCE OF FUNCTIONS FOR EACH NODE'S PROCESSES
def run_node_routing(self):
    # Run node_process function for current node
    bool_value = self.node_process()  # - Return value is set to variable bool_value

    # Run packet_process function for current node
    # bool_value is passed through the function packet_process
    thread_copy_list = self.packet_process(bool_value)  # - Return value is set to variable thread_copy_list

    # Check if thread_copy_list is empty
    if not thread_copy_list:
        pass  # do nothing

    # else if thread_copy_list is not empty
    else:
        '''
        Run "create_copy_threads" functions and pass "thread_copy_list" as its argument.
        create_copy_threads function will create threads for the  current node (using "copy_packet" as the thread
        function and each element of the "thread_copy_list" as an argument passing through it). '''
        self.create_copy_threads(thread_copy_list)

# FUNCTION USED TO PASS IN THREAD_COPY_LIST AND CREATE THREADS FOR COPY_PACKET FUNCTION
def create_copy_threads(self, thread_copy_list):
    threads = []  # - set threads to an empty list
    # loop through contents of thread_copy_list
    for node_number in thread_copy_list:
        t = threading.Thread(target=self.copy_packet, args=(node_number,))  # pass thread function and argument
        t.daemon = True  # - the thread will die when the main thread dies
        t.start()  # - start the thread
        threads.append(t)  # - add the threads to the threads list

    # loop through the threads and run the join() function for the Main Thread to wait for them to finish executing
    for thread in threads:
        thread.join()

# STATIC FUNCTION USED TO DETERMINE ELEMENTS PRESENT IN LIST1 BUT NOT PRESENT IN LIST2
@staticmethod
def remove_similar_nodes(list1, list2):
    a = set(list1)  # - store elements of list1 into set a
    b = set(list2)  # - store elements of list2 into set b
    diff_values = list(a.difference(b))  # - determine what is available in set a but absent in set b
    return diff_values  # - return the results

# FUNCTION USED TO DELETE ENTRIES FROM N_BUFFER AND N_BUFFER_ORDERLIST OF THE CURRENT_NODE
# arguments passed are packet_name and del_type (del_type has two argument options "1" and "2")
def delete_buffer_entry(self, packet_name, del_type):
    # if the argument passed for del_type: "1" deletion from both N_Buffer and N_Buffer_OrderList of the packet_name
    if del_type == 1:
        del self.N_Buffer[packet_name]  # - delete the key in N-Buffer with the packet_name value
        temp_buff_list = self.N_Buffer_OrderList[self.current_node - 1]  # - temporarily store indexed list contents
        del temp_buff_list[0]  # - delete the first entry of the temporarily list indexed by current_node
        self.N_Buffer_OrderList[self.current_node - 1] = temp_buff_list  # - update N_Buffer_OrderList

    # if the argument passed for del_type: "2" deletion from only the N_Buffer_OrderList of the packet_name
    elif del_type == 2:
        temp_buff_list = self.N_Buffer_OrderList[self.current_node - 1]  # - temporarily store indexed list contents
        del temp_buff_list[0]  # - delete the first entry of the temporarily list indexed by current_node
        self.N_Buffer_OrderList[self.current_node - 1] = temp_buff_list  # - update N_Buffer_OrderList

        # FUNCTION USED TO EXAMINE LINK USAGE TO PROCESS PACKETS FOR COPYING INTO THE NEXT NODE
        def packet_process(self, bool_value):
            # check if node_process returned "False" after Packet deletion
            if bool_value is False:
                pass  # do nothing

            # else carry on with the "packet_process" function
            else:
                # condition to check if packet_data has information
                if len(self.packet_data) > 0:
                    # - condition to check if "packet_status_flag" is True
                    if self.packet_data[0] is True:

                        #  use an exception handler to cycle through the copy_list and process the entries for copying
                        try:
                            # Loop through the packet_data copy_list entry and extract the corresponding routing_table route
                            thread_copy_list = []  # - set thread_copy_list to an empty list
                            failed_copy_list = []  # - set failed_copy_list to an empty list
                            for x in self.packet_data[2]:
                                '''
                                index routing_table nested dict by [current node number] and [current copy_list value] "x".
                                variable "link" used to store link name retrieved from routing_table. '''
                                link = self.routing_table[self.current_node][x]

                                # check if retrieved link is currently "False" in link_status dictionary
                                if self.link_status[link] is False:
                                    self.link_status[link] = True  # - set the link to active status
                                    thread_copy_list.append(x)  # append x to thread_copy_list
                                else:
                                    failed_copy_list.append(x)  # append x to failed_copy_list

                            # if failed_copy_list is empty then copy_list has been successfully passed on to copy_packet
                            if not failed_copy_list:
                                # delete the "first_buff_element" (self.packet_data[4]) from N_Buffer and N_Buffer_orderList
                                self.delete_buffer_entry(self.packet_data[4], 1)
                            # else failed_copy_list is not empty then the nodes contained had no free links
                            else:
                                # append the packet back to the N_Buffer with the failed_copy_list as the new "copy_list"
                                # self.packet_data[4] is the first_buff_element
                                buffer_value = {
                                    self.packet_data[4]: {
                                        "packet_status_flag": self.packet_data[0],
                                        "hop_count": self.packet_data[1],
                                        "copy_list": failed_copy_list,
                                        "packet_history": self.packet_data[3]
                                    }
                                }
                                self.N_Buffer.update(buffer_value)  # update the N_Buffer with the amended copy_list
                                '''
                                append the current node's node_cache with the updated packet string to add to the end of
                                the N_BufferOrderList after the time increment '''
                                Node.update_node_cache(self.current_node, self.packet_data[4])

                                # delete the "first_buff_element" N_Buffer_OrderList entry only using del_type: 2
                                self.delete_buffer_entry(self.packet_data[4], 2)
                            return thread_copy_list  # - return thread_copy_list
                        except IndexError:
                            pass  # do nothing
```


<h2 class="text-underline">Conclusion</h2>

In this report a programme was written in Python to simulate Flood Routing in a network with 18 nodes.

The Buffer Count and Buffer Contents for each node was represented graphically through the program’s user interface. As gradual time increments were made the Buffer Count and Buffer Contents were inspected to verify the correct behaviour expected for packet copying, packet deletion and one-way use of links per time interval. The results from the experimental data showed that the program worked as intended by the proposed flood routing algorithm.

<h2 class="text-underline">Full Python Code</h2>

Full code and full report available from <a class="custom_link" href="https://github.com/jamesjrnkhata/Network-Flood-Routing-Simulator">GitHub</a>  
