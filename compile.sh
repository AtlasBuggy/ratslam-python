#!/bin/sh

cd build
cmake ..
make
cp pyratslam.so ../pyratslam
cd ..
