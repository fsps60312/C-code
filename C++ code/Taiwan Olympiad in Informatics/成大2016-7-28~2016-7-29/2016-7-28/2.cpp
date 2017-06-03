#include<cstdio>
#include<cassert>
#include<utility>
#include<vector>
using namespace std;
template<class T>inline bool getmax(T&a,const T&b){return a<b?(a=b,true):false;}
int N,LIMIT,P[500],L[501],SUM[501];
void ReIndex()
{
	static int pre_p[500];
	for(int i=0;i<N;i++)scanf("%d",&pre_p[i]);
	static vector<pair<int,int> >et[500];
	for(int i=0;i<N;i++)et[i].clear();
	for(int i=0,a,b,c;i<N-1;i++)
	{
		scanf("%d%d%d",&a,&b,&c),--a,--b;
		et[a].push_back(make_pair(b,c)),et[b].push_back(make_pair(a,c));
	}
	for(int i=0;i<N;i++)if((int)et[i].size()<=1)
	{
		P[0]=pre_p[i];
		int p=1;
		for(int cur=i,pre=-1;;p++)
		{
			bool vis=false;
//			puts("a");
			int nxtu=0;
			for(const auto &nxt:et[cur])if(nxt.first!=pre)
			{
				L[p-1]=nxt.second;
				P[p]=pre_p[nxt.first];
				nxtu=nxt.first;
//				printf("(%d,%d)",cur+1,nxt.first+1);
				assert(!vis);
				vis=true;
			}
			pre=cur,cur=nxtu;
			if(p==N-1)break;
			assert(vis);
		}
		break;
	}
}
int GetSum(const int l,const int r){return SUM[r+1]-SUM[l];}
pair<int,int>DP[501];
pair<int,int>GetDP(const int u)
{
	auto &dp=DP[u];
	if(dp.first!=-1)return dp;
	dp.first=-2;
	for(int i=u;i<N;i++)if(GetSum(u,i)>=LIMIT)
	{
		auto nxt=GetDP(i+1);
		if(nxt.first==-2)continue;
		nxt.second-=L[i];
		nxt.first++;
		getmax(dp,nxt);
	}
	return dp;
}
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d%d",&N,&LIMIT);
		assert(N<=500);
		ReIndex();
		for(int i=0;i<N;i++)DP[i].first=-1,SUM[i+1]=SUM[i]+P[i];
		DP[N]=make_pair(0,0),L[N]=0;
		const auto &p=GetDP(0);
		if(p.first==-2)puts("-1");
		else printf("%d %d\n",p.first,-p.second);
	}
	return 0;
}
