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
    title: "Figure 2 - State Chart Diagram Depicting Concurrent Processes in Nodes 1 to 18 (Per Time Interval)"
    weight: 2

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


###	CRC Cards

###	Sequence Diagram

###	State Chart Diagram


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
