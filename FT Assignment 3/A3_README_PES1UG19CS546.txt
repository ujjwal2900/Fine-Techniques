Fine Techniques Assignment - 3: State Space Puzzle

Name : Ujjwal Kumar
Section : I
SRN : PES1UG19CS546

-------------------------------------------------------------------------------------------------------------------

To Compile the code the following command is used :

gcc -Wall -c A3_client_PES1UG19CS546.c A3_impl_PES1UG19CS546.c A3_header_PES1UG19CS546.h
gcc A3_client_PES1UG19CS546.o A3_impl_PES1UG19CS546.o
./a.out

-------------------------------------------------------------------------------------------------------------------

Data Structures used in my implementation :

Structures : Structure are used to store the state of the jugs that is how much water they contain at any given time what was the start state of the jugs
			 and what is the final state to be reached.
Linked Lists : Linked list stores all the valid transitions that can be made in order to reach the final state and on getting the solution it displays 
			   all the transitions that were done to reach the final state.
			   
-------------------------------------------------------------------------------------------------------------------			   
			  
Algorithm or the Logic behind the implementation :

Two structure are used one to store the current state of the jugs and the other to store the capacity of each jug
First the linked list is initialized and the start state of the jugs is inserted into it as a structure variable 
as the first node of the linked list
Then while the list is not empty various transitions are made among the jugs with the help of call back array
		For the transitions the water is transferred from one jug to another until either one of the jugs becomes full or the other is empty
		Total 6 such transitions are there between the 3 jugs and is done based on the function index through the call back array
If the transition is valid and is not repeated then it is stored at the end of the linked list.
In each iteration it is checked if we have reached our goal state or not
If the final state is reached at any time then the linked list is printed
This iterations are repeated until the list becomes empty
At the end total number of solutions are printed.
Algorithm :
while the list is not empty
			make a move
			if valid and not repeated
				add to soln
				if soln
					print the soln
			else
				try the next soln
				while list not empty and no more steps
					backtrack
					
-------------------------------------------------------------------------------------------------------------------
					
Key Takeaway from the Assignment :
Through this assignment I learnt how to solve the state space puzzles and other problems of its kind.
I also learnt the concept of backtracking to get the solution in similar kind of problems.
It further brought more clarity on the concepts of structures and linked list.
