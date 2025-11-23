#!/bin/bash

# BFLA-01KP Batch Experiment Script
# Runs the algorithm on multiple instances

echo "BFLA-01KP Batch Experiment Script"
echo "=================================="
echo ""

# Check if executable exists
if [ ! -f "./BFLA_01KP" ]; then
    echo "Error: BFLA_01KP executable not found!"
    echo "Please compile the code first using compile.sh"
    exit 1
fi

# Create output directories if they don't exist
mkdir -p ../results/convergence
mkdir -p ../results/statistics

# List of instances to run
# Modify this list according to your instance files
INSTANCES=(
    "ikp132"
    "ikp133"
    "ikp134"
    # Add more instance names here
)

echo "Running experiments on ${#INSTANCES[@]} instances..."
echo ""

# Run experiments
for instance in "${INSTANCES[@]}"; do
    echo "Processing instance: $instance"
    
    # Note: You need to modify the instance name in BFLA_01KP.cpp
    # or pass it as a parameter if you modify the code to accept command-line arguments
    
    ./BFLA_01KP
    
    if [ $? -eq 0 ]; then
        echo "  ✓ Completed: $instance"
    else
        echo "  ✗ Failed: $instance"
    fi
    echo ""
done

echo "All experiments completed!"
echo "Results are saved in ../results/"

