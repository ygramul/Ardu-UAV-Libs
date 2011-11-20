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
#include "PacketTransmit.h" //include the declaration for this class
#include <util/crc16.h>
 
PacketTransmit::PacketTransmit(){
  receive_error = false;
  syncstate=0;
  write_index = 0;
  read_index = 0;
  transmit_crc.value = 0;
  receive_crc.value = 0;
  receive_crc_calc = 0;
  data_available = false;
}
       
//<<destructor>>
PacketTransmit::~PacketTransmit(){/*nothing to destruct*/}
       
void PacketTransmit::setTransmittingData(void *data, uint16_t data_size) {
  write_pointer = (unsigned char *)data;
  write_index = 0;
  write_size = data_size;
  transmit_length.value = data_size;
}

void PacketTransmit::setReceivingData(void *data, uint16_t data_size) {
  read_pointer = (unsigned char *)data;
  read_index = 0;
  read_size = data_size;
  receive_crc_calc = 0;
  data_available = false;
}

boolean PacketTransmit::isTransmittingInProgress() {
  return ((write_index > 0) && (write_index < (write_size + 7)));
}

boolean PacketTransmit::isDataTransmitted() {
  return (write_index >= (write_size + 7));
}

unsigned char PacketTransmit::getNextItem() {
  unsigned char startstring[]={'>','*','>'};
  unsigned char return_value;
  if (write_index < 3) {
    return_value = startstring[write_index++];
  } 
  else if (write_index < 5) {
    return_value = transmit_length.part[(write_index-3)];
    write_index++;
  } 
  else if (write_index < (write_size + 5)) {
    transmit_crc.value = _crc_ibutton_update(transmit_crc.value, *write_pointer);
    return_value = *write_pointer;
    write_pointer++;
    write_index++;
  } 
  else if (write_index < (write_size + 7)) {
    return_value = transmit_crc.part[write_index-write_size-5];
    write_index++;
  }
  return return_value;
}

void PacketTransmit::setReceivedItem(unsigned char item) {
  if (syncstate==0)
  {
    if (item=='>') syncstate++; 
    else syncstate=0;
  }
  else if (syncstate==1)
  {
    if (item=='*') syncstate++; 
    else syncstate=0;
  }
  else if (syncstate==2)
  {
    if (item=='>') syncstate++; 
    else syncstate=0;
  }
  else if (syncstate==3)
  {
    if ((read_index == 2) && (receive_length.value != read_size)) {
      read_index = 0;
      syncstate = 0;
      receive_crc_calc = 0;
      receive_error = true;
    }
    if (read_index < 2) {
      receive_length.part[read_index] = item;
      read_index++;
    } else if (read_index < (read_size + 2)) {
      *read_pointer = item;
      receive_crc_calc= _crc_ibutton_update(receive_crc_calc, item);
      read_index++;
      read_pointer++;
    }
    else if (read_index < (read_size + 4)) {
      receive_crc.part[read_index-read_size-2] = item;
      read_index++;
    } else if (read_index < (read_size + 6)) {
      if ((receive_length.value == read_size) && (receive_crc_calc == receive_crc.value)) {
        receive_error = false;
        data_available = true;
      } else {
        receive_error = true;
      }
      syncstate=0;
      receive_crc_calc = 0;
    } else {
      receive_error = true;
      syncstate=0;
      receive_crc_calc = 0;
    }
  }
}

boolean PacketTransmit::isReceivingInProgress() {
  return ((syncstate != 0) || ((read_index > 0) && (read_index < (read_size + 6))));
}

boolean PacketTransmit::isReceiveError() {
  return receive_error;
}

boolean PacketTransmit::isDataAvailable() {
  return data_available;
}

