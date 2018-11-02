#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct game{
    char title[200];
    char platform[15];
    int  score;
    int year;
    struct game *next;
}Node, *LinkedList;

LinkedList initialization(){
    Node* head;
    head = (Node*)malloc(sizeof(Node));
    if(head==NULL) printf("No memory allocated\n");
    head->score = 0;
    head->year = 0;
    head->next = NULL;
    return head;
}

LinkedList add(Node* list, Node* p){
    Node* q;
    q = (Node*)malloc(sizeof(Node));
    strcpy(q->title, p->title);
    strcpy(q->platform, p->platform);
    q->score = p->score;
    q->year = p->year;
    q->next = list->next;
    list->next = q;
    return list;
}

void quicksort(Node* head, Node* tail){
    if(head==NULL) return;
    if(head==tail) return;
    int pivot=head->score;
    char titletmp[200];
    titletmp[0]='\0';
    char plattmp[20];
    plattmp[0]='\0';
    int scoretmp = 0, yeartmp = 0;
    Node*p = head;
    Node*q = p->next;
    while(q!=tail){
        if(q->score>pivot){
            p = p->next;
            strcpy(titletmp, p->title);
            strcpy(plattmp, p->platform);
            scoretmp = p->score;
            yeartmp = p->year; // temp = p->data;
            strcpy(p->title, q->title);
            strcpy(p->platform, q->platform);
            p->score = q->score;
            p->year = q->year;//p->data = q->data;
            //q->data = temp;
            strcpy(q->title, titletmp);
            strcpy(q->platform, plattmp);
            q->score = scoretmp;
            q->year = yeartmp;
        }
        q=q->next;
    }
    //temp = p->data;
    strcpy(titletmp, p->title);
    strcpy(plattmp, p->platform);
    scoretmp = p->score;
    yeartmp = p->year;
    //p->data = head->data;
    strcpy(p->title, head->title);
    strcpy(p->platform, head->platform);
    p->score = head->score;
    p->year = head->year;
    //head->data = temp;
    strcpy(head->title, titletmp);
    strcpy(head->platform, plattmp);
    head->score = scoretmp;
    head->year = yeartmp;
    quicksort(head, p);
    quicksort(p->next, tail);
}

int printList(Node* List){
	Node *start;
    int flag=0,length=0,i=0;
	for(start=List->next; start!=NULL; start = start->next) {
        length = strlen(start->title);
        for(i=0;i<length;i++) printf("%c", start->title[i]);
        printf("  ");
        length = strlen(start->platform);
        for(i=0;i<length;i++) {
            if(start->platform[i]=='\n') continue;
            printf("%c", start->platform[i]);
            }
        printf("  ");
        printf("%d %d\n", start->score, start->year);
        flag+=1;
        if(flag==10) break;
    }
	printf("\n");
	return 0;
}

int search(Node* list, int searchyear){
    Node *start;
    int flag=0, length=0, i=0;
    for(start=list->next; start!=NULL; start=start->next){
        if(start->year!=searchyear) continue;
        else{
            length = strlen(start->title);
        for(i=0;i<length;i++) printf("%c", start->title[i]);
        printf("  ");
        length = strlen(start->platform);
        for(i=0;i<length;i++) {
            if(start->platform[i]=='\n') continue;
            printf("%c", start->platform[i]);
            }
        printf("  ");
        printf("%d %d\n", start->score, start->year);
        flag+=1;
        if(flag==5) break;
        }
    }
    return 0;
}

void freefunction(Node* list){
    Node* p;
    while(list!=NULL){
        p = list->next;
        list->next = NULL;
        free(list);
        list = p;
    }
    if(list==NULL) printf("clear\n");
}

int main(){
    FILE *fp;
    char str[100],temp[200],c;
    int length=0,count=0, i=0, flag=0,number=0;
    Node* head;
    Node* list;
    Node* p;
    head = initialization();
    p = (Node*)malloc(sizeof(Node));
    str[0]='\0';
    temp[0]='\0';
    fp = fopen("ign.csv", "r");
    fgets(str, 100, fp);
    while(1){
        flag=0;
        c=fgetc(fp);
        if(c=='\n'||c==EOF) flag=1;
        if(c!=','){
            length++;
            temp[length-1]=c;
        }
        if(c==','&& count==0){
            temp[length]='\0';
            strcpy(p->title, temp);
            memset(temp,0,200);
            length=0;
            count+=1;
        }
        else if(c==','&& count==1){
            temp[length]='\0';
            strcpy(p->platform, temp);
            memset(temp,0,200);
            length=0;
            count+=1;
        }
        else if(c==','&& count==2){
            p->score = atoi(temp);
            memset(temp,0,200);
            length = 0;
            count+=1;
        }
        else if(flag==1 && count==3){
            p->year = atoi(temp);
            memset(temp,0,200);
            length=0;
            count=0;
            add(head, p);
            number+=1;
            if(c==EOF) break;
        }
    }
    quicksort(head->next, NULL);
    printList(head);
    search(head, 2012);
    freefunction(head);
    return 0;
}
