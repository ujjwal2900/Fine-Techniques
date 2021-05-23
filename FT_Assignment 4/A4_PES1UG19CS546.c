#include "assignment_4.h"
#include <stdio.h>

static void print_inorder(int offset, FILE *fp);	//prints the inorder traversal of the tree recursively
static void print_preorder(int offset, FILE *fp);	//prints the preorder traversal of the tree recursively
static void free_node(int offset, FILE *fp);	//It maintains the list of the free nodes available
static int duplicate_key(int key, FILE *fp);	//checks if the value is present in the tree or not
FILE* init_tree(const char* filename)
{
	FILE* fp;
	fp = fopen(filename, "r+");
	if(fp == NULL)
	{
		fp = fopen(filename, "w");//if the file is not existing opens the file in write mode
		tree_t header;
		header.free_head = -1;
		header.root = -1;
		fwrite(&header, sizeof(header), 1, fp);// initializes the header i.e root and free_head as -1
		close_tree(fp);
		fp = fopen(filename, "r+");//after initializing the file closes and then opens in append mode
	}
	return fp;
}

void close_tree(FILE *fp)
{
	fclose(fp);
}

void insert_key(int key, FILE *fp)
{
	node_t new_node;node_t temp;
	tree_t header;
	fseek(fp, 0, SEEK_SET);
	fread(&header, sizeof(tree_t), 1, fp);// reades the header which is stored at the 0th position
	new_node.key = key;
	new_node.left_offset = -1;
	new_node.right_offset = -1;
	int offset ;
	
	if(header.root == -1 && header.free_head == -1)	//checks if it is the first node to be inserted in the tree and no free nodes or holes are available
	{
		fseek(fp, 0, SEEK_END);
		offset = ftell(fp);
		fwrite(&new_node, sizeof(new_node), 1, fp);// since it is the very first node it writes at the end i.e just after the header.
		fseek(fp,0, SEEK_SET);
		header.root = offset;	//updates the root with the offset of the node inserted
		fwrite(&header, sizeof(tree_t), 1, fp);	//rwrites the header with the updated root value
	}
	else if(header.free_head == -1)	//if no free_nodes or holes are available in the file
	{
		if( duplicate_key(key, fp) == 1)	//checks if the key is already present or not
		{
			fseek(fp, 0, SEEK_END);
			offset = ftell(fp);
			fwrite(&new_node, sizeof(new_node), 1, fp);	//since no free_node is available in b/w writes it at the end of file
		
			int index = header.root;
		
			while(index != -1)
			{
				fseek(fp, index, SEEK_SET);
				fread(&temp, sizeof(node_t), 1, fp);

				if(key > temp.key)	//traverse the right subtree if the key value is greater than the value in the node
				{
					if(temp.right_offset == -1)
					{
						temp.right_offset = offset;
						fseek(fp, index, SEEK_SET);
						fwrite(&temp, sizeof(node_t), 1, fp);	//write the offset of the node written at the last 
						index = -1;
					}
					else
						index = temp.right_offset;	//traverse further to the right
				}
				else	//traverse the left subtree if the key value is less than the value in the node
				{
					if(temp.left_offset == -1)
					{
						temp.left_offset = offset;
						fseek(fp, index, SEEK_SET);
						fwrite(&temp, sizeof(node_t), 1, fp);	//write the offset of the node written at the last 
						index = -1;
					}
					else
						index = temp.left_offset;	//traverse further to the left
				}
			}	
		}
	}
	else if(header.free_head != -1)	//if holes are available i.e nodes which are deleted or empty node in between
	{
		if(duplicate_key(key, fp) == 1)
		{
			fseek(fp, header.free_head, SEEK_SET);
			fread(&temp, sizeof(temp),1,fp);	//read the offset of the node stored in free_head
			if(temp.left_offset == -1)	// if only free_node or hole is there
			{
				offset = header.free_head;	//copy the address of that node
				header.free_head = -1;
				fseek(fp, 0, SEEK_SET);
				fwrite(&header,sizeof(header),1,fp);	//make the free_head -1 as the node to be inserted will be inserted at that offset
			}
			else		//if multiple holes are there
			{	//takes the offset the node which was deleted most recently and updates the list accordingly
				node_t val; int offset_2=-1;
				if(temp.left_offset != -1)
				{
					fseek(fp, temp.left_offset, SEEK_SET);
					fread(&val, sizeof(node_t), 1, fp);	
					if(val.left_offset == -1)
						offset_2 = header.free_head;
				}
				while(temp.left_offset != -1)
				{
					offset = temp.left_offset;	//finds the offset of the last free node
					fseek(fp, temp.left_offset, SEEK_SET);
					fread(&temp, sizeof(temp),1,fp);
					if(temp.left_offset != -1)
					{
						fseek(fp, temp.left_offset, SEEK_SET);
						fread(&val, sizeof(node_t), 1, fp);	
						if(val.left_offset == -1)
							offset_2 = offset;
					}
				}
			
				fseek(fp, offset_2, SEEK_SET);
				fread(&val, sizeof(val),1,fp);
				val.left_offset = -1;	//updates the value of the previous free node as -1 indicating that the next node was reused
				fseek(fp, offset_2, SEEK_SET);
				fwrite(&val, sizeof(val),1,fp);	//writes the updated offset back to the list
			
			
			}
			fseek(fp, offset, SEEK_SET);
			fwrite(&new_node, sizeof(new_node), 1, fp);		//writes the node to be inserted at the offset value of the last free node
			if(header.root == -1)	//if there are no nodes in the tree
			{
				header.root = offset;	//the root stores the offset value of the new node inserted
				fseek(fp, 0, SEEK_SET);
				fwrite(&header, sizeof(header), 1, fp);		//writes back the updated root value
			}
			else	//if more than 1 nodes are present
			{
				int index = header.root;
				while(index != -1)
				{
					fseek(fp, index, SEEK_SET);
					fread(&temp, sizeof(node_t), 1, fp);

					if(key > temp.key)	//traverses the right subtree
					{
						if(temp.right_offset == -1)
						{
							temp.right_offset = offset;
							fseek(fp, index, SEEK_SET);	
							fwrite(&temp, sizeof(node_t), 1, fp);	//updates the right_offset of the node to the node which was inserted above at the free_node position found
							index = -1;
						}
						else
							index = temp.right_offset;
					}
					else
					{
						if(temp.left_offset == -1)
						{
							temp.left_offset = offset;
							fseek(fp, index, SEEK_SET);
							fwrite(&temp, sizeof(node_t), 1, fp);	//updates the right_offset of the node to the node which was inserted above at the free_node position found
							index = -1;
						}
						else
							index = temp.left_offset;
					}
				}
			}
		}
	}	
}
		
