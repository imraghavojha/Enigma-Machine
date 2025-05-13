#!/bin/bash
echo "Testing Enigma Machine build..."

# Clean and rebuild
rm -rf build
mkdir build
cd build

echo "Configuring..."
if ! cmake ..; then
    echo "CMake configuration failed!"
    exit 1
fi

echo "Building..."
if ! make; then
    echo "Build failed!"
    exit 1
fi

echo "Build successful! Running tests..."
if ! ctest; then
    echo "Tests failed!"
    exit 1
fi

echo "All tests passed! Running main program..."
echo "5" | ./enigma

echo "Build and test completed successfully!"