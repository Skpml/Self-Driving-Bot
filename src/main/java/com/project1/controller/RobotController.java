package com.project1.controller;

import javafx.application.Platform;

import java.net.http.HttpResponse;
import java.util.Set;
import java.util.function.Consumer;

import com.project1.model.RobotControlState;
import com.project1.model.RobotModel;
import com.project1.services.ArduinoEndpoints;
import com.project1.services.ArduinoHTTPClient;


// In MVC the controller is called by the view and it updates the model
public class RobotController {

    private final ArduinoHTTPClient client;
    private final Consumer<String> logger;
    private final RobotModel model;
    private String currentEndpoint = ArduinoEndpoints.STOP;

    public RobotController(ArduinoHTTPClient client, Consumer<String> logger, RobotModel model) {
        this.client = client;
        this.logger = logger;
        this.model = model;
    }

    public void setSpeed(int targetSpeed) {
        sendRequest(ArduinoEndpoints.getSpeedEndpoint(targetSpeed), res -> {
            model.setSpeed(targetSpeed);
        });
    }

    public void setEmergencyStopDistance(int targetDist) {
        sendRequest(ArduinoEndpoints.getEmergencyStopDistanceEndpoint(targetDist), res -> {
            model.setEmergencyStopDistance(targetDist);
        });
    }

    public void setRotationSpeed(int targetSpeed) {
        sendRequest(ArduinoEndpoints.getRotationSpeedEndpoint(targetSpeed), res -> {
            model.setRotationSpeed(targetSpeed);
        });
    }

    public void setReverseDuration(int targetDuration) {
        sendRequest(ArduinoEndpoints.getReverseDurationEndpoint(targetDuration), res -> {
            model.setReverseDuration(targetDuration);
        });
    }

    public void setTurnDuration(int targetDuration) {
        sendRequest(ArduinoEndpoints.getTurnDurationEndpoint(targetDuration), res -> {
            model.setTurnDuration(targetDuration);
        });
    }

    public void setJunctionDuration(int targetDuration) {
        sendRequest(ArduinoEndpoints.getJunctionDurationEndpoint(targetDuration), res -> {
            model.setJunctionDuration(targetDuration);
        });
    }

    public void setOdometryFudge(double targetFudge) {
        sendRequest(ArduinoEndpoints.getOdometryFudgeEndpoint(targetFudge), res -> {
            model.setOdometryFudge(targetFudge);
        });
    }

    public void resetOdometry() {
        sendRequest(ArduinoEndpoints.RESET_ODOMETRY, res -> {
            model.clearHistory();
            model.setAngle(Math.PI/2.0);
            model.setTotalDistance(0);
            model.setX(0);
            model.setY(0);
        });
    }

    public void setControlState(RobotControlState targetState) {
        String endpoint;
        switch (targetState) {
            case MANUAL:                 endpoint = ArduinoEndpoints.MANUAL;               break; 
            case LINE_FOLLOW_BANGBANG:   endpoint = ArduinoEndpoints.LINE_FOLLOW_BANGBANG; break;
            case SOLVE_MAZE_1:           endpoint = ArduinoEndpoints.SOLVE_MAZE_1;         break;
            case SOLVE_MAZE_2:           endpoint = ArduinoEndpoints.SOLVE_MAZE_2;         break;
            case SOLVE_MAZE_3:           endpoint = ArduinoEndpoints.SOLVE_MAZE_3;         break;
            case LOST_ROBOT:             endpoint = ArduinoEndpoints.LOST_ROBOT;           break;
            case EMERGENCY_STOP:         endpoint = ArduinoEndpoints.EMERGENCY_STOP;       break;
            case U_TURN:                 endpoint = ArduinoEndpoints.U_TURN;               break;
            case PARKING_IN_BOX:         endpoint = ArduinoEndpoints.PARKING_IN_BOX;       break;
            default: return;
        }

        sendRequest(endpoint, res -> {
            model.setControlState(targetState);
        });
    }

    public void stop() {
        sendRequest(ArduinoEndpoints.STOP, res -> {});
    }

    public void handleMovement(Set<String> activeInputs) {
        
        if (activeInputs.isEmpty()) {
            stop();
            return;
        }

        boolean forward   = activeInputs.contains("W");
        boolean backward  = activeInputs.contains("S");
        boolean left      = activeInputs.contains("A");
        boolean right     = activeInputs.contains("D");
        boolean shift     = activeInputs.contains("SHIFT");
        boolean shiftLeft = activeInputs.contains("SHIFT_A"); 
        boolean shiftRight= activeInputs.contains("SHIFT_D"); 

        String endpoint;

        if (forward && !left && !right) {
            endpoint = ArduinoEndpoints.FORWARD;
        } else if (backward) {
            endpoint = ArduinoEndpoints.BACKWARD;
        } else if (forward && left) {
            endpoint = ArduinoEndpoints.LEFT;
        } else if (forward && right) {
            endpoint = ArduinoEndpoints.RIGHT;
        } else if ((shift && left && !right) || shiftLeft) { 
            endpoint = ArduinoEndpoints.CRAB_WALK_LEFT;
        } else if ((shift && right && !left) || shiftRight) {
            endpoint = ArduinoEndpoints.CRAB_WALK_RIGHT;
        } else if (left && !right) {
            endpoint = ArduinoEndpoints.TURN_ON_SPOT_LEFT;
        } else if (right && !left) {
            endpoint = ArduinoEndpoints.TURN_ON_SPOT_RIGHT;
        } else {
            endpoint = ArduinoEndpoints.STOP;
        }

        sendRequest(endpoint, res -> {});
    }

    public void sendRequest(String endpoint, Consumer<HttpResponse<String>> onSuccess) {
        
        currentEndpoint = endpoint;
        logger.accept("Sending: " + endpoint);

        new Thread(() -> {
            try {
                HttpResponse<String> response = client.send(endpoint);
                Platform.runLater(() -> {
                    if (response != null) {
                        if (response.statusCode() == 200) {
                            if (onSuccess != null) {
                                logger.accept(response.body());
                                onSuccess.accept(response);
                            } 
                        } else {
                            logger.accept("Command Failed: " + response.statusCode());
                        }
                    } else {
                        logger.accept("Error: Robot Unreachable after 3 Attempts");
                    }
                });
            } catch (Exception e) {
                Platform.runLater(() -> logger.accept("Failed: " + e.getMessage()));
            }
        }).start();
    }

    public String getCurrentEndpoint() {
        return currentEndpoint;
    }
}