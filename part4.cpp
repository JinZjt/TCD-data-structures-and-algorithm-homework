#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct character{
	char* num;
	char* Name;
	char* Type1;
	char* Type2;
	char* Total;
	char* HP;
	char* Attack;
	char* Defense;
	char* SpAtk;
	char* SpDef;
	char* Speed;
	char* Generatio;
	char* Legendary;
	char* PokedexEntry;
};

int main()
{
	FILE* fp;
	int length = 0, count = 0, number=0, quotation=0, i=0;
	float average=0.0, sum = 0.0;
	char temp[200], str[200], c;
	temp[0]='\0';
	str[0] = '\0';
	struct character pok[648];
	fp = fopen("pokemon.csv", "r");
	fgets(str,190,fp);
	while((c=fgetc(fp))!=EOF){
		if(c=='"') {++quotation;
		continue;}
		++length;
		if (c==',' && quotation%2!=0 ) temp[length-1] = c;
		if (c!=',') temp[length-1] = c;
		if (c==',' && count==0){
			pok[number].num = (char*)malloc(sizeof(char)*length);
			strcpy(pok[number].num, temp);
			length = 0;
			memset(temp,0,200);
			++count;
		} 
		else if (c==',' && count==1) {
			pok[number].Name = (char*)malloc(sizeof(char)*length);
			strcpy(pok[number].Name, temp);
			length = 0;
			memset(temp,0,200);
			++count;
		}
		else if (c==',' && count==2){
			pok[number].Type1 = (char*)malloc(sizeof(char)*length);
			strcpy(pok[number].Type1, temp);
			length = 0;
			memset(temp,0,200);
			++count;
		}
		else if (c==',' && count==3){
			pok[number].Type2 = (char*)malloc(sizeof(char)*length);
			strcpy(pok[number].Type2, temp);
			length = 0;
			memset(temp,0,200);
			++count;
		}
		else if (c==',' && count==4){
			pok[number].Total = (char*)malloc(sizeof(char)*length);
			strcpy(pok[number].Total, temp);
			length = 0;
			memset(temp,0,200);
			++count;
		}
		else if (c==',' && count==5){
			pok[number].HP = (char*)malloc(sizeof(char)*length);
			strcpy(pok[number].HP, temp);
			length = 0;
			memset(temp,0,200);
			++count;
		}
		else if (c==',' && count==6){
			pok[number].Attack = (char*)malloc(sizeof(char)*length);
			strcpy(pok[number].Attack, temp);
			length = 0;
			memset(temp,0,200);
			++count;
		}
		else if (c==',' && count==7){
			pok[number].Defense = (char*)malloc(sizeof(char)*length);
			strcpy(pok[number].Defense, temp);
			length = 0;
			memset(temp,0,200);
			++count;
		}
		else if (c==',' && count==8){
			pok[number].SpAtk = (char*)malloc(sizeof(char)*length);
			strcpy(pok[number].SpAtk, temp);
			length = 0;
			memset(temp,0,200);
			++count;
		}
		else if (c==',' && count==9){
			pok[number].SpDef = (char*)malloc(sizeof(char)*length);
			strcpy(pok[number].SpDef, temp);
			length = 0;
			memset(temp,0,200);
			++count;
		}
		else if (c==',' && count==10){
			pok[number].Speed = (char*)malloc(sizeof(char)*length);
			strcpy(pok[number].Speed, temp);
			length = 0;
			memset(temp,0,200);
			++count;
		}
		else if (c==',' && count==11){
			pok[number].Generatio = (char*)malloc(sizeof(char)*length);
			strcpy(pok[number].Generatio, temp);
			length = 0;
			memset(temp,0,200);
			++count;
		}
		else if (c==',' && count==12){
			pok[number].Legendary = (char*)malloc(sizeof(char)*length);
			strcpy(pok[number].Legendary, temp);
			length = 0;
			memset(temp,0,200);
			++count;
		}
		else if (c=='\n' && count==13){
			pok[number].PokedexEntry = (char*)malloc(sizeof(char)*length);
			strcpy(pok[number].PokedexEntry, temp);
			length = 0;
			memset(temp,0,200);
			count = 0;
			++number;
		}
	}
	printf("%s\n",pok[647].Name);//The right name
	printf("%s\n",pok[647].PokedexEntry); // quotation mark
	for(i = 0; i<648;i++){
		sum+=atol(pok[i].Attack);
	}
	average = (float)(sum/648); //calculate the average attack strength 
	printf("Attack average strength: %f\n", average); 
	fclose(fp);
	return 0;
}
