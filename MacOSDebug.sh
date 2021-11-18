#!/bin/bash
sudo pip install conan
brew  -y install cmake
brew  install libgl1-mesa-dev
brew  install libglu1-mesa-dev

cd ..
rm -r build
rm -r install
mkdir build
conan install Viewer -if build --build missing -s build_type=Debug -r conancenter
cd build
cmake ../Viewer -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug
cmake --build . --config Debug
cmake --install .
