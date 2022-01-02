# Skip-List

***Context***: In order to search, add, delete the value faster O(log n). Skip list is the data structure that is recommended due to its ease to be implemented.

***Software***: C++ (Dynamic Arrays, Pointers, Doubly Linked Lists)
The program will include node head, tail, vector of nodes forward and backward. I first create a constructor for the program that will take the max level and probability that the node can be inserted at higher; head linked to the smallest value INT_MIN, tail linked to the largest value INT_MAX, and vector forward will be pushed back with node tail, backward with head.

****Find****. The program will go from the top, check the value of each node until it found the node that contains the value needed, or go down 1 level if found the node that contains the value that is larger than the value needed.

****Remove****. The program will go from the top, check the value of each node until it found the node that contains the value needed, or go down 1 level if found the node that contains the value that is larger than the value needed. Then it will delete the node that contains the value.

****Add****. The program will go from the bottom, check the value of each node until it reach the one that larger than the one we need to insert, then we insert it and go up 1 level if the probability is high.


***Output***: It runs successfully.


<img width="402" alt="Screen Shot 2021-12-20 at 10 29 31 PM" src="https://user-images.githubusercontent.com/76256179/147868850-8c9d51f3-e218-4767-b0a0-95c9c9a439a6.png">
