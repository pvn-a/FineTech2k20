#ifndef a4_h
#define a4_h

#include <stdio.h>

struct node
{
	int key;
	int left_offset;
	int right_offset;
};
typedef struct node node_t;

struct tree
{
	int free_head;
	int root;
};
typedef struct tree tree_t;

// create a file with the filename and initialize the header with tree_t structure
// if the file already exists, just return the file ptr
FILE* init_tree(const char* filename);

// close the file pointed by fp
void close_tree(FILE *fp);

// Space separated keys. Last key followed by '\n'
void display_inorder(FILE *fp);

// Space separated keys. Last key followed by '\n'
void display_preorder(FILE *fp);

// insert the key into the tree in the file
// if the key already exists just return
void insert_key(int key, FILE *fp);

// delete the key from the tree in the file
// the key may or may not exist
void delete_key(int key, FILE *fp);

#endif
