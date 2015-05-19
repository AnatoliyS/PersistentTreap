#!/bin/bash

echo -e "compiling...\n"
g++ cartesian.cpp Treap.cpp VersionList.cpp VersionTreap.cpp PersistentTreap.cpp -o cartesian

if [ $? -eq 0 ]; then
  echo -e "running\n"
  ./cartesian
else
   echo -e "Error in compilation\n"
fi


echo -e "Tests..\n"
cd Test && ./build.sh && cd ..
