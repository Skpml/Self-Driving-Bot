
void resetUTurn() {
  uTurnCompleted = false;
  resetEndOfLineDetection();
}

void uTurn() {
  if (uTurnCompleted) {
    stopAllMotors();
    return;
  }

  bangLineFollow();
  
  if (detectEndOfLine()) {
    uTurnCompleted = true;
  }
}