# **Auto Guardian**

Auto Guardian is an autonomous security patrol robot powered by ESP32, designed for reliable home and small-area surveillance. It combines real-time obstacle avoidance, human motion detection, audible alerts, and on-demand live video streaming through an ESP32-CAM, delivering an efficient and scalable DIY security solution.

---

## 📸 Project Overview

![Robot Diagram]([https://raw.githubusercontent.com/user/repo/main/images/robot_diagram.png](https://github.com/TahaHaris/Auto-Guardian/blob/main/Auto-Guardian%20Video.mov))  
*Visualizes the entire system: motors, ultrasonic sensors, PIR motion detector, buzzer, and ESP32-CAM module*

This robot leverages:

- Four ultrasonic sensors for 360° obstacle detection.
- PIR sensor-based human motion detection.
- Buzzer alerts for immediate local notification.
- ESP32-CAM triggered streaming over Wi-Fi for remote surveillance.
- Intelligent motion and recovery logic for seamless autonomous patrol.

---

## 🔧 Key Features & Why They Matter

- **360° Real-Time Obstacle Avoidance:** Ensures collision-free navigation using ultrasonic ranging in all directions.
- **Motion-Triggered Camera Streaming:** Optimizes bandwidth and power by streaming only on PIR detection.
- **Fail-Safe Reverse & Turn Maneuvers:** Robust recovery behavior to prevent getting stuck, a hallmark of mature robotics software.
- **Buzzer Alerts:** Simple but effective local warning system enhancing security awareness.
- **Serial Debugging Outputs:** A developer-friendly feature aiding live diagnostics and tuning.

---

## 🧰 Hardware Breakdown

| Component               | Quantity | Purpose                                |
|-------------------------|----------|--------------------------------------|
| ESP32 Dev Board         | 1        | Main controller for motion & sensors |
| ESP32-CAM Module        | 1        | Streaming video on motion detection  |
| L298N / L9110 Motor Driver | 2      | Drives four DC geared motors         |
| DC Geared Motors        | 4        | Four-wheel drive mobility             |
| HC-SR04 Ultrasonic Sensors | 4      | Distance sensing (Front, Back, Left, Right) |
| HC-SR501 PIR Motion Sensor | 1      | Detects presence of humans            |
| Active Buzzer Module    | 1        | Audio alert for motion                |
| Li-ion Battery (7.4V)   | 1        | Portable power supply                  |
| Chassis & Wheels       | 1        | Structural base for mobility          |

---

## 🪛 GPIO Pin Assignments

### Motor Driver Control (ESP32 Main Board)

| Motor        | IN1 | IN2 | EN (PWM) |
|--------------|-----|-----|----------|
| Front Left   | 27  | 26  | 14       |
| Back Left    | 33  | 25  | 32       |
| Back Right   | 19  | 18  | 17       |
| Front Right  | 16  | 15  | 4        |

### Ultrasonic Sensors

| Direction | TRIG | ECHO |
|-----------|------|------|
| Front     | 23   | 22   |
| Back      | 13   | 35   |
| Left      | 5    | 34   |
| Right     | 12   | 36   |

### Additional Peripherals

| Component  | GPIO Pin |
|------------|----------|
| Buzzer     | 21       |
| PIR Sensor | 2        |

> Note: The PIR output (GPIO 2 on main ESP32) connects to GPIO13 on ESP32-CAM to trigger video streaming.

---

## 🧠 Software Architecture & Behavior Logic

![Behavior Logic Diagram](https://raw.githubusercontent.com/user/repo/main/images/robot_logic_flow_cam.png)

- **Normal Patrol Mode:** Continuous movement with ultrasonic sensors guiding obstacle avoidance.
- **Motion Detection:** When PIR sensor detects motion:
  - Buzzer sounds an alert.
  - ESP32-CAM receives trigger signal, activating live video stream.
- **Obstacle Encounter:** If blocked, the robot intelligently reverses and turns, avoiding deadlock or collision.
- **Telemetry:** Real-time sensor values and state transitions output via serial for debugging and performance tuning.

---

## 🔴 ESP32-CAM Streaming Integration

- Designed around the **ESP32-CAM AI-Thinker** board.
- Streaming only initiates when PIR sensor input is HIGH, conserving resources.
- Connects to the same Wi-Fi network as the main ESP32 board.
- Stream URL is configurable and accessible remotely.
  
### Wiring Summary for PIR Trigger

| PIR Output | ESP32-CAM Input |
|------------|-----------------|
| OUT (GPIO2 on ESP32) | GPIO13          |
| VCC        | 5V              |
| GND        | GND             |

---

## 🛠️ Setup & Deployment Instructions

### 1. Upload Main Robot Firmware

- Open `main_sketch.ino` in Arduino IDE.
- Select board: **ESP32 Dev Module**.
- Connect and upload via USB.
- Open Serial Monitor (115200 baud) for live logs.

### 2. Upload ESP32-CAM Firmware

- Open `camera_web_server.ino` in Arduino IDE.
- Select board: **ESP32 AI-Thinker**.
- Configure Wi-Fi credentials in code.
- Use FTDI adapter to upload (hold IO0 LOW during upload).
- After reset, streaming starts on PIR motion detection.

---

## 👨‍💻 Author

**Taha Haris**  

---
