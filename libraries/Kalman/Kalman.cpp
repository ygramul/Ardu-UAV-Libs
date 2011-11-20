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
#include "Kalman.h" //include the declaration for this class
       
Kalman::Kalman(){
}
       
//<<destructor>>
Kalman::~Kalman(){/*nothing to destruct*/}
       
void Kalman::init1D(double q, double r, double p, double intial_value) {
  d1_q = q;
  d1_r = r;
  d1_p = p;
  d1_x = intial_value;
}
             
double Kalman::update1D(double measurement) {
  //prediction update
  //omit x = x
  d1_p = d1_p + d1_q;
 
  //measurement update
  d1_k = d1_p / (d1_p + d1_r);
  d1_x = d1_x + d1_k * (measurement - d1_x);
  d1_p = (1 - d1_k) * d1_p;
  return d1_x;
}

