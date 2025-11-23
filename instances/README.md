# Instance Files

This directory contains the test instances for the 0-1 Knapsack Problem.

## Setup

1. Extract the `Instance_01KP_36.zip` file to this directory
2. The extracted folder should be named `Instance_01KP_36/`
3. The final structure should be:
   ```
   instances/
   └── Instance_01KP_36/
       ├── ikp132.txt
       ├── ikp133.txt
       ├── ...
       └── ikp136.txt
   ```

## Instance File Format

Each instance file follows this format:

```
<unused_integer> <unused_integer>
<knapsack_capacity>
<price_1> <weight_1>
<price_2> <weight_2>
...
<price_n> <weight_n>
```

Where:
- First line: Two unused integers (typically zeros)
- Second line: Maximum capacity of the knapsack
- Remaining lines: Price and weight pairs for each item

## Usage

To use a specific instance, modify the `filename1` variable in `src/BFLA_01KP.cpp`:

```cpp
char filename1[] = "../instances/Instance_01KP_36/<instance_name>.txt";
```

Replace `<instance_name>` with the desired instance file name (e.g., `ikp132`, `ikp133`, etc.).

## Instance List

The 36 instances include:
- **ikp132** to **ikp136**: Different problem configurations
- Each instance has dimension 1000 (1000 items)

For the complete list and details, refer to the instance files after extraction.

