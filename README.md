# CPPS_Table
Command SW for the CPPS Tables (Pedagogic Seismic Simulation Tables)

## Dependencies

To developp software for this project,
* Download arduino IDE 1.5.3
* Install Bounce lib
* Install Metro lib

## Setup

The software is divided in two parts using #ifdef to generate the software for the following simulations :
* House simulation / Liquefaction
* Rod (Resonance static frequencies)

To choose which version you want to generate, open the userConfiguration.h file and comment the define 
* define CFG_HouseBuilder           // Table for creating a house

and uncomment the following define

* define CFG_RodShaking             // 4 Rods with static frequency
