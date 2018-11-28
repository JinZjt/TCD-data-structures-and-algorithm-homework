#include<stdio.h>
#include<stdlib.h>
#define MAX 1000
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
    int *position;// position is used to record current position of each vertex after a change
    MinHeapNode** array;
}MinHeap;

void printvertex(int i, int dist){
    if(i==0) printf("A distance:%d\n",dist);
    else if(i==1) printf("B distance:%d\n",dist);
    else if(i==2) printf("C distance:%d\n",dist);
    else if(i==3) printf("D distance:%d\n",dist);
    else if(i==4) printf("E distance:%d\n",dist);
    else if(i==5) printf("F distance:%d\n",dist);
    else if(i==6) printf("G distance:%d\n",dist);
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

void buildGraph(Graph* graph, int src, int dest, int weight){
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

void swap(MinHeapNode** a, MinHeapNode** b){
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
        struct MinHeapNode* smallestNode = minHeap->array[smallest]; 
        struct MinHeapNode* idxNode = minHeap->array[idx];  
        minHeap->position[smallestNode->v] = idx; 
        minHeap->position[idxNode->v] = smallest; 
        swap(&minHeap->array[smallest], &minHeap->array[idx]); 
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
    // switch the position between root and last node   
    MinHeapNode* root = minHeap->array[0];  
    MinHeapNode* lastNode = minHeap->array[minHeap->size - 1]; 
    minHeap->array[0] = lastNode;  
    minHeap->position[root->v] = minHeap->size-1; 
    minHeap->position[lastNode->v] = 0; 
    // Reduce heap size and heapify from the root 
    --minHeap->size; 
    minHeapify(minHeap, 0); //rebuild minheap
    return root; 
} 

void updateHeap(MinHeap* minHeap, int v, int dist) // update the minheap after extractmin function and distance updation
{ 
    // get the current position and update its distance 
    int i = minHeap->position[v]; 
    minHeap->array[i]->dist = dist; 
    // travel up while the complete tree is not heapified. 
    while (i && minHeap->array[i]->dist < minHeap->array[(i - 1) / 2]->dist) 
    { 
        // swap this node with its parent 
        minHeap->position[minHeap->array[i]->v] = (i-1)/2; 
        minHeap->position[minHeap->array[(i-1)/2]->v] = i; 
        swap(&minHeap->array[i],  &minHeap->array[(i - 1) / 2]); 
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

void dijkstra(Graph* graph, int src) 
{ 
    int V = graph->V;// Get the number of vertices in graph 
    int dist[V];      // dist values used to pick minimum weight edge in cut 
    //initialization
    MinHeap* minHeap = createMinHeap(V);  
    for (int v = 0; v < V; ++v) 
    { 
        dist[v] = MAX; 
        minHeap->array[v] = newMinHeapNode(v, dist[v]); 
        minHeap->position[v] = v; 
    } 
  
    // The first step is to set zero for the source node 
    minHeap->array[src] = newMinHeapNode(src, dist[src]); 
    minHeap->position[src]   = src; 
    dist[src] = 0; 
    updateHeap(minHeap, src, dist[src]); 
    minHeap->size = V; 
    while (!isEmpty(minHeap)) 
    { 
        // Extract the vertex with minimum distance value 
        MinHeapNode* minHeapNode = extractMin(minHeap); 
        int u = minHeapNode->v; // Store the extracted vertex number 
        printvertex(u,dist[u]);
        AdjListNode* temp = graph->array[u].head; //BFS: search all the adjacent vertices
        while (temp != NULL) 
        { 
            int v = temp->dest; 
            if (isInMinHeap(minHeap, v) && dist[u] != MAX &&  
                                          temp->weight + dist[u] < dist[v])//compare the distance and keep the shorter one 
            { 
                dist[v] = dist[u] + temp->weight; 
                // update distance value in min heap 
                updateHeap(minHeap, v, dist[v]); 
            } 
            temp = temp->next; 
        } 
    } 
} 

int main() 
{ 
    // create the graph given in above fugure 
    int V = 9; 
    Graph* graph = createGraph(V); 
    buildGraph(graph, 0, 1, 1);//A-B 1 
    buildGraph(graph, 0, 2, 3);//A-C 3 
    buildGraph(graph, 0, 5, 10);//A-F 10 
    buildGraph(graph, 1, 2, 1);//B-C 1
    buildGraph(graph, 1, 3, 7);//B-D 7 
    buildGraph(graph, 1, 4, 5);//B-E 5 
    buildGraph(graph, 1, 6, 2);//B-G 2 
    buildGraph(graph, 2, 3, 9);//C-D 3 
    buildGraph(graph, 2, 4, 3);//C-E 3
    buildGraph(graph, 3, 4, 2);//D-E 2 
    buildGraph(graph, 3, 5, 1);//D-F 1 
    buildGraph(graph, 3, 6, 12);//D-G 12 
    buildGraph(graph, 4, 5, 2);//E-F 2 
    dijkstra(graph, 0); 
    return 0; 
} 