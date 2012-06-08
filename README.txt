ITG3200 Project

DESCRIPTION:
    This class is used to interface the Arduino with the ITG3200 digital 
    gyro sensor.
 
USAGE:
    The pressure sensor only needs 5 pins hooked up to use: two 3.3V, GND, I2C
    (SDA, SCL).
    
    See ITG3200.h header file for class information.

NOTES:
    If running on an Arduino that operates at 5V (e.g. UNO) it is recommended
    to use a logic level converter for the I2C interface because the sensor
    runs at 3.3V. However, it has been found that the sensor operates normally
    if it is hooked up directly to the Arduino.
 
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
       Initial release.
    