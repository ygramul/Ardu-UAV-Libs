/*
 * Library for ITG3200 gyro. Inspired of MultiWiiCopter V 1.7
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
#ifndef ITG3200_H
#define ITG3200_H
   
#include <WProgram.h> //It is very important to remember this!
#include <ITG3200.h>

typedef void (*func_callback_type_write) (uint8_t);
typedef uint8_t (*func_callback_type_read) ();

// **************************
// I2C Gyroscope ITG3200 
// **************************
// I2C adress: 0xD2 (8bit)   0x69 (7bit)  // for sparkfun breakout board default jumper
// I2C adress: 0xD0 (8bit)   0x68 (7bit)  // for FreeFlight IMU board default jumper
// principle:
// 1) VIO is connected to VDD
// 2) I2C adress is set to 0x69 (AD0 PIN connected to VDD)
// or 2) I2C adress is set to 0x68 (AD0 PIN connected to GND) <- this is the case for the code here
// 3) sample rate = 1000Hz ( 1kHz/(div+1) )

typedef union
{
  struct
  {
    uint8_t rawADC_ITG3200[8];
  };
  struct
  {
    int16_t temperature;
    int16_t pitch;
    int16_t roll;
    int16_t yaw;
  };
} itg_t;
       
class ITG3200 {
private:
	itg_t _itg;

	int16_t roll_offset;
	int16_t pitch_offset;
	int16_t yaw_offset;

        func_callback_type_write rep_start_callback_func;
        func_callback_type_write write_callback_func;
        func_callback_type_read read_ack_callback_func;
        func_callback_type_read read_nack_callback_func;
public:
	ITG3200();
	~ITG3200();
	void init();
        itg_t* get_itg_struct();
	void read_adc();
	void read_temperature();
        void calc_adc_offset();
        int16_t get_pitch_offset();
        int16_t get_roll_offset();
        int16_t get_yaw_offset();
        int16_t get_pitch_calib();
        int16_t get_roll_calib();
        int16_t get_yaw_calib();

        void i2c_start_callback(func_callback_type_write callback_function);
        void i2c_write_callback(func_callback_type_write callback_function);
        void i2c_ack_callback(func_callback_type_read callback_function);
        void i2c_nack_callback(func_callback_type_read callback_function);
};
#endif

