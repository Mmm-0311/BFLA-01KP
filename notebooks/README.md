# Jupyter Notebooks for BFLA-01KP Analysis

This directory contains Jupyter notebooks for analyzing experimental results and visualizing algorithm performance.

## Notebooks Description

1. **Convergence_curve_of_six_instances_in_NP_equal_20_30_40.ipynb**
   - Generates convergence curves for six instances
   - Analyzes performance with different population sizes (NP = 20, 30, 40)

2. **Sensitivity_analysis_of_parameter_A_on_six_instances.ipynb**
   - Performs sensitivity analysis on parameter A
   - Tests algorithm performance with different values of parameter A

3. **Friedman_rank_test_of_8_algorithms_for_solving_36_01KP_instances.ipynb**
   - Statistical comparison using Friedman rank test
   - Compares 8 different algorithms on 36 instances

4. **Friedman_rank_test_of_9_algorithms_for_solving_36_01KP_instances.ipynb**
   - Extended statistical comparison
   - Compares 9 different algorithms on 36 instances

5. **AS_of_Five_algorithms_for_solving_36_01KP_instances.ipynb**
   - Algorithm performance comparison
   - Visualizes results for 5 algorithms

## Requirements

Install the required Python packages:

```bash
pip install jupyter numpy matplotlib pandas scipy
```

## Usage

1. Ensure you have run the experiments and generated results files
2. Update file paths in the notebooks to point to your result files
3. Launch Jupyter:
   ```bash
   jupyter notebook
   ```
4. Open and run the desired notebook

## Note on File Paths

The notebooks may contain hardcoded file paths. Before running:

1. Update the paths to point to your actual result files
2. Ensure the result files are in the correct format
3. Adjust paths according to your directory structure

For example, if results are in `../results/`, update paths accordingly:
```python
# Example path update
results_path = '../results/statistics/BMS.txt'
convergence_path = '../results/convergence/'
```

## Data Format

The notebooks expect data in the following formats:

- **Statistics files**: Results from `BMS.txt` (Best, Worst, Mean, Rate, Std, Time)
- **Convergence files**: Results from convergence files with format:
  ```
  run1 <fitness_1> <fitness_2> ... <fitness_MAXITERA>
  run2 <fitness_1> <fitness_2> ... <fitness_MAXITERA>
  ...
  ```

## Output

The notebooks generate:
- Statistical analysis tables
- Convergence curves
- Performance comparison charts
- Sensitivity analysis plots

Outputs are typically saved in the same directory or a specified output directory.

