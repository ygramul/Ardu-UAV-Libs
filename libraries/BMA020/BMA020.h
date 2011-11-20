/*
 * Library for BMA020 acc. Inspired of MultiWiiCopter V 1.7
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
#ifndef BMA020_H
#define BMA020_H
   
#include <WProgram.h> //It is very important to remember this!

typedef union
{
  struct
  {
    uint8_t rawADC_BMA020[6];
  };
  struct
  {
    // left 10 bits are value, right bit is status flag if this value is already read from sensor
    int16_t z;
    int16_t y;
    int16_t x;
  };
} itg_t;

typedef void (*func_callback_type_write) (uint8_t);
typedef uint8_t (*func_callback_type_read) ();
      
class BMA020 {
private:

        func_callback_type_write rep_start_callback_func;
        func_callback_type_write write_callback_func;
        func_callback_type_read read_ack_callback_func;
        func_callback_type_read read_nack_callback_func;
public:
	BMA020();
	~BMA020();
	void init();
	void readAcc();
	int16_t getRollRaw();
	int16_t getPitchRaw();
	int16_t getYawRaw();
	int16_t getRoll();
	int16_t getPitch();
	int16_t getYaw();

        void i2cStartCallback(func_callback_type_write callback_function);
        void i2cWriteCallback(func_callback_type_write callback_function);
        void i2cAckCallback(func_callback_type_read callback_function);
        void i2cNackCallback(func_callback_type_read callback_function);
};
#endif

