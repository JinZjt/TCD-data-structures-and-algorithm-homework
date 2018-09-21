#include<stdio.h>
int main(){
	char name[10];
	int age=0;
	name[0] = '\0';
	scanf("%s", name);
	scanf("%d", &age);
	printf("Name >> %s\n", name);
	printf("Age >> %d\n", age);
	printf("Hello %s (%d)\n", name,age);
	return 0;
}
