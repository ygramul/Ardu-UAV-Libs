/*
 * Library for a PID controller (Proportional, Integral, Differencial).
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
#include "PID.h" //include the declaration for this class
       
PID::PID(int16_t dt, int16_t divider){
  int_dt = dt;
  int_divider = divider;
  
  pid_previous_error = 0;
  pid_integral = 0;
  pid_Kp = 1024;
  pid_Ki = 8;
  pid_Kd = 96;
}
       
//<<destructor>>
PID::~PID(){/*nothing to destruct*/}
       
// pid controller itself
int16_t PID::calculate(int16_t target, int16_t current) {
  int16_t int_error = target - current;
  pid_integral = pid_integral + (int_error*int_dt);
  int16_t int_derivative = (int_error - pid_previous_error)/int_dt;
  int16_t int_output = ((pid_Kp*int_error) + (pid_Ki*pid_integral) + (pid_Kd*int_derivative) ) / int_divider;
  pid_previous_error = int_error;
  return int_output;
}

void PID::setProp(int16_t Kp) {
  pid_Kp = Kp;
}
 
void PID::setInt(int16_t Ki) {
  pid_Ki = Ki;
}
 
void PID::setDiff(int16_t Kd) {
  pid_Kd = Kd;
}
 
int16_t PID::getProp() {
  return pid_Kp;
}
 
int16_t PID::getInt() {
  return pid_Ki;
}
 
int16_t PID::getDiff() {
  return pid_Kd;
}

