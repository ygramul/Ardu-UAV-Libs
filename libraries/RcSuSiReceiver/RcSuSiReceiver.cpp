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
#include "RcSuSiReceiver.h" //include the declaration for this class

volatile uint16_t rcPinValue[8] = {
  0,0,1000,0,1500,1500,1500,1000};
volatile uint8_t signalAvailable;
       
static uint8_t rcChannel[8];
volatile int16_t rcValue[8] = {1500,1500,1500,1500,1500,1500,1500,1500}; // interval [1000;2000]

void rxInt() {
  uint16_t now,diff;
  static uint16_t last = 0;
  static uint8_t chan = 0;

  now = micros();
  diff = now - last;
  last = now;
  if(diff>3000) chan = 0;
  else {
    if(900<diff && diff<2200 && chan<8 ) rcValue[chan] = diff;
    chan++;
  }
}

RcSuSiReceiver::RcSuSiReceiver(uint8_t ch1, uint8_t ch2, uint8_t ch3, uint8_t ch4, uint8_t ch5, uint8_t ch6, uint8_t ch7, uint8_t ch8) {
  rcChannel[0] = ch1;
  rcChannel[1] = ch2;
  rcChannel[2] = ch3;
  rcChannel[3] = ch4;
  rcChannel[4] = ch5;
  rcChannel[5] = ch6;
  rcChannel[6] = ch7;
  rcChannel[7] = ch8;
  signalAvailable = 100; // Dummy at the moment
}
       
//<<destructor>>
RcSuSiReceiver::~RcSuSiReceiver(){/*nothing to destruct*/}
       
//prepare pins to enable interrupt on receiving signals
void RcSuSiReceiver::configureReceiver(){
  attachInterrupt(0, rxInt, RISING); //PIN 0
}

//read in the raw timing signals from pins
uint8_t RcSuSiReceiver::isSignalAvailable(){
  return signalAvailable;
}
              
//read in the raw timing signals from pins
int16_t RcSuSiReceiver::readRawRC(uint8_t chan){
  int16_t data;
  uint8_t oldSREG;
  oldSREG = SREG;
  cli(); // Let's disable interrupts
  data = rcValue[rcChannel[chan]]; 
  SREG = oldSREG;
  sei();// Let's enable the interrupts
  return data; // We return the value correctly copied when the IRQ's where disabled
}

int16_t RcSuSiReceiver::readScaledRC(uint8_t chan){
  int16_t data;
  uint8_t oldSREG;
  oldSREG = SREG;
  cli(); // Let's disable interrupts
  data = (rcValue[rcChannel[chan]] - 1000) / 4; // Let's copy the data Atomically
  SREG = oldSREG;
  sei();// Let's enable the interrupts
  return data; // We return the value correctly copied when the IRQ's where disabled
}
