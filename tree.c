#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

typedef struct node{
    char s;
    struct node* left;
    struct node* right;
}tree_node;

void tree_print_sorted(tree_node* root){//L->V->R tree printed sorted
    if(root==NULL)
    return;
    else{
        tree_print_sorted(root->left);
        printf("%c ", root->s);
        tree_print_sorted(root->right);
    } 
}

void preorder(tree_node* root){//V->L->R
    if(root==NULL) return;
    else{
        printf("%c ", root->s);
        preorder(root->left);
        preorder(root->right);
    }
}

void tree_insert(tree_node* root, char s){
    tree_node* temp;
    tree_node* parent;
    temp = (tree_node*)malloc(sizeof(tree_node));
    parent = (tree_node*)malloc(sizeof(tree_node));
    parent = root;
    temp->s = s;
    temp->left = NULL;
    temp->right = NULL;
    if(!parent->s) {
        parent->s = s;
        return;
    }
    while(1){
        if(temp->s >= parent->s && parent->right!=NULL) parent = parent->right;
        else if(temp->s < parent->s && parent->left!=NULL) parent = parent->left;
        else if(temp->s >= parent->s && parent->right==NULL) {parent->right = temp; return;}
        else if(temp->s < parent->s && parent->left==NULL) {parent->left = temp; return;}
    }
}

void tree_search(tree_node* root, char s){
    tree_node* temp;
    temp = (tree_node*)malloc(sizeof(tree_node));
    temp = root;
    while(1){
        if(temp==NULL) {
            printf("%c not in tree\n", s);
            return;
        }
        else if(s > temp->s) temp = temp->right;
        else if(s < temp->s) temp = temp->left;
        else if (s==temp->s){
            printf("%c in tree\n", s);
            return;
        }
    }
}

void tree_delete(tree_node* root){
    if(root!=NULL){
        tree_delete(root->left);
        tree_delete(root->right);
        free(root);
    }
    else return;
}

int main(){
    char* string = "FLOCCINAUCINIHILIPILIFICATION";
    int length=0, i=0, temp=0;
    tree_node* root;
    root = (tree_node*)malloc(sizeof(tree_node));
    root->s = '\0';
    root->left = NULL;
    root->left = NULL;
    length = strlen(string);
    printf("ADDING: ");
    for(i=0;i<length;i++){
        printf("%c ", string[i]);
        tree_insert(root, string[i]);
    }
    printf("\nSORTED: ");
    tree_print_sorted(root);
    printf("\n");
    srand((int)time(0));
    for(i=0;i<2;i++){
        temp = rand()%(length-1);
        tree_search(root, string[temp]);
    }
    tree_search(root, 'C');
    tree_search(root, 'Z');
    tree_delete(root);
    return 0;
}



