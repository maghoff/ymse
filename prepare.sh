#!/bin/bash

PACKAGES="build-essential cmake libsdl-dev libsdl-image1.2-dev libglut-dev libboost-dev"
CMAKE_PARAMS="-C../GCCSetup.cmake"
BUILD_TYPES="debug release"


# Not sure what to do with OpenGL
#sudo apt-get install libgl-dev


if ! dpkg -l $PACKAGES >/dev/null
then
    echo "Will install packages: $PACKAGES"
    sudo apt-get install $PACKAGES
fi

for x in $BUILD_TYPES
do
    mkdir -p "$x"

    pushd "$x"
    cmake $CMAKE_PARAMS "-DCMAKE_BUILD_TYPE=$x" ..
    popd
done


export YMSE_PATH=`pwd`
echo "export YMSE_PATH=$YMSE_PATH" >> ~/.profile

echo
echo "export YMSE_PATH=$YMSE_PATH"

