#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define BUCKETCOUNT 99991

struct character{
	char* PersonID;
	char* Deposition;
	char* Surname;
	char* Forename;
	char* Age;
	char* PersonType;
	char* Gender;
	char* Nationality;
	char* Religion;
	char* Occupation;
};
struct character pok[60170];
typedef struct Node{
	struct character info;
	struct Node *next;
}Node, *linkedlist;
int main(){
	FILE* fp;
	int length = 0, count = 0, number=0, quotation=0, i=0;
	float average=0.0, sum = 0.0;
	char temp[200], str[200], c;
	temp[0]='\0';
	str[0] = '\0';
	fp = fopen("people.csv", "r");
	fgets(str,190,fp);
	while((c=fgetc(fp))!=EOF){
		if(c=='"') {++quotation;
		continue;}
		++length;
		if (c==',' && quotation%2!=0 ) temp[length-1] = c;
		if (c!=','&& c!='\n') temp[length-1] = c;
		if (c==',' && count==0){
			pok[number].PersonID = (char*)malloc(sizeof(char)*length);
			strcpy(pok[number].PersonID, temp);
			length = 0;
			memset(temp,0,200);
			++count;
		} 
		else if (c==',' && count==1) {
			pok[number].Deposition = (char*)malloc(sizeof(char)*length);
			strcpy(pok[number].Deposition, temp);
			length = 0;
			memset(temp,0,200);
			++count;
		}
		else if (c==',' && count==2){
			pok[number].Surname = (char*)malloc(sizeof(char)*length);
			strcpy(pok[number].Surname, temp);
			length = 0;
			memset(temp,0,200);
			++count;
		}
		else if (c==',' && count==3){
			pok[number].Forename = (char*)malloc(sizeof(char)*length);
			strcpy(pok[number].Forename, temp);
			length = 0;
			memset(temp,0,200);
			++count;
		}
		else if (c==',' && count==4){
			pok[number].Age = (char*)malloc(sizeof(char)*length);
			strcpy(pok[number].Age, temp);
			length = 0;
			memset(temp,0,200);
			++count;
		}
		else if (c==',' && count==5){
			pok[number].PersonType = (char*)malloc(sizeof(char)*length);
			strcpy(pok[number].PersonType, temp);
			length = 0;
			memset(temp,0,200);
			++count;
		}
		else if (c==',' && count==6){
			pok[number].Gender = (char*)malloc(sizeof(char)*length);
			strcpy(pok[number].Gender, temp);
			length = 0;
			memset(temp,0,200);
			++count;
		}
		else if (c==',' && count==7){
			pok[number].Nationality = (char*)malloc(sizeof(char)*length);
			strcpy(pok[number].Nationality, temp);
			length = 0;
			memset(temp,0,200);
			++count;
		}
		else if (c==',' && count==8){
			pok[number].Religion = (char*)malloc(sizeof(char)*length);
			strcpy(pok[number].Religion, temp);
			length = 0;
			memset(temp,0,200);
			++count;
		}
		else if (c=='\n' && count==9){
			pok[number].Occupation = (char*)malloc(sizeof(char)*length);
			strcpy(pok[number].Occupation, temp);
			length = 0;
			memset(temp,0,200);
			count = 0;
			++number;
		}
}
	
	return 0;
}

















 
