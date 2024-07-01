/******************************************************************************\
|                  Introduction to C++ for Engineering                         |
|                                                                              |
| Elastic shock between round particles                                        |
|                                                                              |
| Class: particle                                                              |
|        Stores all information of the particle and checks for collision       |
|                                                                              |
\******************************************************************************/

#ifndef particle_hpp
#define particle_hpp

#include "vector2D.hpp"
#include <iostream>


class particle
{
    private:
        // position in space
        vector2D pos_;
        
        // current velocity
        // ==> ToDo <==
        
        // Forces on the particle
        // ==> ToDo <==

        // particle radius
        double r_;
        
        // particle mass
        // ==> ToDo <==

        // particle color
        // Here we use an integer to distinguish the color
        // ==> ToDo <==

    
    public:
    
    // Constructor
        
        // Constructor with position and velocity as vector components
        particle
        (
            const double x,
            const double y,
            const double ux,
            const double uy,
            const double r,
            const double m,
            const int color
        );
        
    // Access Functions

        // Get the position of the particle
        inline const vector2D& pos() const {return pos_;}
        
        
    // Change particle state

        // Move the particle with the given velocity and a given time step
        void move(const double deltaT);

        // Update velocities after calculating all forces
        void update(const double deltaT);

    // Collision Handling

        // Check if this particle would collide with particle p
        // if so calculate the new collision force
        void collisionForce(const particle& p, const double& deltaT);

        // Calculate time to collision with another particle 
        // assuming they move in straight lines
        double timeToCollision(const particle& p) const;
};



#endif
