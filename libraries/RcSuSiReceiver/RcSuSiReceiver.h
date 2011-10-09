/*
 * Library to read a sum signal ppm signal of a radio rc. 
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
#ifndef CppTest_H
#define CppTest_H
   
#include <WProgram.h> //It is very important to remember this!
       
/*********** RC alias *****************/
#define RC_ROLL       0
#define RC_PITCH      1
#define RC_YAW        2
#define RC_THROTTLE   3
#define RC_AUX1       4
#define RC_AUX2       5
#define RC_CAMPITCH   6
#define RC_CAMROLL    7

class RcSuSiReceiver {
public:
              RcSuSiReceiver(uint8_t ch1, uint8_t ch2, uint8_t ch3, uint8_t ch4, uint8_t ch5, uint8_t ch6, uint8_t ch7, uint8_t ch8);
              ~RcSuSiReceiver();
              void configureReceiver();
              int16_t readRawRC(uint8_t chan);
              int16_t readScaledRC(uint8_t chan);
              uint8_t isSignalAvailable();
};
#endif

