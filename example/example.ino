/*
 * An example usage of the FourSegDisplay Library with the Arduino Uno board
 * Date: 2020-12-18
 * Author: Shivam Sood
 */
#include <FourSegDisplay.h>

FourSegDisplay segment;

void setup() {
  // Set up custom pin connections 
  segment.setPinA(6);
  segment.setPinB(7);
  segment.setPinC(8);
  segment.setPinD(9);
  segment.setPinE(10);
  segment.setPinF(12);
  segment.setPinG(11);
  segment.setPinDot(13);
  segment.setPinC1(2);
  segment.setPinC2(3);
  segment.setPinC3(4);
  segment.setPinC4(5);

}

void loop() {
  //segment.printState(false); // Prints Off
  // Print a number to the display
  segment.printNum("243.4");
}
