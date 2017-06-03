#include<cstdio>
#include<vector>
#include<cmath>
#include<map>
#include<queue>
#include<algorithm>
#include<stack>
using namespace std;
void assert(bool valid){if(valid)return;for(;;)putchar('E');}
FILE *FA,*FB;
int main()
{
	char filename[1000];
	for(int fileidx=0;fileidx<=32;fileidx++)
	{
		sprintf(filename,"D:\\Users\\Burney\\Downloads\\regions\\regions.%03d.sol",fileidx);
		FA=fopen(filename,"r");
		filename[46]='i',filename[47]='n',filename[48]='\0';
		printf("file: %s\n",filename+34);
		FB=fopen(filename+34,"r");
		int ca,cb;
		while(fscanf(FA,"%d",&ca)==1)
		{
			fscanf(FB,"%d",&cb);
			if(ca!=cb)printf("%d %d\n",ca,cb),system("pause");
		}
	}
	return 0;
}
