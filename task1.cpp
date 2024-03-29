#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define N 99991
char *key[N];
struct Record{
	char *name;
	int freq = 0;
}; 
typedef struct Hashtable{
	int elem[N]={0};
	int count = 0;
	int collision = 0;
}Hashtable;
int hash(char*s){
	int hash = 0, length = 0, i=0;
	length = strlen(s);
	for(i=0;i<length;i++){
		hash += (int)(s[i]);
	}
	return hash;
}

char* inserthash(Hashtable *H, char* name, int freq, char* key[]){
	int index = 0;
	index = hash(name);
	if(H->elem[index]==0){
		H->elem[index] = freq;
		H->count++;
		key[index] = name;
	}
	else{
		while(H->elem[index]!=0){
			H->collision++;
			index++;
			if(index==N-1) printf("overflow");
		}
		H->elem[index] = freq;
		H->count++;
		key[index]=name;
	}
	return *key;
}
void search(Hashtable* H, char* s, char* key[]){
	int value = 0;
	value = hash(s);
	if(strcmp(key[value],s)==0){
		printf("%d\n",H->elem[value]);
	}
	else {
		while(strcmp(key[value], s)!=0){
			value++;
			if(value==N-1) {printf("%s not in the table\n",s);
			break;}
		}
		if(value<N-1) printf("%d\n", H->elem[value]);
	}
	}
int main(){
	FILE *fp;
	struct Record record[N];
	char str[20], check[20];
	str[0] = '\0';
	check[0] = '\0';
	int i=0, tmplen=0, j=0, flag=0,Index=0;
	float load=0.0;
	Hashtable H;
	memset(key, 0, N);
	for(Index=0;Index<N;Index++){
		key[Index] = (char*)malloc(sizeof(char*));
		strcpy(key[Index], "str");
	}
	fp = fopen("names.csv","r");
	if(fp==NULL){
		perror("error opening files");
	}
	else{
		printf("names.csv loaded!\n\t");
		while(fgets(str, 20, fp)!=NULL){
			tmplen = strlen(str);
			str[tmplen-1] = 0x0; 
			flag = 0;
			for(j=0;j<=i;j++){
				if(strcmpi(str, record[j].name)==0){
					record[j].freq+=1;
					flag = 1;
					break;
				}
			}
			if(flag==0){
				record[i].name = (char*)malloc(sizeof(char)*(tmplen-1));
				strcpy(record[i].name, str);
				record[i].freq+=1;
				i++;
		}
		}
	}
	for(j=0;j<i;j++){
		inserthash(&H, record[j].name, record[j].freq, key);
	}
	load = H.count/N;
	printf("Capacity: 99991\n\t");
	printf("Num Terms: %d\n\t", H.count);
	printf("Collisions: %d\n\t", H.collision);
	printf("Load: %4f\n\t", load);
	printf("Enter term to get frequency or type quit to escape\n");
	while(1){
	scanf("%s", &check);
	if(strcmp(check,"quit")==0) {
		printf("end\n");
		return 0;}
	else{
		search(&H, check, key);
	}
}
	fclose(fp);
	return 0;
} 
