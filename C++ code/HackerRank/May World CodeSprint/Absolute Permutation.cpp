#include<cstdio>
#include<cassert>
using namespace std;
int N,K,ANS[100001];
bool VIS[100001];
bool Solve()
{
	for(int i=1;i<=N;i++)VIS[i]=false;
	for(int i=1;i<=N;i++)
	{
		if(i-K>=1&&!VIS[i-K])VIS[i-K]=true,ANS[i]=i-K;
		else if(i+K<=N&&!VIS[i+K])VIS[i+K]=true,ANS[i]=i+K;
		else return false;
	}
	return true;
}
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d%d",&N,&K);
		if(!Solve())puts("-1");
		else
		{
			for(int i=1;i<=N;i++)
			{
				if(i>1)putchar(' ');
				printf("%d",ANS[i]);
			}
			puts("");
		}
	}
	return 0;
}
