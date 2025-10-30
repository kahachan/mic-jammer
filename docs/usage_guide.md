# Usage Guide

## Before powering on
- Verify wiring and connectors.
- Confirm battery is charged and voltage is within safe range.
- Ensure test area is clear and no sensitive equipment is nearby.

## Basic operation
1. Connect Li-Ion battery (12V) to the power input.
2. Connect USB to Arduino only if you need serial debugging.
3. Device boots and runs the sweep automatically (firmware default).
4. To stop: disconnect battery or implement a hardware switch.

## Modes (if implemented in firmware)
- **Auto sweep**: default randomized 24–26 kHz sweep.
- **Static tone**: fixed frequency (change in firmware or via serial/controls).
- **Standby**: amplifier disabled, MCU running.

## Recommended test procedure
- Start at low amplifier gain.
- Use a microphone + spectrum analyzer or audio interface to observe the ultrasonic band.
- Increase gain gradually while monitoring temperature and distortion.

## Troubleshooting
- **No signal detected**: check AD9833 clock and FSYNC; use oscilloscope at AD9833 AOUT.
- **Weak / no audible effect on target mic**: ensure transducer placement and orientation; check amplifier gain.
- **Amplifier overheating**: reduce duty cycle, add heatsink, check speaker load.

## Maintenance
- Inspect transducer leads for wear.
- Periodically check solder joints and battery health.