void display_inorder(FILE *fp)
{
	tree_t header;
	fseek(fp, 0, SEEK_SET);
	fread(&header, sizeof(tree_t), 1, fp);
	if(header.root == -1)
		printf("\n");
	else
	{
		print_inorder(header.root, fp);
		printf("\n");
	}
}

static void print_inorder(int offset, FILE *fp)		//prints the inorder recursively
{
	node_t val;
	fseek(fp, offset, SEEK_SET);
	fread(&val, sizeof(node_t), 1, fp);
	
	if(val.left_offset != -1 )
		print_inorder(val.left_offset, fp);
	
	fseek(fp, offset, SEEK_SET);
	fread(&val, sizeof(node_t), 1, fp);
	printf("%d ", val.key);
	
	if(val.right_offset != -1)
		print_inorder(val.right_offset, fp);
		
}

void display_preorder(FILE *fp)
{
	tree_t header;
	fseek(fp, 0, SEEK_SET);
	fread(&header, sizeof(tree_t), 1, fp);
	if(header.root == -1)
		printf("\n");
	else
	{
		print_preorder(header.root, fp);
		printf("\n");
	}
}

static void print_preorder(int offset, FILE *fp)	//prints the preorder recursively
{
	node_t val;
	fseek(fp, offset, SEEK_SET);
	fread(&val, sizeof(node_t), 1, fp);
	
	printf("%d ", val.key);
	
	if(val.left_offset != -1 )
		print_preorder(val.left_offset, fp);
		
	if(val.right_offset != -1)
		print_preorder(val.right_offset, fp);
	
}

