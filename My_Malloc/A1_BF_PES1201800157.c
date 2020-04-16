#include<stdio.h>
#include<stdlib.h>
#include "assignment_1.h"

char *p;
int size;

enum stat{available,allocated};

typedef struct book
{
    struct book *prev; //pointer to previous book structure 
    struct book *next; //pointer to next book structure
    int mem_size; // size of memory, from p allocated  
    enum stat status;// 0-free----1-allocated
}book;
static void init(book *ptr, book *next, book* prev, int size, int flag); //init(ptr,next,prev,size,flag)


static void init(book *ptr, book *next, book* prev, int size, int flag) //book structure initializations
{
        ptr->next=next;
        ptr->prev=prev;
        ptr->mem_size=size;
        ptr->status=flag;
}

void allocate(int n)
{
    p=(char*)malloc(sizeof(char)*n);
    size=n;
    if(n<=sizeof(book))
        {printf("Memory too low to allocate a book\n"); return;}
    book *first=(book*)p; //first book structure
    init(first,NULL,NULL,size-sizeof(book),available);
}

void* mymalloc(int size)
{
    //printf("MYMALLOC : %d\n",size);     //uncomment this line for easy debuggin and checking
    void *ret_ptr; //to be returned to caller(final return pointer)
    char *position; //position the pointer to the start of book structure (and also for typecasting )
    int alloc_size; // always search for sizeof(book) + size
    int best_size;  // best alloc_size found so far while going through the entire memory
    int best_size1; // best size found so far while going through the entire memory

//best1 ---- anything related with this keeps a track of that book structure which, has the least ( size <= book->mem_size < alloc_size)
//best  ---- anything related with this keeps a track of that book structure which, has the least (book->mem_size>=alloc size)
//both of these are compared to give the best fit of the seeked memory block



    book *curr = NULL;  // curr node 
    book *best = NULL;  // best node found during the best fit algorithm for alloc_size 
    book *best1=NULL;   // best node found during the best fit algorithm for size
    book *temp = NULL; //general usage
    
    if(size<=0)//faulty size
        return NULL;

    alloc_size=size+sizeof(book);
    curr=(book*)p; // head or first book struct in char *p stored in curr
    best_size=0; best_size1=0;

    while(curr) //see if curr book struct is NOT NULL
    {
        if(curr->status==available) //check if book is free
        {
            if(curr->mem_size>=alloc_size && (curr->mem_size < best_size || best_size==0))//best fit condition
            {       //printf("Hello/n");
                    best_size=curr->mem_size;//so far this is the best_size found
                    best=curr;//the best book encountered so far is this
                    //if(curr->mem_size==alloc_size)
                    //    break;
            }
            

            if ((curr->mem_size < alloc_size && curr->mem_size >=size) && (curr->mem_size < best_size1 || best_size1==0))
            {
                //printf("ENtered\n");
                //printf("\nin1");
                best_size1=curr->mem_size;//so far this is the best_size found
                    best1=curr;//the best book encountered so far is this
                    //if(curr->mem_size==size)
                        //break;                          
            }            
        }
        curr=curr->next;
    }

    if(best==NULL && best1==NULL)
        printf("\nAllocation failed: No suitable memory found\n");

    else if(best1!=NULL && (best==NULL || best1->mem_size < best->mem_size))//taking advantage of short circuiting here
    {
        /*
         In case there’s no space to keep a bookkeeping structure for a small amount 
         of free space, make sure that the free space is allocated to the block before 
         (allocated block on the left). 
         Since this is a best fit algorithm, lets say there are two free spaces 50 bytes and 40 bytes.
         Assume sizeof(book)=24bytes. So when I say malloc(20) I either need (20+24=44) from 50 bytes or(40 bytes full instead of 20)
         Obviously best fit needs to give complete 40 . Instead of allocating a book and keeping 6 bytes free
         Thus the above condition hecks for this. 
         best1 considers cases of just turning the status from free to allocated.
         best considers cases wgere u need a book structure + size to be allocated

         Uncomment the below para for the best experience
         */


        /*
        if(size!=best1->mem_size)
            printf("No book created:: Asked for: %d ---- Instead given: %d\n",size,best1->mem_size);
        else
            printf("No book created:: \n");
        */


        init(best1,best1->next,best1->prev,best1->mem_size,allocated);
        position=(char*)best1;
        ret_ptr=position + sizeof(book);
    }
    else
    {
        if(best_size>alloc_size)
        {
            curr=(book*)((char*)best+alloc_size); //position 16 bytes structure ahead of best
            init(curr,best->next,best,(best_size-alloc_size),available);//initialise the created book-keeper
            temp=curr->next; //initialise the next structure that comes after curr
            if(temp!=NULL)
                temp->prev=curr;
            init(best,curr,best->prev,(alloc_size-sizeof(book)),allocated);//reinitialise best again
            position=(char*)best;
            ret_ptr=position + sizeof(book); //final return address of mem block
        }
        else//best_size is equal to ((sizeof(book))+required) make that structure itself accomodable
        {
            //printf("entered here \n");
            best->status=allocated;
            position=(char*)best;
            ret_ptr=position+sizeof(book);
        }//this gives lesser insights 
        
    }
    return ret_ptr;
}


