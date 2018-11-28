#include<stdio.h>
#include<stdlib.h>
#define N 6
int visit[N] = {0};
typedef struct node{
    int s[N];
    int top;
}stack;

int is_empty(stack* s){
    if(s->top==-1) return 1;
    else return 0;
}

stack* initialize(){
    stack* s = (stack*)malloc(sizeof(stack));
    int i=0;
    s->top = -1;
    for(i=0;i<N;i++){
        s->s[i]=0;
    }
    if(s->top!=-1){
        printf("initialization failure\n");
        return NULL;
    }
    else return s;
}

void printvertex(int i){
    if(i==0) printf("A ");
    else if(i==1) printf("B ");
    else if(i==2) printf("C ");
    else if(i==3) printf("D ");
    else if(i==4) printf("E ");
    else if(i==5) printf("F ");
    else printf("error!");
}

void DFS(stack* s, int a[][N]){
    int i=0,j=0;
    while(1){
        if(visit[i]==0 && i==0) {
            visit[i]=1;
            printvertex(0);
        }
        for(j=5;j>=0;j--){
            if(a[i][j]==1 && visit[j]==0){
                s->top++;
                s->s[s->top] = j; // push the stack
                visit[j] = 1;
            }
        }
        i = s->s[s->top]; //pop the stack
        s->s[s->top] = 0;
        s->top--;
        printvertex(i);
        if(is_empty(s)==1) {
            printf("\n");
            return;
            }
    }
}

int main(){
    /*build adjency matrix*/
    int a[N][N] = {{0, 1, 0, 1, 1, 0},
                   {0, 0, 1, 1, 0, 0},
                   {0, 1, 0, 1, 0, 0},
                   {0, 0, 0, 0, 0, 1},
                   {0, 0, 0, 1, 0, 0},
                   {0, 0, 1, 0, 0, 0}};//0:A, 1:B, 2:C, 3:D, 4:E, 5:F
    stack* visitstack;
    visitstack = initialize();
    DFS(visitstack, a);
    return 0;
}