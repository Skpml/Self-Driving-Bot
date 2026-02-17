
// --- Function to Drive a Motor ---
void setMotor(int pwm, int dir, int speed, bool forward) {
  digitalWrite(dir, forward ? HIGH : LOW);  // Set direction
  analogWrite(pwm, speed);                  // Set speed using PWM
}

// --- Setup Function for Each Motor ---
void setupMotor(int pwm, int dir) {
  pinMode(pwm, OUTPUT);  // Set PWM pin as output (for speed)
  pinMode(dir, OUTPUT);  // Set direction pin as output
}

// --- Arduino Setup Function ---
void setupAllMotors() {    
  setupMotor(FL_PWM, FL_DIR);
  setupMotor(FR_PWM,FR_DIR);
  setupMotor(BL_PWM,BL_DIR);
  setupMotor(BR_PWM,BR_DIR);
}

void setSpeed(int newSpeed) {
  motorSpeed = newSpeed;
  motorSpeedOutsideLineFollow = newSpeed;
  motorTurningSpeed = motorSpeed*0.8;
}

// This one we use when we're changing speed on the fly in the line following
void setLineFollowingSpeed(int newSpeed) {
  motorSpeed = newSpeed;
}

void stopAllMotors() {
  currentMovementState = STOPPED;
  setMotor(FL_PWM, FL_DIR, 0, true);
  setMotor(FR_PWM, FR_DIR, 0, true);
  setMotor(BL_PWM, BL_DIR, 0, true);
  setMotor(BR_PWM, BR_DIR, 0, true); 
}

void moveForward() {
  currentMovementState = FORWARD;
  setMotor(FL_PWM, FL_DIR, motorSpeed, true);
  setMotor(FR_PWM, FR_DIR, motorSpeed, true);
  setMotor(BL_PWM, BL_DIR, motorSpeed, true);
  setMotor(BR_PWM, BR_DIR, motorSpeed, true);
}

void moveBackward() {
  currentMovementState = BACKWARD;
  setMotor(FL_PWM, FL_DIR, motorSpeed, false);
  setMotor(FR_PWM, FR_DIR, motorSpeed, false);
  setMotor(BL_PWM, BL_DIR, motorSpeed, false);
  setMotor(BR_PWM, BR_DIR, motorSpeed, false);
}

void moveRight () {
  currentMovementState = RIGHT;
  setMotor(FL_PWM, FL_DIR, motorSpeed, true);
  setMotor(FR_PWM, FR_DIR, motorTurningSpeed, true);
  setMotor(BL_PWM, BL_DIR, motorSpeed, true);
  setMotor(BR_PWM, BR_DIR, motorTurningSpeed, true);
}

void moveLeft () {
  currentMovementState = LEFT;
  setMotor(FL_PWM, FL_DIR, motorTurningSpeed, true);
  setMotor(FR_PWM, FR_DIR, motorSpeed, true);
  setMotor(BL_PWM, BL_DIR, motorTurningSpeed, true);
  setMotor(BR_PWM, BR_DIR, motorSpeed, true);
}

void turnOnSpotRight () {
  currentMovementState = TURN_SPOT_RIGHT;
  setMotor(FL_PWM, FL_DIR, rotationSpeed, true);
  setMotor(FR_PWM, FR_DIR, rotationSpeed, false);
  setMotor(BL_PWM, BL_DIR, rotationSpeed, true);
  setMotor(BR_PWM, BR_DIR, rotationSpeed, false);
}

void turnOnSpotLeft () {
  currentMovementState = TURN_SPOT_LEFT;
  setMotor(FL_PWM, FL_DIR, rotationSpeed, false);
  setMotor(FR_PWM, FR_DIR, rotationSpeed, true);
  setMotor(BL_PWM, BL_DIR, rotationSpeed, false);
  setMotor(BR_PWM, BR_DIR, rotationSpeed, true);
}
void crabWalkRight () {
  currentMovementState = CW_RIGHT;
  setMotor(FL_PWM, FL_DIR, motorSpeed, true);
  setMotor(FR_PWM, FR_DIR, motorSpeed, false);
  setMotor(BL_PWM, BL_DIR, motorSpeed, false);
  setMotor(BR_PWM, BR_DIR, motorSpeed, true);
}
void crabWalkLeft () {
  currentMovementState = CW_LEFT;
  setMotor(FL_PWM, FL_DIR, motorSpeed, false);
  setMotor(FR_PWM, FR_DIR, motorSpeed, true);
  setMotor(BL_PWM, BL_DIR, motorSpeed, true);
  setMotor(BR_PWM, BR_DIR, motorSpeed, false);
}

// angle of 90 degrees is the start, the angle moves counter-clockwise
boolean turnToAbsoluteAngle(float targetAngle) {
  boolean isTurning = false;

  if (robotAngle < degToRad(targetAngle - 1)) {
    motorSpeed = 100;
    turnOnSpotLeft();
    isTurning = true;
  } else if (robotAngle > degToRad(targetAngle + 1)) {
    motorSpeed = 100;
    turnOnSpotRight();
    isTurning = true;
  } else {
    motorSpeed = motorSpeedOutsideLineFollow;
    stopAllMotors();
    isTurning = false;
  }
  return isTurning;
}

boolean turnToAbsoluteAngleRad(float targetAngleRad) {
  boolean isTurning = false;
  
  float tolerance = degToRad(1.0); 

  if (robotAngle < (targetAngleRad - tolerance)) {
    motorSpeed = 100;
    turnOnSpotLeft();
    isTurning = true;
  } 
  else if (robotAngle > (targetAngleRad + tolerance)) {
    motorSpeed = 100;
    turnOnSpotRight();
    isTurning = true;
  } 
  else {
    motorSpeed = motorSpeedOutsideLineFollow;
    stopAllMotors();
    isTurning = false;
  }
  
  return isTurning;
}

// totalTargetDistance should be calculated in the earlier state before this state
boolean moveToDistance(float totalTargetDistance) {
  boolean isMoving = false;
  if (totalDistance < (totalTargetDistance - 1)) {
    moveForward();
    isMoving = true;
  } else if (totalDistance > (totalTargetDistance + 1)) {
    moveBackward();
    isMoving = true;
  } else {
    stopAllMotors();
    isMoving = false;
  }
  return isMoving;
}
