# BFLA-01KP: Binary Flow Learning Algorithm for 0-1 Knapsack Problem

This repository contains the implementation of the Binary Flow Learning Algorithm (BFLA) for solving the 0-1 Knapsack Problem (01KP), along with experimental scripts and analysis notebooks.

## Repository Structure

```
BFLA_01KP/
├── src/                           # Source code
│   └── BFLA_01KP.cpp             # Main algorithm implementation
├── instances/                     # Problem instances
│   └── Instance_01KP_36/         # 36 test instances (extract from Instance_01KP_36.zip)
├── notebooks/                     # Jupyter notebooks for analysis
│   ├── Convergence_curve_of_six_instances_in_NP_equal_20_30_40.ipynb
│   ├── Sensitivity_analysis_of_parameter_A_on_six_instances.ipynb
│   ├── Friedman_rank_test_of_8_algorithms_for_solving_36_01KP_instances.ipynb
│   ├── Friedman_rank_test_of_9_algorithms_for_solving_36_01KP_instances.ipynb
│   └── AS_of_Five_algorithms_for_solving_36_01KP_instances.ipynb
├── scripts/                       # Compilation and execution scripts
│   ├── compile.sh                # Linux/Mac compilation script
│   ├── compile.bat               # Windows compilation script
│   └── run_experiment.sh         # Batch experiment script
└── results/                       # Output directory
    ├── convergence/              # Convergence curve data
    └── statistics/               # Statistical results
```

## Algorithm Overview

BFLA is a population-based metaheuristic algorithm designed specifically for binary optimization problems, particularly the 0-1 Knapsack Problem. The algorithm employs a flow learning mechanism with three operational phases:

1. **Diffusion Operation (DO)**: Applied when `tf < 0.9`
2. **Equilibrium Operation (EO)**: Applied when `0.9 <= tf < 1.0`
3. **Steady-State Operation (SSO)**: Applied when `tf >= 1.0`

where `tf = sinh(t / MAXITERA)` is the transformation factor that evolves with iteration `t`.

## Parameter Settings

The algorithm parameters are defined as constants in `src/BFLA_01KP.cpp`:

### Algorithm Parameters
- `DIMENSION`: Problem dimension (default: 1000)
- `POPSIZE`: Population size (default: 20)
- `MAXITERA`: Maximum iterations (default: 200)
- `RUNS`: Number of independent runs (default: 10)

### Search Space
- `lb`: Lower bound for continuous variables (default: -5)
- `ub`: Upper bound for continuous variables (default: 5)

### Algorithm-Specific Parameters
- `D`: Distance parameter (default: 0.01)
- `C1`: Control parameter 1 (default: 1)
- `C2`: Control parameter 2 (default: 2)
- `C3`: Transfer parameter lower bound (default: 0.1)
- `C4`: Transfer parameter upper bound (default: 0.2)
- `C5`: Transformation parameter (default: 2)
- `A`: Logarithmic function parameter (default: 5.0)
- `Pm`: Mutation probability (default: 0.003)

### Transfer Functions

The code includes 16 transfer functions for converting continuous values to binary:
- **S-shaped**: `s_shaped_1`, `s_shaped_2`, `s_shaped_3`, `s_shaped_4`
- **V-shaped**: `v_shaped_1`, `v_shaped_2`, `v_shaped_3`, `v_shaped_4`
- **U-shaped**: `u_shaped_1`, `u_shaped_2`, `u_shaped_3`, `u_shaped_4`
- **T-shaped**: `t_shaped_1`, `t_shaped_2`, `t_shaped_3`, `t_shaped_4`

Currently, the algorithm uses `lf_1(decimal, 3)` for binary conversion, which implements:
```
y = log_3((2/(2A)) * x + (4/2))
```

## Compilation

### Windows

Using the provided batch script:
```bash
cd scripts
compile.bat
```

Or manually:
```bash
g++ -O2 -o BFLA_01KP.exe ../src/BFLA_01KP.cpp -lm
```

### Linux/Mac

Using the provided shell script:
```bash
cd scripts
chmod +x compile.sh
./compile.sh
```

Or manually:
```bash
g++ -O2 -o BFLA_01KP ../src/BFLA_01KP.cpp -lm
```

