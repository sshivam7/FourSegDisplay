/*
 * FourSegDisplay.h - Library for controlling a four digit seven segment display
 * Author: Shivam Sood 
 * Date: 2020-12-14
 * Released into the public domain
 */

#ifndef FourSegDisplay_h
#define FourSegDisplay_h

#include "Arduino.h"

class FourSegDisplay {
public:
    // Constructor 
    FourSegDisplay();

    // print string representation of a number to the display
    void printNum(String numToPrint) const;

    // print on or off to the display (true or false)
    void printState(boolean state) const;

    // print "Err" to the display
    void printErr() const;

    // clear the display
    void clearDisplay() const;

    // Set pin values 
    void setPinA(int pinA);

    void setPinB(int pinB);

    void setPinC(int pinC);

    void setPinD(int pinD);

    void setPinE(int pinE);

    void setPinF(int pinF);

    void setPinG(int pinG);

    void setPinDot(int pinDot);

    void setPinC1(int pinC1);

    void setPinC2(int pinC2);

    void setPinC3(int pinC3);

    void setPinC4(int pinC4);

private:
    // Private member variables
    int pinA_, pinB_, pinC_, pinD_, pinE_, pinF_, pinG_, pinDot_, pinC1_, pinC2_, pinC3_, pinC4_;

    // Select digit to print to on display
    void selectDigit(int const dig) const;

    // Validate input string 
    bool validateString(String str) const;

    // Print digit functions 
    void printZero() const;

    void printOne() const;

    void printTwo() const;

    void printThree() const;

    void printFour() const;

    void printFive() const;

    void printSix() const;

    void printSeven() const;

    void printEight() const;

    void printNine() const;
};

#endif
