#include <stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct AVLTNode* treeptr;
typedef struct AVLTNode{
	int data;
    int bf;
	treeptr parent;
	treeptr lchild;
	treeptr rchild;
}avlTNode;

void AVL_Insert(treeptr root, int val);
//void BST_Delete(treeptr root, int val);
void AVL_Delete(treeptr root, int val);
void Inorder_Trav(treeptr root);
void Preorder_Trav(treeptr root);
void Postorder_Trav(treeptr root);

int main(int argc, char *argv[])
{
    printf("\n...................AVL Tree..................");
	treeptr root = (treeptr) malloc(sizeof(avlTNode));   
	root->parent = NULL;
	root->data=0;
	root->parent = root->lchild = root->rchild=NULL;
	int choice,val;  
	
    // AVL_Insert(root,1);
    // AVL_Insert(root,2);
    // AVL_Insert(root,3);
    // AVL_Insert(root,6);
    // Inorder_Trav(root->rchild);
    // AVL_Delete(root,1);
    // printf("\n");
    // Inorder_Trav(root->rchild);

	do{
		printf("\n\nSelect your operation :\n\n1. Insert element\n2. Delete element\n3. Inorder Traversal\n4. Preorder Traversal\n5. Postorder Traversal\n0. QUIT\n\nEnter your choice here (0-5) : ");
		scanf("%d",&choice);
		if(choice==1){
			printf("\nEnter the number that you want to insert into BST : ");
			scanf("%d",&val);
			AVL_Insert(root,val);
		}
		else if(choice == 2){
			printf("\nEnter the number that you want to delete from BST : ");
			scanf("%d",&val);
			AVL_Delete(root,val);
		}
		else if(choice ==3){
            printf("\nInorder Traversal : \n\n");
            if (root->rchild != NULL)
			    Inorder_Trav(root->rchild);
            else
                printf("\nBST is empty !!!");
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
	}while(choice!=0);
}

void AVL_Insert(treeptr root, int val){
	treeptr tmp,cur,prev,tmp2;
	tmp = (treeptr)malloc(sizeof(avlTNode));
	if(tmp!=NULL){
        tmp->data =val;
        tmp->bf = 0;
        tmp->parent=NULL;
        tmp->lchild=NULL;
        tmp->rchild=NULL;
        root->data--;
	}
	prev=NULL;
	cur=root;
	while(cur!=NULL){
		prev=cur;
		if(val<cur->data){
			cur=cur->lchild;
		}
		else{
			cur =cur->rchild;
		}
	}
    tmp->parent = prev;
	if(val<prev->data){
		prev->lchild = tmp;
	}
	else{
		prev->rchild =tmp;
	}
    cur = tmp;

    while(cur->parent != root){
        if(cur == cur->parent->lchild)
            cur->parent->bf++;
        else
            cur->parent->bf--;
        cur=cur->parent;
        if(cur->bf == 0 || cur->bf == -2 || cur->bf == 2)
            break;
    }
    prev = cur->parent;
    if(cur->bf == 2){
        printf("\nbf becomes 2 : rotating");
        tmp=cur->lchild;
        if(tmp->bf == 1){ //ll 
            tmp->parent = cur->parent;
            cur->lchild = tmp->rchild;
            tmp->rchild = cur;
            cur->parent = tmp;
            tmp->bf = cur->bf = 0;
            if(cur->data < prev->data)
                prev->lchild = tmp;
            else
                prev->rchild = tmp;
        }//cur A, tmp B, tmp2 C
        else if(tmp->bf == -1){//lr
            tmp2 = tmp->rchild;
            if(tmp2->bf == 0){
                tmp2->parent = cur->parent;
                tmp2->lchild = tmp;
                tmp2->rchild = cur;
                cur->lchild = tmp->rchild = NULL;
                tmp->parent = cur->parent = tmp2;
                tmp->bf = tmp2->bf = cur->bf = 0;
            }
            else if(tmp2->bf == 1 || tmp2->bf == -1){
                tmp2->parent = cur->parent;
                cur->lchild = tmp2->rchild;
                tmp->rchild = tmp2->lchild;
                tmp2->lchild = tmp;
                tmp2->rchild = cur;
                cur->parent = tmp->parent = tmp2;
                if(tmp2->bf == 1){
                    cur->bf = -1;
                    tmp->bf = tmp2->bf = 0;
                }
                else{
                    tmp->bf = 1;
                    cur->bf = tmp2->bf = 0;
                }
            }
            if(cur->data < prev->data)
                prev->lchild = tmp2;
            else
                prev->rchild = tmp2; 
        }
        
    }
    else if(cur->bf == -2){
        printf("\nbf becomes -2 : rotating");
        if(cur->rchild->bf == -1){ //rr
            tmp=cur->rchild;
            tmp->parent = cur->parent;
            cur->rchild = tmp->lchild;
            tmp->lchild = cur;
            cur->parent = tmp;
            tmp->bf = cur->bf = 0;
            if(cur->data < prev->data)
                prev->lchild = tmp;
            else
                prev->rchild = tmp;
            
        }
        else if(cur->rchild->bf == 1){//rl
            tmp = cur->rchild;
            tmp2 = tmp->lchild;
            if(tmp2->bf == 0){
                tmp2->parent = cur->parent;
                tmp2->lchild = cur;
                tmp2->rchild = tmp;
                cur->rchild = tmp->lchild = NULL;
                tmp->parent = cur->parent = tmp2;
                tmp->bf = tmp2->bf = cur->bf = 0;
            }
            else if(tmp2->bf == 1 || tmp2->bf == -1){
                tmp2->parent = cur->parent;
                cur->rchild = tmp2->lchild;
                tmp->lchild = tmp2->rchild;
                tmp2->lchild = cur;
                tmp2->rchild = tmp;
                cur->parent = tmp->parent = tmp2;
                if(tmp2->bf == 1){
                    tmp->bf = -1;
                    cur->bf = tmp2->bf = 0;
                }
                else{
                    cur->bf = 1;
                    tmp->bf = tmp2->bf = 0;
                }
            }
            if(cur->data < prev->data)
                prev->lchild = tmp2;
            else
                prev->rchild = tmp2; 
            
        }
    
    }
    
}


void AVL_Delete(treeptr root, int val){
    treeptr tmp, cur, prev,tmpA,tmpB,tmpC;
    prev = NULL;
    cur = root;
    while(cur != NULL && cur->data != val){
        prev = cur;
        if(val < cur->data){
            cur = cur->lchild;
        }
        else {
            cur = cur->rchild;
        }
    }
    // printf("%d\n",cur->data);

    if(cur != NULL){
        root->data++;
        if(cur->lchild != NULL && cur->rchild != NULL){//node to be delete is not leaf 
            prev = cur;
            tmp = cur;
            cur = cur->rchild;
            while (cur->lchild != NULL){
                prev = cur;
                cur = cur->lchild;
            }
            tmp->data = cur->data;
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
            //prev->bf--;

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
            //prev->bf++;
        }
        // free(tmp);
        // printf("%d,%d",cur->data,cur->parent->data);
        // tmpA = cur;
        while(cur->parent != root){
            if (cur->data < cur->parent->data)
                cur->parent->bf--;
            else cur->parent->bf++;
            cur = cur->parent;
            if(cur->bf == -1 || cur->bf == 1 || cur->bf == 2 || cur->bf == -2)
                break;
        }
        printf("%d,%d",cur->bf,cur->data);
        tmpA = cur;
        prev = cur->parent;
        // // free(cur);
        if (tmpA->bf == 2){
            printf("bf becomes 2 : rotating");
            tmpB = tmpA->lchild;
            if(tmpB->bf == 0 || tmpB->bf == 1){
                tmpB->parent = tmpA->parent;
                tmpA->parent = tmpB;
                tmpA->lchild = tmpB->rchild;
                tmpB->rchild = tmpA;
                if(tmpB->bf == 0){
                    tmpA->bf = 1;
                    tmpB->bf = -1;
                }
                else{
                    tmpA->bf = 0;
                    tmpB->bf = 0;
                }
                if(tmpA->data < prev->data)
                    prev->lchild = tmpB;
                else    prev->rchild = tmpB;
            }
            else if(tmpB->bf == -1){
                tmpC = tmpB->rchild;
                tmpC->parent = tmpA->parent;
                tmpA->lchild = tmpC->rchild;
                tmpB->rchild = tmpC->lchild;
                tmpA->parent = tmpB->parent = tmpC;
                tmpC->lchild = tmpB;
                tmpC->rchild = tmpA;
                
                tmpA->bf = tmpB->bf = tmpC->bf = 0;
                if(tmpA->data < prev->data)
                    prev->lchild = tmpC;
                else    prev->rchild = tmpC;
            }
        }
        else if (tmpA->bf == -2){
            printf("bf becomes -2 : rotating");
            tmpB = tmpA->rchild;
            if(tmpB->bf == 0 || tmpB->bf == -1){
                tmpB->parent = tmpA->parent;
                tmpA->parent = tmpB;
                tmpA->rchild = tmpB->lchild;
                tmpB->lchild = tmpA;
                if(tmpB->bf == 0){
                    tmpA->bf = -1;
                    tmpB->bf = 1;
                }
                else{
                    tmpA->bf = 0;
                    tmpB->bf = 0;
                }
                if(tmpA->data < prev->data)
                    prev->lchild = tmpB;
                else    prev->rchild = tmpB;
            }
            else if(tmpB->bf == 1){
                tmpC = tmpB->rchild;
                tmpC->parent = tmpA->parent;
                tmpA->rchild = tmpC->lchild;
                tmpB->lchild = tmpC->rchild;
                tmpA->parent = tmpB->parent = tmpC;
                tmpC->rchild = tmpB;
                tmpC->lchild = tmpA;
                
                tmpA->bf = tmpB->bf = tmpC->bf = 0;
                if(tmpA->data < prev->data)
                    prev->lchild = tmpC;
                else    prev->rchild = tmpC;
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
		printf("Data : %d, BF : %d, Parent : %d, Left child : %d, Right child : %d\n",root->data,root->bf,root->parent->data,root->lchild ? root->lchild->data : 0,root->rchild ? root->rchild->data : 0);
		Inorder_Trav(root->rchild);
	}
}

void Preorder_Trav(treeptr root){
	if(root!=NULL){
		printf("%d ",root->data);
        Preorder_Trav(root->lchild);
		Preorder_Trav(root->rchild);
	}
}

void Postorder_Trav(treeptr root){
	if(root!=NULL){
		Postorder_Trav(root->lchild);
		Postorder_Trav(root->rchild);
        printf("%d ",root->data);
	}
}