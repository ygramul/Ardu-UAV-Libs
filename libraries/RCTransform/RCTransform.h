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
#ifndef RCTransform_H
#define RCTransform_H
   
#include <WProgram.h> //It is very important to remember this!
       
class RCTransform {
public:
              RCTransform();
              ~RCTransform();
              int16_t turn_rc_roll(int16_t angle, int16_t pitch, int16_t roll);
              int16_t turn_rc_pitch(int16_t angle, int16_t pitch, int16_t roll);
};
#endif

