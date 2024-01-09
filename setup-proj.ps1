# script to build and open output project with personal profile functions
cmake-clean
conan install . --build=missing
quiet-rm .\build\CMakeCache.txt
quiet-rm .\build\CMakeFiles\ -r
cmake --preset conan-default
cd build
cmake --build . --config Release
cmake --open .
