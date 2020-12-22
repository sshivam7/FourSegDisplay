/*
 * FourSegDisplay.cpp - Library for controlling a four digit seven segment display
 * Author: Shivam Sood 
 * Date: 2020-12-14
 * Version: 1.0
 * Released into the public domain
 */

#include "Arduino.h"
#include "FourSegDisplay.h"

// Default Constructor sets default pin values
// Segment control pins : 0 - 7
// Digit control pins : 8 - 11
FourSegDisplay::FourSegDisplay() {
    // Segment control pins
    pinMode(0, OUTPUT);
    pinA_ = 0;
    pinMode(1, OUTPUT);
    pinB_ = 1;
    pinMode(2, OUTPUT);
    pinC_ = 2;
    pinMode(3, OUTPUT);
    pinD_ = 3;
    pinMode(4, OUTPUT);
    pinE_ = 4;
    pinMode(4, OUTPUT);
    pinF_ = 5;
    pinMode(6, OUTPUT);
    pinG_ = 6;
    pinMode(7, OUTPUT);
    pinDot_ = 7;

    // Digit control pins
    pinMode(8, OUTPUT);
    pinC1_ = 8;
    pinMode(9, OUTPUT);
    pinC2_ = 9;
    pinMode(10, OUTPUT);
    pinC3_ = 10;
    pinMode(11, OUTPUT);
    pinC4_ = 11;
}

// Method takes string representation of a number and prints it to
// the 4 digit 7 segment display
void FourSegDisplay::printNum(String numToPrint) const {
    // Check the inputted string is a valid number to print
    if (validateString(numToPrint)) {
        int digitCounter = 1;
        // Loop through string characters to print the corresponding digits
        for (int i = 0; i < numToPrint.length(); ++i) {
            // select digit to print
            selectDigit(digitCounter);
            digitalWrite(pinDot_, HIGH);

            // print the corresponding number 
            switch (numToPrint.charAt(i)) {
                case '0':
                    printZero();
                    break;
                case '1':
                    printOne();
                    break;
                case '2':
                    printTwo();
                    break;
                case '3':
                    printThree();
                    break;
                case '4':
                    printFour();
                    break;
                case '5':
                    printFive();
                    break;
                case '6':
                    printSix();
                    break;
                case '7':
                    printSeven();
                    break;
                case '8':
                    printEight();
                    break;
                case '9':
                    printNine();
                    break;
                default: // add a decimal (.)
                    selectDigit(--digitCounter);
                    digitalWrite(pinDot_, LOW);
            }
            delay(1); // delay for stability
            ++digitCounter;
        }
    } else {
        // If the string is not a valid parameter print "Err" 
        // to the display 
        printErr();
    }
}

// Method to print state (on or off)
void FourSegDisplay::printState(boolean state) const {
    // Print first digit 'O'
    selectDigit(1);
    printZero();
    digitalWrite(pinDot_, HIGH);
    delay(1);

    // print on if state is true and Off if state is false
    if (state) {
        // print second digit
        selectDigit(2);

        // Print 'n'
        digitalWrite(pinA_, HIGH);
        digitalWrite(pinB_, HIGH);
        digitalWrite(pinC_, LOW);
        digitalWrite(pinD_, HIGH);
        digitalWrite(pinE_, LOW);
        digitalWrite(pinF_, HIGH);
        digitalWrite(pinG_, LOW);
        digitalWrite(pinDot_, HIGH);
        delay(1);
    } else { 
        // Loop to print the next two digits
        for (int i = 2; i <= 3; i++) {
            // Select the corresponding digit location
            selectDigit(i);

            // Print 'F'
            digitalWrite(pinA_, LOW);
            digitalWrite(pinB_, HIGH);
            digitalWrite(pinC_, HIGH);
            digitalWrite(pinD_, HIGH);
            digitalWrite(pinF_, LOW);
            digitalWrite(pinE_, LOW);
            digitalWrite(pinG_, LOW);
            digitalWrite(pinDot_, HIGH);
            delay(1);
        }
    }
}

