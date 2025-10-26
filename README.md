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


---

## 🧾 Main Components

- **Microcontroller:** Arduino Nano (ATmega328P)  
- **Signal generator:** AD9833 (DDS)  
- **Audio amplifier / driver:** TPA3116D2  
- **Power MOSFET:** IRF4115  
- **Acoustic output:** Ultrasonic transducer

See `hardware/BOM.csv` for detailed part numbers and quantities.

---

## ⚠️ Status & Notes

- **Current status:** Prototype firmware and schematic available. **PCB layout:** Pending (in development).  
- Keep repository up-to-date as PCB and test results are finalized.  
- Add shielding, grounding, and decoupling capacitors carefully during PCB design to reduce unwanted noise and improve stability.

---

## 🛠️ How to build & run (basic)

1. Prepare hardware according to schematic (`hardware/schematic.pdf`) and BOM.
2. Flash firmware on Arduino Nano (`firmware/`) using Arduino IDE or PlatformIO.
3. Power amplifier stage (TPA3116D2) from an appropriate power supply following its datasheet.
4. Start with low amplitude / short-range tests, measure acoustic output and verify safety.

> See `docs/testing_protocol.md` for recommended test steps (add this file once tests are documented).

---

## 📄 License

This project is licensed under the **MIT License**. See `LICENSE` for details.

---

## 👤 Author & Contact

**Ardian Fikri Abdulah**  
Optimasi AI — Research & Development  
GitHub: [@ardianfikri](https://github.com/kahachan)  
Email: `ardyprmbn7@gmail.com` 

---

## 🔜 Next steps (recommended)

- Finalize PCB footprints & create `hardware/pcb/README_PCB.md`
- Perform DRC and generate Gerbers
- Add `docs/testing_results.pdf` with measurement data (SPL vs distance, frequency response)
- Consider adding a `CHANGELOG.md` and branch `pcb-dev` for PCB work
