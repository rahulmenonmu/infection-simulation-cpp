# Infection Simulaiton
Program in C++ to simulate disease infection in a grid taking into account factors such as Infection rate, mortality rate, recovery rate, quarantine etc.


## Overview

The simulation consists of a YxX grid (termed as the map) in which the representations ( termed as characters) , exist and are permitted to roam freely. Figure 1 shows the simulation for a grid size of 13x17 (Y refers to number of rows and is always presented first, X refers to number of columns). Henceforth we refer to the size as YxX, such that Figure 1 is considered a map of size 13x17.


There are different types of characters:

- H representing healthy individuals before they have been infected
- I representing infected characters
- R representing recovered characters

There are two main types of terrain. Empty terrain is represented using a blank space, “ “, and blocked terrain using a hash, #. Another terrain type, E, representing exits is required for Section 8 only. Characters cannot move out of the map or move over blocked terrain or each other.

The simulation is turn based. At every step of the simulation some of the characters move around the map, ending up in one of the cells that are north, south, east and west of their current location, or not moving at all. The rate of movement is dictated by a movement parameter (MP).

Most of the characters will roam around the environment using a random walk. At initialisation, characters are placed on the map randomly. The number and type of character varies and will be specified during the appropriate part of the assignment. The I characters can infect the H (and Y) characters depending on a simulation probability infection rate (IR) that is variable but fixed for a given simulation. Infections can occur if an I moves towards an H (and Y). Is also have a chance of recovering at any turn, based on a recovery rate (RR). A recovered I becomes an R. Rs continue to operate like Is but cannot be infected again. The Is also have a chance of becoming deceased (or a fatality) based on a mortality rate (MR). A deceased I is removed from the simulation. In summary the variables that directly affect the characters in the simulation are:

- Infection Rate (IR): the rate at which an I can infect an H if the H lies to the north, south, east or west of the I

- Recovery Rate (RR): the rate at which an I can recover to become an H

- Mortality Rate (MR): the rate at which Is become deceased

- Movement Parameter (MP): dictates probability of movement for random walk.

IR, RR and MR represent probabilities and are between 0 and 1. MP is slightly different and will be explained in Section 3. The simulation will, for the most part, run until there are no longer any more infected. The number of remaining healthy, infected, recovered and deceased needs to be maintained. For most of the simulations that are required to be run, the required outcome from the simulation will be the number of deceased characters/fatalities.

![Simulation display](Simulation%20display.png?raw=true "Simulation display")
