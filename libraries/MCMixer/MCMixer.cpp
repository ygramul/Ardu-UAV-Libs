/*
 * Library for mapping movements on the three axis to motor speed. 
 * Inspired of MultiWiiCopter V 1.7
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
#include "MCMixer.h" //include the declaration for this class
       
MCMixer::MCMixer(){
  _min = 1;
  _max = 250;
}
       
//<<destructor>>
MCMixer::~MCMixer(){/*nothing to destruct*/}
       
void MCMixer::calc_axis2motors(int16_t throttle, int16_t pitch, int16_t roll, int16_t yaw) {
  _motor[0] = throttle + pitch - yaw; //REAR
  _motor[1] = throttle - roll  + yaw; //RIGHT
  _motor[2] = throttle + roll  + yaw; //LEFT
  _motor[3] = throttle - pitch - yaw; //FRONT
  _motor[4] = 0;
  _motor[5] = 0; 
}

void MCMixer::set_motor_range(int16_t  min, int16_t  max) {
  _min = min;
  _max = max;
} 
       
int16_t  MCMixer::get_motor1() {
  return constrain(_motor[0], _min, _max);
}

int16_t  MCMixer::get_motor2() {
  return constrain(_motor[1], _min, _max);
}

int16_t  MCMixer::get_motor3() {
  return constrain(_motor[2], _min, _max);
}

int16_t  MCMixer::get_motor4() {
  return constrain(_motor[3], _min, _max);
}

int16_t  MCMixer::get_motor5() {
  return constrain(_motor[4], _min, _max);
}

int16_t  MCMixer::get_motor6() {
  return constrain(_motor[5], _min, _max);
}
