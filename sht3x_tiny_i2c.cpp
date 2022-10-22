/*
    Tiny Library for SHT3X from Sensirion inspired by BME280 conurb's Library

    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version 2
    of the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

    DS used:
    https://www.sensirion.com/fileadmin/user_upload/customers/sensirion/Dokumente/2_Humidity_Sensors/Datasheets/Sensirion_Humidity_Sensors_SHT3x_Datasheet_digital.pdf

*/

#include <Arduino.h>
#include <Wire.h>
#include "configuration.h"
#include "sht3x_tiny_i2c.h"

static void
sht3x_write_register(uint8_t reg, uint8_t value)
{
  Wire.beginTransmission((uint8_t)SHT3X_I2C_ADDR);
  
  Wire.write((uint8_t)reg);
  Wire.write((uint8_t)value);
  Wire.endTransmission();
}

static uint8_t
sht3x_read_register(uint8_t len, uint8_t* data)
{
  uint8_t  received_bytes  = 0;
  uint8_t  remaining_bytes = len;
  uint8_t* data_received   = data;

  Wire.beginTransmission((uint8_t)SHT3X_I2C_ADDR);
  Wire.endTransmission();
  Wire.requestFrom((uint8_t)SHT3X_I2C_ADDR, len);

  while (Wire.available() && remaining_bytes--) {
    *data_received++ = Wire.read();
    ++received_bytes;
  }
  return (received_bytes == len) ? 1 : 0;
}


uint8_t
sht3x_read_sensor(SHT3X* sht)
{
  // Measurement Commands for Single Shot Data Acquisition Mode
  // this selection affect the power consumption
  sht3x_write_register(SHT3X_REG_CS_DIS, SHT3X_CMD_CS_DIS_LOW); // Clock Stretching Disable Medium
  // wait to ensure complete measurement
  delay(50);

  uint8_t sensor_data[SHT3X_T_H_DATA_LEN] = { 0 };

  // get adc values the 6 follwing bit after having written in Single Shot data acquisition
  uint8_t ret = sht3x_read_register(SHT3X_T_H_DATA_LEN, sensor_data);
  if (!ret)
    return 0;
  // temperature data (adc_t)
  const uint16_t adc_t = (uint16_t)sensor_data[0] << 8 |
                         (uint16_t)sensor_data[1];
  // humidity data (adc_h)
  const uint16_t adc_h = (uint16_t)sensor_data[3] << 8 |
                         (uint16_t)sensor_data[4];

  sht->temperature = 0;
  sht->humidity    = 0;


  // Returns temperature in DegC, resolution is 0.01 DegC.
  if (adc_t != 0x80000)
  {

    sht->temperature = (-45.0 + (175.0 * adc_t / 65535.0) + ADJUST_TEMPERATURE_C) ;
  }
  else
  return 0; // we can't compensate others measurements without t_fine define by temperature


  if (adc_h != 0x80000)
  {
    sht->humidity = (100.0 * adc_h / 65535.0 + ADJUST_RELATIVEHUMIDITY);
  }

  return 1;
}

uint8_t
sht3x_init(SHT3X* sht)
{
  Wire.begin();

  

  // clear status register
  sht3x_write_register(SHT3X_REG_CLEARSR, SHT3X_CMD_CLEARSR );

  // DS 1.1
  // start-up time : max 2 ms (take 5)
  delay(5);


  return 1;
}
