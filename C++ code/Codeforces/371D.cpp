#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
int N,M,REMAIN[200000],VOLUMN[200000],DJ[200001];
int Find(const int a){return DJ[a]==a?a:(DJ[a]=Find(DJ[a]));}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)scanf("%d",&VOLUMN[i]),REMAIN[i]=VOLUMN[i];
		for(int i=0;i<=N;i++)DJ[i]=i;
		scanf("%d",&M);
		for(int i=0,type;i<M;i++)
		{
			scanf("%d",&type);
			if(type==1)
			{
				int p,x;scanf("%d%d",&p,&x),p--;
				int cur=Find(p);
				while(cur<N&&x)
				{
					const int v=min(x,REMAIN[cur]);
					x-=v,REMAIN[cur]-=v;
					if(!REMAIN[cur])DJ[cur]=cur+1;
					cur=Find(cur);
				}
			}
			else if(type==2)
			{
				int k;scanf("%d",&k),k--;
				printf("%d\n",VOLUMN[k]-REMAIN[k]);
			}
			else assert(0);
		}
	}
	return 0;
}
