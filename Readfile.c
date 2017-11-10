#include <stdio.h>

void printLine(unsigned char* line);

int main(void)
{
	
	FILE* fFile = fopen("test.txt", "r");
	unsigned char buffer [256];
	char c;
	
	if(fFile != NULL)
	{
		while(!feof(fFile))
		{
			int i = 0;
			while(c != '\n')
			{
				c = getc(fFile);
				buffer[i++] = c;
			}
			printf("\n%s\n", buffer);
		}
		
	}
}

void printLine(unsigned char* line)
{
	static int count = 1;
	printf("\nLine %d: %s\n",count, line);
	count++;
}
