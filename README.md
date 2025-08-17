# Automated Guided Forklift 🚜

This project presents the design and implementation of a **Smart Automated Guided Forklift** capable of:
- Following a predefined path using **IR sensors**  
- Detecting obstacles with **ultrasonic sensors**  
- Lifting and unloading cargo using a **servo-driven forklift mechanism**  
- Being fully controlled by an **Arduino Mega** with motor drivers and battery supply  

This system demonstrates a cost-effective and scalable approach to **warehouse automation**.

---

## 📑 Table of Contents
- [Abstract](#abstract)
- [Features](#features)
- [System Design](#system-design)
- [Hardware Used](#hardware-used)
- [Methodology](#methodology)
- [Results](#results)
- [Future Improvements](#future-improvements)
- [Project Structure](#project-structure)
- [How to Run](#how-to-run)
- [Contributors](#contributors)

---

## 🔍 Abstract
The smart forklift robot autonomously navigates along a black line on a white surface, detects obstacles in its path, and performs pick-and-place operations using a servo-driven forklift.  
It integrates:
- **IR sensors** for path tracking  
- **Ultrasonic sensor** for object detection  
- **Servo motor** for lifting/unloading cargo  
- **Arduino Mega** as the control hub  

This project demonstrates practical applications in **warehouse automation, material handling, and logistics**, where efficiency and safety are key.

---

## ✨ Features
- Line following with adjustable sensor calibration
- Cargo lifting up to **100g (tested prototype)**
- Obstacle detection with **2–400 cm ultrasonic sensing**
- Rechargeable **11.1V Li-ion battery system**
- Modular hardware for easy upgrades

---

## 🛠️ System Design
- **Chassis**: Two-wheel drive with a caster for stability  
- **IR Sensors**: 3-sensor array for line detection  
- **Ultrasonic Sensor**: Forward-facing for obstacle detection  
- **Servo Motor**: Lifting forks via string-pulley mechanism  
- **Motor Driver (L298N)**: Controls DC motors with PWM  
- **Power Supply**: 3S Li-ion pack with BMS, regulated to 5V, 9V, and 3.3V  

---

## 🔧 Hardware Used
- Arduino Mega 2560  
- L298N Motor Driver  
- 3 × IR Line Sensors  
- HC-SR04 Ultrasonic Sensor  
- Servo Motor (SG90 / MG995)  
- 11.1V Li-ion Battery Pack + BMS  
- 3D Printed Forklift Arms  
- Two-wheel chassis with caster support  

---

## 📐 Methodology
1. **Line Following**: IR sensors detect track; Arduino adjusts motor speed/direction  
2. **Obstacle Detection**: Ultrasonic sensor stops forklift within 2 cm of an object  
3. **Loading/Unloading**: Servo motor lifts object; drops it at destination  
4. **Testing**: Line track with 90° turns, 5×5×5 cm cargo box (20–40g)  

---

## 📊 Results
- Successfully followed **3 cm wide black line track** with minor oscillations  
- Cargo lifting tested with loads up to **100g** (1N force)  
- Improved accuracy after reducing sensor count from 4 to 3  
- Stable operation with optimized track width (3 cm)  

---

## 🚀 Future Improvements
- **PID Controller** for smoother line following  
- **AI-based Object Detection** with a camera module  
- **Hybrid Forklift System** (electric + hydraulic)  
- **Counterweight Optimization** for heavier loads  
- **Safety System** to prevent overturn accidents  

---

## 📂 Project Structure
