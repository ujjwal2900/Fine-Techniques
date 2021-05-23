#include<stdio.h>
#include<stdlib.h>
#include"assignment_1.h"

typedef struct mem_block         //Book-keeping structure which keeps record of each block
{
    int alloc_block_size;	//stores the size of the allocated block	
    char enc_status;	//stores the encoding status of each block
    char link;	//stores the next block
}mem_block;

char *p = '\0';
int book_keep_size = sizeof(mem_block);
int tot_size = 0;
void allocate(int n)
{
    p = (char*)malloc(sizeof(char)*n); // allocating memory to the global array p which stores the book-keeping structure
    mem_block* block = (mem_block*)p;
    block->enc_status = '0';
    block->alloc_block_size = n - book_keep_size;
    block->link = '0';
    tot_size = n;
}
void* mymalloc(int size)
{
    if(tot_size > 0)
    {    
    	mem_block* block;
    	int j=0;
    	void* address = NULL;
    	while(j <= tot_size)
    	{	// traverses through the array p
        	block = (mem_block*)(&p[j]);
        	j += book_keep_size;
        	if(block->alloc_block_size < size  || block->enc_status == '1')//Checks the size of the memory block
            		j = j+ block->alloc_block_size;
        	else
        	{
            		address = (void*)(&p[j]);
			j = j+size;
            		if(block->alloc_block_size > size + book_keep_size)// if space for block is not there in the existing memory
            		{
				mem_block* new_block = (mem_block*)(&p[j]);//A new block is created
				new_block->enc_status = '0';
				new_block->alloc_block_size = block->alloc_block_size - size - book_keep_size;
				new_block->link = block->link;
				block->link = (char)j;
				block->alloc_block_size = size;
				block->enc_status = '1';
				return address;
			}
			else{
				block->enc_status= '1';// block size is same as remaining size
				return address;
			}   
        	}
    		}
    	}
    	else
		return NULL;
}
void display_mem_map()
{
	mem_block *block;
	int i = 0;
	while(i < tot_size)
	{// traverses through the array p
		block = (mem_block*)(&p[i]);
		printf("%d\t", i);
		printf("%d\t", book_keep_size);
		printf("0\n");
		i += book_keep_size;
		printf("%d\t", i);
		printf("%d\t", block->alloc_block_size);
		if(block->enc_status == '0')
			printf("2\n"); // 2 if the block is free
		else
			printf("1\n"); // 1 for allocated block
		i = i+block->alloc_block_size;
	}
}
void print_book()
{
    printf("%lu\n", sizeof(mem_block)); // bytes used by the book-keeping structure
}
void myfree(void *b)
{
	mem_block *present = '\0'; 
	mem_block *previous;
	mem_block *link;
	int i = 0, j = 0;
	while(i < tot_size){
		previous = present;
		present = (mem_block*)(&p[i]);
		i += book_keep_size;
		if(b == (void*)(&p[i]))//match the address of the memory-block to be deleted with every block
		{
			if(previous != NULL && previous->enc_status == '0'){
			    if(present->link != -1){//If the next memory-block is there
			        j = i;
			        j += present->alloc_block_size;
			        link = (mem_block*)(&p[j]);
			        if(link->enc_status == '0'){//case : the next memory-block is empty
			            previous->alloc_block_size = previous->alloc_block_size+ (2*book_keep_size) + present->alloc_block_size + link->alloc_block_size;
    					previous->link = link->link;
    					return;
			        }
			        else{//case : the preceding memory-block is not empty
			            previous->alloc_block_size = previous->alloc_block_size+ book_keep_size + present->alloc_block_size;
    					previous->link = present->link;
    					return;
			        }
			    }
			    else{//if this is the last memory-block
			        previous->alloc_block_size = previous->alloc_block_size+ book_keep_size + present->alloc_block_size;
					previous->link = present->link;
					return;
			    }
			}
			else{//case:the previous memory-block is not empty
			    if(present->link != -1){
			        j = i;
			        j += present->alloc_block_size;
			        link = (mem_block*)(&p[j]);
			        if(link->enc_status == '0'){
			            present->alloc_block_size = present->alloc_block_size + book_keep_size + link->alloc_block_size;
    					present->link = link->link;
    					present->enc_status = '0';
			        }
			        else{//If the next memory-block is not empty
			            present->enc_status = '0';
			        }
			    }
			    else{//there is no preceding memory-block
			        present->enc_status = '0';
			    }
			}
		}
		else{
			i = i+present->alloc_block_size;
		}
	}	
}
