# Mic Jammer – Project Overview

The **Mic Jammer** is a compact ultrasonic interference device designed to reduce the effectiveness of digital microphones (especially MEMS microphones commonly found in smartphones, smart speakers, and laptops).  
This project uses an **AD9833 signal generator**, amplified using a **TPA3116D2 audio amplifier**, and transmitted through multiple ultrasonic transducers to generate a sweeping ultrasonic signal that disrupts nearby microphones.

---

## 🎯 Project Goals

- Generate a **24 kHz – 26 kHz ultrasonic carrier** to interfere with microphone recordings
- Implement **randomized frequency sweeping** to prevent filtering or noise-cancellation bypass
- Create a **portable and low-cost** jammer powered by a 12V Li-ion battery
- Provide modular and open-source firmware, hardware, and documentation

---

## 🧩 System Architecture (Simple Explanation)

The system works in a chain of 4 blocks:

| Block | Component | Function |
|-------|------------|------------|
| Signal Generator | AD9833 | Generates ultrasonic frequency |
| Microcontroller | Arduino Nano | Controls frequency sweeping and mode |
| Amplification | TPA3116D2 Amplifier + MOSFET | Boosts ultrasonic signal for transmission |
| Output Stage | 12 Ultrasonic Transducers | Emit ultrasonic beam to jam microphones |

---

## ⚙️ Core Features

- ✅ **Ultrasonic Square Wave Output (24–26 kHz)**  
- 🔀 **Randomized sweeping algorithm** to avoid static tones  
- 🔌 **Operates from 12V Li-ion battery**  
- 📡 Supports multiple transducers for stronger jamming field  
- 🧱 Modular structure:
  - `/firmware` – Arduino source code  
  - `/hardware` – Schematics, BOM, and PCB files  
  - `/docs` – Project documentation (this folder)  
  - `/simulation` – Testing and analysis  

---

## 📦 Repository Structure (Quick Look)


---

## 🚀 Status

| Stage | Status |
|--------|------------|
| Firmware | ✅ Working |
| Hardware Schematic | ✅ Completed |
| PCB Design | ⏳ Planned |
| Testing & Docs | 🔄 In Progress |

---

## 🧠 Requirements to Understand This Project

This project is suitable for:

- Electronics hobbyists with basic Arduino knowledge  
- Students doing research on ultrasonic interference or acoustic security  
- Makers who want to build a portable microphone jammer  

Recommended background:

- Basic Arduino programming  
- Basic electronics (MOSFET, amplifier, power supply)  
- Understanding of SPI communication helps but not required  

---
