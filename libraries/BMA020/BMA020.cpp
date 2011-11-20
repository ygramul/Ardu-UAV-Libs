/*
 * Library for BMA020 acc. Inspired of MultiWiiCopter V 1.7
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
#include "BMA020.h" //include the declaration for this class
       
BMA020::BMA020(){
  rep_start_callback_func = 0;
  write_callback_func = 0;
  read_ack_callback_func = 0;
  read_nack_callback_func = 0;
}
       
BMA020::~BMA020(){/*nothing to destruct*/}
 
void BMA020::i2cStartCallback(func_callback_type_write callback_function) {
   rep_start_callback_func = callback_function;
}

void BMA020::i2cWriteCallback(func_callback_type_write callback_function) {
   write_callback_func = callback_function;
}

void BMA020::i2cAckCallback(func_callback_type_read callback_function) {
   read_ack_callback_func = callback_function;
}

void BMA020::i2cNackCallback(func_callback_type_read callback_function) {
   read_nack_callback_func = callback_function;
}

// **************
// contribution from Point65 and mgros (rc-grooups)
// BMA020 I2C
// **************
// I2C adress: 0x70 (8bit)
static uint8_t rawADC_BMA020[6];
static int16_t accADC[3];
#define ROLL       0
#define PITCH      1
#define YAW        2


void BMA020::init(){
  byte control;

  rep_start_callback_func(0x70);     // I2C write direction
  write_callback_func(0x15);         // 
  write_callback_func(0x80);         // Write B10000000 at 0x15 init BMA020

  rep_start_callback_func(0x70);     // 
  write_callback_func(0x14);         //  
  write_callback_func(0x71);         // 
  write_callback_func(0x71);     //
  control = read_nack_callback_func();
 
  control = control >> 5;  //ensure the value of three fist bits of reg 0x14 see BMA020 documentation page 9
  control = control << 2;
  control = control | 0x00; //Range 2G 00
  control = control << 3;
  control = control | 0x00; //Bandwidth 25 Hz 000
 
  rep_start_callback_func(0x70);     // I2C write direction
  write_callback_func(0x14);         // Start multiple read at reg 0x32 ADX
  write_callback_func(control);
}

void BMA020::readAcc(){
  // set i2c to fast mode
  rep_start_callback_func(0x70);     // I2C write direction
  write_callback_func(0x02);         // Start multiple read at reg 0x32 ADX
  write_callback_func(0x71);  
  rep_start_callback_func(0x71);  //I2C read direction => 1
  for(uint8_t i = 0; i < 5; i++) {
    rawADC_BMA020[i]=read_ack_callback_func();}
  rawADC_BMA020[5]= read_nack_callback_func();

  accADC[ROLL]  =  (((rawADC_BMA020[1])<<8) | ((rawADC_BMA020[0]>>1)<<1))/64;
  accADC[PITCH] =  (((rawADC_BMA020[3])<<8) | ((rawADC_BMA020[2]>>1)<<1))/64;
  accADC[YAW]   = -(((rawADC_BMA020[5])<<8) | ((rawADC_BMA020[4]>>1)<<1))/64;
}

int16_t BMA020::getRollRaw() {
  return ((rawADC_BMA020[1])<<8) | rawADC_BMA020[0];
}

int16_t BMA020::getPitchRaw() {
  return ((rawADC_BMA020[3])<<8) | rawADC_BMA020[2];
}

int16_t BMA020::getYawRaw() {
  return ((rawADC_BMA020[5])<<8) | rawADC_BMA020[4];
}

int16_t BMA020::getRoll() {
  return accADC[ROLL];
}

int16_t BMA020::getPitch() {
  return accADC[PITCH];
}

int16_t BMA020::getYaw() {
  return accADC[YAW];
}

