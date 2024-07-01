/******************************************************************************\
|                  Introduction to C++ for Engineering                         |
|                                                                              |
| Elastic shock between round particles                                        |
|                                                                              |
| Class: particle                                                              |
|        This file contains the implementation of non-inline particle          |
|        member functions.                                                     |
|                                                                              |
\******************************************************************************/


#include "particle.hpp"


// Construct particle from components
particle::particle
(
    const double x,
    const double y,
    const double ux,
    const double uy,
    const double r,
    const double m,
    const int color
)
{
    // ==> ToDo <==
}


void particle::move(const double deltaT)
{
    // ==> ToDo <==
}


void particle::update(const double deltaT)
{
    // ==> ToDo <==
}


void particle::collisionForce(const particle& p,const double& deltaT)
{
    // ==> ToDo <==
}


double particle::timeToCollision(const particle& p) const
{
    // Calculate the time to collision according to:
    // Smallenburg, F. Efficient event-driven simulations of hard spheres. 
    // Eur. Phys. J. E 45, 22 (2022). 
    // https://doi.org/10.1140/epje/s10189-022-00180-8

    // ==> ToDo <==
    
    // Return of -1 is a dummy! This has to be modified
    return -1;
}