void delete_key(int key, FILE *fp)
{
	node_t temp, q, parent, insucc, root;
	parent.left_offset =0; parent.right_offset = 0;
	tree_t header; int offset; int p_offset;	int free_index;
	fseek(fp, 0, SEEK_SET);
	fread(&header, sizeof(tree_t), 1, fp);
	if(header.root == -1)	//if there is no node in the tree then it returns as there is no node to be deleted
		return;
	int index = header.root;
	fseek(fp, index, SEEK_SET);
	fread(&temp, sizeof(node_t), 1, fp);	//first reads the root of the tree
	root = temp;
	while(index !=-1 || temp.key != key)	//the loop runs unless we find the key to be deleted and its offset
	{
		parent = temp;	//stores the parent node of the key
		fseek(fp, index, SEEK_SET);
		fread(&temp, sizeof(node_t), 1, fp);
		
		if(key > temp.key)	//traverse the right subtree if the value is more
		{
			p_offset = index;	//stores the offset of the parent node
			index = temp.right_offset;
		}
		else if(key < temp.key)	// traverse the left subtree if the value is less
		{
			p_offset = index;	//stores the offset of the parent node
			index = temp.left_offset;
		}
		if(key == temp.key )	//breaks out of the loop if the key is found
			break;
		if(index == -1)		//breaks out of the the loop if the key is not found
			break;
	}
	
	fseek(fp, p_offset, SEEK_SET);
	fread(&parent, sizeof(node_t), 1, fp);	//reads the parent node of the key to be deleted
	
	if(temp.key != key)		//if the key is not found do nothing return
		return;
			
	else if( root.key == temp.key )		//if the key to be deleted is the root node
	{
		if(temp.left_offset == -1 && temp.right_offset == -1)	//if the root node does t=not have any children
		{
			free_index = header.root;	
			header.root = -1;	//make the root as -1
			fseek(fp, 0, SEEK_SET);
			fwrite(&header, sizeof(header), 1, fp);	//write the header back to file 
			free_node(free_index, fp);	//pass the offset of the node to be deleted to be added to the free_node list
		}
		else if( (temp.left_offset != -1 && temp.right_offset == -1) || (temp.left_offset == -1 && temp.right_offset != -1))//if the root node has one child
		{
			if(temp.left_offset == -1)	//no left child
			{
				free_index = header.root;
				header.root = temp.right_offset;	//make the root point to the right node of the root node which will become the new root
				fseek(fp, 0, SEEK_SET);
				fwrite(&header, sizeof(header), 1, fp);
				free_node(free_index, fp);	//pass the offset of the deleted node to be added to the free_node list
			}
			if(temp.right_offset == -1)	//no right child
			{
				free_index = header.root;
				header.root = temp.left_offset;	//make the root point to the left node of the root node which will become the new root
				fseek(fp, 0, SEEK_SET);
				fwrite(&header, sizeof(header), 1, fp);
				free_node(free_index, fp);	//pass the offset of the deleted node to be added to the free_node list
			}
		}
		else if(temp.left_offset !=-1 && temp.right_offset != -1)// if the root node has both left and right nodes
		{
			int offset_2 = temp.right_offset; node_t insucc_par;
			offset = temp.right_offset;
			fseek(fp, offset, SEEK_SET);
			fread(&insucc, sizeof(node_t), 1, fp);
			while(insucc.left_offset != -1)		//finds the inorder successor of the root node
			{
				offset = insucc.left_offset;
				fseek(fp, insucc.left_offset, SEEK_SET);
				fread(&insucc, sizeof(node_t), 1, fp);
				if(insucc.left_offset != -1)	//finds the parent of the inorder successor of the root node
				{
					fseek(fp, insucc.left_offset, SEEK_SET);
					fread(&insucc_par, sizeof(node_t), 1, fp);	
					if(insucc_par.left_offset == -1)
					offset_2 = offset;
				}	
			}
			fseek(fp, offset_2, SEEK_SET);
			fread(&insucc_par, sizeof(node_t), 1, fp);
			fseek(fp, offset, SEEK_SET);
			fread(&q, sizeof(node_t), 1, fp);
			if(q.key == insucc_par.key)	//if there is no left node
			{
				q.left_offset = temp.left_offset;
				header.root = offset;	//updates the offset stored in the root to the offset of the inorder successor
				fseek(fp, 0, SEEK_SET);
				fwrite(&header, sizeof(header), 1, fp);
				fseek(fp, offset, SEEK_SET);
				fwrite(&q, sizeof(q), 1, fp);
				free_index = index;
				free_node(free_index, fp);	//pass the offset of the deleted node to be added to the free_node list
			}
			else	//copy the value stored in the insuccessor to the root and then delete the insuccessor or remove the link which it has with its parent
			{
				insucc_par.left_offset = -1;	//removing the link of the insuuccessor with its parent
				fseek(fp, offset_2, SEEK_SET);
				fwrite(&insucc_par, sizeof(insucc_par), 1, fp);
				temp.key = q.key;	//copying the value of the insuccessor to root
				fseek(fp, header.root, SEEK_SET);
				fwrite(&temp, sizeof(temp), 1, fp);
				free_index = offset;
				free_node(free_index, fp);	//pass the offset of the insuccessor to be added to the free_node list
			}
		}
	}

	else if(temp.left_offset == -1 && temp.right_offset == -1)	//if the node does not have any children then simply remove the node
	{
		if(key > parent.key)//making the offset of the node stored in the parent to be -1 thus deleting it
			parent.right_offset = -1;
		if(key < parent.key)
			parent.left_offset = -1;
		fseek(fp, p_offset, SEEK_SET);
		fwrite(&parent, sizeof(parent), 1, fp);
		free_index = index;
		free_node(free_index, fp);	//passing the offset of the deleted node to the free list
	}
	else if( (temp.left_offset != -1 && temp.right_offset == -1) || (temp.left_offset == -1 && temp.right_offset != -1))// if the node has only either left or right subtrees
	{
		if(temp.left_offset != -1)// if the node has left subtree make the parent point to the left subtree
		{
			if(key > parent.key)
				parent.right_offset = temp.left_offset;
			if(key < parent.key)
				parent.left_offset = temp.left_offset;
		}
		else	//if the node has right subtree make the parent point to the right subtree
		{
			if(key > parent.key)
				parent.right_offset = temp.right_offset;
			if(key < parent.key)
				parent.left_offset = temp.right_offset;
		}
		fseek(fp, p_offset, SEEK_SET);
		fwrite(&parent, sizeof(parent), 1, fp);	//rewrite the value of the updated parent node in the file
		free_index = index;
		free_node(free_index, fp);	////passing the offset of the deleted node to the free list
	}
	else if(temp.left_offset != -1 && temp.right_offset != -1)	//if the node has both left and right subtree
	{
		int offset_2 = temp.right_offset; node_t insucc_par;
		offset = temp.right_offset;
		fseek(fp, offset, SEEK_SET);
		fread(&insucc, sizeof(node_t), 1, fp);
		while(insucc.left_offset != -1)	//find the inorder successor of the node
		{
			offset = insucc.left_offset;
			fseek(fp, insucc.left_offset, SEEK_SET);
			fread(&insucc, sizeof(node_t), 1, fp);
			if(insucc.left_offset != -1)	//finds the parent of the inorder successor
			{
				fseek(fp, insucc.left_offset, SEEK_SET);
				fread(&insucc_par, sizeof(node_t), 1, fp);	
				if(insucc_par.left_offset == -1)
					offset_2 = offset;
			}	
		}
		fseek(fp, offset_2, SEEK_SET);
		fread(&insucc_par, sizeof(node_t), 1, fp);
		fseek(fp, offset, SEEK_SET);
		fread(&q, sizeof(node_t), 1, fp);
		
		if(q.key == insucc_par.key)	//if there is no left node
		{
			if(key > parent.key)
				parent.right_offset = temp.right_offset;
			if(key < parent.key)
				parent.left_offset = temp.right_offset;
			fseek(fp, p_offset, SEEK_SET);
			fwrite(&parent, sizeof(parent), 1, fp);	//updates the offset stored in the parent node to the offset of the inorder successor
			q.left_offset = temp.left_offset;
			fseek(fp, offset, SEEK_SET);
			fwrite(&q, sizeof(temp), 1, fp);
			free_index = index;
			free_node(free_index, fp);
		}
		else 	//removes the link of the inorder successor from its parent and copies it to the node which has to be deleted
		{
			insucc_par.left_offset = -1;
			fseek(fp, offset_2, SEEK_SET);
			fwrite(&insucc_par, sizeof(insucc_par), 1, fp);
		
			temp.key = q.key;
			fseek(fp, index, SEEK_SET);
			fwrite(&temp, sizeof(temp), 1, fp);
			free_index = offset;
			free_node(free_index, fp);
		}
	}
}

