
# Enforce C++ 14 standard
# C++ 14 is required for blaze
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# These tests can use the Catch2-provided main
add_executable(tests 
    wallTest.cpp
    rectDomainTest.cpp
    cloudClassTest.cpp
    particleDiffusionTest.cpp
    particleDiffusionLargeTest.cpp
    particleHitWallTest.cpp
    particleClassTest.cpp
)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain particleCollision)

target_include_directories(tests PUBLIC particleCollision)


