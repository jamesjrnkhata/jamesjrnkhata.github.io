---
title: "Car Park Management System (UML)"
date: 2019-06-10
categories: [software-projects]
permalink: /:categories/:title/
feature_img: /images/software_projects/carparkmanagementsystem/carparkmanagementsystem_img00.jpg
excerpt: "uml, oop, ood, software, car park, management"
purpose: "This report outlined the steps taken towards the development of the car park management system through an object-oriented design approach using Unified Modelling Language (UML) notation."
toc: true
classes: wide
images:
  - image_path: /images/software_projects/carparkmanagementsystem/carparkmanagementsystem_img01.jpg
    title: "Figure 1 - Use-Case Diagram"
    weight: 1
  - image_path: /images/software_projects/carparkmanagementsystem/carparkmanagementsystem_img02.jpg
    title: "Figure 2 - Class Diagram (Stereotypes)"
    weight: 2
  - image_path: /images/software_projects/carparkmanagementsystem/carparkmanagementsystem_img03.jpg
    title: "Figure 3 - Sequence Diagram (Car Park Management System) 1"
    weight: 3
  - image_path: /images/software_projects/carparkmanagementsystem/carparkmanagementsystem_img04.jpg
    title: "Figure 3 - Sequence Diagram (Car Park Management System) 2"
    weight: 4    
  - image_path: /images/software_projects/carparkmanagementsystem/carparkmanagementsystem_img05.jpg
    title: "Figure 3 - Sequence Diagram (Car Park Management System)"
    weight: 5        
  - image_path: /images/software_projects/carparkmanagementsystem/carparkmanagementsystem_img06.jpg
    title: "Figure 4 - State Chart Diagram (Car Park Management System) 1"
    weight: 6
  - image_path: /images/software_projects/carparkmanagementsystem/carparkmanagementsystem_img07.jpg
    title: "Figure 4 - State Chart Diagram (Car Park Management System)"
    weight: 7    
  - image_path: /images/software_projects/carparkmanagementsystem/carparkmanagementsystem_img08.jpg
    title: "Figure 5 - "
    weight: 8      
---

<h2 class="text-underline">Introduction</h2>

Software design for a car park management system was required to control access to car parks and automate how users were charged. The system was required to grant users access in and out of specific car parks through a form of identification card or embedded device. Staff users from different organizations were to be charged through their organization’s payroll. The system was also required to extend its users to paying and non-paying visitors.

This report outlines the steps taken towards the development of the car park management system through an object-oriented design approach using Unified Modelling Language (UML) notation.

###	Interpretation of Specifications

The initial specifications were obtained from the client for the car park management system. It was stated that the system was required to automate the process of charging and admitting users in and out of a car park (multiple sites). The charging was done based on two periods, long-stay at a flat rate and short-stay at no charge.

To gain access, the user had an identity card or transponder. This was read (scanned for transponder) in order to raise a barrier that would let them in or out of the car park and finish by bringing the barrier back down. Once raised, the barriers were supposed to give the car enough time to drive through without coming down on it. The process of raising and lowering the barrier was supposed to be done at a rate that did not slow traffic in or out of the car park.

The system was to be operated by three types of users: organization staff, visitors and security.

The assumption was made that the organization staff were referring to those of various companies that used the car parks (multiple locations), hence the charging to payrolls. Each user was only allowed to use specific car park sites. The user’s identity card or transponder was used to verify if they were allowed access to that car park (through a database). The staff’s long-stay flat-rate charges were made and withdrawn from their wages (payroll). Short-stay periods were not charged.

In the case of visitors, an assumption was made that the non-paying applied to accessing the car park for a short-stay period. Visitors would have to pay if they stayed longer than the short period allocated time. The visitors would be issued a ticket on entry into a car park and use it to exit as well. If they left before the short-stay time expired they would not be charged, however if they stayed beyond it they could use a payment machine to pay for the long-stay charge.  

The final user was the security staff capable overriding the barrier control for any car park site by raising and lowering them remotely.

The assumptions made were verified and validated after further elicitation of the requirements from the stakeholders.

###	Stakeholder Requirements

The stakeholders were identified, and the specifications were clarified. Further requirements were obtained from stakeholders, these included:

<span class="custom-tablecaption">Table 1: Stakeholder Requirements for the Car Park Management System</span>

|               |                       |
| ------------- | --------------------- |
| Staff | •	Surveillance cameras for protection of self and vehicle <br> • Discount parking to other sites as a visitor <br> • Designated parking for employees |
| Visitors | • Cheaper rates for long-stay parking <br> •	Availability of disabled parking bays and accessibility |
| Security | • Intercom (telephone) to each car park entrance or exit for assistance |


