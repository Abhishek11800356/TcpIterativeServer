#include<stdio.h>
#include<unistd.h>
#include<string.h>
 void main()
{
	char s[10];
	char s2[10];

	strcpy(s,"quit");
	printf("%s\n",s);
       int x = strcmp(s,"quit");
       printf("%d\n",x);
}
		
