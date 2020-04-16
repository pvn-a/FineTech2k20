typedef struct state // state representation
{
	int A;//jug A
	int B;//Jug B
	int C;//Jug C
	int fn_index; //func index it is pointing to
}state;

void init_state(state *ptr_state, int A, int B, int C); //initialise the state ptr_state with A,B,C contents.
void display_state(const state *ptr_state); //Display the contents of a state

int AtoB(const state *full, const state *src, state *dst, int n); // Pour contents from jug A to B
int AtoC(const state *full, const state *src, state *dst, int n); // Pour contents from jug A to C
int BtoA(const state *full, const state *src, state *dst, int n); // Pour contents from jug B to A
int BtoC(const state *full, const state *src, state *dst, int n); // Pour contents from jug B to C
int CtoA(const state *full, const state *src, state *dst, int n); // Pour contents from jug C to A
int CtoB(const state *full, const state *src, state *dst, int n); // Pour contents from jug C to B

int is_valid_st(const state *full, const state *, int n); //check for overflow of undeflow of JUG here
int are_same_st(const state *lhs, const state *rhs); // check if the two states are equal by comparing A, B, C


typedef struct node // Each node in the linked list is of this type
{
	state st; //state it corresponds to
	struct node *prev; //pointer to prev node
	struct node *next; //pointer to next node
}node;

typedef struct list // List holding all states which yield to the final/end state
{
	node *head;
	node *tail;
}list;

void init_list(list *ptr_list); // initialize the list
void add_at_end(list *ptr_list, const state* ptr_state);  // add a node(i.e state) to the end
void delete_at_end(list *ptr_list); // delete the node(i.e) node at the end
int is_repeated(list *ptr_list, const state* ptr_state); // check if a state is already present in the list 
void display_list(const list *ptr_list); // display a list completely containing all states to the solution
