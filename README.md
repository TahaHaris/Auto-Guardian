# 🤖 Autonomous Security Patrol Robot with ESP32 + Camera + Obstacle Avoidance

An all-in-one intelligent security robot that patrols your home, avoids obstacles, detects motion, **sounds an alarm**, and **triggers a live camera feed** via the ESP32-CAM. Ideal for personal home security projects, student robotics, or embedded systems showcases.

---

## 🎯 Features

- 🔄 **Autonomous Navigation**: Drives forward and avoids obstacles using 4 ultrasonic sensors.
- 🔊 **Buzzer Alarm**: Sounds when motion is detected.
- 👀 **PIR Motion Detection**: Senses intrusions in a room.
- 📷 **ESP32-CAM Streaming**: Triggers a live camera stream when motion is detected.
- 🚘 **Quad Motor Drive**: Differential drive using 4 H-bridge motor channels.
- ⚙️ **Embedded C/C++ (Arduino)**: Entire system coded in Arduino for ESP32 boards.

---

## 🧠 System Overview

```text
             [ PIR Sensor ]
                  |
                  v
        [ ESP32 Control Board ]
                  |
    ┌─────────────┼─────────────┐
    ↓             ↓             ↓
[ Motors ]   [ Ultrasonics ]   [ Buzzer ]
                                  |
                             [ Camera Trigger ]
                                  ↓
                           [ ESP32-CAM Module ]
