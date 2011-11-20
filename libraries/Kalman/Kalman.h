/*
 * Library for kalman filter. 
 * Inspired by http://interactive-matter.eu/2009/12/filtering-sensor-data-with-a-kalman-filter/
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
#ifndef Kalman_H
#define Kalman_H
   
#include <WProgram.h> //It is very important to remember this!
       
class Kalman {
private:
 	double d1_q; //process noise covariance
  	double d1_r; //measurement noise covariance
  	double d1_x; //value
  	double d1_p; //estimation error covariance
  	double d1_k; //kalman gain
 public:
              Kalman();
              ~Kalman();
              void init1D(double q, double r, double p, double intial_value);
              double update1D(double measurement);
};
#endif

