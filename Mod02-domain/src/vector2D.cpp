/******************************************************************************\
|                  Introduction to C++ for Engineering                         |
|                                                                              |
| Elastic shock between round particles                                        |
|                                                                              |
| Class: vector2D                                                              |
|        A 2D vector with access and vector operations                         |
|                                                                              |
| Functions:                                                                   |
|     The vector class comes with some additional functions                    |
|     - mag(const vector2D&) Calculates the vector magnitude             |
|     - Vector-scalar multiplication: v*s or s*v where v is a vector and s is  |
|       a scalar                                                               |
|     - Vector-scalar division: v/s where v is a vector and s is  a scalar     |
|     - Scalar product of two vectors: s= v & v; which returns the scalar s    |
|                                                                              |
\******************************************************************************/

#include "vector2D.hpp"




// Calculate the magnitude of a vector
double mag(const vector2D& p)
{
    return std::sqrt(p.x()*p.x() + p.y()*p.y());
}

vector2D operator*(const double& s, const vector2D& v)
{
    return v*s;
}

