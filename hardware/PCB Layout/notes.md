# Design Notes — Mic Jammer PCB

## Layout Plan
- Place amplifier (TPA3116D2) near transducer connectors.
- Keep AD9833 close to Arduino for SPI signal integrity.
- Separate power and signal ground planes if needed.
- Use thick traces for power (12V rail).

## Pending Tasks
- Choose connector type for battery input.
- Estimate board size (initial target: 10x10 cm).
- Verify AD9833 output level compatibility with amplifier input.
