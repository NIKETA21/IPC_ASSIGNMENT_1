#include<stdio.h>
#include<unistd.h>
#include<string.h>

int main()
{
	int p[2];
	pipe(p);
	printf("Read end of pipe = %d \t write end of pipe = %d\n",p[0],p[1]);
	if(fork())
	{
		int n[20];
		printf("In parent enter data...\n");
		scanf("%d",s);
		write(p[1],n,strlen(n)+1);
	}
	else
	{
		int buf[20];
		printf("In child...\n");
		read(p[0],buf,sizeof(buf));
		printf("child pro printing...data of the parent process...%d\n",buf);
	}
	return 0;
	
}
