#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <iostream>
#include "particle.hpp"
#include "functions.hpp"
#include <fstream>
#include <string>
#include <vector>


TEST_CASE("particleClass")
{ 
    // Create a particle
    const vector2D pos(1.0,2.0);
    const vector2D vel(0.5,0.2);
    const double m = 0.2;
    const double r = 0.1;
    const int color = 1;

    particle p(pos.x(),pos.y(),vel.x(),vel.y(),r,m,color);

    // Check that all values are set correctly 
    std::cout << "Check that private member variables are set..."<<std::endl;
    REQUIRE(p.r() == r);
    REQUIRE(p.m() == m);
    REQUIRE(p.color() == color);
    REQUIRE(p.vel().x() == vel.x());
    REQUIRE(p.vel().y() == vel.y());
    REQUIRE(p.pos().x() == pos.x());
    REQUIRE(p.pos().y() == pos.y());

    // Check the move function
    std::cout << "Check move function..."<<std::endl;
    p.move(1.0);
    REQUIRE(p.pos().x() == pos.x() + vel.x());
    REQUIRE(p.pos().y() == pos.y() + vel.y());
    REQUIRE(p.vel().x() == vel.x());
    REQUIRE(p.vel().y() == vel.y());

    std::cout << "Check time to collision..."<<std::endl;
    // Create a new particle that is moved in the direction of the 
    // other particle and negative velocity

    // To calculate the position we need to account for the radius of the 
    // particles

    double alpha = std::atan(vel.y()/vel.x());


    particle p2
    (
        p.pos().x()+2.0*p.vel().x()+2.0*r*std::cos(alpha),
        p.pos().y()+2.0*p.vel().y()+2.0*r*std::sin(alpha),
        -1.0*p.vel().x(),-1.0*p.vel().y(),
        r,m,color
    );

    REQUIRE_THAT(p.timeToCollision(p2),Catch::Matchers::WithinAbs(1.0,1E-9));
}