#!/bin/bash

#cmake CMakeLists.txt
make
if [ $? -eq 0 ]; then
  ./runTests
fi
