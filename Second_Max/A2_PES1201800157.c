#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<math.h>
#include<limits.h>
#include "assignment_2.h"
#define empty -9999
#define debug 0  //change this to 1 for debugger mode

static void printarray(int *arr[],int size)
{
    for(int i=0; i< size; i++)
    {
        for(int j=0; j<size; j++)
            printf("%d\t",arr[i][j]);
        printf("\n");
    }
    printf("\n");
}

static void reinitcol(int *arr[],int size,int col)//initializes a column to 'empty' values
{
    for(int i=0; i< size; i++)
        arr[i][col]=empty;
}

static void lhs_print(int *arr[],int size, int col)////prints the LHS of the comparision
{
    int i=0;
    while(i<size && arr[i][col+1]!=empty)
        printf("%d ",arr[i++][col+1]);
    printf("x ");
    i=0;
    while(i<size && arr[i][col]!=empty)
        printf("%d ",arr[i++][col]);
    printf("= ");
}

static void rhs_print(int *arr[],int size, int col)//prints the RHS of the comparision
{
    int i=0;
    while(i<size && arr[i][col]!=empty)
        printf("%d ",arr[i++][col]);
    printf("\n");
}

static void fin_col_switch(int *arr[], int size, int cur, int base)
{
	int j=base;
        while(j<size && arr[j][cur]!=empty ) //&&j<size is for the last switching
        {
            arr[j][cur+1] = arr[j][cur];
            j++;
        }
        reinitcol(arr,size,cur);
}

static void start(int *arr[], int size,int base, int cur, int *flag, int *flag2, int playmatch, int when)//play a match for every element collisions. Also used to go through all elements in case there are left out elements(not a power of 2 case)
{       
    if(arr[base][cur+1]==empty)//moving to next col 
    {
        int j = base;
        *flag2=1;
        *flag=1;//so that shift doesnt happen twice later in the end shifting.
        while(j<size && arr[j][cur]!=empty)
        {
            arr[j][cur+1] = arr[j][cur];
            j++;
        }
        reinitcol(arr,size,cur);  
    }
    else if((when==0 && *flag!=1) || (when==1 && ((*flag)!=1 || *flag2==1)))//when==0 due to first call of start(), when==1 (to check for remaining elemnts in the end)
    {   
        //two col filled,equal, check which is grter and smallest set and set the next thing respectively   
        if(arr[base][cur] > arr[base][cur+1])//(base,cur)=>winning => (if cur won, cur+1 lost (base,cur)=>winning)
        {   //if col1=[20,10,2] and col2=[16,6,7] => does this [20,16,10,2]
            lhs_print(arr,size,cur);
            int lost=arr[base][cur+1];
            arr[base][cur+1]=arr[base][cur];
            arr[base+1][cur+1]=lost;
            int j = base+2;
            while(arr[j-1][cur]!=empty)//copying elements
            {
                arr[base+j][cur+1] = arr[base+j-1][cur]; j++;
            }
	        for(;j<size-1;j++)
		        arr[j][cur+1]=empty;
            reinitcol(arr,size,cur);
            rhs_print(arr,size,cur+1);
	        if(debug) printarray(arr,size);      
        }
        else if(arr[base][cur]==empty && arr[base][cur+1]!=empty)
        { /*dummy to skip cases like: if col1 is empty and col2 has elements then it is meaningless to compare a empty(col1's data) with col2's data*/
        }
        else//(base,cur+1)=>winning => (if cur lost, cur+1 won (base,cur+1)=>winning)
        {   //if col1=[20,3,5] and col2=[26,6,7] => does this [26,20,6,7]
            lhs_print(arr,size,cur);                 
            int j=cur+2;//<change this has been hardcoded>
            int lost=arr[base][cur];
            while(j>1)//shift elements down
            {
                arr[j][cur+1] = arr[j-1][cur+1];
                j--;
            }
            arr[j][cur+1]=lost;
            reinitcol(arr,size,cur);
            rhs_print(arr,size,cur+1);
	        if(debug) printarray(arr,size);
        } 
    }
}

void find_second_greatest(int *numbers, int length)
{
    int size=ceil(log2(length)+1);
    bool is_power2 = floor(log2(length))==ceil(log2(length))?true:false;//check if power of 2 can use 'n & (n-1)' also
    int *arr[size];
    for(int i=0;i< size;i++)//row
        arr[i]=(int*)malloc(size*sizeof(int));
    for(int i=0; i< size; i++)
        for(int j=0; j<size; j++)
            arr[i][j] = empty;
    int base=0; int when =0;  
    bool playmatch = false;
    int cur,flag,flag2,ele;
    for(int i=0;i<length;i++)
    {        
        cur = 0; flag=0; flag2=0;
        ele = numbers[i];
        if(arr[base][cur]==empty && playmatch==false) //if the iniital matrix[0][0] is empty put the ele there
            arr[base][cur] = ele;

        else //if matrix[0][0] is not empty
        {
            playmatch = true; //forcefully propell the first match to coninue to the subsequent columns
            printf("%d x %d = ",arr[base][cur],ele);
            if(arr[base][cur] > ele) //bruteforcing first match results in the same 0th column (i.e first column)
                arr[base+1][cur] = ele;

            else
            {
                arr[base+1][cur] = arr[base][cur];
                arr[base][cur] = ele;
            }
            rhs_print(arr,size,cur);
	        if(debug)  printarray(arr,size);    
            while(arr[base][cur+1]!=empty || playmatch==true)//start playing the matches from the first column
            {
                start(arr,size,base,cur,&flag,&flag2,playmatch,0);//when=0 since initial checking during insertion
                cur++;  
                playmatch = false;  
            }
            if(arr[base][cur+1]==empty && flag==0 && flag2==0)//final push into the next column only if not encounterd by start
            	fin_col_switch(arr, size, cur, base);             
        }
        if(debug) { printf("Final element comparision:\n"); printarray(arr,size); }    
    }
    if(is_power2)//skip and print the second biggest element
        {}
    else
    {
        cur = 0;  flag = 0;
        flag2 = 0;  playmatch = true;
        while((arr[base][cur+1]!=empty || playmatch==true || arr[base][size-1]==empty) && cur<size-1 )//continue until the last column is filled(if its not a power of 2 condition)
        {
            start(arr,size,base,cur,&flag,&flag2,playmatch,1);//when=1 for last pass through
            cur++;   playmatch = false;  
        }
        if(arr[base][cur+1]==empty && flag==0 && flag2==0)//final push into the next column only if not encounterd by start
            fin_col_switch(arr, size, cur, base);
	    if(debug) { printf("Final element comparision:\n"); printarray(arr,size); } 
    }  

    int i=1;int sec_max=empty;
    for(;i<size;i++)
	    if(arr[i][size-1] > sec_max)
	        sec_max=arr[i][size-1];
    printf("\n%d\n",sec_max);//final answer printer       
}
