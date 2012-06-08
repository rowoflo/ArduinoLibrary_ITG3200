/*
 -------------------------------------------------------------------------------
 ITG3200.cpp
 ITG3200 Project
 
 Initially created by Rowland O'Flaherty (rowlandoflaherty.com) on 1/12/12.
 
 Version 1.0
 -------------------------------------------------------------------------------
 */

//------------------------------------------------------------------------------
// Includes
//------------------------------------------------------------------------------
#include "ITG3200.h"
#include <Arduino.h>
#include <Wire.h>

//------------------------------------------------------------------------------
// Lifecycle
//------------------------------------------------------------------------------

// Constructors
ITG3200::ITG3200()
:
_calX(0),
_calY(0),
_calZ(0) {
	
}

// Destructor
ITG3200::~ITG3200() {
	
}

// Copy constructor
ITG3200::ITG3200(const ITG3200& srcObj) {
	copyHelper(srcObj);
}

// Copy helper function
void ITG3200::copyHelper(const ITG3200& srcObj) {
	_calX = srcObj._calX;
	_calY = srcObj._calY;
	_calZ = srcObj._calZ;
}

//------------------------------------------------------------------------------
// Overloaded Operators
//------------------------------------------------------------------------------

// Assignment operator
const ITG3200& ITG3200::operator=(const ITG3200& rhsObj) {
	// Self-assignment check
	if (this == &rhsObj) {
		return (*this);
	}
	
	// Free old memory
	
	// Copy new memory
	copyHelper(rhsObj);
	
	return (*this);
}

//------------------------------------------------------------------------------
// Public Member Functions
//------------------------------------------------------------------------------
void ITG3200::initialize() {
    // Initialize device
    Wire.begin();

    //Configure device
    //Set the gyroscope scale for the outputs to +/-2000 degrees per second
    writeByte(_DLPF, (_DLPF2|_DLPF1|_DLPF0));
    //Set the sample rate to 100 hz
    writeByte(_SMPLRTDIV, 4);

    // Calibrate device
	ITG3200::calibrate(20);
}

int ITG3200::x() {
    byte xH = readByte(_xH);
    byte xL = readByte(_xL);
    return (int)(xH << 8 | xL) - _calX;
}

int ITG3200::y() {
    byte yH = readByte(_yH);
    byte yL = readByte(_yL);
    return (int)(yH << 8 | yL) - _calY;
}

int ITG3200::z() {
    byte zH = readByte(_zH);
    byte zL = readByte(_zL);
    return (int)(zH << 8 | zL) - _calZ;
}

void ITG3200::calibrate(int nSamples) {
	long sumX = 0, sumY = 0, sumZ = 0;
	int tempX, tempY, tempZ;
	byte xH, xL, yH, yL, zH, zL;

	for (int n=1; n<=nSamples; n++) {
        delay(200);
        
		xH = readByte(_xH);
		xL = readByte(_xL);
		tempX = (int)(xH << 8 | xL);

		yH = readByte(_yH);
		yL = readByte(_yL);
    		tempY = (int)(yH << 8 | yL);

		zH = readByte(_zH);
    		zL = readByte(_zL);
    		tempZ = (int)(zH << 8 | zL);

		sumX += (long)tempX;
		sumY += (long)tempY;
		sumZ += (long)tempZ;
	}
    
	_calX = (int)(sumX / nSamples);
	_calY = (int)(sumY / nSamples);
	_calZ = (int)(sumZ / nSamples);
}

//------------------------------------------------------------------------------
// Private Member Functions
//------------------------------------------------------------------------------
byte ITG3200::readByte(byte address) {
    // Read 8 bits or 1 byte out EEPROM registers at the given address
    Wire.beginTransmission(_ITG3200Address);
    Wire.write(address);
    Wire.endTransmission();
    
    Wire.requestFrom((int)_ITG3200Address, 1);
    while(!Wire.available());
    
    return Wire.read();
}

void ITG3200::writeByte(byte address, byte value) {
    // Write 8 bits or 1 byte into E2PROM registers at the given address
    Wire.beginTransmission(_ITG3200Address);
    Wire.write(address);
    Wire.write(value);
    Wire.endTransmission();
}
