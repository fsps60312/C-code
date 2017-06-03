#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
int N,M;
int NXT[4000004];
bool VIS[4000004];
bool Walk(const int source,int &transmit)
{
	assert(!VIS[source]&&!(source&1));
	int u=source;VIS[u]=true;
	for(;;)
	{
		if(NXT[u]==u)NXT[u]=((u>>1)+1)<<1;
		if(VIS[NXT[u]]){assert(NXT[u]==source);return false;}
		VIS[NXT[u]]=true;
		if(NXT[u]&1)transmit++;
		u=NXT[u];
		if(u==2000001*2)return true;
	}
}
int Solve()
{
	int transmit=0;
	assert(Walk(0,transmit));
	vector<int>tmp;
	for(int i=1;i<=2000000;i++)
	{
		if(VIS[i*2])continue;
		int t=0;
		assert(!Walk(i*2,t));
		assert(t>=1);
		tmp.push_back(t+2);
	}
	sort(tmp.begin(),tmp.end(),greater<int>());
	for(int i=0;i<tmp.size()&&M;i++)
	{
		if(M%2==0&&i+1==tmp.size()&&tmp[i]<4)break;
		M--,transmit+=tmp[i];
	}
	transmit+=M/2*4;
	if(M&1)transmit++;
	return transmit;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<2000002*2;i++)NXT[i]=i,VIS[i]=false;
		for(int i=0,a,b;i<N;i++)
		{
			scanf("%d%d",&a,&b);
			NXT[a*2]=b*2+1;
			NXT[b*2]=a*2+1;
		}
		printf("%d\n",Solve());
		break;
	}
	return 0;
}