// Method to print "Err" to display
void FourSegDisplay::printErr() const {
    // Select the first digit
    selectDigit(1);

    // print "E"
    digitalWrite(pinA_, LOW);
    digitalWrite(pinB_, HIGH);
    digitalWrite(pinC_, HIGH);
    digitalWrite(pinD_, LOW);
    digitalWrite(pinE_, LOW);
    digitalWrite(pinF_, LOW);
    digitalWrite(pinG_, LOW);
    digitalWrite(pinDot_, HIGH);
    delay(1);

    for (int i = 2; i <= 3; ++i) {
        // select the corresponding digit to print
        selectDigit(i);

        // print 'r'
        digitalWrite(pinA_, HIGH);
        digitalWrite(pinB_, HIGH);
        digitalWrite(pinC_, HIGH);
        digitalWrite(pinD_, HIGH);
        digitalWrite(pinE_, LOW);
        digitalWrite(pinF_, HIGH);
        digitalWrite(pinG_, LOW);
        digitalWrite(pinDot_, HIGH);
        delay(1);
    }
}


// Turn display off
void FourSegDisplay::clearDisplay() const {
    digitalWrite(pinC1_, LOW);
    digitalWrite(pinC2_, LOW);
    digitalWrite(pinC3_, LOW);
    digitalWrite(pinC4_, LOW);
}

// Select digit to write to
void FourSegDisplay::selectDigit(int const dig) const {
    // match the digit entered by the user to the corresponding 
    // digit found on the display 
    switch (dig) {
        case 1:
            digitalWrite(pinC1_, HIGH);
            digitalWrite(pinC2_, LOW);
            digitalWrite(pinC3_, LOW);
            digitalWrite(pinC4_, LOW);
            break;
        case 2:
            digitalWrite(pinC1_, LOW);
            digitalWrite(pinC2_, HIGH);
            digitalWrite(pinC3_, LOW);
            digitalWrite(pinC4_, LOW);
            break;
        case 3:
            digitalWrite(pinC1_, LOW);
            digitalWrite(pinC2_, LOW);
            digitalWrite(pinC3_, HIGH);
            digitalWrite(pinC4_, LOW);
            break;
        case 4:
            digitalWrite(pinC1_, LOW);
            digitalWrite(pinC2_, LOW);
            digitalWrite(pinC3_, LOW);
            digitalWrite(pinC4_, HIGH);
            break;
    }
}

// Method to validate string (check if string is a "printable" number)
// at most a 4 digit number with digits between 0-9
bool FourSegDisplay::validateString(String str) const {
    int dotCount = 0;
    int digitCount = 0;
    boolean wasDot = false;

    // loop through the string and evaluate each character 
    for (int i = 0; i < str.length(); ++i) {
        // Check to see if a decimal (.) had been repeated 
        if (str.charAt(i) == '.') {
            if (wasDot) {
                return false;
            }
            ++dotCount;
            wasDot = true;
            // Check to see if the character is a number between 0 and 9
        } else if ((str.charAt(i) - '0') >= 0 && (str.charAt(i) - '0') <= 9) {
            ++digitCount;
            wasDot = false;
        } else {
            return false;
        }
    }
    // Check to see that there are no more than 4 digits or 4 dots
    if (dotCount > 4 || digitCount > 4) {
        return false;
    }
    return true;
}

// Printing methods to print numbers to the display
void FourSegDisplay::printZero() const {
    digitalWrite(pinA_, LOW);
    digitalWrite(pinB_, LOW);
    digitalWrite(pinC_, LOW);
    digitalWrite(pinD_, LOW);
    digitalWrite(pinE_, LOW);
    digitalWrite(pinF_, LOW);
    digitalWrite(pinG_, HIGH);
}

void FourSegDisplay::printOne() const {
    digitalWrite(pinA_, HIGH);
    digitalWrite(pinB_, LOW);
    digitalWrite(pinC_, LOW);
    digitalWrite(pinD_, HIGH);
    digitalWrite(pinE_, HIGH);
    digitalWrite(pinF_, HIGH);
    digitalWrite(pinG_, HIGH);
}

void FourSegDisplay::printTwo() const {
    digitalWrite(pinA_, LOW);
    digitalWrite(pinB_, LOW);
    digitalWrite(pinC_, HIGH);
    digitalWrite(pinD_, LOW);
    digitalWrite(pinE_, LOW);
    digitalWrite(pinF_, HIGH);
    digitalWrite(pinG_, LOW);
}

