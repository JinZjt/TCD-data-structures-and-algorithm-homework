#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
	char data;
	struct Node *next;
}Node, *LinkedList;

LinkedList initialization(){
	Node* Head;
	Head = (Node*)malloc(sizeof(Node));
	if (Head==NULL) printf("No memory allocated");
	Head->next = NULL;
	printf("Initialize successfully\n");
	return Head;
}
LinkedList addH(Node* List, char element){
	Node *p;
	p = (Node *)malloc(sizeof(Node));
	p->data = element;
	p->next = List->next;
	List->next = p;
	return List;
}
int printList(Node* List){
	Node *start;
	for(start=List->next; start!=NULL; start = start->next) printf("%c", start->data);
	printf("\n");
	return 0;
}
LinkedList remove_iterative(Node* List, char p){
	Node *start, *prev;
	start = (Node *)malloc(sizeof(Node));
	prev = (Node *)malloc(sizeof(Node));
	prev = List;
	start = List->next;
	while(start!=NULL){
		if(start->data == p){
			prev->next = start->next;
			free(start);
			printf("clear\n"); 
			start = prev->next;
		}
		else{
			prev = start;
			start = start->next;
		}
		
	}
	return List;
}
LinkedList remove_recursion(Node *List, char p){
	Node *start, *prev;
	start = (Node*)malloc(sizeof(Node));
	prev = (Node*)malloc(sizeof(Node));
	prev = List;
	prev->next = List->next;
	start = List->next;
	if(start!=NULL){
		if(start->data == p){
			prev->next = start->next;
			free(start);
			start = prev->next;
	}
		else {
			prev = start;
			start = start->next;
		}
		remove_recursion(prev, p);
}
	else return List;
} 
LinkedList deleteall(Node *List){
	Node *start, *Next;
	int C;
	start = (Node*)malloc(sizeof(Node));
	Next = (Node*)malloc(sizeof(Node));
	start = List->next;
	Next = start->next;
	while(start!=NULL){
		free(start);
		++C;
		start = Next;
		if(start == NULL) break;
		Next = Next->next;
		if(Next==NULL) {
		free(start);
		++C;
		List->next = NULL; 
		break;
		}
	}
	printf("%d",C);
	return List;
}
LinkedList deleteall_recursion(Node *List, int count){
	Node *start, *Next;
	start = (Node*)malloc(sizeof(Node));
	Next = (Node*)malloc(sizeof(Node));
	start = List;
	Next = start->next;
	free(start);
	count+=1;
	if(Next==NULL) {
		printf("%d", count);
		return 0;
	}
	else deleteall_recursion(Next,count);
	}
LinkedList reverse(Node *List){
	Node *prev, *current, *Next;
	prev = (Node*)malloc(sizeof(Node));
	current = (Node*)malloc(sizeof(Node));
	Next = (Node*)malloc(sizeof(Node));
	prev = NULL;
	current = List->next;
	while(current!=NULL){
		Next = current->next;
		current->next = prev;
		prev = current;
		current = Next;
	}
	List->next= prev;
	free(current);
	free(Next);
	return List;
}
void add_Node(Node* head, char p, int offset){
	Node* pointer;
	int i=0;
	pointer = head;
	for(i=0;i<offset;i++){
		pointer = pointer->next;
	}
    pointer->data = p;
} 
int main(){
	Node* Head;
	Node list[3];
	int i=0;
	list[0].next = &list[1];
	list[1].next = &list[2];
	list[2].next = NULL;
	add_Node(&list[0], 'A', 0);
	add_Node(&list[0], 'B', 1);
	add_Node(&list[0], 'C', 2);
	printf("%c", list[0].data);
	printf("%c", list[1].data);
	printf("%c", list[2].data);
	Head = initialization();
	//printList(Head);
	addH(Head, 'A');
	addH(Head, 'B');
	addH(Head, 'C');
	addH(Head, 'D');
	printList(Head);
	remove_iterative(Head, 'D');
	remove_recursion(Head, 'A');
	printList(Head);
	//deleteall(Head);
	//deleteall_recursion(Head->next, 0);
	reverse(Head);
	printList(Head);
	return 0;
}
