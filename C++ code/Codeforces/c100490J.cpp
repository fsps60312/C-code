#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
const int INF=2147483647;
int N,M,ANS[100000];
vector<int>ET[100000];
int GetANS(const int u)
{
	int &ans=ANS[u]=0;
	if(ET[u].empty())return ans=(u%2==0?1:-1);
	sort(ET[u].begin(),ET[u].end());
	for(const int nxt:ET[u])
	{
		if(ANS[nxt]==1)
		{
			if(u%2==0)
			{
				if(ans==-1)ans=-1;
				else if(ans==0)ans=1;
				else if(ans==1)ans=1;
				else assert(0);
			}
			else
			{
				if(ans==-1)return ans=1;
				else if(ans==0)ans=1;
				else if(ans==1)return ans=2;
				else assert(0);
			}
		}
		else if(ANS[nxt]==-1)
		{
			if(u%2==1)
			{
				if(ans==-1)ans=-1;
				else if(ans==0)ans=-1;
				else if(ans==1)ans=1;
				else assert(0);
			}
			else
			{
				if(ans==-1)return ans=-2;
				else if(ans==0)ans=-1;
				else if(ans==1)return ans=-2;
				else assert(0);
			}
		}
		else assert(0);
	}
	return ans;
}
int Solve()
{
	for(int i=0;i<N;i++)
	{
		const int result=GetANS(i);
		if(abs(result)==2)return i;
		else assert(abs(result)==1);
	}
	return -1;
}
int main()
{
	freopen("jackpot.in","r",stdin);
	freopen("jackpot.out","w",stdout);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)ET[i].clear();
		for(int i=0,a,b;i<M;i++)
		{
			scanf("%d%d",&a,&b),a--,b--;
			if(a<b)swap(a,b);
			ET[a].push_back(b);
		}
		const int ans=Solve();
		if(ans==-1)puts("Tie");
		else printf("%s %d\n",ans%2==1?"Alice":"Bob",ans+1);
	}
	return 0;
}
