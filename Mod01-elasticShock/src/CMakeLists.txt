# =============================================================================
#                  Introduction to C++ for Engineering                         
#                                                                              
# Elastic shock between round particles                                        
#                                                                              
# CMake file to compile the program and all tests with Catch2
#                                                                              
# =============================================================================
# Author
#   Jan Wilhelm Gärtner <jan.gaertner@outlook.de> Copyright (C) 2020
#
# =============================================================================

file(GLOB_RECURSE _HDRS "*.hpp")

add_library(particleCollision SHARED
    vector2D.cpp
    functions.cpp
    particle.cpp
    ${_HDRS}
)

target_include_directories(particleCollision PUBLIC .)