/*
 * Library for utility functions for a RC.
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
#include "RCTransform.h" //include the declaration for this class
       
RCTransform::RCTransform(){
}
       
RCTransform::~RCTransform(){/*nothing to destruct*/}
       
int16_t RCTransform::turnRcRoll(int16_t angle, int16_t pitch, int16_t roll) {
  int16_t real_roll;
  switch (angle) {
    case 90  : real_roll = -pitch; break;
    case 180 : real_roll = -roll; break;
    case 270 : real_roll = pitch; break;
    case 45  : real_roll = map((roll - pitch), -180, 180, -127, 127); break;
    case 135 : real_roll = map((-roll - pitch), -180, 180, -127, 127); break;
    case 225 : real_roll = map((-roll + pitch), -180, 180, -127, 127); break;
    case 315 : real_roll = map((roll + pitch), -180, 180, -127, 127); break;
    default  : real_roll = roll;
  }
  return real_roll;
}
       
int16_t RCTransform::turnRcPitch(int16_t angle, int16_t pitch, int16_t roll) {
  int16_t real_pitch;
  switch (angle) {
    case 90  : real_pitch = roll; break;
    case 180 : real_pitch = -pitch; break;
    case 270 : real_pitch = -roll; break;
    case 45  : real_pitch = map((pitch + roll), -180, 180, -127, 127); break;
    case 135 : real_pitch = map((-pitch + roll), -180, 180, -127, 127); break;
    case 225 : real_pitch = map((-pitch - roll), -180, 180, -127, 127); break;
    case 315 : real_pitch = map((pitch - roll), -180, 180, -127, 127); break;
    default  : real_pitch = pitch;
  } 
  return real_pitch;
}

int16_t RCTransform::linToExp(int16_t linear_stick, int16_t range_max) {
  return map((linear_stick * abs(linear_stick)), -16129, 16129, -range_max, range_max);
}

