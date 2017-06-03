#include<cstdio>
#include<cstdlib>
#define LL Big
LL WAYS[100][100];
int main()
{
	WAYS[0][0]=1;
	for(int rc=1;rc<100;rc++)WAYS[0][rc]=WAYS[rc][0]=1;
	for(int r=1;r<100;r++)
	{
		for(int c=1;c<100;c++)
		{
			WAYS[r][c]=WAYS[r-1][c]+WAYS[r][c-1];
		}
	}
	for(int i=0;i<100;i++)
	{
		printf("%d: ",i);
		WAYS[i][i].print();
		printf("\n");
	}
	return 0;
}
