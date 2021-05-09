# CS 225 Final Project - TEAM MIK
## Team Members: Soonha Hwang, Shu Xian Lai, Tyler Kim, Akshay Sivaraman

## Table of Contents</br>
<ol>
  <li>
    <a href=#project-goal>Project Goal</a>
  </li>
  <li>
    <a href=#getting-started>Getting Started</a>
  </li>
  <li>
    <a href=#location-of-code-data-and-results> Location of Code, Data, and Results</a>
  </li>
</ol>
  
## Project Goal
asd

## Getting Started
You can follow few easy steps to execute our project.

### Prerequisites
To begin with, you will have to load llvm on EWS environment with `module load llvm`

### Installation
1. Clone this repository
   ```sh
   git clone https://github-dev.cs.illinois.edu/cs225-sp21/soonhah2-sxlai2-tkim139-abs7.git
   ```
2. Locate in correct directory. For more information on our directory structure, please refer to <a href=#Location>Location of Code, Data, and Results</a>
   ```sh
   cd Forest
   ```
### Execution
run main.cpp file to execute our project
```sh
make
./main
```
Following output will show on terminal. Input at your own variable and see different results according to the different inputs!</br>
For example,
```
Enter limit for IDDFS (less than or equal to 4): 2
Enter input file: ../Amazon6061.txt
Enter ranking N: 100
Do you want to execute Tarjan's algorithm? (yes or no): yes
Do you want to execute BFS? (yes or no): no
```
Doing so will output results for IDDFS and Tarjan's Algorithm but not BFS.

#### Executing testcases
you can also run testcases with the following steps:
1. run <a href=../master/Forest/tests/test.cpp>test.cpp</a>
   ```
   make test
   ./test
   ```
2. Test can be run by `./test`, or can be run with `./test "test names"`. <a href=../master/Forest/tests/test.cpp>test.cpp</a> is located in `Forest/tests/`
   ```
   ./test "Checking IDDFS testcase 3"
   ```

## Location of Code, Data, and Results
All our code, test suite and results are in the Forest directory. Our code is in the files "Forest.h", "Forest.cpp" and "main.cpp". Our test suite is in the Tests directory. Our results will be outputted into the "result_midpoint.txt" file (in the results directory). Our dataset is in the general directory - "Amazon0601.txt", while we have self made test cases from sample_testcase1.txt to sample_testcase4.txt in directory called /tests. In the /tests directory, you can also see the visualization of the sample input.
```
├── Forest
│   ├── Forest
│   ├── Forest.cpp
│   ├── Forest.h
│   ├── main.cpp
│   ├── results
│   │   └── result_midpoint.txt (stores result)
│   └── tests
│       ├── testcases.txt (4 self created test cases)
│       └── test.cpp
├── Amazon0601.txt (Main testcase)
├── README.md
├── Final Project Proposal.md
└── Team_Contract.md
```
