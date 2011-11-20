#include <RcReceiver.h>

RcReceiver receiver;
static uint32_t rcTime;
static uint32_t currentTime;

const int motorLeftPin = 9;     // Pin "9"
const int motorRightPin = 10;   // Pin "10"

int ctrlDirection = 0;
int ctrlThrust = 0;
int motorLeftValue = 0;
int motorRightValue = 0;

void setup() {
  receiver.configureReceiver();
  Serial.begin(57600); 
}

void loop () {
  static uint8_t rcDelayCommand; // this indicates the number of time (multiple of RC measurement at 50Hz) the sticks must be maintained to run or switch off motors

  if (currentTime > (rcTime + 20000) ) { // 50Hz
    rcTime = currentTime;
    if (receiver.isSignalAvailable()) {
      ctrlThrust = (receiver.readRawRC(RC_PITCH)-1000) >> 2;
      ctrlDirection = ((receiver.readRawRC(RC_ROLL)-1000) >> 2) - 125;
    } else {
      ctrlThrust = 0;
      ctrlDirection = 0;
      Serial.println("No receiver signal available");
    }
    Serial.print("Thrust:");
    Serial.print(ctrlThrust);
    Serial.print(" Direction:");
    Serial.println(ctrlDirection);
    Serial.print("left:");
    Serial.print(motorLeftValue);
    Serial.print(" right:");
    Serial.println(motorRightValue);
  }

  mapCtrlInputToMotors(ctrlThrust, ctrlDirection);
  analogWrite(motorLeftPin, motorLeftValue);
  analogWrite(motorRightPin, motorRightValue);

  // Measure loop rate just afer reading the sensors
  // meanTime and cycleTime are used to scale the PID term I and D
  // variation are caused by irregular calls to RC loop functions and interruptions
  currentTime = micros();
}

/**
 * Calculate motor values from control input values
 */
void mapCtrlInputToMotors(int thrust, int course_direction) {
  motorLeftValue  = thrust + course_direction;
  motorRightValue = thrust - course_direction;
  if (motorLeftValue < 0) {
    motorLeftValue = 0;
  } 
  else if (motorLeftValue > 255) {
    motorLeftValue = 255;
  }
  if (motorRightValue < 0) {
    motorRightValue = 0;
  } 
  else if (motorRightValue > 255) {
    motorRightValue = 255;
  }  
}

