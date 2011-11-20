#include <PacketTransmit.h>

PacketTransmit transmit;

struct rc_t {
  unsigned char packettype;
  int8_t channel[2];
};

static unsigned char buffer[15];
static uint16_t buffer_index;

void setup() {
  Serial.begin(115200);
  rc_t write_rc;
  rc_t read_rc;

  write_rc.packettype = 0x11;
  write_rc.channel[0] = 3;
  write_rc.channel[1] = -2;
  
  buffer_index = 2; // to have something to synchronize, we store not on the beginning of the buffer

  Serial.println("set data to transmit");
  transmit.setTransmittingData(&write_rc, sizeof(write_rc));
  while(transmit.isDataTransmitted() == false) {
    unsigned char item = transmit.getNextItem();
    buffer[buffer_index++] = item; // save also in the buffer for receiving test
    Serial.print(item, HEX);
    Serial.print('\t');
    Serial.println(item);
  }
  
  Serial.println("init receive data");
  buffer_index = 0;
  transmit.setReceivingData(&read_rc, sizeof(read_rc));
  while(transmit.isDataAvailable() == false) {
    transmit.setReceivedItem(buffer[buffer_index]);
    buffer_index++;
  }
  Serial.print("packettype:"); Serial.println(read_rc.packettype, HEX);
  Serial.print("channel 0:"); Serial.println(read_rc.channel[0]);
  Serial.print("channel 1:"); Serial.println(read_rc.channel[1]);  
}

void loop() {
}
