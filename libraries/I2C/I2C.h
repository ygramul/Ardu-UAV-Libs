/*
 * Library for I2C/Wire communication. Inspired of MultiWiiCopter V 1.7
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
 */
#ifndef I2C_H
#define I2C_H
   
#include <WProgram.h> //It is very important to remember this!
       
#define I2C_SPEED_FAST 400000L     //400kHz 
#define I2C_SPEED_NORMAL 100000L     //100kHz 

#define I2C_PULLUPS_ENABLE         PORTC |= 1<<4; PORTC |= 1<<5;   // PIN A4&A5 (SDA&SCL)
#define I2C_PULLUPS_DISABLE        PORTC &= ~(1<<4); PORTC &= ~(1<<5);

// Mask prescaler bits : only 5 bits of TWSR defines the status of each I2C request
#define TW_STATUS_MASK	(1<<TWS7) | (1<<TWS6) | (1<<TWS5) | (1<<TWS4) | (1<<TWS3)
#define TW_STATUS       (TWSR & TW_STATUS_MASK)

static uint32_t neutralizeTime;

void i2c_init(boolean internal_pullups_activate, boolean fast_mode);
void i2c_rep_start(uint8_t address);
void i2c_write(uint8_t data );
uint8_t i2c_readAck();
uint8_t i2c_readNak(void);
void waitTransmissionI2C();
void checkStatusI2C();

#endif

