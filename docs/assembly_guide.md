# Assembly Guide

> Minimal step-by-step instructions for assembling the Mic Jammer prototype. Follow safety notes and ensure power is disconnected while wiring.

## Required tools
- Soldering iron and solder
- Wire cutters/strippers
- Screwdriver (for terminal blocks)
- Multimeter
- Heat shrink / insulation tape

## BOM & Parts check
1. Verify you have all components listed in `/hardware/bom/mic_jammer_bom.xlsx`.
2. Check footprints / orientation for polarized parts (diodes, electrolytic capacitors, MOSFET).

## Mechanical layout
- If using a protoboard or perfboard: place Arduino Nano where USB access is convenient.
- Keep amplifier module close to the transducer connectors.
- Place the battery connector at the board edge for easy access.

## Wiring steps
1. **Power rails**
   - Connect Li-Ion pack (12V) to amplifier V+ and system main power input.
   - Ensure common ground between Arduino (5V system) and amplifier ground (12V system) if communication references are used.

2. **AD9833 ↔ Arduino**
   - MOSI (D11) → AD9833 SDATA
   - SCK  (D13) → AD9833 SCLK
   - FSYNC (D10) → AD9833 FSYNC (CS)

3. **AD9833 output → Amplifier**
   - AD9833 AOUT → Amplifier input (L/R as appropriate)
   - AD9833 GND → Amplifier audio GND

4. **Amplifier → Transducers**
   - Connect amplifier outputs to transducer array.
   - Use proper wiring and consider series resistors or attenuation if amplifier output is high.

5. **Optional: MOSFET / Switch Control**
   - Wire IRF4115 gate to a control pin if you want software-controlled amplifier gating.
   - Provide proper gate resistor and pull-down to avoid accidental switching.

## First power-up (safe procedure)
1. Remove transducers or keep output disconnected.
2. Power only the Arduino (via USB) and verify AD9833 initialization (use Serial debug if available).
3. Power amplifier supply (12V) without connecting transducers; measure input/output levels with oscilloscope or audio probe at low gain.
4. Only connect transducers after verifying signals and at low volume.

## Troubleshooting common assembly issues
- No output: check module Vcc and GND, verify FSYNC, MOSI, SCK wiring.
- Distorted output: ensure amplifier supply stable and decoupling caps present.
- Overheating MOSFET: check wiring, load, and consider heatsinking or different MOSFET.

## Final notes
- Secure loose wiring and avoid long unshielded signal wires.
- Document any deviations from BOM in `/hardware/bom/notes` for future reference.
