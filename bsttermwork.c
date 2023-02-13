//some basic operations on Binary Search Tree like deletion of a node(All cases satisfied),
//finding the height, no of leaf nodes, existence of a node
#include<stdio.h>
#include<stdlib.h>
typedef struct tree{
    struct  tree* left;
    int data;
    struct tree* right;
}treetype;
void insert(treetype*,treetype*);
void inorder(treetype*);
void leaf(treetype*,int*);
int height(treetype* );
void nodes_on_right(treetype*,int *);
treetype* delete(treetype**,int);
treetype* delete_root(treetype**,int );
treetype* successor(treetype*,treetype*);
treetype* prnt(treetype*,int);
treetype* find(treetype*,int);
int main(){
    treetype *root=NULL,*p=NULL,*node=NULL;
    int ch,x,count=0,ht;
    do{
        printf("\n1.INSERT.\n2.EXIT\n3.Find\n4.Delete a node\n5.Leaf node\n6.Height\n7. Nodes on the right of the root node\n");
        scanf("%d",&ch);
        switch(ch){
            case 1:
            p=NULL;
            p=(treetype*)malloc(sizeof(treetype));
            printf("Enter data : ");
            scanf("%d",&x);
            p->data=x;
            p->left=p->right=NULL;
            if(root==NULL){
                root=p;
            }
            else{
                insert(root,p);
            }
            break;
            case 2:
            printf("EXITING!....");
            exit(0);
            case 3:
            printf("Enter data : ");
            scanf("%d",&x);
            p=find(root,x);
            if(p==NULL){
            printf("Element not found");
            }
            else
            printf("element found ");
            break;
            case 4:
            printf("Enter node to be deleted : ");
            scanf("%d",&x);
            node=delete(&root,x);
            break;
            case 5:
            count=0;
            leaf(root,&count);
            printf("\nNo. of leaf nodes are : %d",count);
            break;
            case 6:
            ht=height(root);
            printf("\nNo. of leaf nodes are : %d",ht);
            break;
            case 7:
            count=0;
            nodes_on_right(root->right,&count);
            printf("\nNo. of leaf nodes are : %d",count);
            break;
            default:
            printf("Invalid choice");
        }
    }while(1);
return 0;
}
void insert(treetype*rt,treetype*p){
        if(p->data<rt->data){
            if(rt->left==NULL)
            rt->left=p;
            else
            insert(rt->left,p);
        }
        else if(p->data>rt->data){
            if(rt->right==NULL)
            rt->right=p;
            else
            insert(rt->right,p);
        }
}
void inorder(treetype*root){
    if(root==NULL)
    return ;
    else{
        inorder(root->left);
        printf("%d\n",root->data);
        inorder(root->right);
    }     
}
void leaf(treetype*root,int*cnt){
    if(root!=NULL){
        if(root->left==NULL&&root->right==NULL){
            (*cnt)++;
        }
        leaf(root->left,cnt);
        leaf(root->right,cnt);
    }
}
int height(treetype* node)
{
    if (node == NULL)
        return 0;
    else {
        int left_h = height(node->left);
        int right_h = height(node->right);
        if (left_h > right_h)
            return (left_h+ 1);
        else
            return (right_h + 1);
    }
}
void nodes_on_right(treetype*root,int *count)
{
    if(root==NULL)
    return;
    (*count)++;
    nodes_on_right(root->right,count);
    nodes_on_right(root->left,count);
}
treetype* delete(treetype**rt,int x){
    treetype*parnt=NULL,*node=NULL,*p=NULL,*suc=NULL;
    if((*rt)->data==x)
        delete_root(rt,x);
    else{
    parnt=prnt(*rt,x);
    if(parnt->left->data==x)
    node=parnt->left;
    else
    node=parnt->right;
    if(node==NULL){
        printf("Element not found");
    }
    else
    {
        printf("Element found!.\n"); 
        printf("\nDeleting %d...\n",node->data);
        if(node->left==NULL&&node->right==NULL){
            if(parnt->right==node)
            parnt->right=NULL;
            else
            parnt->left=NULL;
        }
        else if((node->left==NULL)||(node->right==NULL)){
            if(node->left==NULL){
                if(parnt->right==node)
                parnt->right=node->right;
                else
                parnt->left=node->right;
            }
            else{
                if(parnt->right==node)
                parnt->right=node->left;
                else
                parnt->left=node->left;
                }
        }
        else{            
            treetype*temp=NULL;
            temp=suc=successor(node->right,node);
            delete(&node,suc->data);
            node->data=temp->data;
        }
        printf("\nNode deleted successfully!\n");
        inorder(*rt);
    }
    }
    return node;
}
treetype* prnt(treetype*root,int x){
    treetype*p=root;
if(x<root->data){
    if(x==root->left->data){
        return p;
    }
    else
        p=prnt(root->left,x);
}
else if(x>root->data){
    if(x==root->right->data){
        return p;
    }
    else
        p=prnt(root->right,x);
}
return p;
}
treetype* successor(treetype*root,treetype*node){
    treetype*p=root;
    if(root->right==NULL&&root->left==NULL)
    return p;
    if(root->left==NULL)
    return p;
    if(root->left==NULL&&root->right!=NULL)
    p=successor(root->right,node);
    else
    p=successor(root->left,node);
    
}
treetype* delete_root(treetype**rt,int x){
    treetype*parnt=NULL,*node=NULL,*p=NULL,*suc=NULL;
        node=*rt;
        if(node->left==NULL&&node->right==NULL){
            *rt=NULL;
        }
        else if((node->left==NULL)||(node->right==NULL)){
            if(node->left==NULL){
               (*rt)=(*rt)->right;
            }
            else{
               *rt=(*rt)->left;
                }
        }
        else{            
            treetype*temp=NULL;
            temp=successor(node->right,node);
            delete(&node,temp->data);
            (*rt)->data=temp->data;
        }
        printf("\nNode deleted successfully!\n");
        inorder(*rt);
    return node;
}
treetype* find(treetype*root,int x){
    treetype*p=root;
if(x<=root->data){
    if(x==root->data){
        return p;
    }
    else
        p=find(root->left,x);
}
else if(x>=root->data){
    if(x==root->data){
        return p;
    }
    else
        p=find(root->right,x);
}
else
return NULL;
}
