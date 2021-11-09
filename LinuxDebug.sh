#!/bin/bash
sudo pip install conan
sudo apt-get -y install cmake
sudo apt-get install libgl1-mesa-dev
sudo apt-get install libglu1-mesa-dev

cd ..
rm -r build
rm -r install
mkdir build
conan install Viewer -if build --build missing -s build_type=Debug
cd build
cmake ../Viewer -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug
cmake --build . --config Debug
cmake --install .