<h2 class="text-underline">Use-Case Model</h2>

###	Brain storm

The potential requirements were identified with their predicted costs and priority.

<span class="custom-tablecaption">Table 2: Prioritisation of Potential requirements</span>

| Concept | Necessity | Cost | Priority |
| --------------------------------------------------- | -------------- |  -------------- | -------------- |
| Scan identity card for staff | High |	Medium | Medium |
| Confirm permission to enter car park | High | Medium | High |
| Charge parking to pay-roll for staff |	Medium | High	| High |
| Allow car into the car park | Medium | Medium |	Medium |
| Allow car out of the car park | Medium | Medium	| Medium |
| Avoid lowering barrier on cars (detect car)	| High | Medium | High |
| Charge visitors long-stay parking	| Medium | Medium	| Medium |
| Do not charge visitor for short-stay parking	| Medium | Medium	| Medium |
| Dispense visitor’s identity card (parking ticket)	| High | Medium	| Medium |
| Scan visitor’s ticket on leaving the car park	| High |Low	| Medium |
| Accept payment from payment machine	| Medium | High |	Medium |
| Display time spent in car park | Low | Low | Low |
| Remotely control barrier | High | Medium	| High |
| Allow authorised access and changes to database	| High | High	| High |


The costs associated with incorporating the potential requirements were justified to fall within the intended budget for the car park management system. Therefore, the design was able to include all the potential requirements.

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

The use-case diagram in figure 1 depicted the relationship between the actors and use cases. The relationships were divided into three general scenarios, accessing the car park software by the System Administrator, entering the car park (left of the diagram) and existing the car park (right side of the diagram).

In the scenario of entering the car park, the visitor had used a different set of use cases to enter the car park from the staff hence why the diagram depicted them sharing the open/close barrier use case. Exiting the car park shared a similar depiction in the use-case diagram for the visitor and staff actors where they used different use-cases from each other to exit the car park.

###	Scenario Descriptions

|                                  |                                                                                     |
| -------------------------------- | ----------------------------------------------------------------------------------- |
| User (visitor) at car park entry: | An obstacle sensor would pick up the user’s (visitor) car arriving at the entrance of the car park. The user would request for a parking ID (ticket) by pushing a button on a panel located near the entrance. When the ID was issued, the system would wait for the user to collect the ID. After ID collection, the barrier would be raised. When the obstacle sensor was cleared of the car while barrier was up the barrier would be brought down. |
| User (staff) at car park entry: | An obstacle sensor would pick up the user’s (staff) car arriving at the entrance of the car park. The user would present their ID card to a scanner on a panel located near the entrance. The ID would be verified by checking the details on a database that stored access for staff users to each car park. If the authorization fails, then the ID would be returned to the user informing them on a Display that they are not eligible to use the car park. When authorization, then the ID would be issued back to the user. When the ID was collected, the barrier would be raised. When the obstacle sensor was cleared of the car while barrier was up the barrier would be brought down. |
| User (system administrator) accessing car park software: | An obstacle sensor would pick up the user’s (visitor) car arriving at the exit of the car park. The user would present their ID card (visitor’s ID) to a scanner on a panel located near the exit. If the time accumulated on the card was below the set short-stay duration, then the barrier would be raised and panel would retain the ID. If the time accumulated on the card was above the set short-stay period, then the cost for the time spent over (long-stay) would be calculated. The amount would be displayed to the user with a prompt for them to pay through cash / card payment terminal. After payment was made and authorised, the barrier would be raised. When the ID was collected, the barrier will be raised. When the obstacle sensor was cleared of the car while barrier was up the barrier would be brought down. An inquiry button would be available to contact Security for assistance. |
| User (staff) at car park exit: | An obstacle sensor would pick up the user’s (staff) car arriving at the exit of the car park. The user would present their ID card (staff ID) to the scanner on a panel located near the exit. If the time accumulated on the card was below the set short-stay duration, then no charge would be made to their account (through their payroll). If the time accumulated on the card was above the set short-stay period, then the cost for the time spent over (long-stay) would be calculated and then charged to their account.  Their ID card would be returned to them. When the ID was collected, the barrier will be raised. When the obstacle sensor was cleared of the car while barrier was up the barrier would be brought down. An enquiry button would be available to contact Security for assistance. |
| User (security) remote accessing the barriers: | A remote connection to the desired car park barriers (entry or exit) controller would be established. The status of the obstacle sensors for that barrier would be read. The barriers would be remotely raised. The barrier would be remotely lowered. |


###	Class Identification

To identify the classes from the scenario descriptions all the nouns were listed from each scenario.

