float referenceHeading = 90.0; // Initialize with your starting angle (e.g., 90 for North)
void leftHandWithDegrees() {

  if ( (mazeState == FOLLOW_LINE || mazeState == TURNING_LEFT || mazeState == TURNING_RIGHT || mazeState == BLIND_TURN ) 
        && junctionDetectedTimed() ) {
        
        stopAllMotors();
        stateStartTime = currentTime;
        mazeState = JUNCTION_FOUND;
    }

  switch (mazeState) {
    case FOLLOW_LINE:
      if (obstacleFound()) {
        stopAllMotors();
        stateStartTime = currentTime;
        mazeState = OBJECT_DETECTED;
        break;
      } 
      if (leftDigitalIRReading == 0 && rightDigitalIRReading == 0) {
        moveForward();
      } else if (leftDigitalIRReading == 1 && rightDigitalIRReading == 0) {
        moveBackward(); 
        stateStartTime = currentTime;
        mazeState = TURNING_LEFT;
        break;
      } else if (leftDigitalIRReading == 0 && rightDigitalIRReading == 1) {
        moveBackward(); 
        stateStartTime = currentTime;
        mazeState = TURNING_RIGHT;
        break;
      }
      break;

    case TURNING_LEFT:
      if (currentTime - stateStartTime >= TURN_START_REVERSE_DURATION) { 
        turnOnSpotLeft();
        if (leftDigitalIRReading == 0 && rightDigitalIRReading == 0) {
          stateStartTime = currentTime;
          mazeState = BLIND_TURN;
          break;
        }
      }
      break;

    case TURNING_RIGHT:
      if (currentTime - stateStartTime >= TURN_START_REVERSE_DURATION) {
        turnOnSpotRight();
        if (leftDigitalIRReading == 0 && rightDigitalIRReading == 0) {
          stateStartTime = currentTime;
          mazeState = BLIND_TURN;
          break;
        }
      }
      break;

    case BLIND_TURN:
      if (currentTime - stateStartTime >= MINIMUM_TURN_DURATION) {
        mazeState = FOLLOW_LINE;
        break;
      }
      break;

  case JUNCTION_FOUND:
      if (currentTime - stateStartTime >= STOP_TIME_AT_INTERSECTION) { 
        targetTotalDistance = totalDistance + 8;
        mazeState = DRIVE_THROUGH_INTERSECTION;
        stateStartTime = currentTime;
      }
      break;

   case DRIVE_THROUGH_INTERSECTION: {
      boolean isMoving = moveToDistance(targetTotalDistance);
      
      if (!isMoving) {
        stopAllMotors();
        targetAngleStart = radToDeg(robotAngle); 
        
        float currentGlobalDeg = radToDeg(robotAngle);
        float deviation = currentGlobalDeg - referenceHeading;

        if (abs(deviation) >= 340.0) {
             mazeState = SCAN_RIGHT_FOR_LINE;
        } 
        else {
             mazeState = SCAN_LEFT_FOR_LINE;
        }
      }
    } break;

    case SCAN_LEFT_FOR_LINE: {
      turnOnSpotLeft();

      float currentDeg = radToDeg(robotAngle);
      float angleDiff = abs(currentDeg - targetAngleStart);

      if (leftDigitalIRReading == 1) { 
          mazeState = ALIGN_EXTRA_LEFT;
      } 
      else if (angleDiff > 120) {
          stopAllMotors();
          mazeState = RECOVER_RIGHT_FIND_BLACK;
      }
    } break;


    case SCAN_RIGHT_FOR_LINE: {
      turnOnSpotRight();

      float currentDeg = radToDeg(robotAngle);
      float angleDiff = abs(currentDeg - targetAngleStart);

      if (rightDigitalIRReading == 1) { 
          mazeState = ALIGN_EXTRA_RIGHT;
          referenceHeading = radToDeg(robotAngle);
      } 
      else if (angleDiff > 120) {
          stopAllMotors();
          mazeState = RECOVER_LEFT_IN_ESCAPE;
      }
    } break;

    case RECOVER_LEFT_IN_ESCAPE:
      turnOnSpotLeft();
      
      if (leftDigitalIRReading == 1) {
          float currentDeg = radToDeg(robotAngle);
          
          if (abs(currentDeg - targetAngleStart) < 45) {
               referenceHeading = currentDeg; 
          }
          
          mazeState = RECOVER_LEFT_FIND_WHITE;
      }
      break;

    case ALIGN_EXTRA_LEFT: {
      turnOnSpotLeft();
      if (rightDigitalIRReading == 1) {
          stopAllMotors();
          mazeState = FOLLOW_LINE;
      }
    } break;

    case ALIGN_EXTRA_RIGHT: {
      turnOnSpotRight();
      if (leftDigitalIRReading == 1) {
          stopAllMotors();
          mazeState = FOLLOW_LINE;
      }
    } break;

    case RECOVER_RIGHT_FIND_BLACK:
      turnOnSpotRight();
      if (rightDigitalIRReading == 1) {
          mazeState = RECOVER_RIGHT_FIND_WHITE;
      }
      break;

    case RECOVER_RIGHT_FIND_WHITE:
      turnOnSpotRight();
      if (rightDigitalIRReading == 0) {
          stopAllMotors();
          mazeState = FOLLOW_LINE;
      }
      break;

    case RECOVER_LEFT_FIND_BLACK:
      turnOnSpotLeft();
      if (leftDigitalIRReading == 1) {
          mazeState = RECOVER_LEFT_FIND_WHITE;
      }
      break;

    case RECOVER_LEFT_FIND_WHITE:
      turnOnSpotLeft();
      if (leftDigitalIRReading == 0) {
          stopAllMotors();
          mazeState = FOLLOW_LINE;
      }
      break;
      
    case OBJECT_DETECTED:
      if (currentTime - stateStartTime >= STOP_TIME_AT_INTERSECTION) {
        targetAngleEnd = radToDeg(robotAngle) + 180;
        mazeState = TURNING_180_DEGREES;
        break;
      }
      break;

    case TURNING_180_DEGREES: {
      boolean isTurning = turnToAbsoluteAngle(targetAngleEnd);
      if (!isTurning) {
        stopAllMotors();
        mazeState = AFTER_180_RIGHT_SENSOR_SEARCH;
      }
    } break;

    case AFTER_180_RIGHT_SENSOR_SEARCH:
      turnOnSpotLeft();
      if (rightDigitalIRReading == 1) {
        mazeState = FOLLOW_LINE;
        break;
      }
      break;

    case LOST_ROBOT1:
      stopAllMotors();
      break;
    
  }
}
