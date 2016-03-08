# BJTU-GTD
Repository for the Game Tool Development module

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
- We don't have a framework that let having both P2P and client-server communication.


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

## 4. Architecture
![alt text](https://raw.githubusercontent.com/oborotev/BJTU-GTD/master/architecture/global.png)
## 5. Details of Components

## 6. Milestones
### 0.1.0
The framework encapsulate TCP protocol.

### 0.2.0
The framework let chat two users in basic P2P.

### 0.3.0
The framework encapsulate the client-server communication

### 1.0
The client and server part are done. Both P2P and Server-client are integrated.