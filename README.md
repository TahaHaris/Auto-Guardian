# 🤖 ESP32 Autonomous Security Patrol Robot

This project features an ESP32-powered, 4-wheel autonomous robot equipped with ultrasonic obstacle avoidance, motion sensing, and audible alarm systems. Designed for patrolling indoor areas, it intelligently navigates rooms, avoids obstacles, and sounds an alert if human motion is detected.

---

## 📸 Overview

![Robot Concept](https://raw.githubusercontent.com/user/repo/main/images/robot_top_view.png)
> *Top-down view of the robot chassis with labeled sensors and components.*

---

## 🔧 Features

✅ 360° Obstacle Avoidance  
✅ Intelligent Turn & Reverse Logic  
✅ PIR Motion Detection with Alarm  
✅ Real-Time Serial Debugging  
✅ Modular and Expandable Architecture  

---

## 🧰 Hardware Components

| Component                  | Quantity | Notes                                |
|---------------------------|----------|--------------------------------------|
| ESP32 Dev Board           | 1        | Core microcontroller (WiFi + BLE)    |
| L298N or L9110 H-Bridge   | 2        | For controlling 4 DC motors          |
| DC Geared Motors          | 4        | Mounted on 2WD or 4WD chassis        |
| HC-SR04 Ultrasonic Sensor | 4        | Placed front, back, left, right      |
| HC-SR501 PIR Sensor       | 1        | Detects motion (human/pet)           |
| Active Buzzer Module      | 1        | Sounds alarm if motion is detected   |
| Li-ion Battery (7.4V)     | 1        | Or USB Power Bank for indoor test    |
| Robot Chassis             | 1        | Base platform for assembly           |

---

## 🪛 GPIO Pin Connections

### 🔌 Motor Control (via H-Bridge)

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

### 🔊 Other Peripherals

| Component      | GPIO |
|----------------|------|
| Buzzer         | 21   |
| PIR Sensor     | 2    |

---

## 🧠 Behavior Logic

![Flowchart](https://raw.githubusercontent.com/user/repo/main/images/robot_logic_flow.png)
> *Obstacle avoidance and motion detection logic diagram*

1. **Startup**: Motors, sensors, and serial are initialized.
2. **Patrol Loop**:
   - Robot checks front ultrasonic distance.
   - If clear, it moves forward.
   - If blocked, it reverses and turns based on side distances.
3. **Motion Detection**:
   - PIR sensor continuously reads input.
   - If motion is detected, the buzzer is activated.
4. **Failsafe**:
   - If all directions are blocked, robot stops and raises an alert.

---

## 🛠️ Getting Started

### 📥 1. Install Libraries
No external libraries needed — uses `Arduino.h` core functionality.

### 🧠 2. Flash the ESP32

- Open the `.ino` file in Arduino IDE.
- Select **Board**: ESP32 Dev Module.
- Select the correct **COM Port**.
- Click ✅ Upload.

### 🔋 3. Power the Bot

- Use USB or Li-ion battery module (7.4V).
- Ensure proper GND connection between power, ESP32, and H-bridges.

---

## 📟 Serial Output Example


---

## 📸 Demo Media

> Coming soon — upload a video/GIF of your robot in action and link it here.

---

## 📂 Project Structure


---

## 📄 License

This project is licensed under the MIT License. See [`LICENSE`](LICENSE) for details.

---

## 🙌 Acknowledgments

- Arduino & Espressif documentation
- Open-source community for robotics examples
- Contributors to sensor datasheets and libraries

---

## 🔗 Useful Links

- [HC-SR04 Datasheet](https://cdn.sparkfun.com/datasheets/Sensors/Proximity/HCSR04.pdf)
- [HC-SR501 PIR Datasheet](https://www.mpja.com/download/31227sc.pdf)
- [ESP32 Documentation](https://docs.espressif.com/)

---
