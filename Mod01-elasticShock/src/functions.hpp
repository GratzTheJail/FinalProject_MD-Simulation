/******************************************************************************\
|                  Introduction to C++ for Engineering                         |
|                                                                              |
| Functions to calculate possible collision and elastic shock                  |
|                                                                              |
\******************************************************************************/

#ifndef PARTICLE_FUNCTIONS
#define PARTICLE_FUNCTIONS

#include "particle.hpp"
#include <vector>

void evolveParticles
(
    std::vector<particle>& particles,
    const double minDeltaT,
    const double maxDeltaT
);


#endif