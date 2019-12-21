# -------------------------------------------------------------------------------------------------------------------- #
# -------------------- Computer and Communication Networks (2018 - 2019): Coursework Assignment ---------------------- #
# ------------------------------------ FLOOD ROUTING (18 NODE NETWORK) ----------------------------------------------- #
# ------------------------------------ Instructor:  Dr John Easton --------------------------------------------------- #
# ------------------------------------ Written by:	James J Nkhata --------------------------------------------------- #
# -------------------------------- Student Number:	         --------------------------------------------------------- #
# -------------------------------------------------------------------------------------------------------------------- #
# --------------------------------------------- Classes.py (2 of 2) -------------------------------------------------- #

# ------------------------------------------ Module Imports ---------------------------------------------------------- #
import threading  # used to import threading
# -------------------------------------------------------------------------------------------------------------------- #

# -------------------------------------- Start of Node Class --------------------------------------------------------- #


# NODE CLASS INHERITING FROM THREADING.THREAD
class Node(threading.Thread):

    # --------------------------------- Defining Structure for Network Topology -------------------------------------- #
    # Nested dictionary holding the routing_table (map of connections between nodes and link names)
    routing_table = {
        1: {2: "a", 3: "b"},  # - key "1" refers to current node, internal key "2" to next node and value "a" to link
        2: {1: "a", 3: "c", 6: "d"},
        3: {1: "b", 2: "c", 4: "e"},
        4: {3: "e", 5: "h", 6: "f"},
        5: {4: "h", 8: "i", 9: "j"},
        6: {2: "d", 4: "f", 7: "g"},
        7: {6: "g", 11: "n", 12: "o"},
        8: {5: "i", 9: "k", 11: "m"},
        9: {5: "j", 8: "k", 10: "l"},
        10: {9: "l", 11: "p", 13: "q"},
        11: {7: "n", 8: "m", 10: "p"},
        12: {7: "o", 13: "r", 14: "s"},
        13: {10: "q", 12: "r", 14: "t"},
        14: {12: "s", 13: "t", 15: "u"},
        15: {14: "u", 16: "v", 17: "w"},
        16: {15: "v", 17: "x", 18: "y"},
        17: {15: "w", 16: "x", 18: "z"},
        18: {16: "y", 17: "z"}
    }
    # Dictionary holding the status of links
    link_status = {
        "a": False, "b": False, "c": False, "d": False, "e": False, "f": False, "g": False, "h": False, "i": False,
        "j": False, "k": False, "l": False, "m": False, "n": False, "o": False, "p": False, "q": False, "r": False,
        "s": False, "t": False, "u": False, "v": False, "w": False, "x": False, "y": False, "z": False
    }

    # Dictionary to hold packet information as they are added to to the Buffer
    # N_Buffer = dict("name": {"packet_status_flag": FALSE, "hop_count": 0, "copy_list": [0], "packet_history": [0]})
    N_Buffer = dict()

    # Ordered List to simplify indexing and key information of N_Buffer
    # Initialise an empty list of 18 lists to store the order of each nodes N_Buffer's entries
    N_Buffer_OrderList = [[], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], []]

    # initialise temp node_cache lists for each node used to hold the packet names during each time interval
    node1_cache = []
    node2_cache = []
    node3_cache = []
    node4_cache = []
    node5_cache = []
    node6_cache = []
    node7_cache = []
    node8_cache = []
    node9_cache = []
    node10_cache = []
    node11_cache = []
    node12_cache = []
    node13_cache = []
    node14_cache = []
    node15_cache = []
    node16_cache = []
    node17_cache = []
    node18_cache = []

    time_counter = 0  # variable used to display the Time Increments
    # ---------------------------------------------------------------------------------------------------------------- #

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

    # CLASS FUNCTION USED TO TEMPORARILY HOLD THE ORDER OF THE PACKETS BEFORE UPDATING N_BUFFER_ORDERLIST
    @classmethod
    def update_node_cache(cls, node_number,  new_packet_name):

        # Check the argument node_number value passed through the function
        # if node_number is 1
        if node_number == 1:
            cls.node1_cache.append(new_packet_name)  # append the new_packet_name string to node1_cache
        # if node_number is 2
        elif node_number == 2:
            cls.node2_cache.append(new_packet_name)  # append the new_packet_name string to node2_cache
        # if node_number is 3
        elif node_number == 3:
            cls.node3_cache.append(new_packet_name)  # append the new_packet_name string to node3_cache
        # if node_number is 4
        elif node_number == 4:
            cls.node4_cache.append(new_packet_name)  # append the new_packet_name string to node4_cache
        # if node_number is 5
        elif node_number == 5:
            cls.node5_cache.append(new_packet_name)  # append the new_packet_name string to node5_cache
        # if node_number is 6
        elif node_number == 6:
            cls.node6_cache.append(new_packet_name)  # append the new_packet_name string to node6_cache
        # if node_number is 7
        elif node_number == 7:
            cls.node7_cache.append(new_packet_name)  # append the new_packet_name string to node7_cache
        # if node_number is 8
        elif node_number == 8:
            cls.node8_cache.append(new_packet_name)  # append the new_packet_name string to node8_cache
        # if node_number is 9
        elif node_number == 9:
            cls.node9_cache.append(new_packet_name)  # append the new_packet_name string to node9_cache
        # if node_number is 10
        elif node_number == 10:
            cls.node10_cache.append(new_packet_name)  # append the new_packet_name string to node10_cache
        # if node_number is 11
        elif node_number == 11:
            cls.node11_cache.append(new_packet_name)  # append the new_packet_name string to node11_cache
        # if node_number is 12
        elif node_number == 12:
            cls.node12_cache.append(new_packet_name)  # append the new_packet_name string to node12_cache
        # if node_number is 13
        elif node_number == 13:
            cls.node13_cache.append(new_packet_name)  # append the new_packet_name string to node13_cache
        # if node_number is 14
        elif node_number == 14:
            cls.node14_cache.append(new_packet_name)  # append the new_packet_name string to node14_cache
        # if node_number is 15
        elif node_number == 15:
            cls.node15_cache.append(new_packet_name)  # append the new_packet_name string to node15_cache
        # if node_number is 16
        elif node_number == 16:
            cls.node16_cache.append(new_packet_name)  # append the new_packet_name string to node16_cache
        # if node_number is 17
        elif node_number == 17:
            cls.node17_cache.append(new_packet_name)  # append the new_packet_name string to node17_cache
        # if node_number is 18
        elif node_number == 18:
            cls.node18_cache.append(new_packet_name)  # append the new_packet_name string to node18_cache

    # CLASS FUNCTION USED TO SET ALL THE NODE_CACHE LISTS TO BLANK
    @classmethod
    def reset_node_cache(cls):
        # set all node_caches lists empty
        cls.node1_cache = []
        cls.node2_cache = []
        cls.node3_cache = []
        cls.node4_cache = []
        cls.node5_cache = []
        cls.node6_cache = []
        cls.node7_cache = []
        cls.node8_cache = []
        cls.node9_cache = []
        cls.node10_cache = []
        cls.node11_cache = []
        cls.node12_cache = []
        cls.node13_cache = []
        cls.node14_cache = []
        cls.node15_cache = []
        cls.node16_cache = []
        cls.node17_cache = []
        cls.node18_cache = []

    # CLASS FUNCTION USED TO SET ALL THE LINK_STATUS ENTRIES TO FALSE
    @classmethod
    def reset_links(cls):
        # set the link_status dictionary back to all False
        cls.link_status = {
           "a": False, "b": False, "c": False, "d": False, "e": False, "f": False, "g": False, "h": False, "i": False,
           "j": False, "k": False, "l": False, "m": False, "n": False, "o": False, "p": False, "q": False, "r": False,
           "s": False, "t": False, "u": False, "v": False, "w": False, "x": False, "y": False, "z": False
        }

    # FUNCTION USED TO UPDATE N_BUFFER_ORDERLIST AT THE END OF EACH TIME INTERVAL
    @classmethod
    def update_n_buffer_orderlist(cls):

        # if the index[0] position has no list in the N_Buffer_OrderList
        if not cls.N_Buffer_OrderList[0]:
            cls.N_Buffer_OrderList[0] = cls.node1_cache  # - insert the node1_cache string list into the position
        # else if the index[0] position has a list in the N_Buffer_OrderList
        else:
            cls.N_Buffer_OrderList[0] += cls.node1_cache  # - add node1_cache to existing list

        # if the index[1] position has no list in the N_Buffer_OrderList
        if not cls.N_Buffer_OrderList[1]:
            cls.N_Buffer_OrderList[1] = cls.node2_cache  # - insert the node2_cache string list into the position
        # else if the index[1] position has a list in the N_Buffer_OrderList
        else:
            cls.N_Buffer_OrderList[1] += cls.node2_cache  # - add node2_cache to existing list

        # if the index[2] position has no list in the N_Buffer_OrderList
        if not cls.N_Buffer_OrderList[2]:
            cls.N_Buffer_OrderList[2] = cls.node3_cache  # - insert the node3_cache string list into the position
        # else if the index[2] position has a list in the N_Buffer_OrderList
        else:
            cls.N_Buffer_OrderList[2] += cls.node3_cache  # - add node3_cache to existing list

        # if the index[3] position has no list in the N_Buffer_OrderList
        if not cls.N_Buffer_OrderList[3]:
            cls.N_Buffer_OrderList[3] = cls.node4_cache  # - insert the node4_cache string list into the position
        # else if the index[3] position has a list in the N_Buffer_OrderList
        else:
            cls.N_Buffer_OrderList[3] += cls.node4_cache  # - add node4_cache to existing list

        # if the index[4] position has no list in the N_Buffer_OrderList
        if not cls.N_Buffer_OrderList[4]:
            cls.N_Buffer_OrderList[4] = cls.node5_cache  # - insert the node5_cache string list into the position
        # else if the index[4] position has a list in the N_Buffer_OrderList
        else:
            cls.N_Buffer_OrderList[4] += cls.node5_cache  # - add node5_cache to existing list

        # if the index[5] position has no list in the N_Buffer_OrderList
        if not cls.N_Buffer_OrderList[5]:
            cls.N_Buffer_OrderList[5] = cls.node6_cache  # - insert the node6_cache string list into the position
        # else if the index[5] position has a list in the N_Buffer_OrderList
        else:
            cls.N_Buffer_OrderList[5] += cls.node6_cache  # - add node6_cache to existing list

        # if the index[6] position has no list in the N_Buffer_OrderList
        if not cls.N_Buffer_OrderList[6]:
            cls.N_Buffer_OrderList[6] = cls.node7_cache  # - insert the node7_cache string list into the position
        # else if the index[6] position has a list in the N_Buffer_OrderList
        else:
            cls.N_Buffer_OrderList[6] += cls.node7_cache  # - add node7_cache to existing list

        # if the index[7] position has no list in the N_Buffer_OrderList
        if not cls.N_Buffer_OrderList[7]:
            cls.N_Buffer_OrderList[7] = cls.node8_cache  # - insert the node8_cache string list into the position
        # else if the index[7] position has a list in the N_Buffer_OrderList
        else:
            cls.N_Buffer_OrderList[7] += cls.node8_cache  # - add node8_cache to existing list

        # if the index[8] position has no list in the N_Buffer_OrderList
        if not cls.N_Buffer_OrderList[8]:
            cls.N_Buffer_OrderList[8] = cls.node9_cache  # - insert the node9_cache string list into the position
        # else if the index[8] position has a list in the N_Buffer_OrderList
        else:
            cls.N_Buffer_OrderList[8] += cls.node9_cache  # - add node9_cache to existing list

        # if the index[9] position has no list in the N_Buffer_OrderList
        if not cls.N_Buffer_OrderList[9]:
            cls.N_Buffer_OrderList[9] = cls.node10_cache  # - insert the node10_cache string list into the position
        # else if the index[9] position has a list in the N_Buffer_OrderList
        else:
            cls.N_Buffer_OrderList[9] += cls.node10_cache  # - add node10_cache to existing list

        # if the index[10] position has no list in the N_Buffer_OrderList
        if not cls.N_Buffer_OrderList[10]:
            cls.N_Buffer_OrderList[10] = cls.node11_cache  # - insert the node11_cache string list into the position
        # else if the index[10] position has a list in the N_Buffer_OrderList
        else:
            cls.N_Buffer_OrderList[10] += cls.node11_cache  # - add node11_cache to existing list

        # if the index[11] position has no list in the N_Buffer_OrderList
        if not cls.N_Buffer_OrderList[11]:
            cls.N_Buffer_OrderList[11] = cls.node12_cache  # - insert the node12_cache string list into the position
        # else if the index[11] position has a list in the N_Buffer_OrderList
        else:
            cls.N_Buffer_OrderList[11] += cls.node12_cache  # - add node12_cache to existing list

        # if the index[12] position has no list in the N_Buffer_OrderList
        if not cls.N_Buffer_OrderList[12]:
            cls.N_Buffer_OrderList[12] = cls.node13_cache  # - insert the node13_cache string list into the position
        # else if the index[12] position has a list in the N_Buffer_OrderList
        else:
            cls.N_Buffer_OrderList[12] += cls.node13_cache  # - add node13_cache to existing list

        # if the index[13] position has no list in the N_Buffer_OrderList
        if not cls.N_Buffer_OrderList[13]:
            cls.N_Buffer_OrderList[13] = cls.node14_cache  # - insert the node14_cache string list into the position
        # else if the index[13] position has a list in the N_Buffer_OrderList
        else:
            cls.N_Buffer_OrderList[13] += cls.node14_cache  # - add node14_cache to existing list

        # if the index[14] position has no list in the N_Buffer_OrderList
        if not cls.N_Buffer_OrderList[14]:
            cls.N_Buffer_OrderList[14] = cls.node15_cache  # - insert the node15_cache string list into the position
        # else if the index[14] position has a list in the N_Buffer_OrderList
        else:
            cls.N_Buffer_OrderList[14] += cls.node15_cache  # - add node15_cache to existing list

        # if the index[15] position has no list in the N_Buffer_OrderList
        if not cls.N_Buffer_OrderList[15]:
            cls.N_Buffer_OrderList[15] = cls.node16_cache  # - insert the node16_cache string list into the position
        # else if the index[15] position has a list in the N_Buffer_OrderList
        else:
            cls.N_Buffer_OrderList[15] += cls.node16_cache  # - add node16_cache to existing list

        # if the index[16] position has no list in the N_Buffer_OrderList
        if not cls.N_Buffer_OrderList[16]:
            cls.N_Buffer_OrderList[16] = cls.node17_cache  # - insert the node17_cache string list into the position
        # else if the index[15] position has a list in the N_Buffer_OrderList
        else:
            cls.N_Buffer_OrderList[16] += cls.node17_cache  # - add node17_cache to existing list

        # if the index[16] position has no list in the N_Buffer_OrderList
        if not cls.N_Buffer_OrderList[17]:
            cls.N_Buffer_OrderList[17] = cls.node18_cache  # - insert the node18_cache string list into the position
        # else if the index[15] position has a list in the N_Buffer_OrderList
        else:
            cls.N_Buffer_OrderList[17] += cls.node18_cache  # - add node18_cache to existing list

        # set all node_caches lists empty for the next time increment using reset_node_cache Class Function
        Node.reset_node_cache()

        # set the link_status dictionary back to all False for the next time increment
        Node.reset_links()

    # FUNCTION USED TO RETRIEVE THE PACKET DATA FROM THE N_BUFFER AND N_BUFFER_ORDERLIST
    def node_process(self):
        self.current_node = self.neighbor_nodes[0]  # - Extract the current Node number from the coordinates tuple
        self.packet_data = []  # - set packet_data to blank list

        #  use an exception handler for when the N_Buffer and N_BufferOrderList is empty or the key is not available
        try:
            self.node_buff = self.N_Buffer_OrderList[self.current_node-1]  # Extract data Indexed in N_Buffer_OrderList
            self.first_buff_element = self.node_buff[0]  # - Extract the string value of the element in index (0)

            # condition to check if the "first_buff_element" entry exists in the N_Buffer
            if self.first_buff_element in self.N_Buffer:
                # extract the fields of the "first_buff_element" packet from the N_Buffer
                index0 = self.N_Buffer[str(self.first_buff_element)]["packet_status_flag"]
                index1 = self.N_Buffer[str(self.first_buff_element)]["hop_count"]
                index2 = self.N_Buffer[str(self.first_buff_element)]["copy_list"]
                index3 = self.N_Buffer[str(self.first_buff_element)]["packet_history"]
                index4 = self.first_buff_element
                # - store the extracted fields into the "packet_data" list
                self.packet_data = [index0, index1, index2, index3, index4]

                # condition to check if hop_count is equal to or less than zero
                if self.packet_data[1] <= 0:
                    # DELETE THE PACKET IN N_BUFFER AND N_BUFFER_ORDERLIST
                    self.delete_buffer_entry(self.first_buff_element, 1)
                    # - returning (bool_value) False will bypass the next functions until next time increment
                    return False
                else:  # - if hop_count is not less than or equal to zero continue processing the packet
                    #  condition to check if "packet_status_flag" is false
                    if self.packet_data[0] is False:
                        '''
                        determine nodes already visited and the ones to copy to using remove_similar_nodes() function.
                        First argument passed is used as basis of the comparison remove_similar_nodes(1st_Arg, 2nd_Arg)
                        self.neighbor_nodes[1:] - the neighbours of the Node object (excluding the current node)  
                        self.packet_data[3] - packet_history '''
                        diff_values = self.remove_similar_nodes(self.neighbor_nodes[1:], self.packet_data[3])

                        # check if the returned results from the remove_similar_nodes is empty
                        if not diff_values:
                            pass  # do nothing
                        else:
                            self.packet_data[2] = diff_values  # - update "copy_list" with diff_values

                            # set the "packet_status_flag" to "True" to skip node_process() function next iteration
                            self.packet_data[0] = True
                            # Update "packet_status_flag" in N_Buffer to "True" to skip node_process() next iteration
                            self.N_Buffer[str(self.first_buff_element)]["packet_status_flag"] = self.packet_data[0]
        except IndexError:
            pass  # do nothing

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

    # FUNCTION USED TO COPY PACKETS INTO THE CORRESPONDING NEXT NODES (THROUGH THREADS)
    def copy_packet(self, node_number):

        # append the next node number to the new the packet string
        # self.packet_data[4] is the first_buff_element
        new_packet_name = str(self.packet_data[4]) + '-' + str(node_number)

        # update the hop_count for the next node
        new_hop_count = (self.packet_data[1] - 1)  # remove 1 from hop_count

        # condition used to update "packet_history"
        # if current packet_history is empty
        if not self.packet_data[3]:
            new_packet_history = [self.neighbor_nodes[0]]  # - assign the current node number as new_packet_history

        # else if current packet_history is not empty
        else:
            # add current node number to previous_history and assign as the new_packet_history
            new_packet_history = self.packet_data[3] + [self.neighbor_nodes[0]]

        # new packet entries to be added to the N_Buffer with the new values for the next node copy
        buffer_value = {
            new_packet_name: {
                "packet_status_flag": False,  # - set packet_status_flag to False
                "hop_count": new_hop_count,
                "copy_list": [],  # - clear copy list
                "packet_history": new_packet_history
            }
        }
        self.N_Buffer.update(buffer_value)  # update the N_Buffer with the new packet

        # UPDATE TEMPORARILY NODE_CACHE WITH CURRENT PACKET
        Node.update_node_cache(node_number, new_packet_name)

    # -------------------------------- END OF NODE CLASS FUNCTIONS --------------------------------------------------- #

# -------------------------------------- End of Node Class ----------------------------------------------------------- #
# -------------------------------------------------------------------------------------------------------------------- #





























