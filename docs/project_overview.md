# Project Overview — Mic Jammer

## Summary
The **Mic Jammer** is a compact research prototype designed to generate ultrasonic interference (approx. 24–26 kHz) to reduce the effectiveness of nearby digital microphones. The project explores signal generation, amplification, and real-world testing of ultrasonic jamming using widely available modules (AD9833, TPA3116D2) and an Arduino Nano controller.

## Goals
- Produce a randomized ultrasonic carrier (24–26 kHz) that is hard to filter.
- Provide modular hardware and readable firmware for research and testing.
- Create clear documentation and reproducible build steps for evaluation.

## Core Components
- Arduino Nano (ATmega328P)
- AD9833 DDS signal generator
- TPA3116D2 audio amplifier
- IRF4115 MOSFET (power switching)
- Ultrasonic transducers (multiple units)
- 12V Li-Ion battery pack (power source)

## Status (current)
- Firmware: working (sweep 24–26 kHz)  
- Schematic: completed (EasyEDA + visual)  
- PCB: planned (not yet laid out)  
- Testing: limited prototype tests; more formal tests pending

## Intended Audience
Engineers, hobbyists, and researchers interested in acoustic signal generation and microphone robustness testing.

## Ethical Notice
This project is intended for research and testing. Do not use it to interfere with lawful communications, public safety devices, or to violate privacy laws.
