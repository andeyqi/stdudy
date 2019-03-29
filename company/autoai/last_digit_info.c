#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	int data = 0;
	int bit = 0;
	char buff[256] = {0};
	int len = 0;
	
	printf("const char * infos[] = [\\\n");
	printf("\tNULL,\\\n");
	for(data = 1 ;data < 1024;data++)
	{
		for(bit = 0;bit < 10;bit++)
		{
			if(data & (0x01 << bit))
			{	
				if(!len)
					len += sprintf(buff,"%d",bit);
				else
					len += sprintf(&buff[len],"|%d",bit);
			}
		}
		printf("\t\"%s\",\\\n",buff);
		len = 0;
		memset(buff,0,sizeof(buff));
	}
	printf("];\n");
}