void myfree(void *b)//free the block pointed to by the parameter
{
    
    book *ptr;
    book *prev, *next;
    int temp_size_holder;

    if(ptr==NULL)
        return;
      
    ptr=(book*)((char*)b-sizeof(book)); //position the pointer to the beginning of the book structure's address
    if(ptr->status==available)
        return;
    //printf("MYfree %d\n",ptr->mem_size); //uncomment this line for easy debuggin and checking
    next=ptr->next;
    prev=ptr->prev;

    if(next==NULL)//if it ever happens just in case
    {
        
        if(prev==NULL)//only 1 book record left, like the same when allocate() was called
        {
            //first=last=NULL;
            printf("Minimal Case\n");
            return;
        }
        else
        {
            if(prev->status==allocated)//last book struct is allocated this frees it 
            {
                ptr->status=available;
            }
            else
            {
                ptr->status=available;
                //prev->mem_size=prev->mem_size + sizeof(book) + ptr->mem_size;
                ptr->prev->next=ptr->next;
                 ptr->prev->mem_size+=ptr->mem_size+sizeof(book);
                 ptr=ptr->prev;
                 next=ptr->next;
                 prev=ptr->prev;
            }
            
        }
        
    }
    if(!(prev!=NULL && next==NULL)) //Coalesce free spaces
    {
        ptr->status=available;
        if(prev!=NULL && prev->status==available)//previous + current free fusion
        {
            ptr->prev->next=ptr->next;
            ptr->next->prev=ptr->prev;
            ptr->prev->mem_size+=ptr->mem_size+sizeof(book);
            ptr=ptr->prev;
            next=ptr->next;
            prev=ptr->prev;
        }
        if(next!=NULL && next->status==available)//current + next free fusion => used for case like [free,allocated,free]
        {
            temp_size_holder=ptr->next->mem_size;
            ptr->next=ptr->next->next;
            //printf("entered");
            if(ptr->next!=NULL)
                 ptr->next->prev=ptr;
            ptr->mem_size+=temp_size_holder+sizeof(book);
        }
    }


} 

void print_book()// prints bytes used by the bookkeeping structure
{
    printf("%ld\n",sizeof(book));
} 

void display_mem_map()
{
    book *temp=(book*)p;
    int offset=0;
    while(temp!=NULL)
    {
        printf("%d\t%ld\tbook\n",offset,sizeof(book));
        if(temp->status==available)
            printf("%ld\t%d\tfree\n",offset+sizeof(book),temp->mem_size);
        else
            printf("%ld\t%d\tallocated\n",offset+sizeof(book),temp->mem_size);

        offset+=sizeof(book)+temp->mem_size;
        temp=temp->next;
    }
}
