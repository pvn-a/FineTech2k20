#include<stdio.h>
#include<stdlib.h>
#include "A3_header_PES1201800157.h"
extern int DEBUG1;  //Displays pour amount in each transit
extern int DEBUG2; //Addition Process and Deletion Process

void init_state(state *ptr_state, int A, int B, int C)
{
	ptr_state->A = A;
	ptr_state->B = B;
	ptr_state->C = C;
	ptr_state->fn_index = 0;
}

void display_state(const state *ptr_state)
{
	printf("%d %d %d\n",ptr_state->A,ptr_state->B,ptr_state->C);
}


int AtoB(const state *full, const state *src, state *dst, int n)
{
	int pour = full->B - src->B;
	if(pour <= src->A) //say A has 8 but pour is 5
	{
		dst->B = full->B; //full pour
		dst->A = src->A - pour;
	}
	else // if A has 3 but pour is 6 , u will be completly emptying out A into B
	{
		if(src->A==0) // if its 0 return its not a valid state
			return 0;
		else
		{
			dst->B = src->A + src->B;
			dst->A = 0; //essentially u r emptying out A (src->A - pour)
		}
	}
	dst->C = src->C; //this remains the same in src and dst
	dst->fn_index = 0;
	int check = is_valid_st(full, dst, n);
	if(DEBUG1 && check && pour>0 && pour<=full->B)
	{
		//printf("++++++++++++++++++++++++++++++++++++++++++++\n");
		printf("AtoB()\n");
		printf("%d %d %d",src->A,src->B,src->C);
		printf("  ::Pour %d from A to B::  ", pour);
		display_state(dst);
		//printf("++++++++++++++++++++++++++++++++++++++++++++\n");

	}
	return check;
}

int AtoC(const state *full, const state *src, state *dst, int n)
{
	int pour = full->C - src->C;
	if(pour <= src->A) 
	{
		dst->C = full->C; //full pour
		dst->A = src->A - pour;
	}
	else 
	{
		if(src->A==0)
			return 0;
		else
		{
			dst->C = src->A + src->C;
			dst->A = 0; 
		}
	}
	dst->B = src->B;
	dst->fn_index = 0;
	int check = is_valid_st(full, dst, n);
	if(DEBUG1 && check && pour>0 && pour<=full->C)
	{
		//printf("++++++++++++++++++++++++++++++++++++++++++++\n");
		printf("AtoC()\n");
		printf("%d %d %d",src->A,src->B,src->C);
		printf("  ::Pour %d from A to C::  ", pour);
		display_state(dst);
		//printf("++++++++++++++++++++++++++++++++++++++++++++\n");
	}
	return check;
}

