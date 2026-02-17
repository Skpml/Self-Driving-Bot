
struct Junction
{
  bool triedLeft;
  bool triedStraight;
  bool triedRight;
};

const int MAX_JUNCTIONS = 40;
Junction junctionStack[MAX_JUNCTIONS];
int junctionStackTop = -1;
bool backtracking = false;

void pushJunction()
{
  junctionStackTop++;
  junctionStack[junctionStackTop].triedLeft = false;
  junctionStack[junctionStackTop].triedStraight = false;
  junctionStack[junctionStackTop].triedRight = false;
}

void leftHandWithCounting()
{
  if ((mazeState == FOLLOW_LINE || mazeState == TURNING_LEFT || mazeState == TURNING_RIGHT || mazeState == BLIND_TURN) && junctionDetectedTimed())
  {

    stopAllMotors();
    stateStartTime = currentTime;
    mazeState = JUNCTION_FOUND;
  }
  switch (mazeState)
  {
  case FOLLOW_LINE:
    if (obstacleFound())
    {
      stopAllMotors();
      stateStartTime = currentTime;
      mazeState = OBJECT_DETECTED;
      break;
    }
    if (leftDigitalIRReading == 0 && rightDigitalIRReading == 0)
    {
      moveForward();
    }
    else if (leftDigitalIRReading == 1 && rightDigitalIRReading == 0)
    {
      moveBackward();
      stateStartTime = currentTime;
      mazeState = TURNING_LEFT;
      break;
    }
    else if (leftDigitalIRReading == 0 && rightDigitalIRReading == 1)
    {
      moveBackward();
      stateStartTime = currentTime;
      mazeState = TURNING_RIGHT;
      break;
    }
    break;

  case TURNING_LEFT:
    if (currentTime - stateStartTime >= TURN_START_REVERSE_DURATION)
    {
      turnOnSpotLeft();
      if (leftDigitalIRReading == 0 && rightDigitalIRReading == 0)
      {
        stateStartTime = currentTime;
        mazeState = BLIND_TURN;
        break;
      }
    }
    break;

  case TURNING_RIGHT:
    if (currentTime - stateStartTime >= TURN_START_REVERSE_DURATION)
    {
      turnOnSpotRight();
      if (leftDigitalIRReading == 0 && rightDigitalIRReading == 0)
      {
        stateStartTime = currentTime;
        mazeState = BLIND_TURN;
        break;
      }
    }
    break;

  case BLIND_TURN:
    if (currentTime - stateStartTime >= MINIMUM_TURN_DURATION)
    {
      mazeState = FOLLOW_LINE;
      break;
    }
    break;

  case JUNCTION_FOUND:
    if (currentTime - stateStartTime >= STOP_TIME_AT_INTERSECTION)
    {
      targetTotalDistance = totalDistance + 8;
      mazeState = DRIVE_THROUGH_INTERSECTION;
      if (!backtracking)
        pushJunction();
    }
    break;

  case DRIVE_THROUGH_INTERSECTION:
  {
    boolean isMoving = moveToDistance(targetTotalDistance);
    if (!isMoving)
    {
      stopAllMotors();
      targetAngleStart = radToDeg(robotAngle);

      // Decide junction here
      Junction *junction = &junctionStack[junctionStackTop];

      // our order is left, straight, right
      // so if we are backtracking and we tried right
      // we are coming back from right we should backtrack again.
      if (backtracking && junction->triedRight)
      {
        junctionStackTop--;
        mazeState = SCAN_LEFT_FOR_LINE;
        break;
      }
      // if we are backtracking and tried straight
      // means we are coming back from straight, so try
      // the junctions "right", ours left
      else if (backtracking && junction->triedStraight)
      {
        junction->triedRight = true;
        backtracking = false;
        mazeState = SCAN_LEFT_FOR_LINE;
      }
      // if we are backtracking and tried left
      // means we are coming back from left, so try
      // the junctions "straight", our left
      else if (backtracking && junction->triedLeft)
      {
        junction->triedStraight = true;
        backtracking = false;
        mazeState = SCAN_LEFT_FOR_LINE;
      }
      else if (!junction->triedLeft)
      {
        junction->triedLeft = true;
        mazeState = SCAN_LEFT_FOR_LINE;
      }
      else if (!junction->triedStraight)
      {
        junction->triedStraight = true;
        mazeState = FOLLOW_LINE;
      }
      else if (!junction->triedRight)
      {
        junction->triedRight = true;
        targetAngleStart = radToDeg(robotAngle);
        mazeState = RECOVER_RIGHT_FIND_BLACK;
      }
      else
      {
        junctionStackTop--;
        backtracking = true;
        targetAngleEnd = radToDeg(robotAngle) + 180;
        mazeState = TURNING_180_DEGREES;
      }
    }
  }
  break;

  case SCAN_LEFT_FOR_LINE:
  {
    turnOnSpotLeft();

    float currentDeg = radToDeg(robotAngle);
    float angleDiff = currentDeg - targetAngleStart;

    if (leftDigitalIRReading == 1)
    {
      mazeState = ALIGN_EXTRA_LEFT;
    }
    else if (angleDiff > 135)
    {
      stopAllMotors();
      mazeState = RECOVER_RIGHT_FIND_BLACK;
    }
  }
  break;

  case ALIGN_EXTRA_LEFT:
  {
    turnOnSpotLeft();
    if (rightDigitalIRReading == 1)
    {
      stopAllMotors();
      mazeState = FOLLOW_LINE;
    }
  }
  break;

  case RECOVER_RIGHT_FIND_BLACK:
    turnOnSpotRight();
    if (rightDigitalIRReading == 1)
    {
      mazeState = RECOVER_RIGHT_FIND_WHITE;
    }
    break;

  case RECOVER_RIGHT_FIND_WHITE:
    turnOnSpotRight();
    if (leftDigitalIRReading == 1)
    {
      stopAllMotors();
      mazeState = FOLLOW_LINE;
    }
    break;

  case OBJECT_DETECTED:
    if (currentTime - stateStartTime >= STOP_TIME_AT_INTERSECTION)
    {
      targetAngleEnd = radToDeg(robotAngle) + 170;
      mazeState = TURNING_180_DEGREES;
      break;
    }
    break;

  case TURNING_180_DEGREES:
  {
    boolean isTurning = turnToAbsoluteAngle(targetAngleEnd);
    if (!isTurning)
    {
      stopAllMotors();
      mazeState = AFTER_180_RIGHT_SENSOR_SEARCH;
    }
  }
  break;

  case AFTER_180_RIGHT_SENSOR_SEARCH:
    turnOnSpotLeft();
    if (rightDigitalIRReading == 1)
    {
      mazeState = FOLLOW_LINE;
      break;
    }
    break;

  case LOST_ROBOT1:
    stopAllMotors();
    break;
  }
}