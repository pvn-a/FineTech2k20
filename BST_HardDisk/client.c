#include <stdio.h>
#include <stdlib.h>
#include "assignment_4.h"
int main()
{
	FILE *fp = init_tree("bst2.dat");
	int key;
	int opt; 
    printf("1 - Insert, 2 - Preorder, 3 - Inorder, 4 - Delete :");
	fflush(stdin);
	scanf("%d", &opt);
	fflush(stdin);
	while(opt)
	{
		switch(opt)
		{
			case 1 : printf("Enter key to insert : ");
					 scanf("%d", &key);
					 insert_key(key, fp);
                     printf("Completed\n");printf("\n");
					 break;

			case 2 : display_preorder(fp);printf("\n");
					 break;

			case 3 : display_inorder(fp);printf("\n");
					 break;

            case 4 : printf("Enter key to delete : ");
                     scanf("%d", &key);
                     delete_key(key, fp);
                     printf("completed\n");printf("\n");break;
                     
		}
		printf("enter option : ");
		scanf("%d", &opt);
	}
	close_tree(fp);
}