<span class="custom-tablecaption">Table 2: List of Nouns from the Scenario Descriptions</span>

|                                                                         |                                                                                     |
| ----------------------------------------------------------------------- | ----------------------------------------------------------------------------------- |
| Nouns identified were: | Car, Entry, Exit, Car Park, Visitor, Staff, Security, System Administrator, User, Parking ID, Staff ID, Panel, Display, Button, Inquiry Button, System, Barrier, Scanner, Obstacle Sensor, Payment Terminal, Remote Connection, Remotely,  Database, Account, Charge, Pay-roll, Status, Side, Details, Authorization, Information, Access, Time, Cost, Amount, Card, ID, ID Card. |
| Nouns that described items that were external to the software to be designed were: | Car, Visitor, User, Staff, Security, System Administrator, Entry, Exit and Car Park. |
| Nouns that were synonymous and hence repeated were: | Authorization and Access. <br>Information and Details. <br>Card, ID, ID Card, Parking ID and Staff ID. |
| Nouns that were events carried out in the system (that could later be identified as methods) were: | Charge and Authorize. |
| Nouns that could be identified as attributes of the system were: | Details, Information, Amount, Cost, Time and Status. |  

Most of the nouns that were identified in the sub groups above were eliminated from the list of potential classes. The remaining nouns were further refined to achieve the minimal set of classes:

The noun “system” was renamed to “Car park Controller”. Payment terminal, panel, scanner, button, inquiry button, obstacle sensor and display were integrated into one “Terminal”.  The terminal was to be used by the staff and visitor. The remote access was used by the security (user).

###	Stereotypical Classes

The minimum set of classes were defined as:

Boundary:

*	Terminal – This was set to boundary class because it had payment terminal, buttons, display and obstacle sensor, which were used for the actor to interface with the system.
*	Barrier – This was set as a boundary class because it allowed the actors to interact with other use cases of the system (start timing the user and let the user further interact with the car park).  
*	Remote Connection – This was set as a boundary class because it bridged the security user (remotely to the system).

Control:

*	Car park Controller – This was set as a control class because it was responsible for controlling coordination and sequencing of the objects within the system.

Entity:

*	Database – The database was set to entity class because it was used to store information to do with users.
*	Real-Time Clock – Was set in the entity class because it managed timing information.  

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

###	CRC Cards

<span class="custom-tablecaption">Table 3: Class Responsibility Collaboration Cards</span>

| <strong>Class: Terminal</strong> |                |
| -------------------------------------- | --------------------- |
| <strong>Responsibilities | <strong>Collaborators</strong> |
|The terminal class was responsible for dispensing visitor ID, scanning ID (staff ID and visitor ID when existing), handling payment transactions, displaying information, detecting a car’s presence and establishing a call to security. The terminal class displayed relevant information regarding the calculated duration of their stay (visitor), the cost and the eligibility of using that car park (staff). The terminal class read its sensor information to detect a car next to the terminal. The terminal class also issued a visitor ID when the button (dispense button) was pressed. Scanning of an ID was also done by the terminal class (into the car park by staff and out of the car park for both visitor as well as staff). The terminal class took payments for visitor ID when the duration in the car park was longer than the designated short stay period. The terminal class let the user (visitor/staff) talk to a member of security by pressing a button (intercom).      | Car park Controller |

| <strong>Class: Real-Time Clock</strong> |                |
| -------------------------------------- | --------------------- |
| <strong>Responsibilities | <strong>Collaborators</strong> |
| The real-time clock class was responsible for keeping track of how long the staff and visitor were in the car park. When a user was let through the barrier into the car park the time they got in would be documented, when they left the car park the real-time clock class would document the current time they have scanned their ID and process the time spent for charging in minutes. | Car park Controller |

| <strong>Class: Barrier</strong> |                |
| -------------------------------------- | --------------------- |
| <strong>Responsibilities | <strong>Collaborators</strong> |
| The barrier class was responsible for raising and lowering the barrier. The barrier class responded to control signals from the Car park Controller to either raise the barrier or lower the barrier. | Car park Controller  |

| <strong>Class: Remote Connection</strong> |                |
| -------------------------------------- | --------------------- |
| <strong>Responsibilities | <strong>Collaborators</strong> |
| The remote connection class was responsible for establishing a link between the security’s remote location and the Car park Controller. The security user to the Car park Controller established a communication connection (example internet), this was then used to send request signals to raise and lower the barrier. | Car park Controller |

