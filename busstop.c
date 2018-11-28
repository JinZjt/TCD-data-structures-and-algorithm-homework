#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define INT 999999
typedef struct info{
    int id;
    char name[30];
    float latitude;
    float longitude;
}info;

info information[7668];

typedef struct stacknode{
    int stopid;
    int distance;
    char name[30];
    float latitude;
    float longitude;
}stacknode;

typedef struct stack{
    stacknode list[50];
    int top;
}stack;
typedef struct edgenode{
    int src;
    int dest;
    int weight;
}edge;

/*structure used to build adjecency list*/
typedef struct node{
    int dest;
    int weight;
    struct node* next;
}AdjListNode;

typedef struct list{
    AdjListNode* head;
}AdjList;

typedef struct Graph{
    int V;
    AdjList* array;
}Graph;
/*structure used to build prioity queue(min heap)*/
typedef struct MinHeapNode{
    int v;
    int dist;
}MinHeapNode;

typedef struct MinHeap{
    int size;
    int capacity;
    int *position;
    MinHeapNode** array;
}MinHeap;

void pushstack(stack* s, int dist, info i){
    s->top++;
    s->list[s->top].stopid = i.id;
    s->list[s->top].distance = dist;
    strcpy(s->list[s->top].name, i.name);
    s->list[s->top].latitude = i.latitude;
    s->list[s->top].longitude = i.longitude;
}

void popstack(stack* s){
    
    while(s->top>-1){
        printf("%d %d %s %f %f\n",s->list[s->top].stopid, s->list[s->top].distance, s->list[s->top].name, s->list[s->top].latitude, s->list[s->top].longitude);
        s->top--;
    }
}

