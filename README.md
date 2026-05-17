# Operating System Scheduling Simulator

![C++](https://img.shields.io/badge/C%2B%2B-17-00599c)
![Status](https://img.shields.io/badge/status-academic%20simulator-1b7c5e)

A C++ console application that simulates classic CPU scheduling algorithms used in operating systems coursework. The program reads process data, lets the user select a scheduling strategy, calculates waiting times, and writes results to `output.txt`.

## Algorithms

- First Come First Served (FCFS)
- Shortest Job First (non-preemptive)
- Shortest Job First (preemptive)
- Priority Scheduling (non-preemptive)
- Round Robin with a user-provided time quantum

## Input Format

Process data is read from `input.txt`.

Each line uses:

```text
burst_time:arrival_time:priority
```

Example:

```text
1:2:3
2:3:7
8:4:8
```

## Build And Run

Compile:

```bash
g++ -std=c++17 main.cpp -o scheduler
```

Run:

```bash
./scheduler
```

The program is menu-driven. Choose a scheduling method, optionally add processes during runtime, and use the "Show result" menu option to read the generated `output.txt`.

## Screenshots

Screenshots are not available in the repository yet.

Recommended additions:

- Terminal menu screenshot
- Example scheduling result screenshot
- Sample `output.txt` result

## What This Shows

- C++ procedural programming
- Linked-list based process storage
- File input/output
- Scheduling algorithm simulation
- Console menu interaction

## Portfolio Note

This repository is kept public as an academic operating systems project. It is intentionally small, but now includes a clearer README, sample input, and a compile-verified implementation path.

## Roadmap

- Reduce compiler warnings from unused variables
- Split algorithms into separate functions/files
- Add sample output documentation
- Add basic automated test cases for known input/output
- Add a license if the project should be reused publicly

## Contributing

This repository is maintained as a portfolio/academic project. Contributions should keep the console interface simple and include build/run notes.

## License

No license has been selected yet.
