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
#include "RcReceiver.h" //include the declaration for this class

static uint8_t pinRcChannel[MAXCHANNELS] = {
  ROLLPIN, PITCHPIN, YAWPIN, THROTTLEPIN, AUX1PIN,AUX2PIN,CAM1PIN,CAM2PIN};
volatile int16_t rcPinValue[8] = {1500,1500,1500,1500,1500,1500,1500,1500}; // interval [1000;2000]
volatile uint8_t signalAvailable;
       
ISR(PCINT2_vect) {
  uint8_t mask;
  uint8_t pin;
  uint16_t cTime,dTime;
  static uint16_t edgeTime[8];
  static uint8_t PCintLast;

  pin = PIND;              // PIND indicates the state of each PIN for the arduino port dealing with [D0-D7] digital pins (8 bits variable)
  mask = pin ^ PCintLast;  // doing a ^ between the current interruption and the last one indicates wich pin changed
  sei();                    // re enable other interrupts at this point, the rest of this interrupt is not so time critical and can be interrted safely
  PCintLast = pin;         // we memorize the current state of all PINs [D0-D7]
  cTime = micros();         // micros() return a uint32_t, but it is not usefull to keep the whole bits => we keep only 16 bits
  // mask is pins [D0-D7] that have changed
  // chan = pin sequence of the port. chan begins at D2 and ends at D7
  if (mask & 1<<2)           //indicates the bit 2 of the arduino port [D0-D7], that is to say digital pin 2, if 1 => this pin has just changed
    if (!(pin & 1<<2)) {     //indicates if the bit 2 of the arduino port [D0-D7] is not at a high state (so that we match here only descending PPM pulse)
      dTime = cTime-edgeTime[2]; if (900<dTime && dTime<2200) rcPinValue[2] = dTime; // just a verification: the value must be in the range [1000;2000] + some margin
    } else edgeTime[2] = cTime;    // if the bit 2 of the arduino port [D0-D7] is at a high state (ascending PPM pulse), we memorize the time
  if (mask & 1<<4)   //same principle for other channels   // avoiding a for() is more than twice faster, and it's important to minimize execution time in ISR
    if (!(pin & 1<<4)) {
      dTime = cTime-edgeTime[4]; if (900<dTime && dTime<2200) rcPinValue[4] = dTime;
    } else edgeTime[4] = cTime;
  if (mask & 1<<5)
    if (!(pin & 1<<5)) {
      dTime = cTime-edgeTime[5]; if (900<dTime && dTime<2200) rcPinValue[5] = dTime;
    } else edgeTime[5] = cTime;
  if (mask & 1<<6)
    if (!(pin & 1<<6)) {
      dTime = cTime-edgeTime[6]; if (900<dTime && dTime<2200) rcPinValue[6] = dTime;
    } else edgeTime[6] = cTime;
  if (mask & 1<<7)
    if (!(pin & 1<<7)) {
      dTime = cTime-edgeTime[7]; if (900<dTime && dTime<2200) rcPinValue[7] = dTime;
    } else edgeTime[7] = cTime;
  signalAvailable = (mask & 1<<THROTTLEPIN); // If pulse present on THROTTLE pin signal is available
}

RcReceiver::RcReceiver(){
}
       
//<<destructor>>
RcReceiver::~RcReceiver(){/*nothing to destruct*/}
       
//prepare pins to enable interrupt on receiving signals
void RcReceiver::configureReceiver(){
  uint8_t chan,a;
  PORTD   = (1<<2) | (1<<4) | (1<<5) | (1<<6) | (1<<7); //enable internal pull ups on the PINs of PORTD (no high impedence PINs)
  PCMSK2 |= (1<<2) | (1<<4) | (1<<5) | (1<<6) | (1<<7); 
  PCICR   = 1<<2; // PCINT activated only for [D0-D7] port
}

//read in the raw timing signals from pins
uint8_t RcReceiver::isSignalAvailable(){
  return signalAvailable;
}
              
//read in the raw timing signals from pins
int16_t RcReceiver::readRawRC(uint8_t chan){
  int16_t data;
  uint8_t oldSREG;
  oldSREG = SREG;
  cli(); // Let's disable interrupts
  data = rcPinValue[pinRcChannel[chan]]; // Let's copy the data Atomically
  SREG = oldSREG;
  sei();// Let's enable the interrupts
  return data; // We return the value correctly copied when the IRQ's where disabled
}

int16_t RcReceiver::readScaledRC(uint8_t chan){
  int16_t data;
  uint8_t oldSREG;
  oldSREG = SREG;
  cli(); // Let's disable interrupts
  data = (rcPinValue[pinRcChannel[chan]] - 1000) / 4; // Let's copy the data Atomically
  SREG = oldSREG;
  sei();// Let's enable the interrupts
  return data; // We return the value correctly copied when the IRQ's where disabled
}
