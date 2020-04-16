#include<stdio.h>
#include<stdlib.h>
#include"assignment_4.h"

node_t reinit_node(node_t temp, int data, int left_offset, int right_offset); //reinitializes a node
void update_header(FILE *fp, int free_head, int root); //update the header contents at any point of time
void update_node(FILE *fp, int pos, int data, int left_offset, int right_offset); // update the contents of a node at any point of time, given pos
int total_nodes(FILE *fp);// finds the total number of nodes
void disp_node(node_t *x);// display contents of a node
void preorder(FILE *fp, int k); //recurssive function to display nodes in preorder
void inorder(FILE *fp, int k); //recurssive function to display nodes in inorder
int search(FILE* fp, int key, int k); // search for an element in the tree
int insert(FILE *fp, int key, int k); // recurssive function that return the pos of node to the left or right of which, newnode has to be inserted
void seq_disp(FILE *fp); //used for debugging. sequentially prints all the contents of the file, in their position based order
#define SIZE(x) sizeof(tree_t)+((x-1)*sizeof(node_t))  //offsetting function
#define empty -9999 //this value is inserted into deleted node, also used to check if key to be insereted is already present
#define debug 0 //make this to 1 for amazing debugging experience
#define debug1 0 //additional debugging in delete part of the code

void seq_disp(FILE *fp) // just a seq_disp sequential print
{
	node_t x;
	fseek(fp, SIZE(1), SEEK_SET); int k=1;
	while(fread(&x, sizeof(node_t), 1, fp) > 0)
	{
		k++;
		disp_node(&x);
		fseek(fp, SIZE(k), SEEK_SET);	
	}
}

node_t reinit_node(node_t temp, int data, int left_offset, int right_offset)
{
	temp.key = data;
	temp.left_offset = left_offset;
	temp.right_offset = right_offset;
	return temp;
}

void update_node(FILE *fp, int pos, int data, int left_offset, int right_offset)// updates any node, given its *sequential file position*
{
	node_t temp;
	fseek(fp, SIZE(pos), SEEK_SET); //point the pointer to pos in file
	fread(&temp, sizeof(node_t), 1, fp); //read 1 node from that position
	temp.key = data;
	temp.left_offset = left_offset;
	temp.right_offset = right_offset;
	fseek(fp, SIZE(pos), SEEK_SET); //point again to pos
	fwrite(&temp, sizeof(node_t), 1, fp); //rewrite updated node
}

void update_header(FILE *fp, int free_head, int root) // updates the content of header given root and free_list values
{
	tree_t h;
	fseek(fp, 0, SEEK_SET);//point to header[]
	fread(&h, sizeof(tree_t), 1, fp);//read header[]
	h.free_head = free_head; //update free_head
	h.root = root; //update_root
	fseek(fp, 0, SEEK_SET);//point to beginning of file
	fwrite(&h, sizeof(tree_t), 1, fp);//rewrite header with changes
}

void disp_header(FILE *fp) // displays the content of header
{
	tree_t h;
	fseek(fp, 0, SEEK_SET);//point to header[]
	fread(&h, sizeof(tree_t), 1, fp);//read header[]
	printf("free_head: %d  root: %d\n", h.free_head, h.root );
}

void disp_node(node_t *x) // display content of nodes
{
		if(debug)
			printf("key: %d  left: %d  right: %d\n",x->key,x->left_offset,x->right_offset);
		else
			printf("%d ",x->key);
		
}

int total_nodes(FILE *fp) //finds the toal number of nodes in the BST at any given point of time, given fp
{
	int k = 0; node_t temp;
	fseek(fp, SIZE(k+1), SEEK_SET);
	while(fread(&temp, sizeof(node_t), 1, fp) > 0) //!feof(fp)
	{
		k++;
		fseek(fp, SIZE(k+1), SEEK_SET);		
	}
	return k;
}

