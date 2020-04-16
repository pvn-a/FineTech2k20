#include<stdio.h>
#include "assignment_2.h"
#include<limits.h>

void main()
{
    int org[]={20,5,15,25,10,3,2,18};//works
    int org1[]={3,8,69,5,26,7};//works
    int org2[]={20,5,15,25,10,3,2,18,76,23,56,90,11,123,34,69};//works
    int org3[]={69,87,4};//not working for 2 works for 1,3
    int length=8,length1=6,length2=16,length3=3;
    int n=1000000;
    int org4[n]; int length4=n;
    for(int i=0;i<n;i++)
	org4[i]=i+1;
    org4[30]=69699989;org4[10000]=INT_MAX;
    int org5[]={2, 3, 1, 4, 5, 0, 7}; int length5=7;
    int org6[]={2, 3, 1, 4, 5,34}; int length6=6;
    int org7[]={20,5,15,25,10,3,2,18,76,23,56,909,11,123,34,69,28,48,87}; int length7=20;
    int org8[]={20,5,15,25,10};int length8 =5;////
    find_second_greatest(org7,length7);
}
