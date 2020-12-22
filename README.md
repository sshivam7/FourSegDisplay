# FourSegDisplay 

FourSegDisplay is a library built to allow the Arduino Uno microcontroller
to interface with a four-digit 7-segment display. The library gives users the ability to quickly display numbers and other set messages such as on, off, or Err.

## Setup and Installation 
<img src="/images/seven-segment.png" width="200" align="right"> 

### Default Pin Setup 
#### Segment Control Pins 
pinA --> 2 &emsp;&emsp; pinB --> 3 &emsp;&emsp; pinC --> 4 &emsp;&emsp; pinD --> 5 &emsp;&emsp; pinE --> 6  
pinF --> 7 &emsp;&emsp; pinG --> 8 &emsp;&emsp; pinDot --> 9  

#### Digit Control Pins
pinC1 --> 10 &emsp;&emsp; pinC2 --> 11 &emsp;&emsp; pinC3 --> 12 &emsp;&emsp; pinC4 --> 13  


### Installation 
Download and move the FourSegDisplay folder into the libraries sub-directory
of your sketchbook directory. Then import the library into your code by 
selecting **Sketch >> Include Library**

## Usage 
```cpp
#include <FourSegDisplay.h>

FourSegDisplay segment;

void setup() {
  segment.setPinA(7);
   ...
}

void loop() {
  segment.printNum("243.4");
 }
```

## Functions
##### void printNum(String numToPrint) 
Takes a string representation of a number and prints it to the display. 
Must be a valid number:
- A maximum of 4 digits and no more than 4 decimals (none beside one another)
- Only digits between 0 and 9 are accepted

##### void printState(boolean state)
Take a boolean input and print the corresponding state to the display.
- true --> On 
- false --> Off

##### void printErr()
Print "Err" to the display

##### void clearDisplay()
Clear the display

### Notes
- If the string entered is invalid "Err" will be printed to the display 


## Author
Shivam Sood
