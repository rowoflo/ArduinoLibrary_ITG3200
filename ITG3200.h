/*
 -------------------------------------------------------------------------------
 ITG3200.h
 ITG3200 Project
 
 CLASS NAME:
    ITG3200
 
 DESCRIPTION:
    This class is used to interface the Arduino with the ITG3200 digital
    gyro sensor.
 
 FILES:
    ITG3200.h
    ITG3200.cpp
 
 DEPENDENCIES:
    Arduino.h
    Wire.h
 
 CONSTRUCTORS:
    ITG3200();
 
 PUBLIC METHODS:
    void initialize();
        Initializes the device. Must be done before device can be used.
        Note: A 4 second (20 sample) calibration is done with this
        function.
 
    int x();
        Get x-axis output value.
        
    int y();
        Get x-axis output value.
 
    int z();
        Get x-axis output value.
 
    void calibrate(int nSamples);
        Calibrate the device using a certain number of nSamples. Each
        sample takes 0.2 seconds for calibration. The device should remain
        completely motionless during calibration.
            nSamples - Number of nSamples to use.
 
    int calX();
        Get x-axis calibration value.
 
    int calY();
        Get y-axis calibration value.
 
    int calZ();
        Get z-axis calibration value.
 
 NOTES:
 
 EXAMPLES:
    Example 1: Initializing sensor and printing x, y, and z values.
    ----------------------------------------------------------------------------
    #include <Arduino.h>
    #include <ITG3200.h>
    ITG3200 itg;
    void setup() {
        Serial.begin(9600);
        itg.initialize();
        Serial.println(itg.x());
        Serial.println(itg.y());
        Serial.println(itg.z());
    }
    ----------------------------------------------------------------------------
 
 VERSIONS:
    1.0 - 1/12/12 - Rowland O'Flaherty (rowlandoflaherty.com)
 
 -------------------------------------------------------------------------------
 */

#ifndef _ITG3200_h_
#define _ITG3200_h_

//------------------------------------------------------------------------------
// Includes
//------------------------------------------------------------------------------
#include <Arduino.h>


class ITG3200 {
	
public:
	//--------------------------------------------------------------------------
	// Constants, Enums, and Types
	//--------------------------------------------------------------------------
	
	
	//--------------------------------------------------------------------------
	// Lifecycle
	//--------------------------------------------------------------------------
	
	// Constructors
	ITG3200();
	
	// Destructor
	virtual ~ITG3200();
	
	// Copy constructor
	ITG3200(const ITG3200& srcObj);
	
	//--------------------------------------------------------------------------
	// Overloaded Operators
	//--------------------------------------------------------------------------
	// Assignment operator
	const ITG3200& operator=(const ITG3200& rhsObj);
	
	//--------------------------------------------------------------------------
	// Public Member Functions
	//--------------------------------------------------------------------------
	void initialize();
	int x();
    int y();
    int z();
	void calibrate(int nSamples);
    
    int calX() { return _calX;}
    int calY() { return _calY;}
    int calZ() { return _calZ;}
	
private:
	//--------------------------------------------------------------------------
	// Lifecycle
	//--------------------------------------------------------------------------
	void copyHelper(const ITG3200& srcObj);
	
	//--------------------------------------------------------------------------
	// Private Member Functions
	//--------------------------------------------------------------------------
	byte readByte(byte address);
    void writeByte(byte address, byte value);
	
	//--------------------------------------------------------------------------
	// Private Member Variables
	//--------------------------------------------------------------------------
    // Device constant
    static const byte _ITG3200Address = 0x69; // I2C address of ITG3200
    
    // Register address
	static const char _SMPLRTDIV= 0x15;
    static const char _DLPF = 0x16;
    static const char _xH = 0x1D;
	static const char _xL = 0x1E;
    static const char _yH = 0x1F;
    static const char _yL = 0x20;
    static const char _zH = 0x21;
	static const char _zL = 0x22;
    
    static const char _DLPF0 = (0<<0);
    static const char _DLPF1 = (1<<1);
    static const char _DLPF2 = (0<<2);
    static const char _FS0 = (1<<3);
    static const char _FS1 = (1<<4);

    // Calibration variables
    int _calX;
    int _calY;
    int _calZ;
	
};

#endif
