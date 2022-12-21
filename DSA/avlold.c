#include <stdio.h>
#include<stdlib.h>
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
void Inorder_Trav(treeptr root);
void Preorder_Trav(treeptr root);
void Postorder_Trav(treeptr root);

int main(int argc, char *argv[])
{
    printf("\n...................Binary Search Tree..................");
	treeptr root = (treeptr) malloc(sizeof(avlTNode));   
	root->parent = NULL;
	root->data=0;
	root->parent = root->lchild = root->rchild=NULL;
	int choice,val;  
	
	while(choice!=0){
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
			// BST_Delete(root,val);
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

void AVL_Insert(treeptr root, int val){
	treeptr tmp,cur,prev;
	tmp = (treeptr)malloc(sizeof(avlTNode));
	if(tmp!=NULL){
	tmp->data =val;
    tmp->bf = 0;
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
        if(cur->lchild->bf == 1){ //ll
            tmp=cur->lchild;
            tmp->parent = cur->parent;
            cur->lchild = tmp->rchild;
            tmp->rchild = cur;
            cur->parent = tmp;
            tmp->bf = cur->bf = 0;
            if(cur->data < prev->data)
                prev->lchild = tmp;
            else
                prev->rchild = tmp;
        }
        else if(cur->lchild->bf == -1){//lr
            tmp = cur->lchild;
            treeptr tmp2 = tmp->rchild;
            if(tmp2->bf == 0){
                tmp2->parent = cur->parent;
                tmp2->lchild = tmp;
                tmp2->rchild = cur;
                cur->lchild = tmp->rchild = NULL;
                tmp->parent = cur->parent = tmp2;
                tmp->bf = tmp2->bf = cur->bf = 0;
            }
            else if(tmp2->bf == 1){
                tmp2->parent = cur->parent;
                cur->lchild = tmp2->rchild;
                tmp->rchild = tmp2->lchild;
                tmp2->lchild = tmp;
                tmp2->rchild = cur;
                cur->parent = tmp->parent = tmp2;
                cur->bf = -1;
                tmp->bf = tmp2->bf = 0;
            }
            else if(tmp2->bf == -1){
                tmp2->parent = cur->parent;
                cur->lchild = tmp2->rchild;
                tmp->rchild = tmp2->lchild;
                tmp2->lchild = tmp;
                tmp2->rchild = cur;
                cur->parent = tmp->parent = tmp2;
                tmp->bf = 1;
                cur->bf = tmp2->bf = 0;
            }
            if(cur->data < prev->data)
                prev->lchild = tmp2;
            else
                prev->rchild = tmp2;
        }
    }
    else if(cur->bf == -2){
        if(cur->rchild->bf == -1){ //ll
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
            treeptr tmp2 = tmp->lchild;
            if(tmp2->bf == 0){
                tmp2->parent = cur->parent;
                tmp2->lchild = cur;
                tmp2->rchild = tmp;
                cur->rchild = tmp->lchild = NULL;
                tmp->parent = cur->parent = tmp2;
                tmp->bf = tmp2->bf = cur->bf = 0;
            }
            else if(tmp2->bf == 1){
                tmp2->parent = cur->parent;
                cur->rchild = tmp2->lchild;
                tmp->lchild = tmp2->rchild;
                tmp2->lchild = cur;
                tmp2->rchild = tmp;
                cur->parent = tmp->parent = tmp2;
                tmp->bf = -1;
                cur->bf = tmp2->bf = 0;
            }
            else if(tmp2->bf == -1){
                tmp2->parent = cur->parent;
                cur->rchild = tmp2->lchild;
                tmp->lchild = tmp2->rchild;
                tmp2->lchild = cur;
                tmp2->rchild = tmp;
                cur->parent = tmp->parent = tmp2;
                cur->bf = 1;
                tmp->bf = tmp2->bf = 0;
            }
            if(cur->data < prev->data)
                prev->lchild = tmp2;
            else
                prev->rchild = tmp2;
        }
    } 
}



// void AVL_Delete(treeptr root, int val){
//     treeptr tmp, cur, prev;
//     prev = NULL;
//     cur = root;
//     while(cur != NULL && cur->data != val){
//         prev = cur;
//         if(val < cur->data){
//             cur = cur->lchild;
//         }
//         else {
//             cur = cur->rchild;
//         }
//     }

//     if(cur != NULL){
//         root->data++;
//         if(cur->lchild != NULL && cur->rchild != NULL){
//             prev = cur;
//             tmp = cur;
//             cur = cur->rchild;
//             while (cur->lchild != NULL){
//                 prev = cur;
//                 cur = cur->lchild;
//             }
//             tmp->data = cur->data;
//         }
//         tmp = cur;
//         if(cur == prev->lchild){
//             if(cur->rchild!=NULL){
//                 prev->lchild = cur->rchild;
//                 cur->rchild->parent = prev;
//             }
//             else if(cur->lchild != NULL){
//                 prev->lchild = cur->lchild;
//                 cur->lchild->parent = prev;
//             }
//             else{
//                 prev->lchild = NULL;
//             }

//         }
//         else if(cur == prev->rchild){
//             if(cur->rchild!=NULL){
//                 prev->rchild = cur->rchild;
//                 cur->rchild->parent = prev;
//             }
//             else if(cur->lchild != NULL){
//                 prev->rchild = cur->lchild;
//                 cur->lchild->parent = prev;
//             }
//             else{
//                 prev->rchild = NULL;
//             }
//         }
//         free(tmp);
//     }
//     else {
//         printf("\nNumber not found in BST !!!");
//     }
// }

void Inorder_Trav(treeptr root){
	if(root!=NULL){
		Inorder_Trav(root->lchild);
		printf("\nData : %d, BF : %d, Parent : %d\n",root->data,root->bf,root->parent->data);
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