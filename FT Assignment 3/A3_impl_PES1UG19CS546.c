#include <stdio.h>
#include <stdlib.h>
#include "A3_header_PES1UG19CS546.h"

// initializes the pointer ptr_state to the structure 'state' with values a,b and c 
void set_state(state *ptr_state, int a, int b, int c)
{
	ptr_state->jug_A = a;
	ptr_state->jug_B = b;
	ptr_state->jug_C = c;
	ptr_state->function_index = 0;
	ptr_state->move = "";
}
//initializes the pointer ptr_limit to the structure 'capacity' with the values a,b and c as the capacities of the jugs
void set_capacity(capt *ptr_limit, int a, int b, int c)
{
	ptr_limit->cap_A = a;
	ptr_limit->cap_B = b;
	ptr_limit->cap_C = c;
}
//displays the transition which was made
void display_state(const state *ptr_state)
{
	printf("%s\n",ptr_state->move);
}
//checks if the values of the both the pointers are same or not
int is_same(const state *ptr_initial, const state *ptr_final)
{
	return ptr_initial->jug_A == ptr_final->jug_A && 
			ptr_initial->jug_B == ptr_final->jug_B && 
			ptr_initial->jug_C == ptr_final->jug_C;
			
}

//check whether the transition is valid or not
int is_valid(const state *ptr_state, const capt *ptr_limit)
{
	return
	(ptr_state->jug_A >= 0 && ptr_state->jug_A <= ptr_limit->cap_A) &&
	(ptr_state->jug_B >= 0 && ptr_state->jug_B <= ptr_limit->cap_B) &&
	(ptr_state->jug_C >= 0 && ptr_state->jug_C <= ptr_limit->cap_C);
		
}

// does the transition from jug A to jug B
void move_AB(const state *initial, state *fin, const capt *ptr_limit)
{
		int temp = ptr_limit->cap_B - initial->jug_B;	//stores how much space is left in jug B
		if(initial->jug_A > temp)// if the water in jug A is more than the space left in B then jug B becomes full and that volume is subtracted from jug A
		{
			fin->jug_A = initial->jug_A - temp;
			fin->jug_B = ptr_limit->cap_B;	//water in jug B is equal to its total capacity
		}
		else	//else the jug A becomes empty and that volume is added to jug B
		{
			fin->jug_B = initial->jug_B + initial->jug_A;
			fin->jug_A = 0;
		}
	fin->jug_C = initial->jug_C;
	fin->move = "A B";	//stores that the transition is made from A to B
	fin->function_index = 0;
}
// the remaining 5 functions follow the same logic just among different jugs
// does the transition from jug A to jug C
void move_AC(const state *initial, state *fin, const capt *ptr_limit)
{
		int temp = ptr_limit->cap_C - initial->jug_C;
		if(initial->jug_A > temp)
		{
			fin->jug_A = initial->jug_A - temp;
			fin->jug_C = ptr_limit->cap_C;
		}
		else
		{
			fin->jug_C = initial->jug_C + initial->jug_A;
			fin->jug_A = 0;
		}
	fin->jug_B = initial->jug_B;
	fin->move = "A C";
	fin->function_index = 0;
}

// does the transition from jug B to jug A
void move_BA(const state *initial, state *fin, const capt *ptr_limit)
{
		int temp = ptr_limit->cap_A - initial->jug_A;
		if(initial->jug_B > temp)
		{
			fin->jug_B = initial->jug_B - temp;
			fin->jug_A = ptr_limit->cap_A;
		}
		else
		{
			fin->jug_A = initial->jug_A + initial->jug_B;
			fin->jug_B = 0;
		}
	fin->jug_C = initial->jug_C;
	fin->move = "B A";
	fin->function_index = 0;
}

