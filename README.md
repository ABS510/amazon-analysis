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
    <a href=#Location> Data Location</a>
  </li>
</ol>
  
## Project Goal
asd

## Getting Started
You can follow few easy steps to execute our project.

### Prerequisites
To begin with, you will have to load llvm on EWS environment.

```sh
module load llvm
```


### Installation

Clone this repository
```sh
git clone https://github-dev.cs.illinois.edu/cs225-sp21/soonhah2-sxlai2-tkim139-abs7.git
```
Because our execution file is located inside /Forest, cd into it. For more information on our directory structure, please refer to <a href=#Location>Location of Code, Data, and Results</a>
```sh
cd Forest
```

#### Executing testcases


## Location of Code, Data, and Results
All our code, test suite and results are in the Forest directory. Our code is in the files "Forest.h", "Forest.cpp" and "main.cpp". Our test suite is in the Tests directory. Our results will be outputted into the "result_midpoint.txt" file (in the results directory). Our dataset is in the general directory - "Amazon0601.txt". 
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
