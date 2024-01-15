[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/WwRztHTa)
[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-718a45dd9cf7e7f842a935f5ebbe5719a5e09af4491e668f4dbf3b35d5cca122.svg)](https://classroom.github.com/online_ide?assignment_repo_id=11995946&assignment_repo_type=AssignmentRepo)
# PES Assignment 3: TrafficLights

In assignment 3 I implemeted an startup  led sequence [W B B W] and main sequence [R G Y] between which i was polling fot touch sensor and according to the right or left side touch i blinked either W or B.

NOTE to TA's: You can set the touch offeset value in my "mytouch.h" header file at LINE 24.
              Also as i have my NSCN value set to 32, indicating the scan number for each electrode is 32 while touching the touch sensor PLEASE KEEP YOUR FINGER ENTIRELY and like dont just lightly touch. Thank you :D  ....

## Code Review Comments
* Comment 1: Use of "all.h" header file makes it difficult to understand the dependencies, and could lead to problems maintaining the code later on. You could fix that by only including header files that a required in that specific .c or .h file
    - Response 1: The main purpose behind creating an all.h file was to avoid writing #include of differnt headerfiles in multiple .c files. By creating a single all.h  file i was able to just include this one header all.h whereever necessary. Also all my headers like mytouch.h or myled.h or log.h are guarded with #ifndef preprocessor directives so the same headers will not be included multiple times.

* Comment 2: Light/gentle touches on the left side register as touches on the right side and blink the blue led. This could be resolved by increasing your threshold for a touch or by using two electrodes which lie on opposite sides of the touch sensor, so you could compare their value and figure out which side was touched.
    - Response 2: I have modified the right threshold value as per suggested by code reviewer.

* Comment 3: It is great that you have cited sources for the code that was adapted from a source. But, according to ESE guidelines, you must also provide a URL link to the repository from which the code was adapted.
    - Response 3: I have now also included the link to the sources that i have used.

* Comment 4: Your code is readable and easy to follow, you can remove quite a few of the comments that you have put for self explanatory code. You can reserve comments for complex/difficult to follow lines of code. You can put these comments in the function description comment bloc. An example of the extra use of comments on self explanatory code can be seen here: https://github.com/ECEN5813/assignment-3-JayashCUB/blob/42a3060447e9147640488d30cee04acd2858277f/source/mytouch.c#L93C1-L109C2. The general functioning for these lines of code can be put in the function description comment bloc.
    - Response 4: Removed the unnecessary self explainatory comments from the project.

* Comment 5: Function description and file description comments are not present as required by ESE guidelines. Adding these will make your code easier to follow, understand and maintain.
    - Response 5: File and function description for each file at the top and for fucntion at the top of function defination has beeen added.


## allfiles
-Assg3_TrafficLights_MKL25Z4_project.c [file calling all init function and have my main function]
-all.h [all header files are included in this one header to avoid redundancy of including same headers multiple times]
-log.h [log header file to replace PRINTF by LOG to print only in DEBUG build]
-myled.h [header file for leds having all macros required for led and the function declarations]
-myled.c [file having different functions for leds and thier defination]
-mytouch.h [header file for touch having all macros required for touch and the function declarations]
-mytouch.c [file having different functions for touch and thier defination]
-mtb.c [default file]
-semihost_hardfault.c [default file]

## objdump 
Note: a text file containg the output of objdump for size and addresses is also added in repo
cmd promt instructions:
C:\nxp\MCUXpressoIDE_11.8.0_1165\ide\tools\bin\arm-none-eabi-objdump -h -S "C:\SEM 1 PES\PES Assignment 3\assignment-3-JayashCUB\Release\TrafficLights.axf" > output.txt

C:\nxp\MCUXpressoIDE_11.8.0_1165\ide\tools\bin\arm-none-eabi-objdump -t "C:\SEM 1 PES\PES Assignment 3\assignment-3-JayashCUB\Release\TrafficLights.axf" > output2.txt

## size and address of:
Address of main function: 00000740
Size of mydelay function: 00000016 (22bytes)
Size of .text segment: 0000182c (6188 bytes = 6.188 kB)
Size of .data segment: 00000008 (8bytes)
Stack size: 00000000 (Not sure but as i was unable to understand properly)