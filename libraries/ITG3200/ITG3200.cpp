/*
 * Library for ITG3200 gyro. Inspired of MultiWiiCopter V 1.7
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
#include "ITG3200.h" //include the declaration for this class
       
ITG3200::ITG3200(){
  rep_start_callback_func = 0;
  write_callback_func = 0;
  read_ack_callback_func = 0;
  read_nack_callback_func = 0;

  roll_offset = 0;
  pitch_offset = 0;
  yaw_offset = 0;
}
       
//<<destructor>>
ITG3200::~ITG3200(){/*nothing to destruct*/}
  
void ITG3200::i2cStartCallback(func_callback_type_write callback_function) {
   rep_start_callback_func = callback_function;
}

void ITG3200::i2cWriteCallback(func_callback_type_write callback_function) {
   write_callback_func = callback_function;
}

void ITG3200::i2cAckCallback(func_callback_type_read callback_function) {
   read_ack_callback_func = callback_function;
}

void ITG3200::i2cNackCallback(func_callback_type_read callback_function) {
   read_nack_callback_func = callback_function;
}
     
void ITG3200::init(){
  delay(100);
  rep_start_callback_func(0xD0+0);      // I2C write direction 
  write_callback_func(0x3E);            // Power Management register
  write_callback_func(0x80);            //   reset device
  write_callback_func(0x16);            // register DLPF_CFG - low pass filter configuration & sample rate
  write_callback_func(0x1D);            //   10Hz Low Pass Filter Bandwidth - Internal Sample Rate 1kHz
  write_callback_func(0x3E);            // Power Management register
  write_callback_func(0x01);            //   PLL with X Gyro reference
  delay(100);
}

itg_t* ITG3200::getItgStruct() {
  return &_itg;
}

int16_t ITG3200::getTemperature() {
  return _itg.temperature;
}

void ITG3200::readAdc() {
  rep_start_callback_func(0xD0);     // I2C write direction
  write_callback_func(0x1D);         // Start multiple read
  rep_start_callback_func(0xD0 +1);  // I2C read direction => 1

  _itg.rawADC_ITG3200[3]=read_ack_callback_func();
  _itg.rawADC_ITG3200[2]=read_ack_callback_func();
  _itg.rawADC_ITG3200[5]=read_ack_callback_func();
  _itg.rawADC_ITG3200[4]=read_ack_callback_func();
  _itg.rawADC_ITG3200[7]=read_ack_callback_func();
  _itg.rawADC_ITG3200[6]=read_nack_callback_func();
}

void ITG3200::readTemperature(){
  rep_start_callback_func(0xD0);     // I2C write direction
  write_callback_func(0x1B);         // Start multiple read
  rep_start_callback_func(0xD0 +1);  // I2C read direction => 1

  _itg.rawADC_ITG3200[1]=read_ack_callback_func();
  _itg.rawADC_ITG3200[0]=read_nack_callback_func();
}

void ITG3200::calcAdcOffset() {
  int16_t old_roll = 0;
  int16_t old_pitch = 0;
  int16_t old_yaw = 0;
  for (int i=0; i<256; i++) {
    readAdc();
    old_roll = roll_offset;
    roll_offset = (7 * old_roll + (_itg.roll)) / 8;
    old_pitch = pitch_offset;
    pitch_offset = (7 * old_pitch + (_itg.pitch)) / 8;
    old_yaw = yaw_offset;
    yaw_offset = (7 * old_yaw + (_itg.yaw)) / 8;
    delay(2);
  }
}

int16_t ITG3200::getPitchOffset() {
  return pitch_offset;
}

int16_t ITG3200::getRollOffset() {
  return roll_offset;
}

int16_t ITG3200::getYawOffset() {
  return yaw_offset;
}

int16_t ITG3200::getPitchCalib() {
  return (_itg.pitch - pitch_offset);
}

int16_t ITG3200::getRollCalib() {
  return (_itg.roll - roll_offset);
}

int16_t ITG3200::getYawCalib() {
  return (_itg.yaw - yaw_offset);
}


