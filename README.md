<div align="center">
<h1>IoT Patient Health Monitoring and Emergency Alert System</h1>

An advanced, real-time embedded IoT healthcare system designed to continuously monitor vital physiological parameters, perform automated onboard evaluation, trigger local safety alarms, and stream health telemetry to the cloud for remote clinical oversight.

</div>

---

## 📋 Table of Contents

1. [Project Overview](#-project-overview)
2. [Key Features](#-key-features)
3. [Hardware Specifications](#-hardware-specifications)
4. [Software Architecture & Module Mapping](#-software-architecture--module-mapping)
5. [Signal Processing Chain](#-signal-processing-chain)
6. [Alarm Conditions & Thresholds](#-alarm-conditions--thresholds)
7. [Cloud Integration](#-cloud-integration)
8. [Repository Structure](#-repository-structure)
9. [How to Run](#-how-to-run)
10. [Author](#-author)

---

# 🎯 Project Overview

In modern healthcare environments, continuous manual observation of every patient is practically impossible due to high patient-to-staff ratios. Sudden physiological shifts—such as spikes in body temperature, cardiac arrhythmias, or oxygen desaturation—can rapidly escalate into life-threatening emergencies if undetected.

This project solves this challenge by deploying an intelligent embedded assistant built around the **LPC21xx ARM7 Microcontroller**. It continuously reads body temperature via a **DHT11** sensor and heart rate/blood oxygen saturation (**SpO₂**) via a **MAX30102** sensor. It evaluates thresholds locally to trigger immediate local warnings (LCD, LEDs, Buzzer) and leverages an **ESP-01 Wi-Fi module** to stream real-time data onto the **ThingSpeak IoT Cloud**.

---

# ✨ Key Features

- **Continuous Multi-Parameter Monitoring:** Tracks body temperature, heart rate (BPM), and blood oxygen saturation (SpO₂) simultaneously.
- **Autonomous Embedded Decision-Making:** Compares incoming telemetry against predefined clinical thresholds in real time without human intervention.
- **Dual-Tier Alert Mechanism:**
  - **Local Alerts:** Activates a buzzer, toggles warning LEDs, and updates warning notifications on a 16×2 LCD display.
  - **Remote Cloud Alerts:** Automatically transmits emergency telemetry packages over Wi-Fi to a cloud dashboard.
- **IoT Cloud Telemetry (ThingSpeak):** Logs continuous medical data into distinct channels for historical review and trend analysis.

---

# ⚙️ Hardware Specifications

- **Microcontroller:** LPC21xx (ARM7TDMI)
- **Sensors:**
  - MAX30102 (Heart Rate / SpO₂, I²C Interface)
  - DHT11 (Temperature Sensor)
- **Display:** 16×2 LCD (4-bit Mode)
- **Connectivity:** ESP-01 Wi-Fi Module (UART1)
- **Status Indicators:**
  - Green LED (`P0.17`) – Normal Status
  - Red LED (`P0.18`) – Alert Status
  - Buzzer (`P0.21`) – Audible Alarm
- **Debug Interface:** UART0 (9600 Baud)

---

# 🧩 Software Architecture & Module Mapping

| Module | File Name | Purpose |
|---------|-----------|----------|
| Delay | `delay.c` | Timer-based delay functions |
| UART0 | `uart0_driver.c` | Serial debugging |
| UART1 | `uart1_driver.c` | ESP-01 communication |
| I²C | `i2c_driver.c` | MAX30102 communication |
| MAX30102 | `max30102.c` / `max30102.h` | Sensor driver |
| Filter | `filter.c` / `filter.h` | DC removal & Moving Average filtering |
| Heart Rate | `heartrate.c` / `heartrate.h` | BPM calculation |
| SpO₂ | `spo2.c` / `spo2.h` | Oxygen saturation calculation |
| DHT11 | `dht11_driver.c` | Temperature acquisition |
| LCD | `lcd_driver.c` | LCD interface |
| ESP-01 | `esp01_driver.c` | Wi-Fi & ThingSpeak communication |
| Main | `main.c` | Main application logic |

---

# 📉 Signal Processing Chain

1. Read raw IR samples from the MAX30102 FIFO.
2. Apply **DC Removal Filter**.
3. Smooth the signal using an **8-Point Moving Average Filter**.
4. Detect waveform peaks to calculate Heart Rate (40–180 BPM).
5. Estimate SpO₂ using the ratio of Red and IR signals:

**SpO₂ = 110 − (25 × R)**

---

# 🚨 Alarm Conditions & Thresholds

The system continuously evaluates sensor readings using predefined safety thresholds.

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

* Automatically uploads temperature, heart rate, and SpO₂ telemetry to **ThingSpeak** every 20 seconds.
* Communication is handled via AT commands sent through **UART1** to the **ESP-01** module.

---

# ▶️ How to Run

1. Open the project in **Keil µVision**.
2. Select the LPC21xx target.
3. Build the project to generate the HEX file.
4. Flash the HEX using **Flash Magic**.
5. Connect all sensors and the ESP-01 module.
6. Power the board.
7. Observe live readings on the LCD and the ThingSpeak dashboard.

---

# 📁 Repository Structure

```text IoT-Patient-Healthcare-Monitoring-and-Emergency-Alert-system/
├── src/                 # Embedded C source code files (.c and .h)
├── docs and schematics/ # Complete project documentation, design PDFs, and system block diagrams
├── images/              # Hardware photos and ThingSpeak telemetry charts
└── README.md            # Project description and documentation
```

---

# 👨‍💻 Author

<div align="center">

## **Jayakumar Murugesh**

</div>
