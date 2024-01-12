# script to build and open output project with personal profile functions
function quiet-remove($item) {
    if (Test-Path $item) {
        rm -r -force $item
        echo "Removed $item "
    } else {
        echo "$item does not exist"
    }
}
echo "Building in $args configuration"

quiet-remove CMakeUserPresets.json
quiet-remove ./build/*
conan install . --build=missing --profile=$args
quiet-remove .\build\CMakeCache.txt
quiet-remove .\build\CMakeFiles\ -r
cmake --preset conan-default
cd build
cmake --build . --config $args
cmake --open .
cd ..