// does the transition from jug B to jug C
void move_BC(const state *initial, state *fin, const capt *ptr_limit)
{
		int temp = ptr_limit->cap_C - initial->jug_C;
		if(initial->jug_B > temp)
		{
			fin->jug_B = initial->jug_B - temp;
			fin->jug_C = ptr_limit->cap_C;
		}
		else
		{
			fin->jug_C = initial->jug_C + initial->jug_B;
			fin->jug_B = 0;
		}
	fin->jug_A = initial->jug_A;
	fin->move = "B C";
	fin->function_index = 0;
}

// does the transition from jug C to jug A
void move_CA(const state *initial, state *fin, const capt *ptr_limit)
{
		int temp = ptr_limit->cap_A - initial->jug_A;
		if(initial->jug_C > temp)
		{
			fin->jug_C = initial->jug_C - temp;
			fin->jug_A = ptr_limit->cap_A;
		}
		else
		{
			fin->jug_A = initial->jug_A + initial->jug_C;
			fin->jug_C = 0;
		}
	fin->jug_B = initial->jug_B;
	fin->move = "C A";
	fin->function_index = 0;
}

// does the transition from jug C to jug B
void move_CB(const state *initial, state *fin, const capt *ptr_limit)
{
		int temp = ptr_limit->cap_B - initial->jug_B;
		if(initial->jug_C > temp)
		{
			fin->jug_C = initial->jug_C - temp;
			fin->jug_B = ptr_limit->cap_B;
		}
		else
		{
			fin->jug_B = initial->jug_B + initial->jug_C;
			fin->jug_C = 0;
		}
	fin->jug_A = initial->jug_A;
	fin->move = "C B";
	fin->function_index = 0;
}
//call back array to call the transition functions
void (*move[])(const state *initial, state *fin, const capt *ptr_limit) = {

	move_AB,
	move_AC,
	move_BA,
	move_BC,
	move_CA,
	move_CB
};

void initialize_list(list_t *ptr_list)	// initializes the linked list to NULL
{
	ptr_list->head = NULL;
	ptr_list->tail = NULL;
}

void display_list(const list_t *ptr_list)	//displays the moves made if the solution is found
{
	node_t* temp = ptr_list->head;
	if(temp == NULL)
		printf("The list is empty \n");
	while(temp != NULL)
	{
		if( temp!=ptr_list->head)	//displays the moves made by calling the disp_state except the first node which has the start state
			display_state(&temp->st_jugs);
		temp = temp->next;
	}
}

void insert_at_end(list_t *ptr_list, const state *ptr_state)	//adds at the end of the linked list
{
	node_t* temp = (node_t*)malloc(sizeof(node_t));
	temp->st_jugs = *ptr_state;
	temp->next = NULL;
	// empty list
	if(ptr_list->head == NULL)
	{
		temp->prev = ptr_list->tail;
		ptr_list->head = ptr_list->tail = temp;
	}
	else // has # of nodes
	{
		temp->prev = ptr_list->tail;
		ptr_list->tail = ptr_list->tail->next = temp;
	}
	
}

void delete_at_end(list_t *ptr_list)	//deletes the last node of the linked list
{
	// empty
	if(ptr_list->head == NULL)
	{
		printf("list empty; cannot remove\n");
	}
	else if(ptr_list->head == ptr_list->tail ) // one node
	{
		free(ptr_list->tail);
		ptr_list->head = ptr_list->tail = NULL;
	}
	else
	{
		node_t* temp = ptr_list->tail;
		ptr_list->tail = ptr_list->tail->prev;
		ptr_list->tail->next = NULL;
		free(temp);
	}
}

int is_duplicate(const list_t *ptr_list, const state *ptr_state)	//checks if the node is already present in the list or not
{
	node_t* temp = ptr_list->head;
	while(temp != NULL)
	{
		if(is_same(ptr_state, &temp->st_jugs))
		{
			return 1;
		}
		temp = temp->next;
	}
	return 0;
}
int is_empty(const list_t *ptr_list)	//returns 1 if the list is empty else returns 0
{
	node_t* temp = ptr_list->head;
	if(temp == NULL)
		return 1;
	else
		return 0;
}

