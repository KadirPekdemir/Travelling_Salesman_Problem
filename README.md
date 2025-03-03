# Traveling Salesman Problem (TSP) Solver

This project is a C-based implementation of an algorithm to solve the **Traveling Salesman Problem (TSP)**. The program reads city coordinates from an input file, constructs an initial tour using the **Nearest Neighbor Algorithm**, and optimizes the tour using a **swap-based local search** approach.

## Features
- **Input File:** The program reads city data from a user-specified file. Each city consists of a city ID, x-coordinate, and y-coordinate.
- **Initial Tour Construction:** Generates an initial tour using the **Nearest Neighbor** heuristic.
- **Optimization:** Improves the tour using a **swap-based** method to reduce total travel distance.
- **Distance Calculation:** Computes the total tour distance, including the return to the starting city.
- **Output:** The optimized tour and its total distance are printed to the console and saved in `output.txt`.
- **Performance Measurement:** The execution time of the program is calculated and displayed.

## Requirements
- **C Compiler:** A C compiler such as `gcc`.
- **Math Library:** The program uses the math library, so `-lm` must be included during compilation.

## Installation & Compilation
To compile the program, run the following command in the terminal:

```bash
gcc -o tsp program.c -lm
