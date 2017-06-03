#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
const int INF=2147483647;
void getmin(int &a,const int b){if(b<a)a=b;}
#define scanf(x,...) assert(scanf(__VA_ARGS__)==x)
int REQUIRE[24],N,WORKER[24],USE[24],COVER[24];
void Add(const int t,const int v)
{
	USE[t]+=v;
	assert(USE[t]>=0&&USE[t]<=WORKER[t]);
	for(int i=0;i<8;i++)COVER[(t+i)%24]+=v;
}
bool Fire(const int time,int &ans)
{
	if(USE[time]==0)return false;
	Add(time,-1),ans--;
	for(int i=time+7;i>=time;i--)if(COVER[i%24]<REQUIRE[i%24])
	{
		for(int j=max(0,i-7);j<time;j++)
		{
			if(USE[j%24]<WORKER[j%24]){Add(j%24,1),ans++;return true;}
		}
		Add(time,1),ans++;
		return false;
	}
	return true;
}
int Solve()
{
	int ans=N;
	for(int i=0;i<24;i++)Add(i,WORKER[i]);
	for(int i=0;i<24;i++)if(COVER[i]<REQUIRE[i])return INF;
	for(int i=0;i<24;i++)while(Fire(i,ans));
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	for(int i=0;i<24;i++)WORKER[i]=USE[i]=COVER[i]=0,scanf(1,"%d",&REQUIRE[i]);
	scanf(1,"%d",&N);
	for(int i=0,v;i<N;i++)scanf(1,"%d",&v),WORKER[v]++;
	const int ans=Solve();
	if(ans==INF)puts("No Solution");
	else printf("%d\n",ans);
}