static void free_node(int offset, FILE *fp)	//maintains the list of the free node
{
	tree_t header;	node_t temp,t;
	fseek(fp, 0, SEEK_SET);
	fread (&header, sizeof(header),1,fp);

	temp.key = -91919;		//changing the value of the node which is deleted to -91919
	temp.left_offset = -1;
	temp.right_offset = -1;
	fseek(fp, offset, SEEK_SET);
	fwrite(&temp, sizeof(temp), 1, fp);
	if(header.free_head == -1)	//if there are no free nodes stores and its the first one
	{
		header.free_head = offset;	//updates the value of free head with the offset of the node deleted and writes back to the file
		fseek(fp, 0, SEEK_SET);
		fwrite(&header, sizeof(header), 1,fp);
	}
	else	//if more than 1 free nodes are there then adds the offset of the next free node to the left offset of the previous node thus maintaining the list
	{
		int offset_2;
		fseek(fp, header.free_head, SEEK_SET);
		fread(&t, sizeof(temp), 1, fp);
		offset_2 = header.free_head;
		while(t.left_offset != -1)
		{
			offset_2 = t.left_offset;
			fseek(fp, t.left_offset, SEEK_SET);
			fread (&t, sizeof(t),1,fp);
		}
		t.left_offset = offset;		//stores the offset of the deleted node in the left_offset of the previous deleted node
		fseek(fp, offset_2, SEEK_SET);
		fwrite(&t,sizeof(t),1,fp);
	}
}

static int duplicate_key(int key, FILE *fp)	//this functions traverses through the tree and checks if the key is present in the tree or not
{
	tree_t header; node_t temp;
	fseek(fp, 0, SEEK_SET);
	fread(&header, sizeof(header), 1, fp);
		
	int index = header.root;
	while(index != -1)
	{
		fseek(fp, index, SEEK_SET);
		fread(&temp, sizeof(node_t), 1, fp);
		if(key > temp.key)
		{
			if(temp.right_offset == -1)
			{
				return 1;	//return 1 if the value is not present
				index = -1;
			}
			else
				index = temp.right_offset;
		}
		else if(key < temp.key)
		{
			if(temp.left_offset == -1)
			{
				return 1;	//return 1 if the value is not present
				index = -1;
			}
			else
				index = temp.left_offset;
		}
		else if(key == temp.key)
			return 0;	//return 0 if the value is already present
	}
	return 1;
}

