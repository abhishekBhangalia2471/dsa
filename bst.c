#include <stdio.h>
#include<stdlib.h>
typedef struct TNode* treeptr;
typedef struct TNode{
	int key;
	treeptr parent;
	treeptr lchild;
	treeptr rchild;
}tNode;

void BST_Insert(treeptr root, int val);
//void BST_Delete(treeptr root, int val);
void Inorder_Trav(treeptr root);
//void Preorder_Trav(treeptr root);
//void Postorder_Trav(treeptr root);

int main(int argc, char *argv[])
{
	treeptr root = (treeptr) malloc(sizeof(tNode));
	root->parent = NULL;
	root->key=0;
	root->parent = root->lchild=root->rchild=NULL;
	int choice,val;
	printf("\nEnter choice");
		scanf("%d",&choice);
	
	while(choice!=0){
		printf("\nEnter choice");
		scanf("%d",&choice);
		if(choice==1){
			printf("\nEnter element ");
			
			scanf("%d",&val);
			BST_Insert(root,val);
			
		}
		else if(choice == 2){
			printf("Enter element to delete");
			scanf("%d",&val);
		//	BST_Delete(root,val);
		}
		else if(choice ==3){
			Inorder_Trav(root);
		}
		else if(choice == 4){
		//	Preorder_Trav(root->rchild);
		}
		else if(choice == 5){
		//	Postorder_Trav(root->rchild);
		}
		else if (choice ==0){
			
			return 0;
		}
	}
	
}

void BST_Insert(treeptr root, int x){
	treeptr tmp,cur,prev;
	tmp = (treeptr)malloc(sizeof(tNode));
	if(tmp!=NULL){
	tmp->key =x;
	tmp->lchild=NULL;
	tmp->rchild=NULL;
	root->key--;
	}
	prev=NULL;
	cur=root;
	while(cur!=NULL){
		prev=cur;
		if(tmp->key<cur->key){
			cur=cur->lchild;
		}
		else{
			cur =cur->rchild;
		}
	}
	if(tmp->key<prev->key){
		prev->lchild = tmp;
		tmp->parent = prev;
	}
	else{
		prev->rchild =tmp;
		tmp->parent=prev;
	}
}

void Inorder_Trav(treeptr root){
	while(root!=NULL){
		Inorder_Trav(root->lchild);
		printf("%d",root->key);
		Inorder_Trav(root->rchild);
	}
}
	