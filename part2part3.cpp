#include<stdio.h>
#include<stdlib.h>
int output(char* buffer, int len){
	int lineflag = 0, quotoflag = 0, j = 0;
	for(j=0; j<len-1; j=j+1){
    	if (buffer[j]=='\n' && lineflag==0) {
		++lineflag;
		continue;}
    	if (buffer[j]=='"') {
		++quotoflag;
		continue;}
    	if (lineflag>=1){
    		if(buffer[j]==',' && buffer[j+1]==',') continue; //Because when reading CSV, Buffer gets redundant ',', use this way to avoid print too many '\n'.
    		if(buffer[j]==',' && quotoflag%2==0) printf("\n");
        	else printf("%c", buffer[j]);
        }
    }
    return 0;
}
int main()
{
    /* code */
    FILE *pfile;
    int length = 0, k=0;
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
	output(Buffer, length);
	return 0;
}
