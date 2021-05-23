Fine Techniques Assignment - 4: Binary Search Tree on HardDisk

Name : Ujjwal Kumar
Section : I
SRN : PES1UG19CS546

-------------------------------------------------------------------------------------------------------------------

To Compile the code the following command is used :

gcc -Wall -c A4_PES1UG19CS546.c client.c assignment_4.h
gcc A4_PES1UG19CS546.o client.o
./a.out

-------------------------------------------------------------------------------------------------------------------
Notes :
header.root - offset of the root of the tree
header.free_head - offset of the first free node
Every nodes left_offset contains the offset to its left subtree or -1 and right_Offset contains the offset of its right subtree or -1
Once a node is deleted its link is removed from the parent node, its value is changed to -91919 and left and right offset are -1.
For Insertion :
If the node is the first node to be inserted we traverse to the end of the file which will be just after the header and write it there
then stores its offset in header.root.
If nodes are to be inserted and there is no free node available we seek to the end of the file and then write the node there we store its 
offset in a variable then traverse in the binary search tree where the node needs to be linked with then store its offset to the left or right
of the node depending on the value of the node whether it is greater than or less than the key.
If a free node is there we write the node at that free node instead of the end of file and repeat the above process.
For Deletion :
Three conditions are considered for the root and then the other child nodes
	1. If the node has no children simply removes its link from the parent node and store its offset in the free node list;
	2. If the node has either left or right subtree then connect its parent node to its left or right subtree and pass that to the free node list.
	3. If the node has two children then repalce the values of this node with its inorder successor and remove the link of the inorder successor
	   from it parent and pass it to the free node list.
	   
In the free node list the nodes which are deleted most recently will be inserted with a new node first than the nodes which was deleted earlier
however no extra space will be used unless no free node is available i.e the free node value is -1.
The nodes which are deleted its value is changed to -91919.
Preorder and Inorder are printed recursively. If there are no nodes in the tree then a new line will be printed.
After printing the inorder or preorder the cursor will go the next line in the stdout.

------------------------------------------------------------------------------------------------------------------------

Key Take away from this assignment :
The concept of binary search tree was understood clearly and how it can used for other applications as well by storing it in hard disk.
File handling and the concept of file offset is very well understood and how we can store any tree or linked list within file with the
help of file offsets.
