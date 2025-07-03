# 🤖 ESP32 Autonomous Security Patrol Robot with Camera Streaming

This is a fully autonomous 4-motor patrol robot powered by the ESP32, equipped with ultrasonic obstacle avoidance, motion detection, buzzer alerts, and live camera streaming. When motion is detected by the PIR sensor, the ESP32-CAM module activates and begins real-time video transmission over Wi-Fi — perfect for smart home surveillance.

---

## 📸 Overview

![Robot Diagram](https://raw.githubusercontent.com/user/repo/main/images/robot_diagram.png)
> *Complete system: Motors + Ultrasonic + PIR + Buzzer + ESP32-CAM*

---

## 🔧 Features

✅ 360° Obstacle Avoidance  
✅ PIR Motion Detection with Buzzer  
✅ ESP32-CAM Streaming on Motion  
✅ Intelligent Reverse + Turning Logic  
✅ Real-Time Serial Debugging  

---

## 🧰 Hardware Components

| Component              | Quantity | Notes                                |
|-----------------------|----------|--------------------------------------|
| ESP32 Dev Board       | 1        | Motor & sensor control               |
| ESP32-CAM Module      | 1        | Camera streaming on motion detect   |
| L298N / L9110 H-Bridge| 2        | Motor driver                         |
| DC Geared Motors      | 4        | 4WD chassis                          |
| HC-SR04 Sensors       | 4        | Ultrasonic (front/back/left/right)  |
| HC-SR501 PIR Sensor   | 1        | Motion detection                     |
| Active Buzzer Module  | 1        | Audio alert                          |
| Li-ion Battery (7.4V) | 1        | Power source                         |
| Chassis + Wheels      | 1        | Robot frame                          |

---

## 🪛 GPIO Pin Mapping

### 🧭 Motor Control (ESP32)

| Motor        | IN1 | IN2 | EN (PWM) |
|--------------|-----|-----|----------|
| Front Left   | 27  | 26  | 14       |
| Back Left    | 33  | 25  | 32       |
| Back Right   | 19  | 18  | 17       |
| Front Right  | 16  | 15  | 4        |

### 📡 Ultrasonic Sensors

| Direction | TRIG | ECHO |
|-----------|------|------|
| Front     | 23   | 22   |
| Back      | 13   | 35   |
| Left      | 5    | 34   |
| Right     | 12   | 36   |

### 🎯 Other Peripherals

| Component      | GPIO |
|----------------|------|
| Buzzer         | 21   |
| PIR Sensor     | 2    |

> The ESP32-CAM runs separately but shares the PIR line (GPIO 2) for motion trigger.

---

## 🧠 Behavior Logic

![Logic Flow](https://raw.githubusercontent.com/user/repo/main/images/robot_logic_flow_cam.png)

1. **Normal Patrol**: Uses ultrasonic sensors to move around and avoid obstacles.
2. **Motion Detection**: If PIR sensor detects movement:
   - The buzzer starts sounding.
   - ESP32-CAM module begins live video stream.
3. **Failsafe**: If all directions are blocked, robot stops and alerts via buzzer + stream.

---

## 🔴 ESP32-CAM Streaming Setup

### Prerequisites:
- Use **ESP32-CAM AI-Thinker** board
- Connect to same Wi-Fi as the main ESP32

### Code Behavior:
- PIR sensor input triggers ESP32-CAM to start streaming.
- You can access the camera stream at:
- You can modify `camera_web_server.ino` to start streaming only when PIR = HIGH.

### Connection (ESP32-CAM PIR):

| PIR Signal | ESP32-CAM |
|------------|-----------|
| OUT        | GPIO13    |
| VCC        | 5V        |
| GND        | GND       |

---

## 📂 Project Structure


---

## 🛠️ Setup Instructions

### ✅ Upload Main Robot Code
1. Open `main_sketch.ino` in Arduino IDE.
2. Select **Board**: ESP32 Dev Module.
3. Connect and upload via USB.

### 📸 Upload ESP32-CAM Code
1. Use Arduino IDE with `camera_web_server.ino`.
2. Set Board to **ESP32 AI-Thinker**.
3. Fill in your Wi-Fi SSID and Password.
4. Upload using FTDI adapter (hold `IO0` LOW during upload).

---

## 🔒 License

This project is licensed under the MIT License. See `LICENSE` for details.

---

## 🙌 Credits

- [Espressif Camera Example](https://github.com/espressif/esp32-camera)
- [HC-SR501 PIR Datasheet](https://www.mpja.com/download/31227sc.pdf)
- [ESP32 Technical Docs](https://docs.espressif.com/)

---
