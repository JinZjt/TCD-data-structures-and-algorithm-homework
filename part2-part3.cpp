#include<stdio.h>
#include<stdlib.h>
int main()
{
    /* code */
    FILE *pfile;
    int length = 0, i=0, j=0,lineflag = 0, quotoflag = 0, k=0, count = 0;
    char c, ch;
    char* Buffer;
    pfile = fopen("pokemon.csv", "r"); /*read csv*/
    if (pfile == NULL)
        perror("error opening file");
    else{
    	while((ch=fgetc(pfile)!=EOF)) {
			++length;}
		}
	Buffer = (char*)malloc(length+1);/*allocate memory for Buffer*/
	fseek(pfile,0L,SEEK_SET); /*return to the beginning of CSV*/
    while((c=fgetc(pfile))!=EOF) {
	Buffer[k++] = c;}
	for(i=0; i<length; i++){
		if (Buffer[i]=='\n') ++count;
	}
	printf("%d\n\n",count);
	/*output part2 & part3*/
    for(j=0; j<length-1; j=j+1){
    	if (Buffer[j]=='\n' && lineflag==0) {
		++lineflag;
		continue;}
    	if (Buffer[j]=='"') {
		++quotoflag;
		continue;}
    	if (lineflag>=1){
    		//if(Buffer[j]=='\n') printf("\n");
    		if(Buffer[j]==',' && Buffer[j+1]==',') continue;
    		if(Buffer[j]==',' && quotoflag%2==0) printf("\n");
        	else printf("%c", Buffer[j]);
        }
    }
    fclose(pfile);
    free(Buffer);
    return 0;
}

