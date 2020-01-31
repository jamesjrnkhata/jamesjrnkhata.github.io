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

<span class="custom-tablecaption">Table 1.2.1 Stakeholder Requirements for the Car Park Management System</span>

|               |                        |
| ------------- | :--------------------: |
| Staff | •	Surveillance cameras for protection of self and vehicle<br> * Discount parking to other sites as a visitor <br> *	Designated parking for employees |


<h2 class="text-underline">Use-Case Model</h2>

###	Brain storm

###	Scenario Descriptions

###	Class Identification

###	Stereotypical Classes

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
