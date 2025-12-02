#!/bin/bash

if [[ "$1" == "-clean" ]]; then
    rm -rf build
    echo "Cleaned."
    exit 0
fi

mkdir -p build
clang++ -std=c++17 -O2 -MJ build/main.o.json -o build/main src/main.cpp
echo "[" > build/compile_commands.json
sed 's/,$//' build/main.o.json >> build/compile_commands.json
echo "]" >> build/compile_commands.json
rm build/main.o.json
./build/main
