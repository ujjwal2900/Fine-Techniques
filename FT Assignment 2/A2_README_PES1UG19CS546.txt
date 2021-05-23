FINE TECHNIQUES
ASSIGNMENT -2 STEPANOVS BINARY COUNTER

Name : Ujjwal Kumar
Section : I
SRN : PES1UG19CS546

Data Structure Used : 
			Double Dimensional Array with dimensions ceil(logn) (Space complexity proportional to (logn)^2
			
Algorithm : The element which has undergone i comparison is stored in the ith row
	When the first element is loaded it is stored in the 0th row has it has undergone 0 comparisons then after the
	first comparison the greater element is stored as the first member of the 1st row as it has undergone 1 comparison.
	The first element of each row contains the greatest number in that row.
	Then after the match between the next two elements and the elements of the 1st row two comparisons occur so the three elements which have undergone 2
	comparisons are stored in row number 2.
	Like this match successively occurs along with that the result is also printed.
	At the end comparison occurs between the elements of the last row to find the second largest element.
	Therefore in total n+logn-2 comparison occurs between the elements of the array.
	
Command to compile the code :
				gcc -Wall -c sanity_client.c assignment_2.h A2_PES1UG19CS546.c
				gcc sanity_client.o A2_PES1UG19CS546.o -lm
				./a.out
				
Key Takeaway from the assignment :
	To write the algorithm efficiently requiring the minimum number of comparisons.
	The problems seems difficult at first but gets easier as we try to solve it.
	
			
				
