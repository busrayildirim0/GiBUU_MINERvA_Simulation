# Neutrino-Nucleus Interaction Simulation (CC/NC) with GIbUU

A configurable simulation of **Charged Current (CC)** and **Neutral Current (NC)** neutrino-nucleus interactions using GIbUU.  
- **Flux**: MINERvA 2016 (`MINERvA_MEflux.dat`)  
- **Cross-section model**: Experimental data-driven (`EXP_dSigmaMC`, mode 16)  
- **Processes**: QE, Δ-Resonance, DIS, 2p2h, 1π, 2π included  

## Key Parameters
| Parameter          | Description                          | CC Example | NC Example |
|--------------------|--------------------------------------|------------|------------|
| `process_ID`       | Interaction type (2=CC, 3=NC)       | 2          | 3          |
| `nuXsectionMode`   | Cross-section model (16=EXP_dSigmaMC)| 16         | 16         |
| `nuExp`            | Flux choice (25=MINERvA 2016)       | 25         | 25         |
| `FileNameFlux`     | Flux file                           | `MINERvA_MEflux.dat` | Same |
| **Included processes** | QE, RES, DIS, 2p2h, etc.       | `T` (True) | `T` (True) |
 
