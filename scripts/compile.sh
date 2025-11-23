#!/bin/bash

# BFLA-01KP Compilation Script for Linux/Mac
# Compiles the BFLA_01KP.cpp source code

echo "Compiling BFLA_01KP..."

# Compile with optimization
g++ -O2 -o BFLA_01KP ../src/BFLA_01KP.cpp -lm

# Check if compilation was successful
if [ $? -eq 0 ]; then
    echo "Compilation successful! Executable: BFLA_01KP"
    echo "Run with: ./BFLA_01KP"
else
    echo "Compilation failed!"
    exit 1
fi

