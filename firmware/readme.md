# Firmware - Mic Jammer Project

## Overview
This firmware controls the **AD9833 Signal Generator** using an **Arduino Nano (ATmega328P)** to produce an ultrasonic signal in the range of **24 kHz – 26 kHz**.  
The signal is amplified by a **TPA3116D2 audio amplifier** and transmitted through an **ultrasonic transducer**, creating a jamming effect that interferes with nearby microphones.

---

## Features
- SPI communication with the AD9833 module.  
- Generates **square wave** at ultrasonic frequencies.  
- Performs **frequency sweeping** between 24–26 kHz using a randomized pattern.  
- Configurable waveform modes: **SINE**, **SQUARE**, or **TRIANGLE**.  
- Well-structured and easy-to-modify firmware.

---

## Hardware Connection

### AD9833 ↔ Arduino Nano
| AD9833 Pin | Arduino Nano Pin | Description |
|-------------|------------------|-------------|
| VCC         | 5V               | Power supply |
| GND         | GND              | Common ground |
| FDATA       | D11 (MOSI)       | SPI data line |
| SCLK        | D13 (SCK)        | SPI clock line |
| FSYNC       | D10              | Chip Select (can be changed) |

### AD9833 ↔ TPA3116D2
| AD9833 Pin | Amplifier Pin | Description |
|-------------|----------------|-------------|
| AOUT        | L-IN / R-IN    | Audio input |
| AGND        | AUDIO GND      | Ground connection |

### Power Supply
| Component | Voltage |
|------------|----------|
| Arduino Nano | 5V |
| AD9833 | 5V |
| TPA3116D2 | 12V |
| IRF4115 + Transducer | Follows amplifier supply |

---

## How to Use
1. Open **Arduino IDE**.  
2. Select **Arduino Nano (ATmega328P)** as the target board.  
3. Connect the hardware according to the pin table above.  
4. Upload `main.ino` to your Arduino Nano.  
5. Once uploaded, the jammer will automatically generate and sweep the ultrasonic frequency between 24 kHz and 26 kHz continuously.

---

## Notes
- To change waveform mode, modify this line in `setup()`:
  ```cpp
  ad9833_set_mode(AD_SQUARE);