FILE* init_tree(const char* filename) // probably done
{
	FILE* fp;
	fp = fopen(filename, "r+"); //change this to r+ later
	if(fp == NULL)
	{
		if(debug) printf("Error: for r+\n");
		fp = fopen(filename, "w+");
		if(fp == NULL)
		{
			printf("Fatal Error: for w+ ->> EXIT\n");
			exit(1);
		}
		else
		{
			if(debug) printf("Success first time: for w+\n");
			tree_t h; h.free_head = -1; h.root = -1; fseek(fp, 0, SEEK_SET); fwrite(&h, sizeof(tree_t), 1, fp);
			//update_header(fp, -1, -1);
			return fp;
		}
	}
	else
	{	if(debug) printf("SUCCESS: already present for r+\n");
		return fp;
	}
	
}

void close_tree(FILE *fp) //probably done
{
	fclose(fp);
}

void inorder(FILE *fp, int k) //recursive funtion to find inorder of a BST
{ 
	if (k != -1) 
	{
		node_t temp;
		fseek (fp, SIZE(k), SEEK_SET);
		fread (&temp, sizeof(node_t), 1, fp);
		inorder (fp, temp.left_offset);
		disp_node(&temp);
		inorder (fp, temp.right_offset);
	}
}

void preorder(FILE *fp, int k) //recursive funtion to find inorder of a BST
{
	if (k != -1) 
	{
    		node_t temp;
		fseek(fp, SIZE(k), SEEK_SET);
		fread(&temp, sizeof(node_t), 1, fp);
		disp_node(&temp);
		preorder(fp, temp.left_offset);
		preorder(fp, temp.right_offset);
	}
}

void display_inorder(FILE *fp) // calls inorder() with fp and tree's root as params
{
	tree_t header;   
	fseek(fp, 0, SEEK_SET);
	fread(&header, sizeof(tree_t), 1, fp);
	if(header.root == -1) 
		return;
	if(debug)
	{
		printf("\n---------------- SEQUENTIAL FILE CONTENTS ------------------\n");
		seq_disp(fp);printf("\n\n");
		printf("\n----------HEADER-------------\n");
		disp_header(fp);
		printf("-----------------------------\n");
		printf("------------------------------------------------------------\n\n");
	}
    	inorder(fp, header.root);
	printf("\n");
}

void display_preorder(FILE *fp) // calls preorder() with fp and tree's root as params 
{
	tree_t header;   
	fseek(fp, 0, SEEK_SET);
	fread(&header, sizeof(tree_t), 1, fp);
	if(header.root == -1) 
		return;
	if(debug)
	{
		printf("\n---------------- SEQUENTIAL FILE CONTENTS ------------------\n");
		seq_disp(fp);printf("\n\n");
		printf("\n----------HEADER-------------\n");
		disp_header(fp);
		printf("-----------------------------\n");
		printf("------------------------------------------------------------\n\n");
	}
   	preorder(fp, header.root);
	printf("\n");
}

int insert(FILE *fp, int key, int k)
{
    node_t t;
    fseek(fp, SIZE(k), SEEK_SET);
    if(fread(&t, sizeof(node_t), 1, fp) > 0)
    {
    	if(key < t.key)
    	{
			if(debug) printf("LEFT\n");
    		if(t.left_offset!=-1)
    			insert(fp, key, t.left_offset);
    		else
    			return k;
    	}
    	else if(key > t.key)
    	{
			if(debug) printf("RIGHT\n");
    		if(t.right_offset!=-1)
    		 	insert(fp, key, t.right_offset);
    		else
    			return k;
    	}
		else
			return empty;		
    }
}