int BtoA(const state *full, const state *src, state *dst, int n)
{
	int pour = full->A - src->A;
	if(pour <= src->B) 
	{
		dst->A = full->A; //full pour
		dst->B = src->B - pour;
	}
	else 
	{
		if(src->B==0)
			return 0;
		else
		{
			dst->A = src->B + src->A;
			dst->B = 0; 
		}
	}
	dst->C = src->C;
	dst->fn_index = 0;
	int check = is_valid_st(full, dst, n);
	if(DEBUG1 && check && pour>0 && pour<=full->A)
	{
		//printf("++++++++++++++++++++++++++++++++++++++++++++\n");
		printf("BtoA()\n");
		printf("%d %d %d",src->A,src->B,src->C);
		printf("  ::Pour %d from B to A::  ", pour);
		display_state(dst);
		//printf("++++++++++++++++++++++++++++++++++++++++++++\n");
	}
	return check;
}
int BtoC(const state *full, const state *src, state *dst, int n)
{
	int pour = full->C - src->C;
	if(pour <= src->B) 
	{
		dst->C = full->C; //full pour
		dst->B = src->B - pour;
	}
	else 
	{
		if(src->B==0)
			return 0;
		else
		{
			dst->C = src->B + src->C;
			dst->B = 0; 
		}
	}
	dst->A = src->A;
	dst->fn_index = 0;
	int check = is_valid_st(full, dst, n);
	if(DEBUG1 && check && pour>0 && pour<=full->C)
	{
		//printf("++++++++++++++++++++++++++++++++++++++++++++\n");
		printf("BtoC()\n");
		printf("%d %d %d",src->A,src->B,src->C);
		printf("  ::Pour %d from B to C::  ", pour);
		display_state(dst);
		//printf("++++++++++++++++++++++++++++++++++++++++++++\n");
	}
	return check;
}
int CtoA(const state *full, const state *src, state *dst, int n)
{
	int pour = full->A - src->A;
	if(pour <= src->C) 
	{
		dst->A = full->A; //full pour
		dst->C = src->C - pour;
	}
	else 
	{
		if(src->C==0)
			return 0;
		else
		{
			dst->A = src->C + src->A;
			dst->C = 0; 
		}
	}
	dst->B = src->B;
	dst->fn_index = 0;
	int check = is_valid_st(full, dst, n);
	if(DEBUG1 && check && pour>0 && pour<=full->A)
	{
		//printf("++++++++++++++++++++++++++++++++++++++++++++\n");
		printf("CtoA()\n");
		printf("%d %d %d",src->A,src->B,src->C);
		printf("  ::Pour %d from C to A::  ", pour);
		display_state(dst);
		//printf("++++++++++++++++++++++++++++++++++++++++++++\n");
	}
	return check;
}
int CtoB(const state *full, const state *src, state *dst, int n)
{
	int pour = full->B - src->B;
	if(pour <= src->C) 
	{
		dst->B = full->B; //full pour
		dst->C = src->C - pour;
	}
	else 
	{
		if(src->C==0)
			return 0;
		else
		{
			dst->B = src->C + src->B;
			dst->C = 0; 
		}
	}
	dst->A = src->A;
	dst->fn_index = 0;
	int check = is_valid_st(full, dst, n);
	if(DEBUG1 && check && pour>0 && pour<=full->B)
	{
		//printf("++++++++++++++++++++++++++++++++++++++++++++\n");
		printf("CtoB()\n");
		printf("%d %d %d",src->A,src->B,src->C);
		printf("  ::Pour %d from C to B::  ", pour);
		display_state(dst);
		//printf("++++++++++++++++++++++++++++++++++++++++++++\n");
	}
	return check;
}


int is_valid_st(const state *full, const state *ptr_state, int n)//todo this function
{
	int check =  (ptr_state->A >=0 && ptr_state->A <=full->A) &&
		   (ptr_state->B >=0 && ptr_state->B <=full->B) &&
		   (ptr_state->C >=0 && ptr_state->C <=full->C) &&
		   (ptr_state->A + ptr_state->B + ptr_state->C == n);
	//printf(" %d\n",check);
	return check;
}

int are_same_st(const state *lhs, const state *rhs)
{
	return (lhs->A == rhs->A && lhs->B == rhs->B && lhs->C == rhs->C );
}

void init_list(list *ptr_list)
{
	ptr_list->head = NULL;
	ptr_list->tail = NULL;
}

void add_at_end(list *ptr_list, const state *ptr_state)
{
	node *temp = (node*)malloc(sizeof(node));
	temp->st = *ptr_state;
	if(ptr_list->head == NULL) //EMPTY
	{
		temp->prev = ptr_list->tail;
		ptr_list->head = temp;
		ptr_list->tail = temp;
		temp->next = NULL;
	}
	else //NON-EMPTY
	{
		temp->prev = ptr_list->tail;
		ptr_list->tail->next = temp;
		ptr_list->tail = temp;
		temp->next = NULL;
	}	
}

void delete_at_end(list *ptr_list)
{
	if(ptr_list->head ==NULL)//EMPTY
		printf("EMPTY\n");
	else if(ptr_list->head == ptr_list->tail)//1 node
	{
		free(ptr_list->head);
		ptr_list->head = ptr_list->tail = NULL;
	}
	else// no_of_nodes >1
	{
		node *temp = ptr_list->tail;
		ptr_list->tail = temp->prev;
		ptr_list->tail->next = NULL;
		free(temp);
	}	
}

int is_repeated(list *ptr_list, const state* ptr_state)
{
	node *temp = ptr_list->head;
	while(temp)
	{
		if(are_same_st(&temp->st,ptr_state))
			return 1;
		temp = temp->next;
	}
	return 0;
}

void display_list(const list *ptr_list)
{
	node *temp = ptr_list->head;
	while(temp)
	{
		display_state(&temp->st);
		temp = temp->next;
	}
}