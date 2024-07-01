#!/bin/bash

set -e

PROJECT_DIR=$(pwd)

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

echo "==============================================================================="
echo "    2. Execute Program"
echo "==============================================================================="

cd ${PROJECT_DIR}

if [[ ! -d "data" ]]; then
    mkdir data
fi

if [[ -e "data/particlePos.dat" ]]; then
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
    
    cd PlotScript && rm -r PNG/ && mkdir PNG && python3 plotResults.py  

    cd ${PROJECT_DIR}/PlotScript/PNG && ffmpeg -y -r 20 -i plotcircles-%05d.png -c:v libx264 -profile:v high444 -level:v 4.0 -codec:a aac -pix_fmt yuv420p -crf 18 -an  video.mp4
    echo "==============================================================================="
    echo "==> You find the results in PlotScript/PNG/ folder"
    echo "==============================================================================="
fi
echo "=== DONE ==="



