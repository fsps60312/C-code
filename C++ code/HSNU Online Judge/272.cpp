#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
const int INF=2147483647;
#define scanf(x,...) assert(scanf(__VA_ARGS__)==x)
int R[24],N,CNT[24],USE[24],COVER[24];
int Solve()
{
	int ans=0;
	bool changed=true;
	while(changed)
	{
		changed=false;
		for(int i=0;i<24;i++)
		{
			int mx=-INF;
			for(int j=0;j<8;j++)
			{
				const int t=(i+j)%24;
				mx=max(mx,R[t]-COVER[t]);
			}
			if(mx<0&&USE[i])
			{
				const int dis=min(USE[i],-mx);
				ans-=dis,USE[i]-=dis;
				for(int j=0;j<8;j++)COVER[(i+j)%24]-=dis;
				changed=true;
			}
			else if(mx>0&&USE[i]<CNT[i])
			{
				const int dis=min(R[i]-USE[i],mx);
				ans+=dis,USE[i]+=dis;
				for(int j=0;j<8;j++)COVER[(i+j)%24]+=dis;
				changed=true;
			}
		}
	}
	for(int i=0;i<24;i++)if(COVER[i]<R[i])return -1;
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	for(int i=0;i<24;i++)CNT[i]=USE[i]=COVER[i]=0,scanf(1,"%d",&R[i]);
	scanf(1,"%d",&N);
	for(int i=0,v;i<N;i++)scanf(1,"%d",&v),CNT[v]++;
	const int ans=Solve();
	if(ans==-1)puts("No Solution");
	else printf("%d\n",ans);
}
