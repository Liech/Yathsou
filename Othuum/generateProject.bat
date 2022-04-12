mkdir out
cd out
cmake ./../CMakeLists.txt -G "Visual Studio 17 2022" -DCMAKE_TOOLCHAIN_FILE="./../vcpkg/scripts/buildsystems/vcpkg.cmake"
