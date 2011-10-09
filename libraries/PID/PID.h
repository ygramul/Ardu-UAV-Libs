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
#ifndef PID_H
#define PID_H
   
#include <WProgram.h> //It is very important to remember this!
       
class PID {
private:
	int16_t int_dt;
	int16_t int_divider;

	int16_t pid_previous_error;
	int16_t pid_integral;

	int16_t pid_Kp;
	int16_t pid_Ki;
	int16_t pid_Kd;

public:
	PID(int16_t dt, int16_t divider);
	~PID();
	void setProp(int16_t Kp);
	void setInt(int16_t Ki);
	void setDiff(int16_t Kd); 
	int16_t getProp();
	int16_t getInt();
	int16_t getDiff(); 
	int16_t calculate(int, int);
};
#endif

