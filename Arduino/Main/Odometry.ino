
volatile long leftTick = 0;
volatile long rightTick = 0;

unsigned long prevTime = 0;
long prevLeftTick = 0;
long prevRightTick = 0;

void setUpEncoders() {
  pinMode(leftEncA, INPUT_PULLUP);
  pinMode(leftEncB, INPUT_PULLUP);
  pinMode(rightEncA, INPUT_PULLUP);
  pinMode(rightEncB, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(leftEncA), handleLeftEncoder, RISING);
  attachInterrupt(digitalPinToInterrupt(rightEncA), handleRightEncoder, RISING);
}

float degToRad(float degrees) {
  return degrees * (PI / 180.0);
}

float radToDeg(float radians) {
  return radians * (180.0 / PI);
}

void updateOdometry() {
  if (currentTime - prevTime < 10) return; 

  long currentLeft, currentRight;
  noInterrupts();
  currentLeft = leftTick;
  currentRight = rightTick;
  interrupts();

  // We calculate how many ticks have passed since the last loop
  long distLeftTicks = currentLeft - prevLeftTick;
  long distRightTicks = currentRight - prevRightTick;

  // We convert the ticks to centimetres
  float distLeft = distLeftTicks * DISTANCE_PER_TICK;
  float distRight = distRightTicks * DISTANCE_PER_TICK;

  // We calculate the average distance moved
  float distAverage = (distLeft + distRight) / 2.0;
  totalDistance += distAverage;

  float changeInAngle = (distRight - distLeft) / (TRACK_WIDTH * odometryFudge);
  
  // We use the center of the angle turned,
  // because the robot is constantly changing angle as it moves
  // so we take an average of the starting and ending angle for this time period
  float midAngle = robotAngle + (changeInAngle / 2.0);
  
  robotX += distAverage * cos(midAngle);
  robotY += distAverage * sin(midAngle);
  robotAngle += changeInAngle;

  prevTime = currentTime;
  prevLeftTick = currentLeft;
  prevRightTick = currentRight;
}

void handleLeftEncoder() {
  if (digitalRead(leftEncB)) {
    leftTick--;
  }
  else {
    leftTick++;
  }
}

void handleRightEncoder() {
  if (digitalRead(rightEncB)) {
    rightTick++;
  }
  else {
    rightTick--;
  }
}

void resetOdometry() {

  noInterrupts();
  leftTick = 0;
  rightTick = 0;
  interrupts();

  prevLeftTick = 0;
  prevRightTick = 0;

  robotX = 0;
  robotY = 0;

  robotAngle = PI / 2.0;
  totalDistance = 0;
}