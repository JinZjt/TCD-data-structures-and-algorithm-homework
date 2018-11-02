#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define N 10000
void swap(int *a, int *b){
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int *a, int start, int end, int *record){
    int low = start;
    int high = end;
    int pivot = a[high];
    int index = end;
    if(start == end){
        record[1]++;
        return start;
    }
    while(1){
        while(a[low]<=pivot&&low<end) {
            record[1]++;
            low++;}
        while(a[high]>=pivot&&high>start) {
            record[1]++;
            high--;}
        if(low>=high){
            swap(&a[low], &a[index]);
            record[0]++;
            record[1]++;
            return low;
        }
        swap(&a[low],&a[high]);
        record[0]++;
    }
}
void quicksort(int *a, int start, int end, int *record){
    int p=0;
    if(start<end){
        p = partition(a, start, end, record);
        quicksort(a, start, p-1, record);
        quicksort(a, p+1, end, record);
    }
}
int main(){
    int a[N], record[2]={0,0}, flag=0, n, num=0,rec[2]={0,0};// record[0] records swaps; record[1] records comparisons
    int i=0;
    int b[10]={4,3,5,1,0,2,9,8,6,7};
    while(i<N){
        n = rand()%100000;
        for(i=0;i<num;i++)
            if(a[i]==n) continue;
        a[num++]=n;
        i++;
    }
    /*
    for(i=0;i<N;i++){
        a[i] = 3;
    }*/
    quicksort(a, 0, N-1, record);
    quicksort(b,0,9,rec);
    for(i=0;i<N-1;i++){
        if(a[i]>a[i+1]) flag++;
    }
    //for(i=0;i<100;i++){
      //  printf("%d ", a[i]);
    //}
    for(i=0;i<10;i++){
        printf("%d ", b[i]);
    }
    printf("\n");
    if(flag==0) printf("Sorted: Y\n");
    printf("swaps = %d\ncomparisons = %d\n", rec[0], rec[1]);

    return 0;
}
