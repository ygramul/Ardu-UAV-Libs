/*
 * Library to read a 8 channels of a radio rc. Inspired of MultiWiiCopter V 1.7
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
       
// ******************
// rc functions
// ******************
#define MINCHECK 1168
#define MAXCHECK 1900
#define MAXCHANNELS 8

//RX PIN assignment
#define THROTTLEPIN 2
#define ROLLPIN 4
#define PITCHPIN 5
#define YAWPIN 6
#define AUX1PIN 7
#define AUX2PIN                    7   //unused just for compatibility with MEGA
#define CAM1PIN                    7   //unused just for compatibility with MEGA
#define CAM2PIN                    7   //unused just for compatibility with MEGA

/*********** RC alias *****************/
#define RC_ROLL 0
#define RC_PITCH 1
#define RC_YAW 2
#define RC_THROTTLE 3
#define RC_AUX1 4

class RcReceiver {
public:
              RcReceiver();
              ~RcReceiver();
              void configureReceiver();
              int16_t readRawRC(uint8_t chan);
              int16_t readScaledRC(uint8_t chan);
              uint8_t isSignalAvailable();
};
#endif

