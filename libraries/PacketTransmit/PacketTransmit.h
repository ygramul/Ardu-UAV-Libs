/*
 * Library transmitting and receiving different types of data blocks. 
 * Inspired by http://sf.net/p/opensourcepilot/
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
#ifndef PacketTransmit_H
#define PacketTransmit_H
   
#include <WProgram.h> //It is very important to remember this!

typedef union {
  uint16_t value;
  unsigned char part[2];
} 
unit16_combined_t;

class PacketTransmit {
private:
	unsigned char syncstate;
	unsigned int write_index;
	unsigned int read_index;
	unsigned char * write_pointer;
	unsigned char * read_pointer;
	unsigned int write_size;
	unsigned int read_size;
	unit16_combined_t transmit_crc;
	unit16_combined_t receive_crc;
	uint16_t receive_crc_calc;
	unit16_combined_t transmit_length;
	unit16_combined_t receive_length;
	boolean receive_error;
	boolean data_available;

public:
        PacketTransmit();
        ~PacketTransmit();
	void setTransmittingData(void *data, uint16_t data_size);
	void setReceivingData(void *data, uint16_t data_size);
	boolean isDataTransmitted();
        boolean isTransmittingInProgress();
	unsigned char getNextItem();
	void setReceivedItem(unsigned char item);
        boolean isReceivingInProgress();
	boolean isReceiveError();
	boolean isDataAvailable();
};
#endif

