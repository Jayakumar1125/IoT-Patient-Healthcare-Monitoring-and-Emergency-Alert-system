# IoT Patient Health Monitoring and Emergency Alert System

<div align="center">

[![ARM7 LPC21xx](https://img.shields.io/badge/Microcontroller-LPC21xx%20ARM7-blue.svg)](https://en.wikipedia.org/wiki/ARM7)
[![Embedded C](https://img.shields.io/badge/Language-Embedded%20C-orange.svg)](https://en.wikipedia.org/wiki/Embedded_C)
[![IoT Cloud](https://img.shields.io/badge/Cloud-ThingSpeak-brightgreen.svg)](https://thingspeak.com/)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

An advanced, real-time embedded IoT healthcare system designed to continuously monitor vital physiological parameters, perform automated onboard evaluation, trigger local safety alarms, and stream health telemetry to the cloud for remote clinical oversight[cite: 19].

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
9. [Getting Started & Installation](#-getting-started--installation)
10. [Author](#-author)

---

## 🎯 Project Overview

In modern healthcare environments, continuous manual observation of every patient is practically impossible due to high patient-to-staff ratios[cite: 19]. Sudden physiological shifts—such as spikes in body temperature, cardiac arrhythmias, or oxygen desaturation—can rapidly escalate into life-threatening emergencies if undetected[cite: 19]. 

This project solves this challenge by deploying an intelligent embedded assistant built around the **LPC21xx ARM7 Microcontroller**[cite: 19]. It continuously reads body temperature via a DHT11 sensor and heart rate/blood oxygen saturation ($SpO_2$) via a MAX30102 sensor[cite: 19]. It evaluates thresholds locally to trigger immediate local warnings (LCD, LEDs, Buzzer) and leverages an **ESP-01 Wi-Fi module** to stream real-time data onto the **ThingSpeak IoT Cloud**[cite: 19].

---

## ✨ Key Features

* **Continuous Multi-Parameter Monitoring:** Tracks body temperature, heart rate (BPM), and blood oxygen saturation ($SpO_2$) simultaneously[cite: 19].
* **Autonomous Embedded Decision-Making:** Compares incoming telemetry against predefined clinical thresholds in real time without human intervention[cite: 19].
* **Dual-Tier Alert Mechanism:**
  * **Local Alerts:** Activates a buzzer, toggles warning LEDs, and updates warning notifications on a 16x2 LCD display[cite: 13, 19].
  * **Remote Cloud Alerts:** Automatically transmits emergency telemetry packages over Wi-Fi to a cloud dashboard[cite: 8, 13, 19].
* **IoT Cloud Telemetry (ThingSpeak):** Logs continuous medical data into distinct channels for historical review and trend analysis[cite: 8, 13, 19].

---

## ⚙️ Hardware Specifications

* **MCU:** LPC21xx (ARM7TDMI)[cite: 19]
* **Sensors:** 
  * MAX30102 (Heart Rate / $SpO_2$, I²C interface)
  * DHT11 (Temperature, GPIO interface)
* **Display:** 16x2 LCD (configured in 4-bit mode)[cite: 12]
* **Connectivity:** ESP-01 WiFi module (interfaced via UART1)[cite: 8]
* **Alarms & Indicators:** 
  * Green LED (`P0.17`) — Normal Status[cite: 13]
  * Red LED (`P0.18`) — Alert Status[cite: 13]
  * Buzzer (`P0.21`) — Audible Alarm[cite: 13]
* **Debugging:** UART0 (9600 baud)[cite: 17]

---

## 🧩 Software Architecture & Module Mapping

| Module | File Name | Core Function |
| :--- | :--- | :--- |
| **Delay** | `delay.c` | Timer0-based ms/us/sec delays[cite: 6] |
| **UART0** | `uart0_driver.c` | Debug serial communication[cite: 17] |
| **UART1** | `uart1_driver.c` | ESP-01 communication interface[cite: 18] |
| **I²C** | `i2c_driver.c` | MAX30102 register access protocol[cite: 11] |
| **MAX30102** | `max30102.c` / `max30102.h` | Heart rate & SpO₂ sensor driver |
| **Filter** | `filter.c` / `filter.h` | DC removal + 8-point moving average[cite: 9] |
| **Heart Rate** | `heartrate.c` / `heartrate.h` | Peak detection & BPM calculation[cite: 10] |
| **SpO₂** | `spo2.c` / `spo2.h` | AC/DC ratio SpO₂ estimation[cite: 15] |
| **DHT11** | `dht11_driver.c` | Temperature data acquisition[cite: 7] |
| **LCD** | `lcd_driver.c` | 16x2 display driver[cite: 12] |
| **ESP-01** | `esp01_driver.c` | Wi-Fi configuration + ThingSpeak HTTP upload[cite: 8] |
| **Main Application** | `main.c` | Application logic & control loop execution[cite: 13] |

---

## 📉 Signal Processing Chain

1. Raw IR samples are ingested from the MAX30102 FIFO buffer[cite: 14].
2. A **DC removal filter** (`DC_Remove`) isolates the AC pulsatile component[cite: 9].
3. An **8-point moving average filter** (`Moving_Average`) smooths out high-frequency noise[cite: 9].
4. **Peak detection** processes the waveform to calculate BPM within a valid 40–180 range[cite: 10].
5. Red and IR AC-DC ratios are computed to estimate SpO₂ using the formula: $SpO_2 = 110 - 25 \times R$[cite: 15].

---

## 🚨 Alarm Conditions & Thresholds

The system evaluates conditions continuously and triggers alerts based on the following safety rules[cite: 13]:
* **Temperature:** $> 38^\circ\text{C}$[cite: 13]
* **Heart Rate:** $< 60$ or $> 120$ BPM[cite: 13]
* **SpO₂ Level:** $< 95\%$[cite: 13]
* **Indication Behavior:** Abnormal conditions trigger the **Red LED + Buzzer**, while safe parameters maintain the **Green LED**[cite: 13].

---

## ☁️ Cloud Integration

* Automatically uploads temperature, heart rate, and SpO₂ telemetry to **ThingSpeak** every 20 seconds.
* Communication is handled via AT commands sent through **UART1** to the **ESP-01** module[cite: 8].

---

## ▶️ How to Run

1. Open the project in **Keil µVision**.
2. Select the LPC21xx target configuration.
3. Build the project to generate the HEX file.
4. Flash the HEX using **Flash Magic**.
5. Connect the sensors and ESP-01 module.
6. Power the board.
7. Observe live readings on the LCD and ThingSpeak dashboard.

---


## 📁 Repository Structure

```text
IoT-Patient-Healthcare-Monitoring-and-Emergency-Alert-system/
├── src/                   # Embedded C source code files (.c and .h)
├── docs and schematics/   # Complete project documentation, design PDFs, and system block diagrams
├── images/                # Hardware photos and ThingSpeak telemetry charts
└── README.md              # Project description and documentation
```
---
## 👨‍💻 Author

<div align="center">
### **Jayakumar Murugesh**
</div>