void FourSegDisplay::printThree() const {
    digitalWrite(pinA_, LOW);
    digitalWrite(pinB_, LOW);
    digitalWrite(pinC_, LOW);
    digitalWrite(pinD_, LOW);
    digitalWrite(pinE_, HIGH);
    digitalWrite(pinF_, HIGH);
    digitalWrite(pinG_, LOW);
}

void FourSegDisplay::printFour() const {
    digitalWrite(pinA_, HIGH);
    digitalWrite(pinB_, LOW);
    digitalWrite(pinC_, LOW);
    digitalWrite(pinD_, HIGH);
    digitalWrite(pinE_, HIGH);
    digitalWrite(pinF_, LOW);
    digitalWrite(pinG_, LOW);
}

void FourSegDisplay::printFive() const {
    digitalWrite(pinA_, LOW);
    digitalWrite(pinB_, HIGH);
    digitalWrite(pinC_, LOW);
    digitalWrite(pinD_, LOW);
    digitalWrite(pinE_, HIGH);
    digitalWrite(pinF_, LOW);
    digitalWrite(pinG_, LOW);
}

void FourSegDisplay::printSix() const {
    digitalWrite(pinA_, LOW);
    digitalWrite(pinB_, HIGH);
    digitalWrite(pinC_, LOW);
    digitalWrite(pinD_, LOW);
    digitalWrite(pinE_, LOW);
    digitalWrite(pinF_, LOW);
    digitalWrite(pinG_, LOW);
}

void FourSegDisplay::printSeven() const {
    digitalWrite(pinA_, LOW);
    digitalWrite(pinB_, LOW);
    digitalWrite(pinC_, LOW);
    digitalWrite(pinD_, HIGH);
    digitalWrite(pinE_, HIGH);
    digitalWrite(pinF_, HIGH);
    digitalWrite(pinG_, HIGH);
}

void FourSegDisplay::printEight() const {
    digitalWrite(pinA_, LOW);
    digitalWrite(pinB_, LOW);
    digitalWrite(pinC_, LOW);
    digitalWrite(pinD_, LOW);
    digitalWrite(pinE_, LOW);
    digitalWrite(pinF_, LOW);
    digitalWrite(pinG_, LOW);
}

void FourSegDisplay::printNine() const {
    digitalWrite(pinA_, LOW);
    digitalWrite(pinB_, LOW);
    digitalWrite(pinC_, LOW);
    digitalWrite(pinD_, LOW);
    digitalWrite(pinE_, HIGH);
    digitalWrite(pinF_, LOW);
    digitalWrite(pinG_, LOW);
}

// Setter methods to set up pins 
void FourSegDisplay::setPinA(int pinA) {
    pinMode(pinA, OUTPUT);
    pinA_ = pinA;
}

void FourSegDisplay::setPinB(int pinB) {
    pinMode(pinB, OUTPUT);
    pinB_ = pinB;
}

void FourSegDisplay::setPinC(int pinC) {
    pinMode(pinC, OUTPUT);
    pinC_ = pinC;
}

void FourSegDisplay::setPinD(int pinD) {
    pinMode(pinD, OUTPUT);
    pinD_ = pinD;
}

void FourSegDisplay::setPinE(int pinE) {
    pinMode(pinE, OUTPUT);
    pinE_ = pinE;
}

void FourSegDisplay::setPinF(int pinF) {
    pinMode(pinF, OUTPUT);
    pinF_ = pinF;
}

void FourSegDisplay::setPinG(int pinG) {
    pinMode(pinG, OUTPUT);
    pinG_ = pinG;
}

void FourSegDisplay::setPinDot(int pinDot) {
    pinMode(pinDot, OUTPUT);
    pinDot_ = pinDot;
}

void FourSegDisplay::setPinC1(int pinC1) {
    pinMode(pinC1, OUTPUT);
    pinC1_ = pinC1;
}

void FourSegDisplay::setPinC2(int pinC2) {
    pinMode(pinC2, OUTPUT);
    pinC2_ = pinC2;
}

void FourSegDisplay::setPinC3(int pinC3) {
    pinMode(pinC3, OUTPUT);
    pinC3_ = pinC3;
}

void FourSegDisplay::setPinC4(int pinC4) {
    pinMode(pinC4, OUTPUT);
    pinC4_ = pinC4;
}
