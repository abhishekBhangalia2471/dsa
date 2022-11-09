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
void BST_Delete(treeptr root, int val);
void Inorder_Trav(treeptr root);
void Preorder_Trav(treeptr root);
void Postorder_Trav(treeptr root);

int main(int argc, char *argv[])
{
    printf("\n...................Binary Search Tree..................");
	treeptr root = (treeptr) malloc(sizeof(tNode));
	root->parent = NULL;
	root->key=0;
	root->parent = root->lchild=root->rchild=NULL;
	int choice,val;  
	
	while(choice!=0){
		printf("\n\nSelect your operation :\n\n1. Insert element\n2. Delete element\n3. Inorder Traversal\n4. Preorder Traversal\n5. Postorder Traversal\n0. QUIT\n\nEnter your choice here (0-5) : ");
		scanf("%d",&choice);
		if(choice==1){
			printf("\nEnter the number that you want to insert into BST : ");
			scanf("%d",&val);
			BST_Insert(root,val);
		}
		else if(choice == 2){
			printf("\nEnter the number that you want to delete from BST : ");
			scanf("%d",&val);
			BST_Delete(root,val);
		}
		else if(choice ==3){
            printf("\nInorder Traversal : ");
            if (root->rchild != NULL)
			    Inorder_Trav(root->rchild);
            else
                printf("BST is empty !!!");
		}
		else if(choice == 4){
            printf("\nPreorder Traversal : ");
            if(root->rchild != NULL)
			    Preorder_Trav(root->rchild);
            else 
                printf("BST is empty !!!");
		}
		else if(choice == 5){
            printf("\nPostorder Traversal : ");
            if(root->rchild != NULL)
			    Postorder_Trav(root->rchild);
            else 
                printf("BST is empty !!!");
		}
		else if (choice ==0){
			printf("\n\nQuiting...");
			return 0;
		}
	}
}

void BST_Insert(treeptr root, int val){
	treeptr tmp,cur,prev;
	tmp = (treeptr)malloc(sizeof(tNode));
	if(tmp!=NULL){
	tmp->key =val;
	tmp->lchild=NULL;
	tmp->rchild=NULL;
	root->key--;
	}
	prev=NULL;
	cur=root;
	while(cur!=NULL){
		prev=cur;
		if(val<cur->key){
			cur=cur->lchild;
		}
		else{
			cur =cur->rchild;
		}
	}
	if(val<prev->key){
		prev->lchild = tmp;
		tmp->parent = prev;
	}
	else{
		prev->rchild =tmp;
		tmp->parent=prev;
	}
}


void BST_Delete(treeptr root, int val){
    treeptr tmp, cur, prev;
    prev = NULL;
    cur = root;
    while(cur != NULL && cur->key != val){
        prev = cur;
        if(val < cur->key){
            cur = cur->lchild;
        }
        else {
            cur = cur->rchild;
        }
    }

    if(cur != NULL){
        root->key++;
        if(cur->lchild != NULL && cur->rchild != NULL){
            prev = cur;
            tmp = cur;
            cur = cur->rchild;
            while (cur->lchild != NULL){
                prev = cur;
                cur = cur->lchild;
            }
            tmp->key = cur->key;
        }
        tmp = cur;
        if(cur == prev->lchild){
            if(cur->rchild!=NULL){
                prev->lchild = cur->rchild;
                cur->rchild->parent = prev;
            }
            else if(cur->lchild != NULL){
                prev->lchild = cur->lchild;
                cur->lchild->parent = prev;
            }
            else{
                prev->lchild = NULL;
            }

        }
        else if(cur == prev->rchild){
            if(cur->rchild!=NULL){
                prev->rchild = cur->rchild;
                cur->rchild->parent = prev;
            }
            else if(cur->lchild != NULL){
                prev->rchild = cur->lchild;
                cur->lchild->parent = prev;
            }
            else{
                prev->rchild = NULL;
            }
        }
        free(tmp);
    
    }
    else {
        printf("\nNumber not found in BST !!!");
    }
}

void Inorder_Trav(treeptr root){
	if(root!=NULL){
		Inorder_Trav(root->lchild);
		printf("%d ",root->key);
		Inorder_Trav(root->rchild);
	}
}

void Preorder_Trav(treeptr root){
	if(root!=NULL){
		printf("%d ",root->key);
        Preorder_Trav(root->lchild);
		Preorder_Trav(root->rchild);
	}
}

void Postorder_Trav(treeptr root){
	if(root!=NULL){
		Postorder_Trav(root->lchild);
		Postorder_Trav(root->rchild);
        printf("%d ",root->key);
	}
}
