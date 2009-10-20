#!/bin/bash

sudo apt-get install build-essential cmake libsdl-dev libglut-dev libboost-dev

# Not sure what to do with OpenGL
#sudo apt-get install libgl-dev

cmake .

export YMSE_PATH=`pwd`
echo "export YMSE_PATH=$YMSE_PATH" >> ~/.profile
