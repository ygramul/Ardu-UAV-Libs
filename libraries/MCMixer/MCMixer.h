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
#ifndef MCMixer_H
#define MCMixer_H
   
#include <WProgram.h> //It is very important to remember this!
       
class MCMixer {
private:
	int16_t _motor[6];
        int16_t _min;
        int16_t _max;
public:
	MCMixer();
	~MCMixer();
	void calc_axis2motors(int16_t throttle, int16_t pitch, int16_t roll, int16_t yaw);
        void set_motor_range(int16_t min, int16_t max); 
	int16_t get_motor1();
	int16_t get_motor2();
	int16_t get_motor3();
	int16_t get_motor4();
	int16_t get_motor5();
	int16_t get_motor6();
};
#endif

