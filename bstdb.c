#include "bstdb.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<uuid/uuid.h>
#define N 110000
// Write your submission in this file
//
// A main function and some profiling tools have already been set up to test
// your code in the task2.c file. All you need to do is fill out this file
// with an appropriate Binary Search Tree implementation.
//
// The input data will be books. A book is comprised of a title and a word
// count. You should store both these values in the tree along with a unique
// integer ID which you will generate.
//
// We are aiming for speed here. A BST based database should be orders of
// magnitude faster than a linked list implementation if the BST is written
// correctly.
//
// We have provided an example implementation of what a linked list based
// solution to this problem might look like in the db/listdb.c file. If you
// are struggling to understand the problem or what one of the functions
// below ought to do, consider looking at that file to see if it helps your
// understanding.
//
// There are 6 functions you need to look at. Each is provided with a comment
// which explains how it should behave. The functions are:
//
//  + bstdb_init
//  + bstdb_add
//  + bstdb_get_word_count
//  + bstdb_get_name
//  + bstdb_stat
//  + bstdb_quit
//
// Do not rename these functions or change their arguments/return types.
// Otherwise the profiler will not be able to find them. If you think you
// need more functionality than what is provided by these 6 functions, you
// may write additional functions in this file.

typedef struct node{
	int doc_id;
	char* name;
	int word_count;
	struct node* left;
	struct node* right;
}tree_node;

tree_node* g_linked_list; 		 // database storage
int g_num_comps;
int g_num_searches;
int a[N];
int begin=0;
int sum = 0;
int times = 0;

int bstdb_init ( void ) {
	// This function will run once (and only once) when the database first
	// starts. Use it to allocate any memory you want to use or initialize 
	// some globals if you need to. Function should return 1 if initialization
	// was successful and 0 if something went wrong.
	int i=0, temp=0;
	for(i=0;i<N;i++){
		temp = rand();
		a[i] = temp;
	}
	g_linked_list = (tree_node*)malloc(sizeof(tree_node));
	g_linked_list->doc_id = -1;
	g_linked_list->word_count = 0;
	g_linked_list->left = NULL;
	g_linked_list->right = NULL;
	g_num_comps = 0;
	g_num_searches = 0;
	if(g_linked_list->doc_id!=-1) return 0;
	else return 1;
}

void tree_delete(tree_node* root){
    if(root!=NULL){
        tree_delete(root->left);
        tree_delete(root->right);
        free(root);
    }
    else return;
}

void insert(tree_node* root, tree_node* new){
	if(new->doc_id < root->doc_id){
		if(root->left==NULL) root->left = new;
		else insert(root->left, new);
		}
	else if(new->doc_id >= root->doc_id){
		if(root->right==NULL) root->right = new; 
		else insert(root->right, new);
	}
}


tree_node* Search(tree_node* root, int doc_id){
	if(root==NULL||doc_id==root->doc_id) {
		sum++;
		return root;}
	if(doc_id>root->doc_id) {
		sum++;
		return Search(root->right, doc_id);}
		sum++;
	return Search(root->left, doc_id);
}

int
bstdb_add ( char *name, int word_count ) {
	// This function should create a new node in the binary search tree, 
	// populate it with the name and word_count of the arguments and store
	// the result in the tree.
	//
	// This function should also generate and return an identifier that is
	// unique to this document. A user can find the stored data by passing
	// this ID to one of the two search functions below.
	//
	// How you generate this ID is up to you, but it must be an integer. Note
	// that this ID should also form the keys of the nodes in your BST, so
	// try to generate them in a way that will result in a balanced tree.
	//
	// If something goes wrong and the data cannot be stored, this function
	// should return -1. Otherwise it should return the ID of the new node
	tree_node* p;
	int length = 0;
	length = strlen(name);
	p = (tree_node*)malloc(sizeof(tree_node));
	p->left = NULL;
	p->right = NULL;
	if(g_linked_list->doc_id==-1){
		g_linked_list->doc_id = a[begin++];
		g_linked_list->name = (char*)malloc(sizeof(char)*length);
		strcpy(g_linked_list->name, name);
		g_linked_list->word_count = word_count;
		g_linked_list->left = NULL;
		g_linked_list->right = NULL;
		return g_linked_list->doc_id;
	}
	else {
		p->word_count = word_count;
		p->doc_id = a[begin++];
		p->name = calloc(length+1,sizeof(char)); // store new node information
		if(p->name) strcpy(p->name, name);
		else return -1;
		insert(g_linked_list, p);
		return p->doc_id;
	}
	return -1;
}

int
bstdb_get_word_count ( int doc_id ) {
	// This is a search function. It should traverse the binary search tree
	// and return the word_count of the node with the corresponding doc_id.
	//
	// If the required node is not found, this function should return -1
	tree_node* node;
	times++;
	node = (tree_node*)malloc(sizeof(tree_node));
	node->word_count = 0;
	node = Search(g_linked_list, doc_id);
	if(node->word_count!=0) {
		return node->word_count;}
	else return -1;
}

char*
bstdb_get_name ( int doc_id ) {
	// This is a search function. It should traverse the binary search tree
	// and return the name of the node with the corresponding doc_id.
	//
	// If the required node is not found, this function should return NULL or 0
	tree_node* node;
	times++;
	node = (tree_node*)malloc(sizeof(tree_node));
	node->word_count=0;
	node = Search(g_linked_list, doc_id);
	if(node->word_count!=0) {
		return node->name;}
	else return NULL;
}

void
bstdb_stat ( void ) {
	// Use this function to show off! It will be called once after the 
	// profiler ends. The profiler checks for execution time and simple errors,
	// but you should use this function to demonstrate your own innovation.
	//
	// Suggestions for things you might want to demonstrate are given below,
	// but in general what you choose to show here is up to you. This function
	// counts for marks so make sure it does something interesting or useful.
	//
	//  + Check if your tree is balanced and print the result
	//
	//  + Does the number of nodes in the tree match the number you expect
	//    based on the number of insertions you performed?
	//
	//  + How many nodes on average did you need to traverse in order to find
	//    a search result? 
	//
	//  + Can you prove that there are no accidental duplicate document IDs
	//    in the tree?
	printf("Average visted nodes: %d\n", sum/times);
}

void
bstdb_quit ( void ) {
	// This function will run once (and only once) when the program ends. Use
	// it to free any memory you allocated in the course of operating the
	// database.
	tree_delete(g_linked_list);
	return;
}