AdjListNode* newAdjListNode(int dest, int weight){
    AdjListNode* newNode = (AdjListNode*)malloc(sizeof(AdjListNode));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

Graph* createGraph(int V){
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    int i=0;
    graph->V = V;
    graph->array = (AdjList*)malloc(V*sizeof(AdjList));
    for(i=0;i<V;i++) graph->array[i].head = NULL;
    return graph;
}

void addEdge(Graph* graph, int src, int dest, int weight){
    AdjListNode* newNode = newAdjListNode(dest, weight);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;//insert from the head

    newNode = newAdjListNode(src, weight);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

MinHeapNode* newMinHeapNode(int v, int dist){
    MinHeapNode* minHeapNode = (MinHeapNode*)malloc(sizeof(MinHeapNode));
    minHeapNode->v = v;
    minHeapNode->dist = dist;
    return minHeapNode;
}

MinHeap* createMinHeap(int capacity){
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    minHeap->position = (int*)malloc(capacity*sizeof(int));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (MinHeapNode**)malloc(capacity*sizeof(MinHeapNode*));
    return minHeap;
}

void swapMinHeapNode(MinHeapNode** a, MinHeapNode** b){
    MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(MinHeap* minHeap, int idx){
    int smallest, left, right;
    smallest = idx;
    left = 2*idx+1;
    right = 2*idx+2;
    if(left<minHeap->size && minHeap->array[left]->dist < minHeap->array[smallest]->dist)
        smallest = left;
    if(right<minHeap->size && minHeap->array[right]->dist < minHeap->array[smallest]->dist)
        smallest = right;
    if (smallest != idx) 
    { 
        // The nodes to be swapped in min heap 
        struct MinHeapNode* smallestNode = minHeap->array[smallest]; 
        struct MinHeapNode* idxNode = minHeap->array[idx]; 
        // Swap positions 
        minHeap->position[smallestNode->v] = idx; 
        minHeap->position[idxNode->v] = smallest; 
        // Swap nodes 
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]); 
        minHeapify(minHeap, smallest); 
    } 
}

int isEmpty(struct MinHeap* minHeap) 
{ 
    return minHeap->size == 0; 
} 
  
MinHeapNode* extractMin(MinHeap* minHeap) 
{ 
    if (isEmpty(minHeap)) 
        return NULL; 
    // Store the root node 
    MinHeapNode* root = minHeap->array[0]; 
    // Replace root node with last node 
    MinHeapNode* lastNode = minHeap->array[minHeap->size - 1]; 
    minHeap->array[0] = lastNode; 
    // Update position of last node 
    minHeap->position[root->v] = minHeap->size-1; 
    minHeap->position[lastNode->v] = 0; 
    // Reduce heap size and heapify root 
    --minHeap->size; 
    minHeapify(minHeap, 0); 
    return root; 
} 

void decreaseKey(MinHeap* minHeap, int v, int dist) 
{ 
    // Get the index of v in  heap array 
    int i = minHeap->position[v]; 
    // Get the node and update its dist value 
    minHeap->array[i]->dist = dist; 
    // Travel up while the complete tree is not hepified. 
    // This is a O(Logn) loop 
    while (i && minHeap->array[i]->dist < minHeap->array[(i - 1) / 2]->dist) 
    { 
        // Swap this node with its parent 
        minHeap->position[minHeap->array[i]->v] = (i-1)/2; 
        minHeap->position[minHeap->array[(i-1)/2]->v] = i; 
        swapMinHeapNode(&minHeap->array[i],  &minHeap->array[(i - 1) / 2]); 
        // move to parent index 
        i = (i - 1) / 2; 
    } 
} 

int isInMinHeap(MinHeap *minHeap, int v) 
{ 
   if (minHeap->position[v] < minHeap->size) 
     return 1; 
   return 0; 
} 

void deletegraph(Graph* graph){
    int i=0;
    AdjListNode* p;
    p = (AdjListNode*)malloc(sizeof(AdjListNode));
    for(i=0;i<graph->V;i++){
        while(graph->array[i].head!=NULL){
            p = graph->array[i].head;
            graph->array[i].head = graph->array[i].head->next;
            free(p);
        }
    }
}

void dijkstra(Graph* graph, int src, int destination) 
{   
    stack*s;
    s = (stack*)malloc(sizeof(stack));
    s->top = -1;
    int temp=0;
    int V = graph->V;
    int dist[V];      
    int parent[V]; 
    MinHeap* minHeap = createMinHeap(V); 
    // Initialization  
    for (int v = 0; v < V; ++v) 
    { 
        dist[v] = INT;
        parent[v] = v; 
        minHeap->array[v] = newMinHeapNode(v, dist[v]); 
        minHeap->position[v] = v; 
    } 
    minHeap->array[src] = newMinHeapNode(src, dist[src]); 
    minHeap->position[src]   = src; 
    dist[src] = 0; 
    decreaseKey(minHeap, src, dist[src]);
    minHeap->size = V;  
    while (1) 
    { 
        MinHeapNode* minHeapNode = extractMin(minHeap); 
        int u = minHeapNode->v; // Store the extracted vertex number 
        //printf("%d %d %s %f %f\n", u, dist[u], information[u].name, information[u].latitude, information[u].longitude);
        if(u == destination) break; 
        AdjListNode* temp = graph->array[u].head; 
        while (temp != NULL) 
        { 
            int v = temp->dest; 
            if (isInMinHeap(minHeap, v) && dist[u] != INT && temp->weight + dist[u] < dist[v]) 
            { 
                dist[v] = dist[u] + temp->weight; 
                parent[v]=u;
                decreaseKey(minHeap, v, dist[v]); 
            } 
            temp = temp->next; 
        } 
    }
    //printf("%d %d %s %f %f\n", destination, dist[destination], information[destination].name, information[destination].latitude, information[destination].longitude);
    temp = destination;
    pushstack(s, dist[temp], information[temp]);
    while(temp!=src){
        temp = parent[temp];
        pushstack(s, dist[temp], information[temp]);
    }
    popstack(s);
    deletegraph(graph);
    return; 
} 

int main(){
    FILE* fp;
    FILE* fl;
    char str[50], temp[50], c;
    int i=0,flag=0,count = 0;
    int V = 7668; 
    struct Graph* graph = createGraph(V); 
    edge tmp;
    info tmp1;
    fp = fopen("edges.csv","r");
    fl = fopen("vertices.csv", "r");
    fgets(str, 50, fp);
    while(flag!=2){
    c = fgetc(fp);
    if(c=='\n') flag=1;
    if(c==EOF) flag=2;
    if(c=='"') continue;
    if(c!=','&& flag==0) temp[i++] = c;
    if(count==0&&c==',') {
        tmp.src = atoi(temp);
        memset(temp,0,50);
        count++;
        i=0;
    }
    else if(count==1&&c==','){
        tmp.dest = atoi(temp);
        memset(temp,0,50);
        count++;
        i=0;
    }
    else if(count==2&&flag==1){
        tmp.weight = atoi(temp);
        memset(temp,0,50);
        count=0;
        flag=0;
        addEdge(graph,tmp.src, tmp.dest, tmp.weight);
        i=0;
    }
    else if(count==2&&flag==2){
        tmp.weight = atoi(temp);
        memset(temp,0,50);
        count=0;
        flag=0;
        addEdge(graph,tmp.src, tmp.dest, tmp.weight);
        i=0;
        break;
    }
    }


while(flag!=2){
    c = fgetc(fl);
    if(c=='\n') flag=1;
    if(c==EOF) flag=2;
    if(c=='"') continue;
    if(c!=','&& flag==0) temp[i++] = c;
    if(count==0&&c==',') {
        tmp1.id = atoi(temp);
        memset(temp,0,50);
        count++;
        i=0;
    }
    else if(count==1&&c==','){
        strcpy(tmp1.name, temp);
        memset(temp,0,50);
        count++;
        i=0;
    }
    else if(count==2&&c==',') {
        tmp1.latitude = atof(temp);
        memset(temp,0,50);
        count++;
        i=0;
    }
    else if(count==3&&flag==1){
        tmp1.longitude = atof(temp);
        memset(temp,0,50);
        count=0;
        flag=0;
        i=0;
        information[tmp1.id]=tmp1;
    }
    else if(count==3&&flag==2){
        tmp1.longitude = atof(temp);
        memset(temp,0,50);
        count=0;
        flag=0;
        i=0;
        information[tmp1.id]=tmp1;
        break;
    }
    }
    dijkstra(graph, 300, 253);
    fclose(fp);
    fclose(fl);
    return 0;
}