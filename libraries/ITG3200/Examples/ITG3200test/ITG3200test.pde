#include <I2C.h>
#include <ITG3200.h>
#include <Kalman.h>

ITG3200 itg3200;

static uint32_t currentTime;
static uint32_t hz1000Time;
static uint32_t hz20Time;

static int16_t roll_acc;
static int32_t roll_angle;
static int16_t temperature;

void setup() {
  Serial.begin(115200);
  
  Serial.println("Init i2c");
  // init wire. i2c_init(internal pullups disabled, 400kHz)
  i2c_init(false, true); 
  delay(100);
  
  // If you power your ITG with a pin of the arduino, therefore activate the ITG
  //pinMode (12, OUTPUT);
  //PORTB |= 1<<4;
  //delay(100);
   
  Serial.println("Init itg callbacks");
  // make i2c access functions available to sensor methods
  itg3200.i2cStartCallback(i2c_rep_start);
  itg3200.i2cWriteCallback(i2c_write);
  itg3200.i2cAckCallback(i2c_readAck);
  itg3200.i2cNackCallback(i2c_readNak);
  Serial.println("Init itg sensor");
  itg3200.init(); // init sensor. Set working values
  Serial.println("Calibrate gyro");
  // gyro_calibration(); // get deviation of sensor values
  itg3200.calcAdcOffset();  
}

void loop() {
  if (currentTime > (hz1000Time + 1000) ) { // 1000000 / 1000 = 1000 Hz
    hz1000Time = currentTime;
    itg3200.readAdc();
    roll_acc = itg3200.getRollCalib();
    roll_angle += roll_acc;
    itg3200.readTemperature();
    temperature = itg3200.getTemperature();
  }
  if (currentTime > (hz20Time + 50000) ) { // 1000000 / 50000 = 20 Hz 
    hz20Time = currentTime;
    Serial.print(35.0 + ((temperature + 13200)/280.0)); // Degrees Celsius
    Serial.print('\t');
    Serial.print(roll_acc / 32, DEC);
    Serial.print('\t');
    Serial.println(roll_angle / 110000, DEC); // approximatly degrees
  }
  currentTime = micros();
}
