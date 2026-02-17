package com.project1.model;

import javafx.beans.property.*;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.geometry.Point2D;

// In MVC the model stores all the data in one place, is is updated by the Controller and it tells the View what to display
public class RobotModel {
    public RobotModel() {};

    // We use these JavaFX property objects so we can bind our GUI to these values
    private final IntegerProperty speed = new SimpleIntegerProperty(80);
    private final IntegerProperty emergencyStopDistance = new SimpleIntegerProperty(30);
    
    private final IntegerProperty rotationSpeed = new SimpleIntegerProperty(100);
    private final IntegerProperty reverseDuration = new SimpleIntegerProperty(120);
    private final IntegerProperty turnDuration = new SimpleIntegerProperty(150);
    private final IntegerProperty junctionDuration = new SimpleIntegerProperty(200);
    private final DoubleProperty odometryFudge = new SimpleDoubleProperty(1.75);

    // State
    private final ObjectProperty<RobotMovementState> movementState = new SimpleObjectProperty<>(RobotMovementState.STOPPED);
    private final ObjectProperty<RobotControlState> controlState = new SimpleObjectProperty<>(RobotControlState.MANUAL);
    
    // Sensors
    private final StringProperty ultrasonic = new SimpleStringProperty("WAITING");
    private final StringProperty irLeftDigital = new SimpleStringProperty("WAITING");
    private final StringProperty irRightDigital = new SimpleStringProperty("WAITING");

    // Map
    private final DoubleProperty x = new SimpleDoubleProperty(0);
    private final DoubleProperty y = new SimpleDoubleProperty(0);
    private final DoubleProperty angle = new SimpleDoubleProperty(Math.toRadians(90)); 
    private final DoubleProperty totalDistance = new SimpleDoubleProperty(0.0);
    private final ObservableList<Point2D> positionHistory = FXCollections.observableArrayList();

    // Property Accessors
    public IntegerProperty speedProperty() { return speed; }
    public IntegerProperty emergencyStopDistanceProperty() { return emergencyStopDistance; }
    
    public IntegerProperty rotationSpeedProperty() { return rotationSpeed; }
    public IntegerProperty reverseDurationProperty() { return reverseDuration; }
    public IntegerProperty turnDurationProperty() { return turnDuration; }
    public IntegerProperty junctionDurationProperty() { return junctionDuration; }
    public DoubleProperty odometryFudgeProperty() { return odometryFudge; }

    public ObjectProperty<RobotMovementState> movementStateProperty() { return movementState; }
    public ObjectProperty<RobotControlState> controlStateProperty() { return controlState; }

    public DoubleProperty xProperty() { return x; }
    public DoubleProperty yProperty() { return y; }
    public DoubleProperty angleProperty() { return angle; }
    public DoubleProperty totalDistanceProperty() { return totalDistance; }
    public ObservableList<Point2D> getPositionHistory() { return positionHistory; }

    public StringProperty ultrasonicProperty() { return ultrasonic; }
    public StringProperty leftIRDigitalProperty() { return irLeftDigital; }
    public StringProperty rightIRDigitalProperty() { return irRightDigital; }

    // Getters and Setters
    public int getSpeed() { return speed.get(); }
    public void setSpeed(int val) { this.speed.set(val); }

    public int getEmergencyStopDistance() { return emergencyStopDistance.get(); }
    public void setEmergencyStopDistance(int val) { this.emergencyStopDistance.set(val); }

    public int getRotationSpeed() { return rotationSpeed.get(); }
    public void setRotationSpeed(int val) { this.rotationSpeed.set(val); }

    public int getReverseDuration() { return reverseDuration.get(); }
    public void setReverseDuration(int val) { this.reverseDuration.set(val); }

    public int getTurnDuration() { return turnDuration.get(); }
    public void setTurnDuration(int val) { this.turnDuration.set(val); }

    public int getJunctionDuration() { return junctionDuration.get(); }
    public void setJunctionDuration(int val) { this.junctionDuration.set(val); }

    public double getOdometryFudge() { return odometryFudge.get(); }
    public void setOdometryFudge(double val) { this.odometryFudge.set(val); }
    
    public RobotMovementState getMovementState() { return movementState.get(); }
    public void setMovementState(RobotMovementState val) { this.movementState.set(val); }
    
    public RobotControlState getControlState() { return controlState.get(); }
    public void setControlState(RobotControlState val) { this.controlState.set(val); }
    
    public double getX() { return x.get(); }
    public void setX(double val) { this.x.set(val); }
    
    public double getY() { return y.get(); }
    public void setY(double val) { this.y.set(val); }
    
    public double getAngle() { return angle.get(); }
    public void setAngle(double val) { this.angle.set(val); }
    
    public double getTotalDistance() { return totalDistance.get(); }
    public void setTotalDistance(double val) { this.totalDistance.set(val); }

    public void clearHistory() {
        positionHistory.clear();
    }

    public void setSensorData(String dist, String irLeftDigital, String irRightDigital, double angle, double totalDist) {
        this.ultrasonic.set(dist);
        this.irLeftDigital.set(irLeftDigital);
        this.irRightDigital.set(irRightDigital);
        
        this.angle.set(angle);
        this.totalDistance.set(totalDist);
    }
    
}