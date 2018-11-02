#include<stdio.h>
#include<stdlib.h>
#define N 10000

void swap(int *a, int *b){
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

int main(){
    int sortflag=0, i=0,n=0,num=0,flag=0;
    int a[N];
    int record[2]={0,0};
    while(i<N){
        n = rand()%100000;
        for(i=0;i<num;i++)
            if(a[i]==n) continue;
        a[num++]=n;
    }
    while(sortflag==0){
        sortflag = 1;
        for(i=0;i<N-1;i++){
            record[1]++;
            if(a[i]>a[i+1]) {
                record[0]++;
                swap(&a[i], &a[i+1]);
                sortflag = 0;
                }
        }
    }
    for(i=0;i<N-1;i++){
        if(a[i]>a[i+1]) flag++;
    }
    for(i=0;i<100;i++){
        printf("%d ", a[i]);
    }
    if(flag==0) printf("Sorted: Y\n");
    printf("swaps=%d\ncomparisons=%d\n", record[0], record[1]);
    return 0;
}