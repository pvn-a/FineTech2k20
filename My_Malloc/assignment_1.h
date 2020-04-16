#ifndef assignment1_h
#define assignment1_h

extern char *p;
extern int size;

void allocate(int n); //function to allocate memory for the global array p, n number of bytes long.

void* mymalloc(int size); //function to allocate a block of size "size" from p

void myfree(void *b); //free the block pointed to by the parameter

void print_book(); // prints bytes used by the bookkeeping structure

void display_mem_map(); // print the memory array p in the following format
// start_addr   block_in_bytes  status

// sample output based on sanity_client
// allocate(200);

// mymalloc(30 * sizeof(char));
// display_mem_map();
// 0       16      book
// 16      30      allocated
// 46      16      book
// 62      138     free

// look at the screenshot in the google docs sample output for entire output

#endif
