# Final Project Proposal - TeamMIK

## Leading Question
Suppose we are the owners of Amazon, and we want to shrink the number of products that we are selling on the platform and we want to do so as optimally as possible. 
In other words, we want to find products that render the most number of other related purchases given the co-purchasing dataset.

To answer the leading question, we will:
1. Find top-N nodes with the most co-purchase index using IDDFT,
2. Decide which products to promote on by using Tarjan's Algorithm,
3. Find the products with high potential using Djisktra's Algorithm.

This will be described more in detail in section <strong>Graph Traversal</strong> and <strong>Graph Algorithm</strong>.

## Dataset Acquisition and Processing
We will be using "Amazon product co-purchasing network" from Stanford's Network Dataset (SNAP). The dataset is stored in a .txt file 
with each node representing an item and directed edges of node A to node B representing "customer bought item A, customer therefore also bought item B".

Data processing will involve collapsing multigraph into a simple graph, and performing Iterative Deepening Depth First Traversal (IDDFT) on each node to determine which 
item links to the most number of nodes given a certain depth.

Link to dataset can be found at [SNAP-Amazon Product co-purchasing Network](http://snap.stanford.edu/data/amazon0505.html)
