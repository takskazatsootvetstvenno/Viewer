cd ..
if exist build rmdir /s /q build
mkdir build
conan install Viewer -if build --build missing --profile msvc16
cd build
cmake ../Viewer -G "Visual Studio 16 2019" -A x64
cmake --build . --config Release
