# Self Driving Bot

A comprehensive robot control system featuring an Arduino-based robot and a JavaFX-based control dashboard. This project demonstrates the integration of embedded systems with high-level software for real-time control and monitoring.

## 🎥 Demo

<div align="center">
  <video src="https://github.com/user-attachments/assets/96de0a4a-f1ab-4d88-93ca-827c8ef7eeb5" width="400" controls="controls"></video>
</div>

## 🚀 Features

*   **State Machine Architecture**: The robot is controlled by a state machine that manages the different modes of operation.
*   **WiFi Control**: wirelessly control the robot using a custom communication protocol (HTTP + TCP).
*   **Modes of Operation**:
    *   **Manual Control**: Drive the robot using the GUI or keyboard.
    *   **Line Following**: Autonomous line tracking using IR sensors.
    *   **Maze Solving**: Algorithms to navigate and solve mazes.
    *   **Obstacle Avoidance**: Autonomous obstacle avoidance using Ultrasonic sensor.
    *   **Autonomous Maneuvers**: The robot can perform a series of autonomous maneuvers using its encoders and sensors.
*   **Real-time Telemetry**: Visualize sensor data (UltraSonic, IR) and odometry in real-time.
*   **GUI Dashboard**: A user-friendly JavaFX interface for control and monitoring.

## 🛠️ Technology Stack

*   **Hardware**: Arduino (with WiFi support), DC Motors, Encoders, IR Sensors, Ultrasonic Sensor.
*   **Firmware**: C++ (Arduino).
*   **Software**: Java 17+, JavaFX, Maven.

## 📋 Prerequisites

Before you begin, ensure you have the following installed:

1.  **Java Development Kit (JDK) 17** or higher.
2.  **Maven** (for building and running the Java application).
3.  **Arduino IDE** (for uploading code to the robot).

## 💻 Installation & Setup

### 1. Hardware Setup (Arduino)
1.  Open the `Arduino/Main/Main.ino` file in the Arduino IDE.
2.  Connect your Arduino board to your computer.
3.  Install necessary libraries (e.g., `WiFi101`).
4.  Upload the sketch to your board.

### 2. Software Setup (Java App)
1.  Clone this repository:
    ```bash
    git clone https://github.com/Skpml/Self-Driving-Bot.git
    cd self-driving-bot-main
    ```
2.  Clean and build the project:
    ```bash
    mvn clean install
    ```

## 🎮 How to Run

1.  **Start the Robot**: Power on your Arduino robot. Ensure it creates or joins the expected WiFi network.
2.  **Run the Dashboard**:
    Open a terminal in the project root and run:
    ```bash
    mvn javafx:run
    ```
3.  **Connect**: Use the GUI to connect to the robot's IP address and start controlling it!

## 📂 Project Structure

*   `Arduino/`: Contains all Arduino firmware code.
*   `src/main/java`: Source code for the JavaFX application.
*   `src/main/resources`: FXML files and assets for the GUI.
*   `pom.xml`: Maven project configuration.

