package com.project1.services;


public final class ArduinoEndpoints {

    // These are the things we attach at the end of the IP address. e.g. 192.168.1.1/forward for our HTTP request in ArduinoClient
    public static final String FORWARD            = "/forward";
    public static final String BACKWARD           = "/backward";
    public static final String TURN_ON_SPOT_RIGHT = "/turnOnSpotRight";
    public static final String TURN_ON_SPOT_LEFT  = "/turnOnSpotLeft";
    public static final String LEFT               = "/left";
    public static final String RIGHT              = "/right";
    public static final String STOP               = "/stop";
    public static final String CRAB_WALK_LEFT     = "/crabWalkLeft";
    public static final String CRAB_WALK_RIGHT    = "/crabWalkRight";
    
    public static final String MANUAL               = "/manual";
    public static final String LINE_FOLLOW_BANGBANG = "/lineFollowBangBang";
    public static final String SOLVE_MAZE_1         = "/solveMaze1";
    public static final String SOLVE_MAZE_2         = "/solveMaze2";
    public static final String SOLVE_MAZE_3         = "/solveMaze3";
    public static final String LOST_ROBOT           = "/lostRobot";
    public static final String EMERGENCY_STOP       = "/emergencyStop";
    public static final String U_TURN               = "/uTurn";
    public static final String PARKING_IN_BOX       = "/parkingInBox";

    public static final String RESET_ODOMETRY       = "/resetOdometry";


    public static String getSpeedEndpoint(int value) {
        return "/setSpeed?s=" + value;
    }

    public static String getEmergencyStopDistanceEndpoint(int value) {
        return "/setEmergencyStopDistance?s=" + value;
    }

    public static String getRotationSpeedEndpoint(int value) {
        return "/setRotationSpeed?s=" + value;
    }

    public static String getReverseDurationEndpoint(int value) {
        return "/setReverseDuration?s=" + value;
    }

    public static String getTurnDurationEndpoint(int value) {
        return "/setTurnDuration?s=" + value;
    }

    public static String getJunctionDurationEndpoint(int value) {
        return "/setJunctionDuration?s=" + value;
    }

    public static String getOdometryFudgeEndpoint(double value) {
        return "/setOdometryFudge?s=" + value;
    }
    
}