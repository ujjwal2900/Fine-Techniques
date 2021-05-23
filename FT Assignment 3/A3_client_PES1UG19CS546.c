#include <stdio.h>
#include <stdlib.h>
#include "A3_header_PES1UG19CS546.h"

int main()
{
	// create start state and final state
	state start;	//variable start of type state to store the starting volume of the jugs
	state final;	//variable final of type state to store the final volume of the jugs
	capt limit;		//variable limit of type capt to store the capacities of the jugs
	int cap_A,cap_B,cap_C;	//capacities of the JUG A, B and C
	int ini_A,ini_B,ini_C;	//initial volumes of the JUG A, B and C
	int fin_A,fin_B,fin_C;	//final volumes of the JUG A, B and C
	scanf("%d %d %d",&cap_A,&cap_B,&cap_C);
	scanf("%d %d %d",&ini_A,&ini_B,&ini_C);
	scanf("%d %d %d",&fin_A,&fin_B,&fin_C);
	// initializes the start,final and limit pointers with their values
	set_state(&start, ini_A,ini_B,ini_C);	
	set_state(&final, fin_A,fin_B,fin_C);
	set_capacity(&limit, cap_A, cap_B, cap_C);
	int soln = 0; 	//0 if not a solution else 1
	int no_of_solution = 0;		//stores the number of solutions
	list_t list_state;	//a list to store the valid moves in it
	initialize_list(&list_state);
	int index;
	state temp = start;
	insert_at_end(&list_state, &temp);
	// while the list is not empty
	//		make a move
	//		if valid and not repeated
	//			add to soln
	//		else
	//			try the next soln
	//			while list not empty and no more steps
	//				backtrack
	while(  is_empty(&list_state) ==0 )
	{
		//pickup the index from the last node in the list
		index = list_state.tail->st_jugs.function_index;
		move[index](&list_state.tail->st_jugs, &temp, &limit);	//calls the transition functions
		if(is_valid(&temp, &limit) && ! is_duplicate(&list_state, &temp))	//if the move is valid and is not repeated add at the end of the list
		{
			insert_at_end(&list_state, &temp);
			soln = is_same(&final, &temp);
			if(soln)	// if a solution is found then display the list and increment the no of solutions
			{
				display_list(&list_state);
				printf("\n");
				no_of_solution++;
			}		
		}
		else
		{
			// empty list : should exit the loop
			while( ++list_state.tail->st_jugs.function_index == 6)
			{
				// backtrack
				delete_at_end(&list_state);
				if( is_empty(&list_state) ==1)	//if the list is empty that means there are no more solutions, so exit the loop.
					break;
			}
		}
		
	}
	printf("%d\n",no_of_solution);	//prints the total number of solutions obtained
}
