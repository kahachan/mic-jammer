# How It Works

## Overview
The Mic Jammer creates an ultrasonic carrier signal and modulates it in a randomized sweep pattern so that microphones in the vicinity receive a rapidly changing high-frequency signal that can disrupt capture or cause signal processing algorithms to fail.

## Signal Chain
1. **Control (Arduino Nano)**
   - Initializes the AD9833 using SPI.
   - Executes the sweep algorithm and timing.
   - (Optionally) controls amplifier enable and status indicators.

2. **Signal Generation (AD9833)**
   - Produces a precise waveform (square, triangle, or sine).
   - Frequency register updated to perform the sweep between 24 kHz and 26 kHz.
   - Uses a 25 MHz reference clock (check module).

3. **Amplification (TPA3116D2)**
   - Receives AD9833 output and amplifies to drive multiple transducers.
   - Requires 12V power and proper grounding/decoupling.

4. **Output Stage (Transducers + MOSFET)**
   - Transducers convert amplified electrical signal into ultrasonic pressure waves.
   - MOSFET(s) such as IRF4115 may be used for switching or power handling.

## Sweep & Randomization
- The firmware steps the frequency up and down across the 24–26 kHz band using a pseudo-random step table to make the spectral pattern less predictable.
- Randomized stepping reduces the effectiveness of narrowband filtering or fixed notch algorithms.

## Important Notes on Compatibility
- Many MEMS and small electret mics have limited response above 20 kHz, but aliasing or ADC front-end behavior in devices may still be disrupted by ultrasonic energy.
- Always verify AD9833 reference clock and module wiring; wrong clock value produces incorrect output frequencies.

## Safety & Signal Levels
- High sound pressure levels at ultrasonic frequencies can damage transducers and possibly be harmful in certain circumstances—see `safety_notice.md` before testing.
