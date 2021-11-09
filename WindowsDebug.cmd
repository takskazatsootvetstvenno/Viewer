cd ..
if exist build rmdir /s /q build
if exist install rmdir /s /q install
mkdir build
conan install Viewer -if build --build missing -s build_type=Debug
cd build
cmake ../Viewer -G "Visual Studio 16 2019" -A x64 -DCMAKE_BUILD_TYPE=Debug
cmake --build . --config Debug
cmake --install .