**Requirements:**
- C++ compiler with C++11 support (g++, clang++, or MSVC)
- Standard math library (`-lm` flag for GCC)

## Usage

### Preparing Instance Files

1. Extract `Instance_01KP_36.zip` to the `instances/` directory
2. The instance file format should be:
   ```
   <unused> <unused>
   <capacity>
   <price_1> <weight_1>
   <price_2> <weight_2>
   ...
   <price_n> <weight_n>
   ```

### Running the Algorithm

#### Single Execution

From the project root directory:

**Windows:**
```bash
cd scripts
BFLA_01KP.exe
```

**Linux/Mac:**
```bash
cd scripts
./BFLA_01KP
```

#### Batch Execution

Use the provided script to run experiments on multiple instances:
```bash
cd scripts
chmod +x run_experiment.sh
./run_experiment.sh
```

**Note:** Before running, modify the instance filename in `src/BFLA_01KP.cpp`:
```cpp
char filename1[] = "../instances/Instance_01KP_36/<instance_name>.txt";
```

### Output Files

The algorithm generates two output files:

1. **`results/statistics/BMS.txt`**: Contains statistical summary for each run:
   - `Best`: Best fitness value found
   - `Worst`: Worst fitness value found
   - `Mean`: Mean fitness value
   - `Rate`: Success rate (percentage of runs achieving best value)
   - `Std`: Standard deviation
   - `Time`: Average execution time per run (seconds)

2. **`results/convergence/cvg_np30_ikp132.txt`**: Contains convergence data:
   - Format: `run1 <fitness_iter1> <fitness_iter2> ... <fitness_iterMAXITERA>`
   - One line per run, showing fitness evolution

**Important:** Ensure the output directories exist:
```bash
mkdir -p results/convergence results/statistics
```

## Modifying Parameters

To modify algorithm parameters, edit the `#define` statements in `src/BFLA_01KP.cpp`:

```cpp
#define POPSIZE 20        // Change population size
#define MAXITERA 200      // Change maximum iterations
#define RUNS 10           // Change number of runs
#define A 5.0             // Change parameter A
// ... etc
```

After modifying parameters, recompile the code.

## Experiment Analysis

The Jupyter notebooks in the `notebooks/` directory provide:

1. **Convergence Analysis**: Convergence curves for different population sizes
2. **Sensitivity Analysis**: Parameter sensitivity analysis for parameter A
3. **Statistical Tests**: Friedman rank test comparing multiple algorithms
4. **Performance Comparison**: Algorithm performance comparison visualizations

To use the notebooks:

1. Install required Python packages:
   ```bash
   pip install jupyter numpy matplotlib pandas scipy
   ```

2. Update file paths in the notebooks to match your setup

3. Run the notebooks:
   ```bash
   jupyter notebook notebooks/
   ```

## File Format Details

### Instance File Format

Each instance file contains:
- Line 1: Two unused integers
- Line 2: Knapsack capacity
- Lines 3 to 3+DIMENSION-1: Price and weight pairs (one per line)

Example:
```
0 0
1000
100 50
200 30
...
```

### Output File Format

**BMS.txt format:**
```
Best:12345    Worst:12300.000000   Mean:12320.500000    Rate:80.000000    Std:15.231000    Time:2.345000
```

**Convergence file format:**
```
run1 1000 1200 1300 ... 12345
run2 1000 1210 1320 ... 12340
...
run10 1000 1190 1310 ... 12350
```

## Citation

If you use this code in your research, please cite:

```
[Please add your citation information here]
```

## License

[Please specify your license here, e.g., MIT, GPL, etc.]

## Contact

[Please add contact information]

## Troubleshooting

### Common Issues

1. **File not found error**: 
   - Ensure instance files are extracted to `instances/Instance_01KP_36/`
   - Check the file path in `src/BFLA_01KP.cpp`

2. **Permission denied (Linux/Mac)**:
   - Make scripts executable: `chmod +x scripts/*.sh`

3. **Compilation errors**:
   - Ensure you have a C++ compiler installed
   - For Windows, use MinGW or MSVC
   - For Linux, install build-essential: `sudo apt-get install build-essential`

4. **Output directory errors**:
   - Create output directories manually if they don't exist:
     ```bash
     mkdir -p results/convergence results/statistics
     ```

## Version History

- **v1.0**: Initial release with complete BFLA implementation

