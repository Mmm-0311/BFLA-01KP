# Setup Guide

This guide will help you set up and run the BFLA-01KP algorithm.

## Quick Start

### 1. Extract Instance Files

Extract the instance files to the correct location:

**Windows (PowerShell):**
```powershell
cd instances
Expand-Archive -Path Instance_01KP_36.zip -DestinationPath .
```

**Linux/Mac:**
```bash
cd instances
unzip Instance_01KP_36.zip
```

After extraction, you should have:
```
instances/
└── Instance_01KP_36/
    ├── ikp132.txt
    ├── ikp133.txt
    └── ... (other instance files)
```

### 2. Configure Instance File

Edit `src/BFLA_01KP.cpp` and set the instance file path:

```cpp
char filename1[] = "../instances/Instance_01KP_36/ikp132.txt";
```

Replace `ikp132.txt` with your desired instance file.

### 3. Compile

**Windows:**
```bash
cd scripts
compile.bat
```

**Linux/Mac:**
```bash
cd scripts
chmod +x compile.sh
./compile.sh
```

### 4. Run

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

### 5. View Results

Results will be saved to:
- Statistics: `results/statistics/BMS.txt`
- Convergence: `results/convergence/cvg_np30_ikp132.txt`

## Directory Structure

After setup, your directory structure should look like:

```
BFLA_01KP/
├── src/
│   └── BFLA_01KP.cpp              # Source code
├── instances/
│   ├── Instance_01KP_36.zip       # Instance archive
│   ├── Instance_01KP_36/          # Extracted instances (after step 1)
│   │   ├── ikp132.txt
│   │   ├── ikp133.txt
│   │   └── ...
│   └── README.md
├── notebooks/                      # Analysis notebooks
├── scripts/                        # Compilation scripts
│   ├── compile.sh
│   ├── compile.bat
│   ├── run_experiment.sh
│   └── BFLA_01KP[.exe]            # Compiled executable (after step 3)
├── results/                        # Output directory (auto-created)
│   ├── convergence/
│   └── statistics/
├── README.md                       # Main documentation
├── SETUP.md                        # This file
└── .gitignore
```

## Troubleshooting

### Issue: Instance file not found

**Solution:**
1. Ensure you extracted the ZIP file to `instances/`
2. Check the path in `src/BFLA_01KP.cpp` matches your instance file name
3. Verify the file exists: `instances/Instance_01KP_36/ikp132.txt`

### Issue: Output directory error

**Solution:**
The code automatically creates output directories. If you encounter errors:
```bash
mkdir -p results/convergence results/statistics
```

### Issue: Compilation fails

**Solution:**
- **Windows**: Install MinGW or use MSVC compiler
- **Linux**: Install build tools: `sudo apt-get install build-essential`
- **Mac**: Install Xcode Command Line Tools: `xcode-select --install`

## Next Steps

1. Read the main [README.md](README.md) for detailed documentation
2. Modify parameters in `src/BFLA_01KP.cpp` as needed
3. Run experiments and analyze results using the notebooks in `notebooks/`

## Getting Help

For detailed information, see:
- [README.md](README.md) - Complete documentation
- [instances/README.md](instances/README.md) - Instance file information
- [notebooks/README.md](notebooks/README.md) - Notebook usage guide

