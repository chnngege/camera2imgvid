#!/bin/bash
mkdir -p build
cd build
cmake ../
make
cd bin
./camera2imgvid
