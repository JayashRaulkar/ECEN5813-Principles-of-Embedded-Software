[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/meBZ0hNV)
[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-718a45dd9cf7e7f842a935f5ebbe5719a5e09af4491e668f4dbf3b35d5cca122.svg)](https://classroom.github.com/online_ide?assignment_repo_id=12220130&assignment_repo_type=AssignmentRepo)
# PES Assignment 4: DIA Trains

In assignment 4 I implemented a train monitoring system using a finite state machines, which has a terminal/baggage claim(T), two concourse stops A and B and train storageshed(S). An indicator light in the control room dashboard shows the current position of the train and it’s distance between the stops.

NOTE to TA's: You can set the touch offeset value in my "mytouch.h" header file at LINE 23.
             PLEASE KEEP YOUR FINGER ENTIRELY and just LIGHTLY touch. Thank you :D  ....

             For the Switch part i have used port D pin 5 (PTD5) [J2 junction 2 pin 4] as my switch. connect this to the ground pin to go into emergency state


## allfiles
-main.c [file calling all init functions and have my main function]
-all.h [all header files are included in this one header to avoid redundancy of including same headers multiple times]
-log.h [log header file to replace PRINTF by LOG to print only in DEBUG build ad set different delay value for DEBUG and RELEASE MODE]
-mypwm.h [header file having led positions and PWM_period]
-mypwm.c [file having different functions for TPM module intialisation and controlling leds, and the function declarations]
-mytouch.h [header file for touch having all macros required for touch and the function declarations]
-mytouch.c [file having different functions for touch initialization, and checkking the touch for emergency state and thier defination]
-mysystick.h [header file having function declarations for systick]
-mysystick.c [file containing systick initialization, its Handler and various other API functions]
-myfsm.h [header file having different macros for state colors and function declarations]
-myfsmk.c [file containing FSM function and the transition function]
-mtb.c [default file]
-semihost_hardfault.c [default file]