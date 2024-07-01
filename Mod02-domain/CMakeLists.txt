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

# Set minimum required cmake version
cmake_minimum_required (VERSION 3.10)

# Enforce C++ 14 standard
# C++ 14 is required for blaze
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(particleCollisionTest
  VERSION 1.0
  LANGUAGES CXX
  DESCRIPTION "ICE Mod01: Particle Class"
)

add_subdirectory(src)
add_subdirectory(tests)