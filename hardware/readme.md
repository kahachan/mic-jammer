# Hardware Design — Mic Jammer Project

This folder contains the hardware design files for the **Mic Jammer** project developed by **Ardian Fikri Abdulah** at **Optimasi AI**.

---

## 📘 Overview
The hardware system is designed to generate and amplify ultrasonic signals (around 24–26 kHz) to interfere with nearby microphones.  
It uses an **AD9833 signal generator**, an **audio amplifier (TPA3116D2)**, and a **high-power transducer** as the main components.

---

## ⚙️ Components
| No | Component | Description |
|----|------------|-------------|
| 1 | **Arduino Nano (ATmega328P)** | Controls AD9833 frequency and sweep timing |
| 2 | **AD9833 Signal Generator Module** | Generates ultrasonic sine wave |
| 3 | **TPA3116D2 Audio Amplifier** | Boosts signal to drive transducer |
| 4 | **IRF4115 MOSFET** | Used for power stage / signal switching |
| 5 | **Ultrasonic Transducer** | Emits high-frequency sound waves |
| 6 | **Power Supply (12V DC)** | Main supply for amplifier and system |

---

## 🧩 Hardware Connection Diagram

---

## 📐 Pin Mapping (Arduino → AD9833)
| Arduino Pin | AD9833 Pin | Function |
|--------------|-------------|----------|
| D13 | SCLK | Serial Clock |
| D11 | SDATA | Serial Data |
| D10 | FSYNC | Chip Select (CS) |
| 5V | VCC | Power |
| GND | GND | Ground |

---

## 🧠 Design Notes
- The **signal flow** starts from AD9833 generating a sine wave, which is then **amplified** by TPA3116D2.  
- The **IRF4115** MOSFET is used to handle **high-current switching** between amplifier output and transducer.  
- Make sure the **ground** between all modules is shared properly to avoid noise or unstable operation.
- Use short and thick wires for **power and ground lines** to minimize losses.

---

## 🧾 Files in this folder
| File | Description |
|------|--------------|
| `schematic.pdf` | Schematic circuit of the complete system |
| `pcb_layout.png` | PCB layout preview |
| `BOM.xlsx` | Bill of Materials for all components |

---

## 🧰 Future Work
- Upload schematic and PCB layout files once design is finalized  
- Add test result photos or oscilloscope screenshots  
- Document PCB dimensions and layer stack-up

---

© 2025 Ardian Fikri Abdulah — Optimasi AI  
