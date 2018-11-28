#include<stdio.h>
#include<stdlib.h>
#define N 6
int visit[N] = {0};

typedef struct node{
    int data;
    struct node* next;
}queue;

typedef struct nodex{
    queue* head;
    queue* tail;
}linkqueue;

void printvertex(int i){
    if(i==0) printf("A ");
    else if(i==1) printf("B ");
    else if(i==2) printf("C ");
    else if(i==3) printf("D ");
    else if(i==4) printf("E ");
    else if(i==5) printf("F ");
    else printf("error!");
}

int is_empty(linkqueue* q){
    if(q->head->next == NULL) return 1;
    else return 0;
}

void initialization(linkqueue* q){
    q->tail = (queue*)malloc(sizeof(queue));
    q->tail->data = -1;
    q->tail->next = NULL;
    q->head = (queue*)malloc(sizeof(queue));
    q->head->data = -1;
    q->head->next = NULL;
}

void insertion(linkqueue* q, int data){
    queue* temp = (queue*)malloc(sizeof(queue));
    temp->data = data;
    temp->next = NULL;
    if(q->tail->next==NULL){
        q->head->next = temp;
        q->tail->next = temp;
    }
    else{
        q->tail->next->next = temp;
        q->tail->next = temp;
    }
}

void dequeue(linkqueue* q){
    queue* temp;
    temp = (queue*)malloc(sizeof(queue));
    if(is_empty(q)==1) printf("empty\n");
    else{
    temp = q->head->next->next;
    q->head->next->next = NULL;
    printvertex(q->head->next->data);
    free(q->head->next);
    q->head->next = temp;
    if(q->head->next==NULL) q->tail->next = NULL;
}
}

void deletequeue(linkqueue* q){
    queue* temp;
    temp = (queue*)malloc(sizeof(queue));
    while(q->head->next!=NULL){
    temp = q->head->next->next;
    q->head->next->next = NULL;
    free(q->head->next);
    q->head->next = temp;
    }
    free(q->head);
    free(q->tail);
}

void BFS(linkqueue* q, int a[][N]){
    int i=0, j=0;
    while(1){
        if(visit[i]==0 && i==0){
            visit[i]=0;
            insertion(q, i);
            dequeue(q);
        }
        for(j=0;j<N;j++){
            if(a[i][j]==1 && visit[j]==0){//find unvisited adjacency
                visit[j]=1;
                insertion(q, j);
            }
        }
        i = q->head->next->data;
        dequeue(q);
        if(is_empty(q)==1) return; 
    }
}

int main(){
    /*build adjacency matrix*/
    int a[N][N] = {{0, 1, 0, 1, 1, 0},
                   {0, 0, 1, 1, 0, 0},
                   {0, 1, 0, 1, 0, 0},
                   {0, 0, 0, 0, 0, 1},
                   {0, 0, 0, 1, 0, 0},
                   {0, 0, 1, 0, 0, 0}};//0:A, 1:B, 2:C, 3:D, 4:E, 5:F
    linkqueue* queue;
    queue = (linkqueue*)malloc(sizeof(linkqueue));
    initialization(queue);
    BFS(queue, a);
    printf("\n");
    return 0;
}