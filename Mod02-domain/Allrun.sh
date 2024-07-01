#!/bin/bash

PROJECT_DIR=$(pwd)

set -e

echo "=== Start Allrun ==="
echo " "

echo "==============================================================================="
echo "    1. Compiling the C++ Source code"
echo "==============================================================================="
[[ ! -d build ]] && mkdir build
cd build
cmake ..
make > log.build

set +e

cd ${PROJECT_DIR}

echo "==============================================================================="
echo "    2. Execute Program"
echo "==============================================================================="

if [[ ! -d "data" ]]; then
    mkdir data
fi

if [[ -e "data/particlePos.dat" ]]; then
    echo  "Delete old data/particlePos.dat"
    rm data/particlePos.dat
fi

# Check the current input which tests should be run
if [[ ${#} == 0 ]]; then
    cp build/tests/src/tests particleTests.exe 
    echo "Following tests are available:"
    ./particleTests.exe --list-tests
    echo "Please select one of the test cases with:"
    echo "./Allrun nameOfTestCase"
    exit 0
else
    cp build/tests/src/tests particleTests.exe 
    if [[ ${1} == "all" ]]; then
        ./particleTests.exe
    else
        ./particleTests.exe ${@}
    fi
fi 


if [[ -e "data/particlePos.dat" ]]; then
    echo "==============================================================================="
    echo "    3. Plot Results"
    echo "==============================================================================="
    if [[ $1 == "particleHitWallTest" ]]; then
        cd PlotScript && rm -r PNG/ && mkdir PNG && ./plotResults.py -o '-0.5,-0.5' -d '1.0,2.0'
    elif [[ $1 == "particleDiffusionLargeTest" ]]; then
        cd PlotScript && rm -r PNG/ && mkdir PNG && ./plotResults.py -o '-0.5,-0.5' -d '2.0,5.0' 
    else
        cd PlotScript && rm -r PNG/ && mkdir PNG && ./plotResults.py  -o '0,0' -d '1.0,2.0' 
    fi
    cd ${PROJECT_DIR}/PlotScript/PNG && ffmpeg -y -r 20 -i plotcircles-%05d.png -c:v libx264 -profile:v high444 -level:v 4.0 -codec:a aac -pix_fmt yuv420p -crf 18 -an  video.mp4
    echo "==============================================================================="
    echo "==> You find the results in PlotScript/PNG/ folder"
    echo "==============================================================================="
fi
echo "=== DONE ==="



