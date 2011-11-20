#include <I2C.h>
#include <BMA020.h>

BMA020 bma020;

static uint32_t currentTime;
static uint32_t hz1000Time;
static uint32_t hz50Time;

static int16_t roll_acc;
static int32_t roll_angle;

void setup() {
  Serial.begin(115200);
  
  Serial.println("Init i2c");
  // init wire. i2c_init(internal pullups disabled, 400kHz)
  i2c_init(false, true); 
  delay(100);
     
  Serial.println("Init itg callbacks");
  // make i2c access functions available to sensor methods
  bma020.i2cStartCallback(i2c_rep_start);
  bma020.i2cWriteCallback(i2c_write);
  bma020.i2cAckCallback(i2c_readAck);
  bma020.i2cNackCallback(i2c_readNak);
  Serial.println("Init bma020 sensor");
  bma020.init(); // init sensor. Set working values
}

void loop() {
  if (currentTime > (hz1000Time + 1000) ) { // 1000000 / 1000 = 1000 Hz
    hz1000Time = currentTime;
    bma020.readAcc();
  }
  if (currentTime > (hz50Time + 50000) ) { // 1000000 / 20000 = 50 Hz 
    hz50Time = currentTime;
    Serial.print(bma020.getRoll());
    Serial.print('\t');
    Serial.print(bma020.getPitch());
    Serial.print('\t');
    Serial.println(bma020.getYaw());
  }
  currentTime = micros();
}
