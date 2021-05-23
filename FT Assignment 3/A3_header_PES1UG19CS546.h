struct state_of_jugs
{
	int jug_A; // Amount of water in jug A
	int jug_B; // Amount of water in jug B
	int jug_C; // Amount of water in jug C
	// implementation field to track which transition has been applied
	int function_index;
	char *move; //store which moves was made i.e AtoB AtoC BtoA BtoC CtoA CtoB
};
struct capacity	// stores the capacities or the limits of the jug A,B and C
{
	int cap_A;
	int cap_B;
	int cap_C;
};
typedef struct state_of_jugs state;
typedef struct capacity capt;
// linked list to store each valid move or state 
struct node
{
	state st_jugs;		//stores the structure state
	struct node* prev;		// pointer to the previous node
	struct node* next;		// pointer to the next node
};
typedef struct node node_t;
struct list
{
	node_t* head;	// pointer to the head of the linked list
	node_t* tail;	// pointer to the tail or end of the linked list
};
typedef struct list list_t;
void set_state(state *ptr_state, int can, int mis, int boatpos);	//set the state of the pointer to the structure
void set_capacity(capt *ptr_limit, int a, int b, int c);		//set the capacities of the jug A,B and C to the pointer ptr_limit
void display_state(const state *ptr_state);		//used to print the transition which were made and stored in the list
int is_same(const state *ptr_initial, const state *ptr_final);	//checks if the values of both the pointer to the structure are same or not
int is_valid(const state *ptr_state, const capt *ptr_limit);	//checkks if the transition was valid or not

// state *initial: store the initial state of the jug   state *fin: stores the state of the jug after the transition	*ptr_limit : has the capcity of each jug
void move_AB(const state *initial, state *fin, const capt *ptr_limit);	//transition from A to B
void move_AC(const state *initial, state *fin, const capt *ptr_limit);	//transition from A to C
void move_BA(const state *initial, state *fin, const capt *ptr_limit);	//transition from B to A
void move_BC(const state *initial, state *fin, const capt *ptr_limit);	//transition from B to C
void move_CA(const state *initial, state *fin, const capt *ptr_limit);	//transition from C to A
void move_CB(const state *initial, state *fin, const capt *ptr_limit);	//transition from C to B

extern void (*move[])(const state *initial, state *fin, const capt *ptr_limit);	//call back array to call the transition functions

void initialize_list(list_t *ptr_list);	//used to initialize the linked list
void display_list(const list_t *ptr_list);		//displays the list after the solution is obtained
void insert_at_end(list_t *ptr_list, const state *ptr_state);	//adds at the end of the linked list
void delete_at_end(list_t *ptr_list);	//deletes the last node of the list
int is_duplicate(const list_t *ptr_list, const state *ptr_state);	//checks if the same node is already present in the list or not
int is_empty(const list_t *ptr_list);	// checks whether the list is empty or not