void insert_key(int key, FILE *fp)
{
    if(debug) 
    {
	printf("\n\n============================================================\n");
	printf("\t\t\tINSERT :  %d\n", key);
	printf("============================================================\n");
    }
    int no_of_nodes = total_nodes(fp);
    node_t temp; int k;
    tree_t header;
    fseek(fp, 0, SEEK_SET);
    fread(&header, sizeof(tree_t), 1, fp);
    temp = reinit_node(temp, key, -1, -1); //reinit a node with new key and left_offset=right_offset=-1
    if (header.root == -1 && header.free_head == -1) // the first node in the file ever
    {
	if(debug)  printf("the first node in the file ever\n");
        fseek(fp, SIZE(1), SEEK_SET);
	fwrite(&temp, sizeof(node_t), 1, fp);
	update_header(fp, -1, 1); // i have only a root, but no free_head
        return;
    }
    else// very first node alrady exists
    {
	node_t check, dump; int pos;
	fseek(fp, 0, SEEK_SET);
	fread(&header, sizeof(tree_t), 1, fp);
	if(header.free_head == -1) //no free nodes, insert node in the end
		k = no_of_nodes +1;
	//else if(header.root==-1 && heder.free_head!=-1)
	else// there is/are free nodes in the file, into which a node can be inserted/updated
	{
		k = header.free_head;
		fseek(fp, SIZE(header.free_head), SEEK_SET);
		fread(&dump, sizeof(node_t), 1, fp);
		if(header.root==-1)////////
			header.root = header.free_head;
		update_header(fp, dump.right_offset, header.root);
	}
	fseek(fp, 0, SEEK_SET);//these 8 lines were present after SEQ file content block
	fread(&header, sizeof(tree_t), 1, fp);
    	pos = insert(fp, key, header.root); //pos of the node to the left/right of which node, kth node has to be inserted
	//printf("pos: %d\n", pos);
	if(pos == empty)
	{
		if(debug) printf("ELEMENT ALREADY PRESENT\n");
		return;
	}
        fseek(fp, SIZE(k), SEEK_SET);//this is changing 
        fwrite(&temp, sizeof(node_t), 1, fp);
	if(debug) printf("Node written onto pos: %d\n",k);
	if(debug)
	{
		printf("\n---------------- SEQUENTIAL FILE CONTENTS ------------------\n");
		seq_disp(fp); //check if the new node got inserted in the end
		printf("------------------------------------------------------------\n\n");
	}
   	fseek(fp, SIZE(pos), SEEK_SET);
	fread(&check, sizeof(node_t), 1, fp);
    	if(key < check.key && check.key != empty) // update left_offset 
	{
		//disp_node(&check);
		if(debug)  printf("%d inserted to the left of %d\n",key,check.key);
		update_node(fp, pos, check.key, k, check.right_offset);
	}
	else if(key > check.key && check.key != empty)
	{
		//disp_node(&check);
		if(debug)  printf("%d inserted to the right of %d\n",key, check.key);
		update_node(fp, pos, check.key, check.left_offset, k);
	}
	if(debug)
	{
		printf("\n---------------- SEQUENTIAL FILE CONTENTS ------------------\n");
		seq_disp(fp);printf("\n");
		printf("\n----------HEADER-------------\n");
		disp_header(fp);
		printf("-----------------------------\n");
		printf("------------------------------------------------------------\n\n");
	}	
    }
}

int search(FILE* fp, int key, int k) // search for a key ina  file
{
    node_t t;
    //printf("k : %d\n", k);
    fseek(fp, SIZE(k), SEEK_SET);
    if(k!=-1 && fread(&t, sizeof(node_t), 1, fp) > 0)
    {
	if(key == t.key)
		return k;
    	else if(key < t.key)
    		return search(fp, key, t.left_offset);
    	else //(key > t.key)
    		return search(fp, key, t.right_offset);
    }
}

int minValueNode(FILE *fp, int pos) // equivalent to finding th inorder_successor, finds the pos of node which has min key value
{ 
	node_t temp;
	fseek (fp, SIZE(pos), SEEK_SET);
	while(fread (&temp, sizeof(node_t), 1, fp)>0 && temp.left_offset!= -1)
	{
		pos = temp.left_offset; // keep going left
		fseek(fp, SIZE(pos), SEEK_SET);
	}
	return pos;//return position of min key value node, which is obviously the leftmost node in a right sub tree of a BST
} 


