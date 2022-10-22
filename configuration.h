#ifndef __CONFIGURATION_H__
#define __CONFIGURATION_H__

/********************************************/
/************* USER CONFIGURATION ***********/
/********************************************/

/*  
 *   Wiring (ATtiny85):
 *                             +-------+
 *                            1|*      |8  VCC
 *                            2|       |7  SCL (SHT3X)
 *   Data TX RF 433Mhz - PB4  3|       |6  PB1 VCC to RF 433Mhz
 *                       GND  4|       |5  SDA (SHT3X)
 *                             +-------+
*/
  
/***
 * USAGE
 */

/* 
 * Choose your mode
 * 0 : Temperature                       [THN132N]
 * 1 : Temperature + Humidity            [THGR122N]

*/ 
 
#define MODE                    (1)

/* Roughly, how many SECONDS should I sleep between 2 transmissions ? */

#define SLEEPING_TIME_S         (60)

/* 
 * Should I ALWAYS send messages or ONLY NEW message ? 
 * 0 : Always send messages
 *      - even if the new message is the same as the last one (no data has changed)
 * 1 : Only send if there is a NEW message
 *      - only send a message if at least a data has changed since the last message
 *        (battery level alert, temperature, humidity or pressure in regard of the chosen MODE) 
*/

#define SEND_ONLY_NEW_MESSAGE   (0)

/*
 * Should I send a message twice ?
 * A real Oregon Scientific sensor sends a message twice but if you have a good RF reception, 
 * imho, sending a message twice is a waste of energy.
 * 0 : Don't send a message twice
 * 1 : Send a message twice
*/

#define SEND_MESSAGE_TWICE      (1)

/* Limit in mV for LOW Battery Alert */

#define LOW_BATTERY_ALERT       (2750)

/* Oregon Scientific protocol */

/* 
 * CHANNEL
 * You could safely keep this as is
*/

#define CHANNEL                 (0x10)

/* 
 * ID
 * Each sensor must have a unique ID
 * eg:
 * - first sensor:  0xCC 204
 * - second sensor: 0xCD 205
 * - third sensor:  0xCE 206
 * - fourth sensor: 0xCF 207
 * - fifth sensor:  0xD0
 * - etc...
*/

#define ID                      (0xCA)


/***
 * SHT3X PARAMETERS
 */
 
/* 
 * I2C address of the device
 * If you want to use address 0x45 set the appropriate pin to high
*/

#define SHT3X_I2C_ADDR         (0x44)

/* If needed, you can adjust the temperature in °C and the Relative Humidity % returned by the sensor */

#define ADJUST_TEMPERATURE_C    (-0.5)
#define ADJUST_RELATIVEHUMIDITY    (-3.0)


#
