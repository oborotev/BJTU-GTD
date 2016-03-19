# Communication Framework
This subdirectory contains the communication framework due for the 1st week.

# Table of Contents
## 1. Problems
## 2. Goals
## 3. User Story
## 4. Architecture
## 5. Details of Components
## 6. Milestones

# Design
## 1. Problems
- We don't have a framework that works easily on the 3 main desktop architectures : Linux, Windows and Mac

## 2. Goals
- Code a framework easy to use, to cover the 3 main systems.
- Permit the developer to use it for P2P features or client-server communication

## 3. User Story
### As a developer
- As a developer I want that the framework to be usable for P2P communication
- As a developer I want a class that covers the P2P communication and easy to use.
- As a developer I also want some classes that let client-server communication
- As a developer I want to use this framework independently from the fact that I'm working in a Windows, Linux or Mac environment.

### As a user
- As a user I want to be able to communicate to one person through an instant chat system
- As a user I want to chat with multiple people in a chatroom
- As a user I want to chat on my Windows OS, Linux OS or Max OS
- As a user I want to be able to chat from a graphical front-end and a console.

## 4. Architecture
![alt text](https://raw.githubusercontent.com/oborotev/BJTU-GTD/master/CommunicationFramework/architecture/global.png)
## 5. Details of Components

## 6. Milestones
### 0.1.0 (Current)
The framework let chat two users in basic P2P in console mode.

### 0.2.0
The framework let chat two users in basic P2P in graphical mode.

### 0.3.0
The framework encapsulate the client-server communication

### 0.4.0
The framework let multiple users chat in console mode.

### 0.5.0
The framework let multiple users chat in graphical mode.

### 1.0
The client and server part are done. Both P2P and Server-client are integrated.