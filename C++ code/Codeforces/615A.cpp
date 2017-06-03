#include<cstdio>
#include<cassert>
using namespace std;
int N,M;
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		static bool vis[101];
		for(int i=1;i<=M;i++)vis[i]=false;
		for(int i=1,cnt;i<=N;i++)
		{
			scanf("%d",&cnt);
			for(int v;cnt--;)
			{
				scanf("%d",&v);
				vis[v]=true;
			}
		}
		for(int i=2;i<=M;i++)vis[i]&=vis[i-1];
		puts(vis[M]?"YES":"NO");
	}
	return 0;
}
