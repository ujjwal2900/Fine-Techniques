

This repository contains the Assignments carried out as part of our Fine Techniques Course


1. Memory Management :
   
      To demonstrate the memory management policies
   
      a. First Fit: Allocates the first sufficient free memory block from the start of main memory.
   
      b. Next Fit: Similar to the first fit policy, but allocates the first sufficient free memory block starting from the last allocation point.
   
      Move back to the beginning of the main memory, once you reach the end.
   
      c. Best Fit: Allocates the smallest sufficient memory block among the available free memory blocks.
   
      If there are multiple blocks with the same smallest size, choose the first one.
   


2. Stepanov’s Binary Counter :
   
      Implemented Stepanov’s Binary counter to find the second largest element in an array of distinct/unique integers.
   
      Let n be the number of elements in the array (n>=2).  n may or may not be an exact power of 2.
   
      The algorithm does at most n + logn - 2 comparisons (however when n is not an exact power of 2, the number of comparisons can be little more).
   
      It may use extra space proportional to (logn) ^ 2.
   


3. State Space Puzzle :
   
      Find all the solutions to A-B-C jug problem.
   
      We are given 3 jugs A, B, C of capacities a, b, c litres respectively.
   
      The initial state/initial volumes of water in the jugs are X, Y, Z.
   
      Our goal is to get to a final state of P, Q, R litres.

   

4. Binary Search Tree on HardDisk :
   
     Implemented a binary search tree on a harddisk.
   
     The tree supports the following operations
   
      a. insert
   
      b. delete based on the key
   
      c. traversal - inorder : space separated values followed by \n
   
      d. traversal - pre-order : space separated values followed by \n
   

                 
