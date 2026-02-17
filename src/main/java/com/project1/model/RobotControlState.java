package com.project1.model;

// We can add the other control states here (like maze following, PD, U turn etc)
public enum RobotControlState {
  MANUAL,
  LINE_FOLLOW_BANGBANG,
  SOLVE_MAZE_1,
  SOLVE_MAZE_2,
  SOLVE_MAZE_3,
  LOST_ROBOT,
  EMERGENCY_STOP,
  U_TURN,
  PARKING_IN_BOX
}
