## Week 1 (April 12 - April 16)
This week's goal was to finish setting up all classes and the consturctors for our project. Specifically, we wanted to create:
 - Forest Class : Parent function for Node class where all the algorithms will run in.
 - Node Class : Has the information of all the nodes including it's copurchase index, path to linked node, etc.
 
To successfully create the classes, we first had to read through every single line of the dataset and change it into the way we would like to process. </b>
Because our data consists of two tab seperated numbers, we decided to parse our data into a unordered_map, first element being the current point and second element being the second point.
In order to do that we implemented function readFromFile() that reads the dataset and generate the node in a way we want it to be in.

## Week 2 (April 19 - April 23)
This week's goal was to finish implementing the code to find top-N most influencial product(Product with largest copurchase index). We decided to do that by using IDDFS</b>.
Because we already had the set limit, we had to implement the Depth Limited Search part of IDDFS. </b>
In order to perform that, we made a function IDDFS(), as well as a IDDFS_Helper(). </b>
We also made a function that calls the IDDFS and filters out the top-N products using it callsed filter(), which takes an input of number of ranks we would like to implement.</b>
For example, if we want top-10 products with largest COP index, we would set filter(10).</b>
We also made a makefile and testcases in order to test our functions individually.</b>
After filtering out top-N product, we implemented a code in which it outputs the filtered top-N products as well as its cop index to a seperate txt file in main.cpp.</b>

## Week 3 (April 26 - April 30)
