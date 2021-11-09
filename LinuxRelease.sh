#!/bin/bash
sudo pip install conan
sudo apt-get -y install cmake
sudo apt-get install libgl1-mesa-dev

cd ..
rm -r build
rm -r install
mkdir build
conan install Viewer -if build --build missing -s build_type=Release
cd build
cmake ../Viewer -G "Unix Makefiles" -A x64 -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release
cmake --install .
