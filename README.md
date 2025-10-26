# 🎙️ Mic Jammer Prototype

This repository contains the design, firmware, and documentation for a **Microphone Jammer Device**, developed as an internal research & development prototype at **Optimasi AI**.  
The device generates controlled ultrasonic / wideband noise signals to study how such signals affect nearby microphone performance.

---

## 📘 Project Overview

The **Mic Jammer** is a prototype aimed to explore ultrasonic and broadband acoustic interference against nearby microphones (phone mics, voice recorders, etc.).  
This project focuses on **hardware design**, **firmware control**, and **signal testing** for the jammer unit.

**Key Objectives:**
- Design a compact, low-power microphone jammer circuit.
- Implement adjustable signal generation (frequency & amplitude).
- Measure effective jamming range and frequency response.
- Document limitations and safe-use considerations.

---

## ⚙️ Features

- Microcontroller-based control (Arduino Nano / ATmega328P)
- AD9833-based signal generator for precise waveforms
- TPA3116D2 audio amplifier as output driver stage
- MOSFET switching (IRF4115) for power drive
- Ultrasonic transducer as acoustic emitter
- Configurable frequency and output level for testing

---

## 🧩 Project Structure

