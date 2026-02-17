// Has A at front so we know we compile this right after Main
// Pins that describe the WIFI module.
// Pins used from the Arduino Wi-Fi library
const int WINC_CS  = 8, WINC_IRQ = 7, WINC_RST = 4, WINC_EN = 2;

// Wifi name and password
const char ssid[] = "Team 36";
const char pass[] = "Team36Rules";
// >= 8 chars for WPA2

// Assign PWM (speed) and DIR (direction) pins for each motor
const int FL_PWM = 6,  FL_DIR = 5;     // Front Left Motor
const int FR_PWM =9, FR_DIR=10;        // Front Right 
const int BL_PWM = A4, BL_DIR = A5;    // Back Left
const int BR_PWM=11, BR_DIR = 12;      // Back Right

// IR Digital Sensor Pins
const int IR_DIGITAL_LEFT_SENSOR_PIN = A0;
const int IR_DIGITAL_RIGHT_SENSOR_PIN = A2; 

// Pins for encoders
const int leftEncA = A3; // Pin A3
const int leftEncB = A1; // Pin A1
const int rightEncA = 21; // Pin SCL
const int rightEncB = 20; // Pin SDA

// Ultrasonic pins
const int TRIG_PIN = 0;
const int ECHO_PIN = 1;

// Robot physical constants
const float WHEEL_RADIUS = 3.25;   // 3.25 cm 
const float TRACK_WIDTH  = 22; // 22 cm in real life (multiplied later by odometryFudge to account for slippage)
const float ROBOT_LENGTH = 30;
const float TICKS_PER_REV  = 224.5;    // Ticks for one full spin
const float DISTANCE_PER_TICK = (2 * PI * WHEEL_RADIUS) / TICKS_PER_REV;
double odometryFudge = 1.75;


// Robot Position and Speed
int motorSpeed = 80;           // Default speed for all motors (range: 0–255)
int motorTurningSpeed = motorSpeed*0.8;
int motorSpeedOutsideLineFollow = motorSpeed;
int rotationSpeed = 100;


float robotAngle = PI/2; // angle in Radians (initial is 90 degrees for facing up on the map)
float totalDistance = 0;// in centimetres
float robotX = 0;
float robotY = 0;


// Ultrasonic
float duration, ultrasonicDistance;
// We have HC-SR04 sensor, 60 ms is needed to avoid bad data from ghost echoes
const int ULTRASONIC_READ_INTERVAL = 60;
unsigned long lastUltrasonicReadTime = 0;

// IR
int leftDigitalIRReading, rightDigitalIRReading;

// Target values  
float targetAngleStart = 0;
float targetAngleEnd = 0;
float targetTotalDistance = 0;

long stateStartTime = 0;
long lastLeftBlackTime = 0;
long lastRightBlackTime = 0;

boolean isMoving;

long TURN_START_REVERSE_DURATION = 120;// To counter the momentum that could send us over the line if we started turning as soon as we found a line
long MINIMUM_TURN_DURATION = 150; // So that we dont immediately trigger on the sensor again after turning, this makes us commit to a turn for a bit for better allignment
const long STOP_TIME_AT_INTERSECTION = 500;
long JUNCTION_TIME_DELTA = 200;  

int emergencyStopDistance = 30;
const int MAZE_OBSTACLE_DISTANCE = 13;
bool uTurnCompleted = false;


RobotMovementState currentMovementState = STOPPED;
RobotControlState currentControlState = MANUAL;
MazeState mazeState = FOLLOW_LINE;
LostRobotState lostRobotState = SEARCHING_FOR_THE_LINE;
EmergencyStopState emergencyStopState = BANG_LINE_FOLLOWING;
ParkingBoxState parkingBoxState = APPROACHING_PARKING_BOX;