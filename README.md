# 1. Generate build files using CMake
cmake -S . -B build

# 2. Build the project
cmake --build build

# 3. Run the executable
# On Linux/macOS:
./build/bitpawn

# On Windows:
./build/bitpawn.exe
