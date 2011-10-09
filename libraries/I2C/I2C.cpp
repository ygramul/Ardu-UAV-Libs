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
#include "I2C.h" //include the declaration for this class
       
void i2c_init(boolean internal_pullups_activate, boolean fast_mode) {
  if (internal_pullups_activate) {
    I2C_PULLUPS_ENABLE
  } else {
    I2C_PULLUPS_DISABLE
  }
  TWSR = 0;        // no prescaler => prescaler = 1
  if (fast_mode) {
    TWBR = ((16000000L / I2C_SPEED_FAST) - 16) / 2; // change the I2C clock rate
  } else {
    TWBR = ((16000000L / I2C_SPEED_NORMAL) - 16) / 2; // change the I2C clock rate
  }
  TWCR = 1<<TWEN;  // enable twi module, no interrupt
}

void i2c_rep_start(uint8_t address) {
  TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN) | (1<<TWSTO); // send REAPEAT START condition
  waitTransmissionI2C(); // wait until transmission completed
  checkStatusI2C(); // check value of TWI Status Register
  TWDR = address; // send device address
  TWCR = (1<<TWINT) | (1<<TWEN);
  waitTransmissionI2C(); // wail until transmission completed
  checkStatusI2C(); // check value of TWI Status Register
}

void i2c_write(uint8_t data ) {	
  TWDR = data; // send data to the previously addressed device
  TWCR = (1<<TWINT) | (1<<TWEN);
  waitTransmissionI2C(); // wait until transmission completed
  checkStatusI2C(); // check value of TWI Status Register
}

uint8_t i2c_readAck() {
  TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);
  waitTransmissionI2C();
  return TWDR;
}

uint8_t i2c_readNak(void) {
  TWCR = (1<<TWINT) | (1<<TWEN);
  waitTransmissionI2C();
  return TWDR;
}

void waitTransmissionI2C() {
  uint8_t count = 255;
  while (count-->0 && !(TWCR & (1<<TWINT)) );
  if (count<2) { //we are in a blocking state => we don't insist
    TWCR = 0;  //and we force a reset on TWINT register
    neutralizeTime = micros(); //we take a timestamp here to neutralize the value during a short delay after the hard reset
  }
}

void checkStatusI2C() {
  if ( TW_STATUS  == 0xF8) { //TW_NO_INFO : this I2C error status indicates a wrong I2C communication.
    // WMP does not respond anymore => we do a hard reset. I did not find another way to solve it. It takes only 13ms to reset and init t
      TWCR = 0;
/*    POWERPIN_OFF //switch OFF WMP
    delay(1);  
    POWERPIN_ON  //switch ON WMP
*/
    delay(10);
    neutralizeTime = micros(); //we take a timestamp here to neutralize the WMP or WMP+NK values during a short delay after the hard reset
  }
}

