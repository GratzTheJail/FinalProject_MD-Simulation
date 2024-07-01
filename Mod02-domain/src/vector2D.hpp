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



#ifndef vector2D_hpp
#define vector2D_hpp

#include "math.h"
#include <iostream>

// Forward declaration of class
class vector2D;

// Forward declartion of multiplication of scalar 
vector2D operator*(const double& s, const vector2D& v);

double mag(const vector2D& v);

//------------------------------------------------------------------------------
//                          Class Definition
//------------------------------------------------------------------------------

class vector2D
{
    private:
        double x_{0};
        double y_{0};
        
    public:
    
    // Constructor    
        // Default constructor 
        vector2D() = default;
    
        // Construction with elements
        vector2D(const double x, const double y)
        : x_(x),y_(y)
        {}
        
    // Access
    
        // Const reference access 
        const double& x() const {return x_;}
        const double& y() const {return y_;}

        // Non-const reference access
        double& x() {return x_;}
        double& y() {return y_;}
    
    
    // Operators
        vector2D& operator+=(const vector2D& p2)
        {
            this->x() += p2.x();
            this->y() += p2.y();
            return *this;
        }
        
        vector2D& operator-=(const vector2D& p2)
        {
            this->x() -= p2.x();
            this->y() -= p2.y();
            return *this;
        }

        vector2D& operator/=(const double s)
        {
            this->x() = x_/s;
            this->y() = y_/s;
            return *this;
        }

        vector2D operator+(const vector2D& p2) const
        {
            // The result of p1+p2
            vector2D p1p2 = *this;
            p1p2.x() += p2.x();
            p1p2.y() += p2.y();
            return p1p2;
        }
        
        vector2D operator-(const vector2D& p2) const
        {
            // The result of p1+p2
            vector2D p1p2 = *this;
            p1p2.x() -= p2.x();
            p1p2.y() -= p2.y();
            return p1p2;
        }
        
        // Division by scalar
        vector2D operator/(const double s) const
        {
            vector2D p1 = *this;
            p1.x() /= s;
            p1.y() /= s;
            return p1;
        }        
        
        // Multiplication by scalar
        vector2D operator*(const double s) const
        {
            vector2D p1 = *this;
            p1.x() *= s;
            p1.y() *= s;
            return p1;
        }
        
        // Scalar product
        double operator&(const vector2D& p2) const
        {
            return x_*p2.x() + y_*p2.y(); 
        }
};

#endif
