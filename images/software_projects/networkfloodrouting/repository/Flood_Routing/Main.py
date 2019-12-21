# -------------------------------------------------------------------------------------------------------------------- #
# -------------------- Computer and Communication Networks (2018 - 2019): Coursework Assignment ---------------------- #
# ------------------------------------ FLOOD ROUTING (18 NODE NETWORK) ----------------------------------------------- #
# ------------------------------------ Instructor:  Dr John Easton --------------------------------------------------- #
# ------------------------------------ Written by:	James J Nkhata --------------------------------------------------- #
# -------------------------------- Student Number:	         --------------------------------------------------------- #
# -------------------------------------------------------------------------------------------------------------------- #
# --------------------------------------------- Main.py (1 of 2) ----------------------------------------------------- #

# ------------------------------------------ Module Imports ---------------------------------------------------------- #
from tkinter import *  # used to import all from the tkinter library
import Classes  # - used to import Classes module
from tkinter import messagebox  # used to import messagebox from the tkinter library
# -------------------------------------------------------------------------------------------------------------------- #
# --------------------------------- Creating Node objects to define Network ------------------------------------------ #
# Create Node objects using Tuples to define the connection structure between the nodes
# The values will not be changeable
Node_1 = Classes.Node(1, 2, 3)  # - 1st element in the Tuple defines the node number, the rest define its neighbours
Node_2 = Classes.Node(2, 1, 3, 6)
Node_3 = Classes.Node(3, 1, 2, 4)
Node_4 = Classes.Node(4, 3, 5, 6)
Node_5 = Classes.Node(5, 4, 8, 9)
Node_6 = Classes.Node(6, 2, 4, 7)
Node_7 = Classes.Node(7, 6, 11, 12)
Node_8 = Classes.Node(8, 5, 9, 11)
Node_9 = Classes.Node(9, 5, 8, 10)
Node_10 = Classes.Node(10, 9, 11, 13)
Node_11 = Classes.Node(11, 7, 8, 10)
Node_12 = Classes.Node(12, 7, 13, 14)
Node_13 = Classes.Node(13, 10, 12, 14)
Node_14 = Classes.Node(14, 12, 13, 15)
Node_15 = Classes.Node(15, 14, 16, 17)
Node_16 = Classes.Node(16, 15, 17, 18)
Node_17 = Classes.Node(17, 15, 16, 18)
Node_18 = Classes.Node(18, 16, 17)
# -------------------------------------------------------------------------------------------------------------------- #


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

    # FUNCTION USED TO RUN THE PROCESSES FOR EACH NODE TO SIMULATE A TIME INCREMENT (TIME +1) CONCURRENTLY
    def increment_time():
        Classes.Node.time_counter += 1  # Increment time_counter by 1 on each increment_time function call
        # run node processes for Node1 to Node18
        Node_1.run_node_routing()
        Node_2.run_node_routing()
        Node_3.run_node_routing()
        Node_4.run_node_routing()
        Node_5.run_node_routing()
        Node_6.run_node_routing()
        Node_7.run_node_routing()
        Node_8.run_node_routing()
        Node_9.run_node_routing()
        Node_10.run_node_routing()
        Node_11.run_node_routing()
        Node_12.run_node_routing()
        Node_13.run_node_routing()
        Node_14.run_node_routing()
        Node_15.run_node_routing()
        Node_16.run_node_routing()
        Node_17.run_node_routing()
        Node_18.run_node_routing()

        Classes.Node.update_n_buffer_orderlist()  # update the N_Buffer_OrderList with node_cache lists
        display_buff_count()  # run display_buff_count() to display buffer values on the userinterface

    # -------------------------------- UserInterface Display Functions ----------------------------------------------- #

    # FUNCTION USED TO SPLIT THE CONTENTS OF A PASSED LIST INTO MULTIPLE ROWS OF LABELS (BUFFER CONTENT:)
    def display_buffer_contents(list_to_display):

        # check the length of the list to display
        # if the list is empty
        if len(list_to_display) <= 0:
            # set the list to the 1st Buffer Contents label only
            display_buff_text1.set("NODE BUFFER IS EMPTY !")  # set the message to display
            display_buff_text2.set(" ")
            display_buff_text3.set(" ")
            display_buff_text4.set(" ")
            display_buff_text5.set(" ")
            display_buff_text6.set(" ")
            display_buff_text7.set(" ")
        # if the list is less than 5 elements long and not empty
        elif 0 < len(list_to_display) <= 5:
            # set the list to the 1st Buffer Contents label only and display all the contents in it
            display_buff_text1.set(", ".join(list_to_display))  # set the list without brackets
            display_buff_text2.set(" ")
            display_buff_text3.set(" ")
            display_buff_text4.set(" ")
            display_buff_text5.set(" ")
            display_buff_text6.set(" ")
            display_buff_text7.set(" ")
        # if the list is greater than 5 and less than or equal to 10 elements long
        elif 5 < len(list_to_display) <= 10:
            # set the list to the 1st and 2nd Buffer Contents label and split the contents
            display_buff_text1.set(", ".join(list_to_display[0:5]))  # first 5 elements
            display_buff_text2.set(", ".join(list_to_display[5:]))  # elements 6 - 10
            display_buff_text3.set(" ")
            display_buff_text4.set(" ")
            display_buff_text5.set(" ")
            display_buff_text6.set(" ")
            display_buff_text7.set(" ")
        # if the list is greater than 10 and less than or equal to 15 elements long
        elif 10 < len(list_to_display) <= 15:
            # set the list to the 1st, 2nd and 3rd Buffer Contents label and split the contents
            display_buff_text1.set(", ".join(list_to_display[0:5]))  # first 5 elements
            display_buff_text2.set(", ".join(list_to_display[5:10]))  # elements 6 - 10
            display_buff_text3.set(", ".join(list_to_display[10:]))  # elements 11 - 15
            display_buff_text4.set(" ")
            display_buff_text5.set(" ")
            display_buff_text6.set(" ")
            display_buff_text7.set(" ")
        # if the list is greater than 15 and less than or equal to 20 elements long
        elif 15 < len(list_to_display) <= 20:
            # set the list to the 1st, 2nd, 3rd and 4th Buffer Contents label and split the contents
            display_buff_text1.set(", ".join(list_to_display[0:5]))  # first 5 elements
            display_buff_text2.set(", ".join(list_to_display[5:10]))  # elements 6 - 10
            display_buff_text3.set(", ".join(list_to_display[10:15]))  # elements 11 - 15
            display_buff_text4.set(", ".join(list_to_display[15:]))  # elements 16 - 20
            display_buff_text5.set(" ")
            display_buff_text6.set(" ")
            display_buff_text7.set(" ")
        # if the list is greater than 20 and less than or equal to 25 elements long
        elif 20 < len(list_to_display) <= 25:
            # set the list to the 1st, 2nd, 3rd, 4th and 5th Buffer Contents label and split the contents
            display_buff_text1.set(", ".join(list_to_display[0:5]))  # first 5 elements
            display_buff_text2.set(", ".join(list_to_display[5:10]))  # elements 6 - 10
            display_buff_text3.set(", ".join(list_to_display[10:15]))  # elements 11 - 15
            display_buff_text4.set(", ".join(list_to_display[15:20]))  # elements 16 - 20
            display_buff_text5.set(", ".join(list_to_display[20:]))  # elements 21 - 25
            display_buff_text6.set(" ")
            display_buff_text7.set(" ")
        # if the list is greater than 25 and less than or equal to 30 elements long
        elif 25 < len(list_to_display) <= 30:
            # set the list to the 1st, 2nd, 3rd, 4th, 5th and 6th Buffer Contents label and split the contents
            display_buff_text1.set(", ".join(list_to_display[0:5]))  # first 5 elements
            display_buff_text2.set(", ".join(list_to_display[5:10]))  # elements 6 - 10
            display_buff_text3.set(", ".join(list_to_display[10:15]))  # elements 11 - 15
            display_buff_text4.set(", ".join(list_to_display[15:20]))  # elements 16 - 20
            display_buff_text5.set(", ".join(list_to_display[20:25]))  # elements 21 - 25
            display_buff_text6.set(", ".join(list_to_display[25:]))  # elements 26 - 30
            display_buff_text7.set(" ")
        # if the list is greater than 25 and less than or equal to 40 elements long
        elif 30 < len(list_to_display) <= 40:
            # set the list to the 1st, 2nd, 3rd, 4th, 5th, 6th and 7th Buffer Contents label and split the contents
            display_buff_text1.set(", ".join(list_to_display[0:5]))  # first 5 elements
            display_buff_text2.set(", ".join(list_to_display[5:10]))  # elements 6 - 10
            display_buff_text3.set(", ".join(list_to_display[10:15]))  # elements 11 - 15
            display_buff_text4.set(", ".join(list_to_display[15:20]))  # elements 16 - 20
            display_buff_text5.set(", ".join(list_to_display[20:25]))  # elements 21 - 25
            display_buff_text6.set(", ".join(list_to_display[25:30]))  # elements 26 - 30
            display_buff_text7.set(", ".join(list_to_display[30:]))  # elements 30 - 40

    # FUNCTION USED TO SET THE CONTENTS OF N_BUFFER_ORDERLIST INDEX 0
    def show_node1(event):
        # run the display_buffer_contents function and pass N_Buffer_OrderList[0] as its list
        display_buffer_contents(Classes.Node.N_Buffer_OrderList[0])

    # FUNCTION USED TO SET THE CONTENTS OF N_BUFFER_ORDERLIST INDEX 1
    def show_node2(event):
        # run the display_buffer_contents function and pass N_Buffer_OrderList[1] as its list
        display_buffer_contents(Classes.Node.N_Buffer_OrderList[1])

    # FUNCTION USED TO SET THE CONTENTS OF N_BUFFER_ORDERLIST INDEX 2
    def show_node3(event):
        # run the display_buffer_contents function and pass N_Buffer_OrderList[2] as its list
        display_buffer_contents(Classes.Node.N_Buffer_OrderList[2])

    # FUNCTION USED TO SET THE CONTENTS OF N_BUFFER_ORDERLIST INDEX 3
    def show_node4(event):
        # run the display_buffer_contents function and pass N_Buffer_OrderList[3] as its list
        display_buffer_contents(Classes.Node.N_Buffer_OrderList[3])

    # FUNCTION USED TO SET THE CONTENTS OF N_BUFFER_ORDERLIST INDEX 4
    def show_node5(event):
        # run the display_buffer_contents function and pass N_Buffer_OrderList[4] as its list
        display_buffer_contents(Classes.Node.N_Buffer_OrderList[4])

    # FUNCTION USED TO SET THE CONTENTS OF N_BUFFER_ORDERLIST INDEX 5
    def show_node6(event):
        # run the display_buffer_contents function and pass N_Buffer_OrderList[5] as its list
        display_buffer_contents(Classes.Node.N_Buffer_OrderList[5])

    # FUNCTION USED TO SET THE CONTENTS OF N_BUFFER_ORDERLIST INDEX 6
    def show_node7(event):
        # run the display_buffer_contents function and pass N_Buffer_OrderList[6] as its list
        display_buffer_contents(Classes.Node.N_Buffer_OrderList[6])

    # FUNCTION USED TO SET THE CONTENTS OF N_BUFFER_ORDERLIST INDEX 7
    def show_node8(event):
        # run the display_buffer_contents function and pass N_Buffer_OrderList[7] as its list
        display_buffer_contents(Classes.Node.N_Buffer_OrderList[7])

    # FUNCTION USED TO SET THE CONTENTS OF N_BUFFER_ORDERLIST INDEX 8
    def show_node9(event):
        # run the display_buffer_contents function and pass N_Buffer_OrderList[8] as its list
        display_buffer_contents(Classes.Node.N_Buffer_OrderList[8])

    # FUNCTION USED TO SET THE CONTENTS OF N_BUFFER_ORDERLIST INDEX 9
    def show_node10(event):
        # run the display_buffer_contents function and pass N_Buffer_OrderList[9] as its list
        display_buffer_contents(Classes.Node.N_Buffer_OrderList[9])

    # FUNCTION USED TO SET THE CONTENTS OF N_BUFFER_ORDERLIST INDEX 10
    def show_node11(event):
        # run the display_buffer_contents function and pass N_Buffer_OrderList[10] as its list
        display_buffer_contents(Classes.Node.N_Buffer_OrderList[10])

    # FUNCTION USED TO SET THE CONTENTS OF N_BUFFER_ORDERLIST INDEX 11
    def show_node12(event):
        # run the display_buffer_contents function and pass N_Buffer_OrderList[11] as its list
        display_buffer_contents(Classes.Node.N_Buffer_OrderList[11])

    # FUNCTION USED TO SET THE CONTENTS OF N_BUFFER_ORDERLIST INDEX 12
    def show_node13(event):
        # run the display_buffer_contents function and pass N_Buffer_OrderList[12] as its list
        display_buffer_contents(Classes.Node.N_Buffer_OrderList[12])

    # FUNCTION USED TO SET THE CONTENTS OF N_BUFFER_ORDERLIST INDEX 13
    def show_node14(event):
        # run the display_buffer_contents function and pass N_Buffer_OrderList[13] as its list
        display_buffer_contents(Classes.Node.N_Buffer_OrderList[13])

    # FUNCTION USED TO SET THE CONTENTS OF N_BUFFER_ORDERLIST INDEX 14
    def show_node15(event):
        # run the display_buffer_contents function and pass N_Buffer_OrderList[14] as its list
        display_buffer_contents(Classes.Node.N_Buffer_OrderList[14])

    # FUNCTION USED TO SET THE CONTENTS OF N_BUFFER_ORDERLIST INDEX 15
    def show_node16(event):
        # run the display_buffer_contents function and pass N_Buffer_OrderList[15] as its list
        display_buffer_contents(Classes.Node.N_Buffer_OrderList[15])

    # FUNCTION USED TO SET THE CONTENTS OF N_BUFFER_ORDERLIST INDEX 16
    def show_node17(event):
        # run the display_buffer_contents function and pass N_Buffer_OrderList[16] as its list
        display_buffer_contents(Classes.Node.N_Buffer_OrderList[16])

    # FUNCTION USED TO SET THE CONTENTS OF N_BUFFER_ORDERLIST INDEX 17
    def show_node18(event):
        # run the display_buffer_contents function and pass N_Buffer_OrderList[17] as its list
        display_buffer_contents(Classes.Node.N_Buffer_OrderList[17])

    # FUNCTION USED TO PROMPT USER TO MOVE CURSOR OVER CANVAS NODES TO DISPLAY CONTENTS OF N_BUFFER_ORDERLIST
    def rollover_node_message(event):
        display_buff_text1.set("ROLL MOUSE CURSOR OVER A NODE TO DISPLAY THE BUFFER CONTENTS")
        display_buff_text2.set(" ")
        display_buff_text3.set(" ")
        display_buff_text4.set(" ")
        display_buff_text5.set(" ")
        display_buff_text6.set(" ")
        display_buff_text7.set(" ")

    # FUNCTION USED TO DISPLAY THE BUFFER VALUES ON THE USERINTERFACE
    def display_buff_count():
        # display time count
        display_time_text.set("TIME: " + str(Classes.Node.time_counter))

        # Check if the multidimensional N_BufferOrderList is empty at index [0]
        if not Classes.Node.N_Buffer_OrderList[0]:
            node1text.set(0)  # if empty print the value 0
        # else if the N_BufferOrderList is not empty at index [0]
        else:
            node1text.set(len(Classes.Node.N_Buffer_OrderList[0]))  # check the length of the Node 1 buffer& display

        # Check if the multidimensional N_BufferOrderList is empty at index [1]
        if not Classes.Node.N_Buffer_OrderList[1]:
            node2text.set(0)  # if empty print the value 0
        # else if the N_BufferOrderList is not empty at index [1]
        else:
            node2text.set(len(Classes.Node.N_Buffer_OrderList[1]))  # check the length of the Node 2 buffer& display

        # Check if the multidimensional N_BufferOrderList is empty at index [2]
        if not Classes.Node.N_Buffer_OrderList[2]:
            node3text.set(0)  # if empty print the value 0
        # else if the N_BufferOrderList is not empty at index [2]
        else:
            node3text.set(len(Classes.Node.N_Buffer_OrderList[2]))  # check the length of the Node 3 buffer& display

        # Check if the multidimensional N_BufferOrderList is empty at index [3]
        if not Classes.Node.N_Buffer_OrderList[3]:
            node4text.set(0)  # if empty print the value 0
        # else if the N_BufferOrderList is not empty  at index [3]
        else:
            node4text.set(len(Classes.Node.N_Buffer_OrderList[3]))  # check the length of the Node 4 buffer& display

        # Check if the multidimensional N_BufferOrderList is empty at index [4]
        if not Classes.Node.N_Buffer_OrderList[4]:
            node5text.set(0)  # if empty print the value 0
        # else if the N_BufferOrderList is not empty  at index [4]
        else:
            node5text.set(len(Classes.Node.N_Buffer_OrderList[4]))  # check the length of the Node 5 buffer& display

        # Check if the multidimensional N_BufferOrderList is empty at index [5]
        if not Classes.Node.N_Buffer_OrderList[5]:
            node6text.set(0)  # if empty print the value 0
        # else if the N_BufferOrderList is not empty  at index [5]
        else:
            node6text.set(len(Classes.Node.N_Buffer_OrderList[5]))  # check the length of the Node 6 buffer& display

        # Check if the multidimensional N_BufferOrderList is empty at index [6]
        if not Classes.Node.N_Buffer_OrderList[6]:
            node7text.set(0)  # if empty print the value 0
        # else if the N_BufferOrderList is not empty  at index [6]
        else:
            node7text.set(len(Classes.Node.N_Buffer_OrderList[6]))  # check the length of the Node 7 buffer& display

        # Check if the multidimensional N_BufferOrderList is empty at index [7]
        if not Classes.Node.N_Buffer_OrderList[7]:
            node8text.set(0)  # if empty print the value 0
        # else if the N_BufferOrderList is not empty  at index [7]
        else:
            node8text.set(len(Classes.Node.N_Buffer_OrderList[7]))  # check the length of the Node 8 buffer& display

        # Check if the multidimensional N_BufferOrderList is empty at index [8]
        if not Classes.Node.N_Buffer_OrderList[8]:
            node9text.set(0)  # if empty print the value 0
        # else if the N_BufferOrderList is not empty at index [8]
        else:
            node9text.set(len(Classes.Node.N_Buffer_OrderList[8]))  # check the length of the Node 9 buffer& display

        # Check if the multidimensional N_BufferOrderList is empty at index [9]
        if not Classes.Node.N_Buffer_OrderList[9]:
            node10text.set(0)  # if empty print the value 0
        # else if the N_BufferOrderList is not empty at index [9]
        else:
            node10text.set(len(Classes.Node.N_Buffer_OrderList[9]))  # check the length of the Node 10 buffer& display

        # Check if the multidimensional N_BufferOrderList is empty at index [10]
        if not Classes.Node.N_Buffer_OrderList[10]:
            node11text.set(0)  # if empty print the value 0
        # else if the N_BufferOrderList is not empty at index [10]
        else:
            node11text.set(len(Classes.Node.N_Buffer_OrderList[10]))  # check the length of the Node 11 buffer& display

        # Check if the multidimensional N_BufferOrderList is empty at index [11]
        if not Classes.Node.N_Buffer_OrderList[11]:
            node12text.set(0)  # if empty print the value 0
        # else if the N_BufferOrderList is not empty at index [11]
        else:
            node12text.set(len(Classes.Node.N_Buffer_OrderList[11]))  # check the length of the Node 12 buffer& display

        # Check if the multidimensional N_BufferOrderList is empty at index [11]
        if not Classes.Node.N_Buffer_OrderList[12]:
            node13text.set(0)  # if empty print the value 0
        # else if the N_BufferOrderList is not empty at index [12]
        else:
            node13text.set(len(Classes.Node.N_Buffer_OrderList[12]))  # check the length of the Node 13 buffer& display

        # Check if the multidimensional N_BufferOrderList is empty at index [13]
        if not Classes.Node.N_Buffer_OrderList[13]:
            node14text.set(0)  # if empty print the value 0
        # else if the N_BufferOrderList is not empty at index [13]
        else:
            node14text.set(len(Classes.Node.N_Buffer_OrderList[13]))  # check the length of the Node 14 buffer& display

        # Check if the multidimensional N_BufferOrderList is empty at index [14]
        if not Classes.Node.N_Buffer_OrderList[14]:
            node15text.set(0)  # if empty print the value 0
        # else if the N_BufferOrderList is not empty at index [14]
        else:
            node15text.set(len(Classes.Node.N_Buffer_OrderList[14]))  # check the length of the Node 15 buffer& display

        # Check if the multidimensional N_BufferOrderList is empty at index [15]
        if not Classes.Node.N_Buffer_OrderList[15]:
            node16text.set(0)  # if empty print the value 0
        # else if the N_BufferOrderList is not empty at index [15]
        else:
            node16text.set(len(Classes.Node.N_Buffer_OrderList[15]))  # check the length of the Node 16 buffer& display

        # Check if the multidimensional N_BufferOrderList is empty at index [16]
        if not Classes.Node.N_Buffer_OrderList[16]:
            node17text.set(0)  # if empty print the value 0
        # else if the N_BufferOrderList is not empty at index [16]
        else:
            node17text.set(len(Classes.Node.N_Buffer_OrderList[16]))  # check the length of the Node 17 buffer & display

        # Check if the multidimensional N_BufferOrderList is empty at index [17]
        if not Classes.Node.N_Buffer_OrderList[17]:
            node18text.set(0)  # if empty print the value 0
        # else if the N_BufferOrderList is not empty at index [17]
        else:
            node18text.set(len(Classes.Node.N_Buffer_OrderList[17]))  # check the length of the Node 18 buffer & display

    # -------------------------------- END OF USERINTERFACE FUNCTIONS ------------------------------------------ #

    # ------------------------------- START OF TKINTER USERINTERFACE DEFINITIONS --------------------------------- #
    # ------------------------------- main Frame widgets for the userinterface ----------------------------------- #
    # Set root title
    root.title("Flood Routing: Simulator")
    # create Frame object for the top section of the gui
    topframe = Frame(root)
    topframe.pack()  # pack the object into the window

    # create a label for the time display
    display_time_text = StringVar()
    display_time = Label(root, font="Arial 20 italic bold", textvariable=display_time_text)
    display_time.pack(anchor=W)  # pack the object into the window

    # create Frame object for the middle section of the gui
    middleframe = Frame(root)
    middleframe.pack()  # pack the object into the window

    # create a label for the bottomframe
    label_Buffer = Label(root, text="Buffer Contents:")
    label_Buffer.pack()  # pack the object into the window

    # create Frame object for the bottom section of the gui
    bottomframe = Frame(root, bd=2, relief=SUNKEN)
    bottomframe.pack()  # pack the object into the window
    # ------------------------------- define variables for the userinterface ------------------------------ #
    # control variables definitions for displaying text
    node1text = IntVar()
    node2text = IntVar()
    node3text = IntVar()
    node4text = IntVar()
    node5text = IntVar()
    node6text = IntVar()
    node7text = IntVar()
    node8text = IntVar()
    node9text = IntVar()
    node10text = IntVar()
    node11text = IntVar()
    node12text = IntVar()
    node13text = IntVar()
    node14text = IntVar()
    node15text = IntVar()
    node16text = IntVar()
    node17text = IntVar()
    node18text = IntVar()

    display_buff_text1 = StringVar()
    display_buff_text2 = StringVar()
    display_buff_text3 = StringVar()
    display_buff_text4 = StringVar()
    display_buff_text5 = StringVar()
    display_buff_text6 = StringVar()
    display_buff_text7 = StringVar()
    # ------------------------------------------------------------------------------------------------------------ #

    # ------------------------------- define Label widgets for the userinterface --------------------------------- #
    label_node1 = Label(middleframe, text="Node 1", fg="black")
    label_node2 = Label(middleframe, text="Node 2", fg="black")
    label_node3 = Label(middleframe, text="Node 3", fg="black")
    label_node4 = Label(middleframe, text="Node 4", fg="black")
    label_node5 = Label(middleframe, text="Node 5", fg="black")
    label_node6 = Label(middleframe, text="Node 6", fg="black")
    label_node7 = Label(middleframe, text="Node 7", fg="black")
    label_node8 = Label(middleframe, text="Node 8", fg="black")
    label_node9 = Label(middleframe, text="Node 9", fg="black")
    label_node10 = Label(middleframe, text="Node 10", fg="black")
    label_node11 = Label(middleframe, text="Node 11", fg="black")
    label_node12 = Label(middleframe, text="Node 12", fg="black")
    label_node13 = Label(middleframe, text="Node 13", fg="black")
    label_node14 = Label(middleframe, text="Node 14", fg="black")
    label_node15 = Label(middleframe, text="Node 15", fg="black")
    label_node16 = Label(middleframe, text="Node 16", fg="black")
    label_node17 = Label(middleframe, text="Node 17", fg="black")
    label_node18 = Label(middleframe, text="Node 18", fg="black")

    label_node1_value = Label(middleframe, textvariable=node1text, width=6, bd=1, relief=SUNKEN)
    label_node2_value = Label(middleframe, textvariable=node2text, width=6, bd=1, relief=SUNKEN)
    label_node3_value = Label(middleframe, textvariable=node3text, width=6, bd=1, relief=SUNKEN)
    label_node4_value = Label(middleframe, textvariable=node4text, width=6, bd=1, relief=SUNKEN)
    label_node5_value = Label(middleframe, textvariable=node5text, width=6, bd=1, relief=SUNKEN)
    label_node6_value = Label(middleframe, textvariable=node6text, width=6, bd=1, relief=SUNKEN)
    label_node7_value = Label(middleframe, textvariable=node7text, width=6, bd=1, relief=SUNKEN)
    label_node8_value = Label(middleframe, textvariable=node8text, width=6, bd=1, relief=SUNKEN)
    label_node9_value = Label(middleframe, textvariable=node9text, width=6, bd=1, relief=SUNKEN)
    label_node10_value = Label(middleframe, textvariable=node10text, width=6, bd=1, relief=SUNKEN)
    label_node11_value = Label(middleframe, textvariable=node11text, width=6, bd=1, relief=SUNKEN)
    label_node12_value = Label(middleframe, textvariable=node12text, width=6, bd=1, relief=SUNKEN)
    label_node13_value = Label(middleframe, textvariable=node13text, width=6, bd=1, relief=SUNKEN)
    label_node14_value = Label(middleframe, textvariable=node14text, width=6, bd=1, relief=SUNKEN)
    label_node15_value = Label(middleframe, textvariable=node15text, width=6, bd=1, relief=SUNKEN)
    label_node16_value = Label(middleframe, textvariable=node16text, width=6, bd=1, relief=SUNKEN)
    label_node17_value = Label(middleframe, textvariable=node17text, width=6, bd=1, relief=SUNKEN)
    label_node18_value = Label(middleframe, textvariable=node18text, width=6, bd=1, relief=SUNKEN)

    label_buffer_value1 = Label(bottomframe, textvariable=display_buff_text1, fg="blue", width=150, bd=1)
    label_buffer_value2 = Label(bottomframe, textvariable=display_buff_text2, fg="blue", width=150, bd=1)
    label_buffer_value3 = Label(bottomframe, textvariable=display_buff_text3, fg="blue", width=150, bd=1)
    label_buffer_value4 = Label(bottomframe, textvariable=display_buff_text4, fg="blue", width=150, bd=1)
    label_buffer_value5 = Label(bottomframe, textvariable=display_buff_text5, fg="blue", width=150, bd=1)
    label_buffer_value6 = Label(bottomframe, textvariable=display_buff_text6, fg="blue", width=150, bd=1)
    label_buffer_value7 = Label(bottomframe, textvariable=display_buff_text7, fg="blue", width=150, bd=1)

    label_entry = Label(middleframe, text="Enter Start Node", fg="red")

    label_buffer_count = Label(middleframe, text="Buffer Packet Count:", fg="black")

    # ------------------------------------------------------------------------------------------------------------ #

    # ------------------------------- define Entry widgets for the userinterface --------------------------------- #
    entry_init = Entry(middleframe, width=3)  # entry used to specify node to insert packet in
    # ------------------------------------------------------------------------------------------------------------ #

    # ------------------------------- define button widgets for the userinterface -------------------------------- #
    buttonstart = Button(middleframe, text="Start", command=gui_init_routing)
    buttonreset = Button(middleframe, text="Reset", fg="black", state="disabled", command=gui_restart)
    buttonmanual = Button(middleframe, text="Next Increment (Time + 1)", state="disabled", command=increment_time)
    # ------------------------------------------------------------------------------------------------------------ #

    # ------------------------------- layout of widgets for the userinterface ------------------------------------ #
    # layout the widgets using grid geometry manager
    label_entry.grid(row=0, sticky=E, pady=(0, 8))  # pad the bottom by 8
    entry_init.grid(row=0, column=1, pady=(0, 8))  # pad the bottom by 8
    buttonstart.grid(row=0, column=6, columnspan=2, pady=(0, 8))  # pad the bottom by 8
    buttonmanual.grid(row=0, column=12, columnspan=3, pady=(0, 8))  # pad the bottom by 8
    buttonreset.grid(row=0, column=18, columnspan=2, pady=(0, 8))  # pad the bottom by 8
    label_buffer_count.grid(row=2, columnspan=2, pady=(0, 8))  # pad the bottom by 8

    label_node1.grid(row=1, column=4)
    label_node2.grid(row=1, column=5)
    label_node3.grid(row=1, column=6)
    label_node4.grid(row=1, column=7)
    label_node5.grid(row=1, column=8)
    label_node6.grid(row=1, column=9)
    label_node7.grid(row=1, column=10)
    label_node8.grid(row=1, column=11)
    label_node9.grid(row=1, column=12)
    label_node10.grid(row=1, column=13)
    label_node11.grid(row=1, column=14)
    label_node12.grid(row=1, column=15)
    label_node13.grid(row=1, column=16)
    label_node14.grid(row=1, column=17)
    label_node15.grid(row=1, column=18)
    label_node16.grid(row=1, column=19)
    label_node17.grid(row=1, column=20)
    label_node18.grid(row=1, column=21)
    label_node1_value.grid(row=2, column=4)
    label_node2_value.grid(row=2, column=5)
    label_node3_value.grid(row=2, column=6)
    label_node4_value.grid(row=2, column=7)
    label_node5_value.grid(row=2, column=8)
    label_node6_value.grid(row=2, column=9)
    label_node7_value.grid(row=2, column=10)
    label_node8_value.grid(row=2, column=11)
    label_node9_value.grid(row=2, column=12)
    label_node10_value.grid(row=2, column=13)
    label_node11_value.grid(row=2, column=14)
    label_node12_value.grid(row=2, column=15)
    label_node13_value.grid(row=2, column=16)
    label_node14_value.grid(row=2, column=17)
    label_node15_value.grid(row=2, column=18)
    label_node16_value.grid(row=2, column=19)
    label_node17_value.grid(row=2, column=20)
    label_node18_value.grid(row=2, column=21)

    # layout the widgets using pack geometry manager
    label_buffer_value1.pack()  # pack the object into the bottomframe
    label_buffer_value2.pack()  # pack the object into the bottomframe
    label_buffer_value3.pack()  # pack the object into the bottomframe
    label_buffer_value4.pack()  # pack the object into the bottomframe
    label_buffer_value5.pack()  # pack the object into the bottomframe
    label_buffer_value6.pack()  # pack the object into the bottomframe
    label_buffer_value7.pack()  # pack the object into the bottomframe
    # ------------------------------------------------------------------------------------------------------------ #

    # ------------------------------- define canvas widgets for the userinterface -------------------------------- #

    canvas = Canvas(topframe, width=1200, height=700, bg="white", bd=2, relief=SUNKEN)
    canvas.pack()

    # define circle variables and caption for the nodes
    node1_circle = create_circle(50, 50, 25)  # - draw node 1 circle
    canvas.create_text(50, 50, fill="black", font="Arial 20 italic bold", text="1")  # - node 1 circle caption

    node2_circle = create_circle(250, 50, 25)  # - draw node 2 circle
    canvas.create_text(250, 50, fill="black", font="Arial 20 italic bold", text="2")  # - node 2 circle caption

    node3_circle = create_circle(50, 250, 25)  # - draw node 3 circle
    canvas.create_text(50, 250, fill="black", font="Arial 20 italic bold", text="3")  # - node 3 circle caption

    node4_circle = create_circle(250, 250, 25)  # - draw node 4 circle
    canvas.create_text(250, 250, fill="black", font="Arial 20 italic bold", text="4")  # - node 4 circle caption

    node5_circle = create_circle(50, 450, 25)  # - draw node 5 circle
    canvas.create_text(50, 450, fill="black", font="Arial 20 italic bold", text="5")  # - node 5 circle caption

    node6_circle = create_circle(450, 50, 25)  # - draw node 6 circle
    canvas.create_text(450, 50, fill="black", font="Arial 20 italic bold", text="6")  # - node 6 circle caption

    node7_circle = create_circle(450, 250, 25)  # - draw node 7 circle
    canvas.create_text(450, 250, fill="black", font="Arial 20 italic bold", text="7")  # - node 7 circle caption

    node8_circle = create_circle(250, 450, 25)  # - draw node 8 circle
    canvas.create_text(250, 450, fill="black", font="Arial 20 italic bold", text="8")  # - node 8 circle caption

    node9_circle = create_circle(250, 650, 25)  # - draw node 9 circle
    canvas.create_text(250, 650, fill="black", font="Arial 20 italic bold", text="9")  # - node 9 circle caption

    node10_circle = create_circle(450, 650, 25)  # - draw node 10 circle
    canvas.create_text(450, 650, fill="black", font="Arial 20 italic bold", text="10")  # - node 10 circle caption

    node11_circle = create_circle(450, 450, 25)  # - draw node 11 circle
    canvas.create_text(450, 450, fill="black", font="Arial 20 italic bold", text="11")  # - node 11 circle caption

    node12_circle = create_circle(650, 450, 25)  # - draw node 12 circle
    canvas.create_text(650, 450, fill="black", font="Arial 20 italic bold", text="12")  # - node 12 circle caption

    node13_circle = create_circle(650, 650, 25)  # - draw node 13 circle
    canvas.create_text(650, 650, fill="black", font="Arial 20 italic bold", text="13")  # - node 13 circle caption

    node14_circle = create_circle(850, 450, 25)  # - draw node 14 circle
    canvas.create_text(850, 450, fill="black", font="Arial 20 italic bold", text="14")  # - node 14 circle caption

    node15_circle = create_circle(1050, 450, 25)  # - draw node 15 circle
    canvas.create_text(1050, 450, fill="black", font="Arial 20 italic bold", text="15")  # - node 15 circle caption

    node16_circle = create_circle(850, 250, 25)  # - draw node 16 circle
    canvas.create_text(850, 250, fill="black", font="Arial 20 italic bold", text="16")  # - node 16 circle caption

    node17_circle = create_circle(1050, 250, 25)  # - draw node 17 circle
    canvas.create_text(1050, 250, fill="black", font="Arial 20 italic bold", text="17")  # - node 17 circle caption

    node18_circle = create_circle(850, 50, 25)  # - draw node 18 circle
    canvas.create_text(850, 50, fill="black", font="Arial 20 italic bold", text="18")  # - node 18 circle caption

    # drawline links between nodes: starting node (x,y) to end point node (x,y) and "Orientation"
    create_link(50, 50, 250, 50, "horizontal")  # link_a connect node 1 to 2
    create_link(50, 50, 50, 250, "vertical")  # link_b connect node 1 to 3)
    create_link(250, 50, 50, 250, "diagonal-left")  # link_c connect node 2 to 3
    create_link(250, 50, 450, 50, "horizontal")  # link_d connect node 2 to 6
    create_link(50, 250, 250, 250, "horizontal")  # link_e connect node 3 to 4
    create_link(450, 50, 250, 250, "diagonal-left")  # link_f connect node 6 to 4 (reversed order to work)
    create_link(450, 50, 450, 250, "vertical")  # link_g connect node 6 to 7
    create_link(250, 250, 50, 450, "diagonal-left")  # link_h connect node 4 to 5
    create_link(50, 450, 250, 450, "horizontal")  # link_i connect node 5 to 8
    create_link(50, 450, 250, 650, "diagonal-right")  # link_j connect node 5 to 9
    create_link(250, 450, 250, 650, "vertical")  # link_k connect node 8 to 9
    create_link(250, 650, 450, 650, "horizontal")  # link_l connect node 9 to 10
    create_link(250, 450, 450, 450, "horizontal")  # link_m connect node 8 to 11
    create_link(450, 250, 450, 450, "vertical")  # link_n connect node 7 to 11
    create_link(450, 250, 650, 450, "diagonal-right")  # link_o connect node 7 to 12
    create_link(450, 450, 450, 650, "vertical")  # link_p connect node 11 to 10 (reversed order to work)
    create_link(450, 650, 650, 650, "horizontal")  # link_q connect node 10 to 13
    create_link(650, 450, 650, 650, "vertical")  # link_r connect node 12 to 13
    create_link(650, 450, 850, 450, "horizontal")  # link_s connect node 12 to 14
    create_link(850, 450, 650, 650,  "diagonal-left")  # link_t connect node 14 to 13 (reversed order to work)
    create_link(850, 450, 1050, 450, "horizontal")  # link_u connect node 14 to 15
    create_link(850, 250, 1050, 450,  "diagonal-right")  # link_v connect node 16 to 15 (reversed order to work)
    create_link(1050, 250, 1050, 450, "vertical")  # link_w connect node 17 to 15 (reversed order to work)
    create_link(850, 250, 1050, 250, "horizontal")  # link_x connect node 16 to 17
    create_link(850, 50, 850, 250, "vertical")  # link_y  connect node 18 to 16 (reversed order to work)
    create_link(850, 50, 1050, 250,  "diagonal-right")  # link_z connect node 18 to 17 (reversed order to work)

    # bind the canvas items to mouse over event handlers to display node buffer content in the Buffer Contents labels
    canvas.tag_bind(node1_circle, "<Enter>", show_node1)
    canvas.tag_bind(node2_circle, "<Enter>", show_node2)
    canvas.tag_bind(node3_circle, "<Enter>", show_node3)
    canvas.tag_bind(node4_circle, "<Enter>", show_node4)
    canvas.tag_bind(node5_circle, "<Enter>", show_node5)
    canvas.tag_bind(node6_circle, "<Enter>", show_node6)
    canvas.tag_bind(node7_circle, "<Enter>", show_node7)
    canvas.tag_bind(node8_circle, "<Enter>", show_node8)
    canvas.tag_bind(node9_circle, "<Enter>", show_node9)
    canvas.tag_bind(node10_circle, "<Enter>", show_node10)
    canvas.tag_bind(node11_circle, "<Enter>", show_node11)
    canvas.tag_bind(node12_circle, "<Enter>", show_node12)
    canvas.tag_bind(node13_circle, "<Enter>", show_node13)
    canvas.tag_bind(node14_circle, "<Enter>", show_node14)
    canvas.tag_bind(node15_circle, "<Enter>", show_node15)
    canvas.tag_bind(node16_circle, "<Enter>", show_node16)
    canvas.tag_bind(node17_circle, "<Enter>", show_node17)
    canvas.tag_bind(node18_circle, "<Enter>", show_node18)

    # bind the middleframe and the bottomframe to an event handler to prompt the user to roll cursor over a node
    middleframe.bind("<Enter>", rollover_node_message)
    bottomframe.bind("<Enter>", rollover_node_message)
    # ------------------------------------------------------------------------------------------------------------ #
    # ------------------------------- END OF TKINTER USERINTERFACE DEFINITIONS --------------------------------- #

    root.mainloop()  # - continuously run the root object
# ----------------------------------------- END OF MAIN FUNCTION ----------------------------------------------------- #
# -------------------------------------------------------------------------------------------------------------------- #


# CONDITION TO CHECK IF THE CURRENT MODULE IS THE MAIN MODULE
if __name__ == '__main__':
    # Function used to reset the user interface
    def gui_restart():
        root.destroy()  # - destroy the root object
        # Clear N_Buffer_OrderList
        Classes.Node.N_Buffer_OrderList = [[], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], []]
        Classes.Node.N_Buffer = dict()  # - clear N_Buffer nested dictionary
        flood_start_gui()  # - restart the flood_start_gui

    # Run the flood_start_gui
    flood_start_gui()

# -------------------------------------------------------------------------------------------------------------------- #
# -------------------------------------------------------------------------------------------------------------------- #






