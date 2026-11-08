# Tidal Buoy Sensor Kit

Deployment firmware, carrier hardware and calibration data for the tidal buoy
sensor kit.

The logger sleeps between sample windows and wakes on a timer interrupt. The
sensor carrier holds the conductivity, temperature and pressure front ends; the
logger board adds the solar charger and the LiFePO4 protection circuit.

## Contents

- `firmware/buoy_logger.ino` — sampling schedule and SD card writer
- `hardware/sensor_carrier.kicad_pcb` — carrier board layout
- `data/calibration.csv` — tank calibration coefficients per unit
- `docs/deployment.md` — mooring and recovery procedure
- `LICENSE` — hardware licence
