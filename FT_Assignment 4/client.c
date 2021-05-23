#include "assignment_4.h"
#include <stdio.h>

int main()
{
	FILE *fp = init_tree("bst.dat");
	int inp = -1; int key; tree_t header; node_t val;
	while(inp != 0)
	{
		printf("1. To insert  2.To delete  3.To display free node 4. To display inorder&preorder :");
		scanf("%d",&inp);
		switch (inp)
		{
		case 1:
			scanf("%d",&key);
			insert_key(key,fp);
			break;
		case 2:
			scanf("%d",&key);
			delete_key(key,fp);
			break;
		case 3:
			fseek(fp, 0, SEEK_SET);
			fread (&header, sizeof(header),1,fp);
			printf("free_offset : %d \n",header.free_head);
			if(header.free_head != -1)
			{
				fseek(fp, header.free_head,SEEK_SET);
				fread(&val,sizeof(val),1,fp);
				printf("free_offset : %d  %d\n",val.left_offset,val.key);
				while(val.left_offset != -1)
				{
					fseek(fp, val.left_offset,SEEK_SET);
					fread(&val,sizeof(val),1,fp);
					printf("free_offset : %d  %d\n",val.left_offset,val.key);
				}
			}
			break;
		case 4:
			display_inorder(fp);
			display_preorder(fp);
			break;
		}
		
	}
	close_tree(fp);
}

/*
int main()
{
	FILE* fp =  init_tree("bst.dat");
	tree_t header;node_t val;
	
	fseek(fp, 0, SEEK_SET);
	fread(&header, sizeof(tree_t), 1, fp);
	//printf("root : %d free :%d\n", header.root, header.free_head);
	int inp=-1;
	scanf("%d",&inp);
	while(inp!=0)
	{
		insert_key(inp, fp);
		scanf("%d",&inp);
	}
	
	fseek(fp, 0, SEEK_SET);
	fread(&header, sizeof(tree_t), 1, fp);
	//printf("root : %d free :%d\n", header.root, header.free_head);

	
	int i=0;
	
	while(i<5)
	{
		fseek(fp, sizeof(tree_t)+i*sizeof(node_t), SEEK_SET);
		fread(&val, sizeof(node_t), 1, fp);
		//printf("%d\n",ftell(fp));
		printf("value: %d left_offset: %d right_offset: %d\n", val.key, val.left_offset, val.right_offset);
		i++;
	}
	display_inorder(fp);
	printf("\n");
	display_preorder(fp);
	
	scanf("%d",&inp);
	while(inp!=0)
	{
		delete_key(inp, fp);
		display_inorder(fp);
		printf("\n");
		display_preorder(fp);
		scanf("%d",&inp);
	}
	
	
	fseek(fp, 0, SEEK_SET);
	fread (&header, sizeof(header),1,fp);
	printf("free_offset : %d \n",header.free_head);
	if(header.free_head != -1)
	{
		fseek(fp, header.free_head,SEEK_SET);
		fread(&val,sizeof(val),1,fp);
		printf("free_offset : %d  %d\n",val.left_offset,val.key);
		while(val.left_offset != -1)
		{
			fseek(fp, val.left_offset,SEEK_SET);
			fread(&val,sizeof(val),1,fp);
			printf("free_offset : %d  %d\n",val.left_offset,val.key);
		}
	}
	
	i=0;
	while(i<8)
	{
		fseek(fp, sizeof(tree_t)+i*sizeof(node_t), SEEK_SET);
		fread(&val, sizeof(node_t), 1, fp);
		printf("%d\n",ftell(fp));
		printf("value: %d left_offset: %d right_offset: %d\n", val.key, val.left_offset, val.right_offset);
		i++;
	}
	
	close_tree(fp);
}*/
