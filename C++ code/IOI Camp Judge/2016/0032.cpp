#include<cstdio>
#include<cassert>
#include<map>
using namespace std;
const int INF=1000000000;
int N,K;
int PRE[100001];
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d%d",&N,&K);
		for(int i=1;i<=100000;i++)PRE[i]=-INF;
		bool ans=true;
		for(int i=0,v;i<N;i++)
		{
			scanf("%d",&v);
			if(i-PRE[v]-1<K)ans=false;
			PRE[v]=i;
		}
		puts(ans?"Yes":"No");
	}
	return 0;
}
