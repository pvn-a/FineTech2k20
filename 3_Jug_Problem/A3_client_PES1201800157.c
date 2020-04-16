#include<stdio.h>
#include<stdlib.h>
#include "A3_header_PES1201800157.h"
//#include <stdio_ext.h> //for fpurge
int DEBUG1=0; //Displays pour amount in each transit
int DEBUG2=0;//Addition Process and Deletion Process

int main()
{
	state full, start, final; int total_solutions=0;
	int arr[3], arr1[3], arr2[3];
	scanf("%d %d %d", &arr[0], &arr[1], &arr[2]);
	scanf("%d %d %d", &arr1[0], &arr1[1], &arr1[2]);
	scanf("%d %d %d", &arr2[0], &arr2[1], &arr2[2]);
	//__fpurge(stdin);
	//fflush(stdin);
	init_state(&full, arr[0], arr[1], arr[2]);
	init_state(&start, arr1[0], arr1[1], arr1[2]);
	init_state(&final, arr2[0], arr2[1], arr2[2]);
	//init_state(&full,12,8,5);
	//init_state(&start,12,0,0);
	//init_state(&final,6,6,0);
	int n = start.A + start.B + start.C; //used to compute if its valid or not
	if(is_valid_st(&full,&start,n)==0 || is_valid_st(&full,&final,n)==0)
	{
		printf("%d\n",0);
		return -1;
	}
	int (*move[])(const state *full, const state *src, state *dst, int n) = {AtoB,AtoC,BtoA,BtoC,CtoA,CtoB}; //callback array

	list soln_list; //final list to be printed
	init_list(&soln_list);
	add_at_end(&soln_list,&start);
	if(DEBUG1)
	{
		printf("######## INITIAL LIST ########\n");
		display_list(&soln_list);
	}
	int soln = 0;
	state temp;
	init_state(&temp,0,0,0);
	int fn_index;
	while(soln_list.head!=NULL) //until no solutions can be possibly obtained
	{
		fn_index = soln_list.tail->st.fn_index;
		if(move[fn_index](&full, &soln_list.tail->st,&temp, n) && !is_repeated(&soln_list, &temp))
		{
			add_at_end(&soln_list, &temp);
			if(DEBUG2)
			{
				printf("######## ADDITION PROCESS ########\n");
				printf("added : ");
				display_state(&temp);
				printf("----------\n");
				display_list(&soln_list);
				printf("----------\n");
				getchar();
			}
			soln = are_same_st(&temp, &final);
			if(soln)
			{
				++total_solutions;
				//printf("+++++++++++++++++++++++++SOLUTION:+++++++++++++++++++\n");
				display_list(&soln_list);
				printf("\n");
				soln = 0;
			}
		}
		else //delete nodes until that "repeated" node, delete at end
		{
			while(soln_list.head!=NULL && soln_list.tail->st.fn_index++ == 5)
			{
				if(DEBUG2)
				{
					printf("######## DELETION PROCESS ########\n");
					printf("removed : ");
					display_state(&soln_list.tail->st);
				}
				delete_at_end(&soln_list);
				if(DEBUG2)
				{
					printf("----------\n");
					display_list(&soln_list);
					printf("----------\n");
					getchar();
				}
			}
		}
		
	}
	printf("%d\n",total_solutions);
}
