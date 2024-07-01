#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <iostream>
#include "cloud.hpp"
#include <fstream>
#include <string>
#include <vector>


TEST_CASE("particleDiffusionTest")
{
    // Create a domain
    double width = 1.0;
    double height = 2.0;

    vector2D origin(0,0);

    rectDomain domain(width,height,origin);

    // Create an empty cloud
    cloud particleCloud(domain);

    // domain particle 1
    rectDomain domainP1(width,height*0.5,origin);
    // Initialize with 10 particles
    particleCloud.init
    (
        domainP1,
        10,
        1.0,
        0.05,
        1.0,
        1
    );

    // domain particle 2
    rectDomain domainP2(width,height*0.5,origin+vector2D(0,height*0.5));

    // Initialize with 10 particles
    particleCloud.init
    (
        domainP2,
        10,
        1.0,
        0.05,
        1.0,
        2
    );

    // Calculate total kinetic energy
    double kinEnergy = 0;
    for (auto& p : particleCloud.particles())
        kinEnergy += 0.5*p.m()*std::pow(mag(p.vel()),2);

    // Create a file to write out particle positions for each time 
    std::ofstream file("data/particlePos.dat");

    // Set file deliminator
    // This makes it easier to change to file format from a tabulated
    // to a comma separated file
    std::string DLM("\t");
    
    file << "# Time, P1x,P1y,Radius1,Color1,P2x,P2y,Radius2,Color2\n";

    const double minDeltaT = 1E-9;
    const double maxDeltaT = 1e-4;
    const double startTime = 0;
    const double endTime = 3;

    double deltaT = minDeltaT;

    for (double time=startTime; time <= endTime; time+=deltaT)
    {
        file << time;
        for (const particle& p : particleCloud.particles())
            file << DLM << p.pos().x() << DLM << p.pos().y()
                 << DLM << p.r() << DLM << p.color();
        file << std::endl;

        deltaT = particleCloud.evolve(minDeltaT,maxDeltaT);

        // Check after each iteration that the kinetic energy is conserved
        double kinEnergyNew = 0;
        for (auto& p : particleCloud.particles())
            kinEnergyNew += 0.5*p.m()*std::pow(mag(p.vel()),2);

        INFO("Kinetic energy is not conserved for time "<<time);
        REQUIRE_THAT(kinEnergy, Catch::Matchers::WithinAbs(kinEnergyNew,1E-6));
    } 

    // Check that none of the particles is outside the box
    int nParticleOutside = 0;
    for (auto& p : particleCloud.particles())
    {
        if (!domain.inside(p))
            nParticleOutside++;
    }
    INFO(nParticleOutside <<" particles are outside of the domain!");
    REQUIRE(nParticleOutside == 0);
}