#!/bin/bash

# Create folder
mkdir -p build/win-package/package

# Copy files
cp -r src build/win-package/package &
cp CMakeLists.txt build/win-package/package/ &
cp .gitignore build/win-package/package/ &
cp -r .git build/win-package/package/ &

wait

cd build/win-package
zip -r C21-TP3-SIMON.zip package
cd ../..
