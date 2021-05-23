FINE TECHNIQUES
ASSIGNMENT -1 MEMORY MANAGER
Name : Ujjwal Kumar

    1. Allocation policy used : First Fit
In this method, first request claims the first available memory with space more than or equal to it’s size. The pointer doesn’t search for appropriate partition but just allocate the job to the nearest memory partition available with sufficient size. It always search for empty location from the beginning of the memory block.
     
    2. It first dynamically allocates memory to the global char pointer using malloc.
It then makes a new book with index 0 and size of the block with the size of the book keeping structure.
For subsequent memory requests it checks from the beginning if any block is free or not and checks if the size is less than or equal to the size of the block to be allocated. If an empty block is not present then a new memory-block is created.It then then updates the values of the fields in the present book and return the address.
To delete the memory allocated the address of the pointer is passed as the parameter of the function.
It then traverses through the array and finds if the block with the address is present or not.
If found the following operation takes place.
It checks for the different condition if the next block is present or not and if its present then is it empty or not. It merges the blocks if two continuous memory-blocks are empty.
If the next memory-block is not empty then it just updates the memory block details in the structure pointer.

    3. Book Keeping Structure : 
alloc_block_size : It stores the size of the allocated block
enc_status : stores the encoding status of the memory blocks whether its empty, occupied by the book keeping or memory requested.
Link : Stores 0 if there is no next memory-block, or else it stores the index of the next memory-block
tot_size : stores the total memory allocated
mem_block : name of the book keeping structure
To Compile :
gcc -Wall -c sanity_client.c assignment_1.h
gcc -Wall -c A1_FF_PES1UG19CS546.c
gcc A1_FF_PES1UG19CS546.o sanity_client.o
./a.out