int deleteNode(FILE *fp, int pos, int key) 
{ 
	node_t root, temp;
	tree_t header;
	fseek (fp, SIZE(pos), SEEK_SET);
	if(debug1) printf("pos: %d\t key: %d\n", pos, key);
	if((fread(&root, sizeof(node_t), 1, fp) > 0))
	{
		if(key < root.key) // lies in left subtree
		{
			//root.left_offset = deleteNode(fp, root.left_offset, key);
			update_node(fp, pos, root.key, deleteNode(fp, root.left_offset, key), root.right_offset);
			if(debug1) disp_node(&root); 
		}
		else if (key > root.key) // lies in right subtree		
		{
			//root.right_offset = deleteNode(fp, root.right_offset, key);
			update_node(fp, pos, root.key, root.left_offset, deleteNode(fp, root.right_offset, key));
			if(debug1) disp_node(&root);  
		}
		else // key found
		{ 
			// node with only one child or no child 
			if (root.left_offset == -1) //only has right child
			{ 
				int hold = root.right_offset; 
				//free(root);
				fseek(fp, 0, SEEK_SET);
				fread(&header, sizeof(tree_t), 1, fp);
				update_node(fp, pos, empty, -1, header.free_head);
				update_header(fp, pos, header.root);
				return hold; 
			} 
			else if (root.right_offset == -1) // only has left child
			{ 
				int hold = root.left_offset; 
				//free(root);
				fseek(fp, 0, SEEK_SET);
				fread(&header, sizeof(tree_t), 1, fp);
				update_node(fp, pos, empty, -1, header.free_head);
				update_header(fp, pos, header.root);
				return hold; 
			} 
			//parent nodes: 2 children => get inorder_successor i.e minvalue node from the right subtree
			int pos2 = minValueNode(fp, root.right_offset); //position of minvalue(right sub tree)	
			fseek(fp, SIZE(pos2), SEEK_SET);
			fread(&temp, sizeof(node_t), 1, fp); 	
			if(debug1) {printf("temp: \t");disp_node(&temp);}
			// fseek (fp, SIZE(pos), SEEK_SET);
			// fread(&root, sizeof(node_t), 1, fp);
			// Copy the inorder successor's key to this node 
			if(debug) printf("Inorder successor of %d  => pos2: %d\n",root.key, pos2);
			update_node(fp, pos, temp.key, root.left_offset, root.right_offset);//root.key = temp.key;
			
			//root.right_offset = deleteNode(fp, root.right_offset, temp.key);
			//if at any point of time something feels fishy fseek(to 1), read root again
			update_node(fp, pos, temp.key, root.left_offset, deleteNode(fp, root.right_offset, temp.key));// Delete the inorder successor 
			//printf("Delete the inorder successor\n");
			//disp_node(&root); 
		}
		return pos; //root position
	}
} 

void delete_key(int key, FILE *fp)
{	
	tree_t t; int k;
	node_t temp, final;
	if(debug) 
	{
		printf("\n\n============================================================\n");
		printf("\t\t\tDELETE :  %d\n", key);
		printf("============================================================\n");
	}
	fseek(fp, 0, SEEK_SET);
	fread(&t, sizeof(tree_t),1 ,fp);
	if(t.free_head == -1 && t.root == -1)
	{
		if(debug) printf("NO NODE IN EXISTENCE AT ALL\n");
		return ;
	}
	int search_pos = search(fp, key, t.root);
	if(debug) printf("search_pos: %d\n",search_pos);
	if(search_pos == 0 || search_pos == -1)
	{
		if(debug) printf("ELEMENT NOT FOUND\n");
	 	return ;
	}
	else
		k = deleteNode(fp, t.root, key);////
	fseek(fp, 0, SEEK_SET);
	fread(&t, sizeof(tree_t),1 ,fp);
	update_header(fp, t.free_head, k);
	if(debug)
	{
		printf("\n----------HEADER-------------\n");
		disp_header(fp);
		printf("-----------------------------\n");
		printf("\n---------------- SEQUENTIAL FILE CONTENTS ------------------\n");
		seq_disp(fp); //check if the new node got inserted in the end
		printf("------------------------------------------------------------\n\n");

	}
}