| <strong>Class: Car park Controller</strong> |                |
| -------------------------------------- | --------------------- |
| <strong>Responsibilities | <strong>Collaborators</strong> |
| The car park controller class was responsible for facilitating payment transactions, deciding when to raise and lower the barrier. The car park controller class responded to signals from the user interface and the remote link from the security (user). The car park controller class would determine how much time was spent in the car park and charge the user accordingly. The car park controller would allow the system administrator access and modify the database. The car park controller class would determine when to raise and lower the barrier based on: <br><br> 1.	The signal from the car detected by the obstacle sensor was received as well as the signal from the remote connection. The barriers were raised and once the obstacle sensor cleared, the barrier was lowered. <br><br> 2.	A signal was received from the obstacle sensor when a car was detected and data from the scanner unit of the terminal when an ID was scanned. The scanner data was used to verify access with the database. After confirmation, the barriers were raised and once the obstacle sensor cleared, the barrier was lowered. <br><br> 3.	A signal was received from the obstacle sensor when a car was detected. A button press would issue out an ID. After collection, the barriers would be raised and once the obstacle sensor cleared, the barrier would be lowered. When visitor existed the car park, the entry cost would have to be settled by payment before raising and lowering of the barrier. | Barrier, Database, Terminal, Remote Connection, Real-Time Clock |

| <strong>Class: Database</strong> |                |
| -------------------------------------- | --------------------- |
| <strong>Responsibilities | <strong>Collaborators</strong> |
| The database class was responsible for storing information to do with authorizing (staff) and charging of the long-stay periods spent in the car park. When a query was received to access information relative to a specific ID, table entry results would be returned in response to the query. The query results would then be used to confirm access into a car park or not. On exiting the car park, a table entry would be added to that of the ID counting how much time was spent in the car park, this count would be forwarded to the respective company to be deducted from their payroll monthly.  For visitor ID the query would be made in the database in relation to time spent in the car park and used to produce a cost. After payment, the cost table entry would be marked as settled giving access out of the car park. | Car park Controller |

###	Sequence Diagram

Potential Method Identification

|                                   |                                   |
| --------------------------------- | --------------------------------- |
| <strong>Car park Controller</strong> <br><br>1.	VerifyEntry() <br>2.	CalculateDuration()	| <strong>Real-Time Clock</strong> <br><br>1.	GetTime() |
| <strong>Terminal</strong> <br><br>1. GetSensorData() <br>2.	UpdateDisplay()<br>3.	CheckIDCollection()	| <strong>Remote Connection</strong> <br><br>1.	Connect() |
| <strong>Database</strong> <br><br>1.	GetDatabaseInformation() <br>2.	SetStartTime() <br>3.	SetEndTime() <br>4.	SetDuration()	| <strong>Barrier</strong> <br><br>1.	OpenBarrier() <br>2.	CloseBarrier() |

The sequence diagram (excluding the Collaboration Diagram as it represented the same information) was the choice of interaction diagram used to show the order of interactions between the objects and the messages sent as time progressed in the system.

<ul class="photo-gallery">
  {% for image in page.images %}
    {% if image.weight == 3 %}
      <li>
        <img src="{{ image.image_path }}" alt="{{ image.title }}">          
        {{ image.title }}                    
      </li>
    {% endif %}  
  {% endfor %}  
</ul>

<ul class="photo-gallery">
  {% for image in page.images %}
    {% if image.weight == 4 %}
      <li>
        <figure class="custom-figure">
          <img src="{{ image.image_path }}" alt="{{ image.title }}">          
          {{ image.title }}          
        </figure>  
      </li>
    {% endif %}  
  {% endfor %}  
</ul>

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


###	State Chart Diagram

The state chart was used to describe the different states of the system driven by internal and external events.

<ul class="photo-gallery">
  {% for image in page.images %}
    {% if image.weight == 6 %}
      <li>
        <figure class="custom-figure">
          <img src="{{ image.image_path }}" alt="{{ image.title }}">          
          {{ image.title }}          
        </figure>  
      </li>
    {% endif %}  
  {% endfor %}  
</ul>

<ul class="photo-gallery">
  {% for image in page.images %}
    {% if image.weight == 7 %}
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

<h2 class="text-underline">Analysis Model</h2>

###	Attributes

###	Methods

###	Sequence Diagram

###	Class Diagram

###	State Chart Diagram

###	Non-functional Requirements

###	Packages


<h2 class="text-underline">Design Model</h2>

###	Revisit Use-Case Model

###	Sequence Diagram

###	Textual Description of Object to Object Interaction

###	Subsystems

###	Implementation of Non-functional Requirements

###	Deployment Model

###	Legacy Issues

###	Reconsidered Attributes

###	Reconsider the Associations

###	State Chart (Revision)

###	Class Diagram Showing Visibility


<h2 class="text-underline">Conclusion</h2>

<h2 class="text-underline">References</h2>
