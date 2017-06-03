#include<cstdio>
#include<algorithm>
using namespace std;
int N;
int S[2000000];
int main()
{
	while(scanf("%d",&N)==1&&N)
	{
		for(int i=0;i<N;i++)scanf("%d",&S[i]);
		sort(S,S+N);
		for(int i=0;i<N;i++)
		{
			if(i)putchar(' ');
			printf("%d",S[i]);
		}
		puts("");
	}
}
