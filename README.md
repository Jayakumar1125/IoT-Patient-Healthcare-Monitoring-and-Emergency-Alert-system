<div align="center">

# IoT Patient Health Monitoring and Emergency Alert System

An advanced, real-time embedded IoT healthcare system designed to continuously monitor vital physiological parameters, perform automated onboard evaluation, trigger local safety alarms, and stream health telemetry to the cloud for remote clinical oversight.

</div>

---

## 📋 Table of Contents

1. [Project Overview](#-project-overview)
2. [Key Features](#-key-features)
3. [Hardware Specifications](#-hardware-specifications)
4. [Hardware Configuration](#️-hardware-configuration)
5. [Software Architecture & Module Mapping](#-software-architecture--module-mapping)
6. [Signal Processing Chain](#-signal-processing-chain)
7. [Alarm Conditions & Thresholds](#-alarm-conditions--thresholds)
8. [Cloud Integration](#-cloud-integration)
9. [How to Run](#-how-to-run)
10. [Repository Structure](#-repository-structure)
11. [Author](#-author)

---

# 🎯 Project Overview

In modern healthcare environments, continuous manual observation of every patient is practically impossible due to high patient-to-staff ratios. Sudden physiological shifts—such as spikes in body temperature, cardiac arrhythmias, or oxygen desaturation—can rapidly escalate into life-threatening emergencies if undetected.

This project solves this challenge by deploying an intelligent embedded assistant built around the **LPC2129 ARM7TDMI-S Microcontroller**. It continuously reads body temperature using the **DHT11** sensor and measures heart rate and blood oxygen saturation (**SpO₂**) using the **MAX30102** sensor. The system performs real-time analysis of the acquired physiological data, displays live readings on a **16×2 LCD**, activates visual and audible alerts whenever abnormal conditions are detected, and uploads patient health data to the **ThingSpeak IoT Cloud** through the **ESP-01 Wi-Fi module** for remote monitoring.

---

# ✨ Key Features

- **Continuous Multi-Parameter Monitoring:** Simultaneously monitors body temperature, heart rate (BPM), and blood oxygen saturation (SpO₂).
- **Real-Time Embedded Processing:** Continuously processes sensor data using the LPC2129 microcontroller.
- **Autonomous Health Evaluation:** Compares measured parameters against predefined medical thresholds.
- **Dual Alert Mechanism:**
  - **Local Alerts:** LCD notifications, Green/Red LEDs, and Buzzer.
  - **Remote Monitoring:** Uploads health telemetry to ThingSpeak via ESP-01 Wi-Fi.
- **Cloud Data Logging:** Stores historical patient data for remote observation and analysis.
- **Serial Debugging:** UART0 interface for development and troubleshooting.

---

# ⚙️ Hardware Specifications

- **Microcontroller:** LPC2129 ARM7TDMI-S
- **Sensors:**
  - MAX30102 (Heart Rate & SpO₂ Sensor)
  - DHT11 (Temperature Sensor)
- **Display:** 16×2 LCD (4-bit Mode)
- **Communication:**
  - UART0 – Serial Debugging
  - UART1 – ESP-01 Wi-Fi Module
  - I²C – MAX30102 Sensor
- **Alert Devices:**
  - Green LED
  - Red LED
  - Buzzer
- **Power Supply:** +5V Regulated DC

---

# ⚙️ Hardware Configuration

The **IoT Patient Health Monitoring and Emergency Alert System** is developed using the **LPC2129 ARM7TDMI-S Microcontroller** as the central processing unit. The system continuously acquires patient vital parameters, processes the sensor data in real time, displays the measured values on a 16×2 LCD, provides visual and audible alerts during abnormal health conditions, and transmits the patient data to the cloud through the ESP-01 Wi-Fi module for remote monitoring.

---

## 📌 LPC2129 Pin Mapping

| Device / Module | LPC2129 Pin | Description |
| :-------------- | :---------: | :---------- |
| **UART0 (Serial Terminal)** | `P0.0 (TXD0)` / `P0.1 (RXD0)` | PC Communication & Debugging |
| **MAX30102 Heart Rate & SpO₂ Sensor** | `P0.2 (SCL)` / `P0.3 (SDA)` | I²C Communication |
| **DHT11 Temperature Sensor** | `P0.4` | Digital Temperature Sensor |
| **ESP-01 Wi-Fi Module (UART1)** | `P0.8 (RXD1)` / `P0.9 (TXD1)` | IoT Cloud Communication |
| **Green LED** | `P0.17` | Indicates Normal Patient Condition |
| **Red LED** | `P0.18` | Indicates Critical Patient Condition |
| **Buzzer** | `P0.21` | Emergency Alert |
| **16×2 LCD Display** | `P1.17 – P1.23` | 4-bit LCD Interface |

---

## 🌐 Communication Protocols & Interfaces

| Protocol | Connected Device | Purpose |
| :-------- | :--------------- | :------ |
| **GPIO** | DHT11, Green LED, Red LED, Buzzer | Digital Input/Output and Alert Control |
| **I²C** | MAX30102 Sensor | Heart Rate & SpO₂ Data Communication |
| **UART0** | PC / Serial Terminal | Debugging and Monitoring |
| **UART1** | ESP-01 Wi-Fi Module | Wireless IoT Communication |
| **LCD Interface** | 16×2 LCD | Real-Time Display of Patient Parameters |

---

## 🩺 Hardware Components

| Category | Components |
| :-------- | :--------- |
| **Microcontroller** | LPC2129 ARM7TDMI-S |
| **Health Monitoring Sensors** | MAX30102 (Heart Rate & SpO₂), DHT11 |
| **Communication Module** | ESP-01 Wi-Fi Module |
| **Display Unit** | 16×2 LCD |
| **Alert System** | Green LED, Red LED, Buzzer |
| **Power Supply** | +5V Regulated DC Supply |

---

## 📡 System Interfacing Diagram

```text
                         +----------------------+
                         |   +5V Power Supply   |
                         +----------+-----------+
                                    |
                                    |
                     +--------------v--------------+
                     |      LPC2129 ARM7TDMI-S     |
                     |      Microcontroller        |
                     +--------------+--------------+
                                    |
    ---------------------------------------------------------------------
    |             |              |             |          |              |
 UART0         UART1          I²C Bus       GPIO      GPIO          GPIO
    |             |              |             |          |              |
    |             |              |             |          |              |
 Serial        ESP-01       MAX30102       DHT11    Green LED      Red LED
Terminal       Wi-Fi      Heart Rate &   Temperature   Status        Alert
(Debug)                     SpO₂ Sensor

                                    |
                              +-----+-----+
                              |  Buzzer   |
                              | Emergency |
                              |   Alert   |
                              +-----+-----+
                                    |
                          +---------+---------+
                          |    16×2 LCD       |
                          |  (P1.17–P1.23)    |
                          +-------------------+
```

---

## 📋 System Summary

- **Microcontroller:** LPC2129 ARM7TDMI-S
- **Health Sensors:** MAX30102 (Heart Rate & SpO₂), DHT11
- **Communication:** UART0, UART1, I²C
- **Wireless Module:** ESP-01 Wi-Fi
- **Display:** 16×2 LCD
- **Alert Devices:** Green LED, Red LED, Buzzer
- **Power Supply:** +5V DC Regulated

---

> **Note:** The LPC2129 communicates with the MAX30102 sensor through the **I²C protocol**, interfaces with the ESP-01 Wi-Fi module using **UART1**, utilizes **UART0** for debugging through a serial terminal, displays real-time patient health information on a **16×2 LCD**, and controls the **Green LED**, **Red LED**, and **Buzzer** through GPIO pins to provide immediate visual and audible alerts whenever abnormal health conditions are detected.

---

# 🧩 Software Architecture & Module Mapping

| Module | File Name | Purpose |
|---------|-----------|----------|
| Delay | `delay.c` | Timer-based delay functions |
| UART0 | `uart0_driver.c` | Serial debugging |
| UART1 | `uart1_driver.c` | ESP-01 communication |
| I²C | `i2c_driver.c` | MAX30102 communication |
| MAX30102 | `max30102.c` / `max30102.h` | Sensor driver |
| Filter | `filter.c` / `filter.h` | DC Removal & Moving Average Filtering |
| Heart Rate | `heartrate.c` / `heartrate.h` | BPM Calculation |
| SpO₂ | `spo2.c` / `spo2.h` | Oxygen Saturation Calculation |
| DHT11 | `dht11_driver.c` | Temperature Acquisition |
| LCD | `lcd_driver.c` | LCD Interface |
| ESP-01 | `esp01_driver.c` | Wi-Fi & ThingSpeak Communication |
| Main | `main.c` | Main Application Logic |

---

# 📉 Signal Processing Chain

1. Read raw IR samples from the MAX30102 FIFO.
2. Apply a **DC Removal Filter**.
3. Smooth the signal using an **8-Point Moving Average Filter**.
4. Detect waveform peaks to calculate Heart Rate (40–180 BPM).
5. Estimate SpO₂ using:

**SpO₂ = 110 − (25 × R)**

---

# 🚨 Alarm Conditions & Thresholds

| Parameter | Threshold |
|-----------|-----------|
| Temperature | > 38°C |
| Heart Rate | < 60 BPM or > 120 BPM |
| SpO₂ | < 95% |

### Alert Behavior

- ✅ Green LED ON → Normal Condition
- 🔴 Red LED + Buzzer ON → Abnormal Condition
- LCD displays warning messages during emergency situations.

---

# ☁️ Cloud Integration

- Automatically uploads temperature, heart rate, and SpO₂ values to **ThingSpeak** every 20 seconds.
- Communication is performed through **UART1** using AT commands with the **ESP-01 Wi-Fi module**.
- Enables remote patient monitoring through an IoT dashboard.

---

# ▶️ How to Run

1. Open the project in **Keil µVision**.
2. Select the **LPC2129** target device.
3. Build the project to generate the HEX file.
4. Flash the HEX using **Flash Magic**.
5. Connect all sensors, LCD, LEDs, Buzzer, and the ESP-01 module.
6. Power the development board.
7. Observe live sensor readings on the LCD and ThingSpeak dashboard.

---

# 📁 Repository Structure

```text
IoT-Patient-Health-Monitoring-and-Emergency-Alert-System/
├── src/
│   ├── *.c                 # Embedded C source files
│   ├── *.h                 # Header files
│   └── main.c              # Main application
│
├── docs and schematics/
│   ├── IoT_Patient_Health_Monitoring_Report.pdf
│   └── Working_Diagram.jpg
│
├── images/
│   ├── Project_Op_Img.jpg
│   ├── Video_Project.mp4
│   └── THINKSPEAK_OUTPUT.jpg
│
└── README.md               # Project documentation
```

---

# 👨‍💻 Author

**Jayakumar Murugesh**
